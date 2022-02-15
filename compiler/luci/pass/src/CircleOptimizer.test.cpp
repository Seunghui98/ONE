/*
 * Copyright (c) 2021 Samsung Electronics Co., Ltd. All Rights Reserved
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

#include "luci/CircleOptimizer.h"

#include <gtest/gtest.h>

using namespace luci;
using Algorithms = luci::CircleOptimizer::Options::Algorithm;
using AlgorithmParameters = luci::CircleOptimizer::Options::AlgorithmParameters;

TEST(CircleOptimizerTest, optimize_algorithms)
{
  loco::Graph g;
  luci::CircleOptimizer o;

  auto options = o.options();

  // NOTE these are added to cover the test
  // TODO add more if needed
  options->enable(Algorithms::FoldAddV2);
  options->enable(Algorithms::FoldCast);
  options->enable(Algorithms::FoldDepthwiseConv2D);
  options->enable(Algorithms::FoldDequantize);
  options->enable(Algorithms::FoldSparseToDense);
  options->enable(Algorithms::FusePreActivationBatchNorm);
  options->enable(Algorithms::MakeBatchNormGammaPositive);
  options->enable(Algorithms::ShuffleWeightTo16x1Float32);
  options->enable(Algorithms::RemoveUnnecessaryReshape);
  options->enable(Algorithms::RemoveUnnecessarySlice);
  options->enable(Algorithms::RemoveUnnecessarySplit);
  options->enable(Algorithms::ReplaceMulAddWithDepthwiseConv);
  options->enable(Algorithms::SubstituteStridedSliceToReshape);
  options->enable(Algorithms::SubstituteTransposeToReshape);
  options->enable(Algorithms::ConvertNCHWToNHWC);
  options->enable(Algorithms::ExpandBroadcastConst);

  o.optimize(&g);

  SUCCEED();
}

TEST(CircleOptimizerTest, sparsify_simple)
{
  loco::Graph g;
  luci::CircleOptimizer o;

  auto options = o.options();

  options->enable(Algorithms::SparsifyTensorPass);
  options->param(AlgorithmParameters::Sparsify_tensor_name, "dummy");
  options->param(AlgorithmParameters::Sparsify_traversal_order, "dummy");
  options->param(AlgorithmParameters::Sparsify_format, "ds");
  options->param(AlgorithmParameters::Sparsify_block_size, "1,1");
  options->param(AlgorithmParameters::Sparsify_block_map, "1,1");

  o.sparsify(&g);

  SUCCEED();
}
