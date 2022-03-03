/*
 * Copyright (c) 2022 Samsung Electronics Co., Ltd. All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "QuantizeActivation.h"
#include "QuantizationUtils.h"

#include <luci/Service/Nodes/CircleConst.h>
#include <luci/Log.h>

#include <algorithm>
#include <cmath>

using namespace luci;

namespace
{

void quant_const(CircleConst *node, loco::DataType quant_type)
{
  assert(node->dtype() == loco::DataType::FLOAT32);

  float min = std::numeric_limits<float>::max();
  float max = std::numeric_limits<float>::lowest();
  for (uint32_t i = 0; i < node->size<loco::DataType::FLOAT32>(); i++)
  {
    auto data = node->at<loco::DataType::FLOAT32>(i);
    min = std::min(data, min);
    max = std::max(data, max);
  }

  float scaling_factor{0.0};
  int64_t zp{0};
  float nudged_min{0.0};
  float nudged_max{0.0};

  switch (quant_type)
  {
    case loco::DataType::U8:
      asymmetric_wquant_with_minmax_per_layer(node, min, max, scaling_factor, zp, nudged_min,
                                              nudged_max);
      break;
    case loco::DataType::S16:
      symmetric_wquant_with_minmax_per_layer(node, min, max, scaling_factor, zp, nudged_min,
                                             nudged_max);
      break;
    default:
      throw std::runtime_error("Unsupported data type");
  }

  auto quantparam = std::make_unique<CircleQuantParam>();
  quantparam->scale.push_back(scaling_factor);
  quantparam->zerop.push_back(zp);
  node->quantparam(std::move(quantparam));
}

void set_act_qparam(luci::CircleNode *node, float scale, int64_t zp)
{
  assert(node);               // FIX_CALLER_UNLESS
  assert(node->quantparam()); // FIX_CALLER_UNLESS

  auto qparam = node->quantparam();
  assert(qparam->scale.size() == 1); // FIX_CALLER_UNLESS
  assert(qparam->zerop.size() == 1); // FIX_CALLER_UNLESS
  qparam->scale[0] = scale;
  qparam->zerop[0] = zp;
}

// For nodes with integer output, we use integer scale
void set_int_scale(luci::CircleNode *node)
{
  assert(node); // FIX_CALLER_UNLESS

  auto qparam = node->quantparam();
  assert(qparam);                    // FIX_CALLER_UNLESS
  assert(qparam->scale.size() == 1); // FIX_CALLER_UNLESS

  auto fp_scale = qparam->scale[0];
  qparam->scale[0] = fp_scale < 1 ? 1.0f : std::round(fp_scale);
}

bool has_min_max(const CircleNode *node)
{
  return node->quantparam() && !node->quantparam()->min.empty() && !node->quantparam()->max.empty();
}

// Check if the node is the bias of Conv2D, DepthwiseConv2D, FullyConnected, or TransposeConv layer
// Returns a list of <input, weights, output> vectors for the above operators.
// Note that it returns a 'list' because bias can be used by multiple operators.
std::vector<std::vector<loco::Node *>> get_input_weight_output_of_bias(CircleNode *node)
{
  std::vector<std::vector<loco::Node *>> result;
  auto circle_const = dynamic_cast<CircleConst *>(node);
  if (circle_const == nullptr)
    return result;

  auto succs = loco::succs(node);

  for (auto out : succs)
  {
    auto conv = dynamic_cast<CircleConv2D *>(out);
    if (conv != nullptr && conv->bias() == circle_const)
    {
      assert(conv->input() != nullptr);
      assert(conv->filter() != nullptr);
      result.push_back({conv->input(), conv->filter(), conv});
      continue;
    }
    auto dw_conv = dynamic_cast<CircleDepthwiseConv2D *>(out);
    if (dw_conv != nullptr && dw_conv->bias() == circle_const)
    {
      assert(dw_conv->input() != nullptr);
      assert(dw_conv->filter() != nullptr);
      result.push_back({dw_conv->input(), dw_conv->filter(), dw_conv});
      continue;
    }
    auto fc = dynamic_cast<CircleFullyConnected *>(out);
    if (fc != nullptr && fc->bias() == circle_const)
    {
      assert(fc->input() != nullptr);
      assert(fc->weights() != nullptr);
      result.push_back({fc->input(), fc->weights(), fc});
      continue;
    }
    auto tconv = dynamic_cast<CircleTransposeConv *>(out);
    if (tconv != nullptr && tconv->bias() == circle_const)
    {
      assert(tconv->outBackprop() != nullptr);
      assert(tconv->filter() != nullptr);
      result.push_back({tconv->outBackprop(), tconv->filter(), tconv});
      continue;
    }
  }
  return result;
}

} // namespace

// QuantizeActivation
namespace luci
{

void QuantizeActivation::visit(luci::CircleNode *node)
{
  LOGGER(l);
  INFO(l) << "QuantizeActivation visit node: " << node->name() << std::endl;

  // Check if this is already quantized
  if (is_quantized(node))
    return;

  // Check if this is bias (bias is quantized later)
  auto iwo = get_input_weight_output_of_bias(node);
  if (iwo.size() > 0)
    return;

  // Check if this is bool type (bool type is not quantized)
  if (node->dtype() == loco::DataType::BOOL)
    return;

  // Check if this is activation
  // We assume min/max are recorded only for activations
  if (has_min_max(node) && !is_weights(node))
  {
    // Quantize using recorded min/max
    auto quantparam = node->quantparam();
    assert(quantparam);
    assert(quantparam->min.size() == 1); // only support layer-wise quant
    assert(quantparam->max.size() == 1); // only support layer-wise quant
    auto min = quantparam->min[0];
    auto max = quantparam->max[0];

    float scaling_factor{0};
    int64_t zp{0};
    float nudged_min{0};
    float nudged_max{0};

    if (output_type == loco::DataType::U8)
    {
      compute_asym_scale_zp(min, max, scaling_factor, zp, nudged_min, nudged_max);
      node->dtype(loco::DataType::U8);
    }
    else
    {
      compute_sym_scale_zp(min, max, scaling_factor, zp, nudged_min, nudged_max);
      node->dtype(loco::DataType::S16);
    }

    node->quantparam()->scale.push_back(scaling_factor);
    node->quantparam()->zerop.push_back(zp);
  }
  // Fix special attributes
  if (node->opcode() == luci::CircleOpcode::CAST)
  {
    auto *cast = loco::must_cast<luci::CircleCast *>(node);
    auto *cast_input = loco::must_cast<luci::CircleNode *>(cast->x());

    // make sure that cast_input is already quantized
    assert(cast_input->dtype() != loco::DataType::FLOAT32);
    cast->in_data_type(cast_input->dtype());
    cast->out_data_type(cast->dtype());
  }
}

} // namespace luci

// QuantizeSpecialActivation
namespace luci
{

void QuantizeSpecialActivation::visit(luci::CircleNode *node)
{
  // Nodes fused with activation functions which need special quantization
  auto fused_act_node = dynamic_cast<CircleNodeMixin<CircleNodeTrait::FusedActFunc> *>(node);
  if (fused_act_node != nullptr && fused_act_node->fusedActivationFunction() == FusedActFunc::TANH)
  {
    if (output_type == loco::DataType::U8)
      set_act_qparam(node, 2.0f / 256.0f, 128);
    else
    {
      assert(output_type == loco::DataType::S16);
      set_act_qparam(node, 1.0f / 32768.0f, 0);
    }
  }
}

void QuantizeSpecialActivation::visit(luci::CircleLogistic *node)
{
  if (output_type == loco::DataType::U8)
    set_act_qparam(node, 1.0f / 256.0f, 0);
  else
  {
    assert(output_type == loco::DataType::S16);
    set_act_qparam(node, 1.0f / 32768.0f, 0);
  }
}

void QuantizeSpecialActivation::visit(luci::CircleTanh *node)
{
  if (output_type == loco::DataType::U8)
    set_act_qparam(node, 2.0f / 256.0f, 128);
  else
  {
    assert(output_type == loco::DataType::S16);
    set_act_qparam(node, 1.0f / 32768.0f, 0);
  }
}

void QuantizeSpecialActivation::visit(luci::CircleSoftmax *node)
{
  if (output_type == loco::DataType::U8)
    set_act_qparam(node, 1.0f / 255.0f, 0);
  else
  {
    assert(output_type == loco::DataType::S16);
    set_act_qparam(node, 1.0f / 32767.0f, 0);
  }
}

void QuantizeSpecialActivation::visit(luci::CircleFloor *node) { set_int_scale(node); }

void QuantizeSpecialActivation::visit(luci::CircleFloorDiv *node) { set_int_scale(node); }

void QuantizeSpecialActivation::visit(luci::CircleFloorMod *node) { set_int_scale(node); }

void QuantizeSpecialActivation::visit(luci::CircleCeil *node) { set_int_scale(node); }

} // namespace luci

// QuantizeConstInputActivation
namespace luci
{

// Default behavior (NYI)
void QuantizeConstInputActivation::visit(luci::CircleNode *node)
{
  for (uint32_t i = 0; i < node->arity(); i++)
  {
    auto input_node = node->arg(i);
    auto const_node = dynamic_cast<luci::CircleConst *>(input_node);
    if (const_node != nullptr)
      throw std::runtime_error("Unsupported Op for const inputs");
  }
}

// INPUT_NAME is the only activation of NODE
#define QUANTIZE_SINGLE_CONST_INPUT(NODE, INPUT_NAME)           \
  void QuantizeConstInputActivation::visit(NODE *node)          \
  {                                                             \
    auto input = node->INPUT_NAME();                            \
    auto const_node = dynamic_cast<luci::CircleConst *>(input); \
    if (const_node && !is_quantized(const_node))                \
    {                                                           \
      auto new_const = luci::clone(const_node);                 \
      quant_const(new_const, _output_type);                     \
      node->INPUT_NAME(new_const);                              \
    }                                                           \
  }

// INPUT_NAME1 and INPUT_NAME2 are the only activations of NODE
#define QUANTIZE_TWO_CONST_INPUTS(NODE, INPUT_NAME1, INPUT_NAME2) \
  void QuantizeConstInputActivation::visit(NODE *node)            \
  {                                                               \
    auto input1 = node->INPUT_NAME1();                            \
    auto const_node1 = dynamic_cast<luci::CircleConst *>(input1); \
    if (const_node1 && !is_quantized(const_node1))                \
    {                                                             \
      auto new_const1 = luci::clone(const_node1);                 \
      quant_const(new_const1, _output_type);                      \
      node->INPUT_NAME1(new_const1);                              \
    }                                                             \
    auto input2 = node->INPUT_NAME2();                            \
    auto const_node2 = dynamic_cast<luci::CircleConst *>(input2); \
    if (const_node2 && !is_quantized(const_node2))                \
    {                                                             \
      auto new_const2 = luci::clone(const_node2);                 \
      quant_const(new_const2, _output_type);                      \
      node->INPUT_NAME2(new_const2);                              \
    }                                                             \
  }

// Ops that receive a single activation as an input
QUANTIZE_SINGLE_CONST_INPUT(luci::CircleArgMax, input)
QUANTIZE_SINGLE_CONST_INPUT(luci::CircleArgMin, input)
QUANTIZE_SINGLE_CONST_INPUT(luci::CircleBatchToSpaceND, input)
QUANTIZE_SINGLE_CONST_INPUT(luci::CircleDepthToSpace, input)
QUANTIZE_SINGLE_CONST_INPUT(luci::CircleElu, features)
QUANTIZE_SINGLE_CONST_INPUT(luci::CircleExp, x)
QUANTIZE_SINGLE_CONST_INPUT(luci::CircleFloor, x)
QUANTIZE_SINGLE_CONST_INPUT(luci::CircleGather, params)
QUANTIZE_SINGLE_CONST_INPUT(luci::CircleLocalResponseNormalization, input)
QUANTIZE_SINGLE_CONST_INPUT(luci::CircleLogistic, x)
QUANTIZE_SINGLE_CONST_INPUT(luci::CircleMean, input)
QUANTIZE_SINGLE_CONST_INPUT(luci::CircleMirrorPad, input)
QUANTIZE_SINGLE_CONST_INPUT(luci::CirclePad, input)
QUANTIZE_SINGLE_CONST_INPUT(luci::CircleReduceAny, input)
QUANTIZE_SINGLE_CONST_INPUT(luci::CircleReduceProd, input)
QUANTIZE_SINGLE_CONST_INPUT(luci::CircleReduceMax, input)
QUANTIZE_SINGLE_CONST_INPUT(luci::CircleReduceMin, input)
QUANTIZE_SINGLE_CONST_INPUT(luci::CircleReshape, tensor)
QUANTIZE_SINGLE_CONST_INPUT(luci::CircleResizeBilinear, input)
QUANTIZE_SINGLE_CONST_INPUT(luci::CircleResizeNearestNeighbor, input)
QUANTIZE_SINGLE_CONST_INPUT(luci::CircleReverseSequence, input)
QUANTIZE_SINGLE_CONST_INPUT(luci::CircleRsqrt, x)
QUANTIZE_SINGLE_CONST_INPUT(luci::CircleSlice, input)
QUANTIZE_SINGLE_CONST_INPUT(luci::CircleSoftmax, logits)
QUANTIZE_SINGLE_CONST_INPUT(luci::CircleSpaceToBatchND, input)
QUANTIZE_SINGLE_CONST_INPUT(luci::CircleSpaceToDepth, input)
QUANTIZE_SINGLE_CONST_INPUT(luci::CircleSplit, input)
QUANTIZE_SINGLE_CONST_INPUT(luci::CircleSplitV, input)
QUANTIZE_SINGLE_CONST_INPUT(luci::CircleSqrt, x)
QUANTIZE_SINGLE_CONST_INPUT(luci::CircleStridedSlice, input)
QUANTIZE_SINGLE_CONST_INPUT(luci::CircleSum, input)
QUANTIZE_SINGLE_CONST_INPUT(luci::CircleTanh, x)
QUANTIZE_SINGLE_CONST_INPUT(luci::CircleTile, input)
QUANTIZE_SINGLE_CONST_INPUT(luci::CircleTopKV2, input)
QUANTIZE_SINGLE_CONST_INPUT(luci::CircleTranspose, a)
QUANTIZE_SINGLE_CONST_INPUT(luci::CircleUnpack, value)

// Ops that receive two activations as inputs
QUANTIZE_TWO_CONST_INPUTS(luci::CircleAdd, x, y)
QUANTIZE_TWO_CONST_INPUTS(luci::CircleBatchMatMul, x, y)
QUANTIZE_TWO_CONST_INPUTS(luci::CircleDiv, x, y)
QUANTIZE_TWO_CONST_INPUTS(luci::CircleEqual, x, y)
QUANTIZE_TWO_CONST_INPUTS(luci::CircleFloorDiv, x, y)
QUANTIZE_TWO_CONST_INPUTS(luci::CircleGreater, x, y)
QUANTIZE_TWO_CONST_INPUTS(luci::CircleGreaterEqual, x, y)
QUANTIZE_TWO_CONST_INPUTS(luci::CircleLess, x, y)
QUANTIZE_TWO_CONST_INPUTS(luci::CircleLessEqual, x, y)
QUANTIZE_TWO_CONST_INPUTS(luci::CircleMaximum, x, y)
QUANTIZE_TWO_CONST_INPUTS(luci::CircleMinimum, x, y)
QUANTIZE_TWO_CONST_INPUTS(luci::CircleMul, x, y)
QUANTIZE_TWO_CONST_INPUTS(luci::CircleNotEqual, x, y)
QUANTIZE_TWO_CONST_INPUTS(luci::CirclePow, x, y)
QUANTIZE_TWO_CONST_INPUTS(luci::CircleSub, x, y)

// AddN has arbitrary number of inputs
void QuantizeConstInputActivation::visit(luci::CircleAddN *node)
{
  auto arity = node->arity();
  for (uint32_t i = 0; i < arity; i++)
  {
    auto input_node = node->inputs(i);
    auto const_node = dynamic_cast<luci::CircleConst *>(input_node);
    if (const_node && !is_quantized(const_node))
    {
      auto new_const = luci::clone(const_node);
      quant_const(new_const, _output_type);
      node->inputs(i, new_const);
    }
  }
}

#undef QUANTIZE_SINGLE_CONST_INPUT
#undef QUANTIZE_TWO_CONST_INPUTS

} // namespace luci
