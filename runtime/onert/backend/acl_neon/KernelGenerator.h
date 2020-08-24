/*
 * Copyright (c) 2019 Samsung Electronics Co., Ltd. All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __ONERT_BACKEND_ACL_NEON_KERNEL_GENERATOR_H__
#define __ONERT_BACKEND_ACL_NEON_KERNEL_GENERATOR_H__

#include <backend/IKernelGenerator.h>

#include "ir/Operands.h"
#include "TensorBuilder.h"
#include "AclTensorRegistry.h"
#include "TensorManager.h"

namespace onert
{
namespace backend
{
namespace acl_neon
{

class KernelGenerator : public IKernelGenerator
{
public:
  KernelGenerator(const ir::Operands &operands_ctx, const ir::Operations &operations_ctx,
                  const std::shared_ptr<TensorBuilder> &tensor_builder,
                  const std::shared_ptr<acl_common::AclTensorRegistry<TensorManager>> &_tensor_reg);

  void visit(const ir::OpSequence &) override;
  void visit(const ir::operation::Abs &) override;
  void visit(const ir::operation::ArgMax &) override;
  void visit(const ir::operation::BatchToSpaceND &) override;
  void visit(const ir::operation::BinaryArithmetic &) override;
  void visit(const ir::operation::Cast &) override;
  void visit(const ir::operation::Conv2D &) override;
  void visit(const ir::operation::DepthToSpace &) override;
  void visit(const ir::operation::DepthwiseConv2D &) override;
  void visit(const ir::operation::Dequantize &) override;
  void visit(const ir::operation::Concat &) override;
  void visit(const ir::operation::ElementwiseActivation &) override;
  void visit(const ir::operation::ElementwiseBinary &) override;
  void visit(const ir::operation::EmbeddingLookup &) override;
  void visit(const ir::operation::Floor &) override;
  void visit(const ir::operation::FullyConnected &) override;
  void visit(const ir::operation::Gather &) override;
  void visit(const ir::operation::HashtableLookup &) override;
  void visit(const ir::operation::InstanceNorm &) override;
  void visit(const ir::operation::L2Normalization &) override;
  void visit(const ir::operation::LocalResponseNormalization &) override;
  void visit(const ir::operation::LogicalNot &) override;
  void visit(const ir::operation::LSTM &) override;
  void visit(const ir::operation::Neg &) override;
  void visit(const ir::operation::Pack &) override;
  void visit(const ir::operation::Pad &) override;
  void visit(const ir::operation::Pool2D &) override;
  void visit(const ir::operation::Permute &) override;
  void visit(const ir::operation::PReLU &) override;
  void visit(const ir::operation::Reduce &) override;
  void visit(const ir::operation::Reshape &) override;
  void visit(const ir::operation::ResizeBilinear &) override;
  void visit(const ir::operation::RNN &) override;
  void visit(const ir::operation::RSQRT &) override;
  void visit(const ir::operation::Squeeze &) override;
  void visit(const ir::operation::Softmax &) override;
  void visit(const ir::operation::SpaceToBatchND &) override;
  void visit(const ir::operation::SpaceToDepth &) override;
  void visit(const ir::operation::Split &) override;
  void visit(const ir::operation::SQRT &) override;
  void visit(const ir::operation::SquaredDifference &) override;
  void visit(const ir::operation::Slice &) override;
  void visit(const ir::operation::StridedSlice &) override;
  void visit(const ir::operation::TransposeConv &) override;
  void visit(const ir::operation::Transpose &) override;
  void visit(const ir::operation::Unpack &) override;
  void visit(const ir::operation::Exp &) override;
  void visit(const ir::operation::ExpandDims &) override;
  void visit(const ir::operation::Comparison &) override;
  void visit(const ir::operation::OneHot &) override;

private:
  const ir::Operands &_ctx;
  const ir::Operations &_operations_ctx;
  std::shared_ptr<TensorBuilder> _tensor_builder;
  std::shared_ptr<acl_common::AclTensorRegistry<TensorManager>> _tensor_reg;
  ir::Layout _current_op_seq_layout;
};

} // namespace acl_neon
} // namespace backend
} // namespace onert

#endif // __ONERT_BACKEND_ACL_NEON_KERNEL_GENERATOR_H__
