/*
 * Copyright (c) 2023 Samsung Electronics Co., Ltd. All Rights Reserved
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

#ifndef LUCI_INTERPRETER_TEST_MODELS_PACK_KERNEL_H
#define LUCI_INTERPRETER_TEST_MODELS_PACK_KERNEL_H

#include "TestDataPackBase.h"

namespace luci_interpreter
{
namespace test_kernel
{
namespace pack_float
{
/*
 * Pack Kernel:
 *
 * Input(2, 4, 3)   Input(2, 4, 3)
 *        \             /
 *          \         /
 *              Pack
 *                |
 *          Output(2, 2, 4, 3)
 */
const unsigned char test_kernel_model_circle[] = {
  0x18, 0x00, 0x00, 0x00, 0x43, 0x49, 0x52, 0x30, 0x00, 0x00, 0x0e, 0x00, 0x14, 0x00, 0x00, 0x00,
  0x0c, 0x00, 0x08, 0x00, 0x10, 0x00, 0x04, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
  0x34, 0x00, 0x00, 0x00, 0x7c, 0x01, 0x00, 0x00, 0x98, 0x01, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
  0x20, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
  0xf4, 0xff, 0xff, 0xff, 0xf8, 0xff, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xff, 0x04, 0x00, 0x04, 0x00,
  0x04, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x00,
  0x18, 0x00, 0x14, 0x00, 0x10, 0x00, 0x0c, 0x00, 0x08, 0x00, 0x04, 0x00, 0x0e, 0x00, 0x00, 0x00,
  0x14, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x6c, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00,
  0x78, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x6d, 0x61, 0x69, 0x6e, 0x00, 0x00, 0x00, 0x00,
  0x01, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x14, 0x00, 0x00, 0x00,
  0x10, 0x00, 0x0c, 0x00, 0x07, 0x00, 0x08, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3b,
  0x14, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x08, 0x00, 0x0c, 0x00,
  0x08, 0x00, 0x04, 0x00, 0x08, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
  0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00,
  0x3c, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0xa0, 0xff, 0xff, 0xff, 0x0c, 0x00, 0x00, 0x00,
  0x03, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x73, 0x74, 0x61, 0x63,
  0x6b, 0x5f, 0x34, 0x64, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
  0x02, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0xd4, 0xff, 0xff, 0xff,
  0x0c, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00,
  0x69, 0x6e, 0x70, 0x75, 0x74, 0x5f, 0x31, 0x00, 0x03, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
  0x04, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x10, 0x00, 0x0c, 0x00, 0x00, 0x00,
  0x08, 0x00, 0x04, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x10, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x69, 0x6e, 0x70, 0x75, 0x74, 0x00, 0x00, 0x00,
  0x03, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
  0x01, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x0c, 0x00, 0x0b, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x04, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x53, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x53,
  0x11, 0x00, 0x00, 0x00, 0x4f, 0x4e, 0x45, 0x2d, 0x74, 0x66, 0x6c, 0x69, 0x74, 0x65, 0x32, 0x63,
  0x69, 0x72, 0x63, 0x6c, 0x65, 0x00, 0x00, 0x00};

const std::vector<float> input_data_1 = {
  -0.17432976, -10.103649, 4.2064724,   -7.185501, 7.6475716, -34.405083, 14.065273,  -17.566177,
  16.921495,   -8.886711,  16.913736,   -8.991537, 18.480549, 17.71526,   -3.8370514, 16.570705,
  -14.831467,  17.709942,  0.026670456, -6.250948, 10.977406, 22.907639,  -37.32604,  -1.3433037};

const std::vector<float> input_data_2 = {
  -22.672482, 10.947399, -9.828194, -3.2829914, 14.490927,  24.998316,  33.86125,   -17.046562,
  7.1629715,  21.064964, 5.813303,  -16.67994,  -22.828697, -7.9325237, -23.776447, -17.539246,
  -3.8784523, 14.898129, 27.151598, -3.9495945, 21.426613,  -8.786135,  0.22362137, -7.534506};

const std::vector<float> reference_output_data = {
  -1.7432976e-01, -1.0103649e+01, 4.2064724e+00,  -7.1855011e+00, 7.6475716e+00,  -3.4405083e+01,
  1.4065273e+01,  -1.7566177e+01, 1.6921495e+01,  -8.8867111e+00, 1.6913736e+01,  -8.9915371e+00,
  -2.2672482e+01, 1.0947399e+01,  -9.8281937e+00, -3.2829914e+00, 1.4490927e+01,  2.4998316e+01,
  3.3861252e+01,  -1.7046562e+01, 7.1629715e+00,  2.1064964e+01,  5.8133030e+00,  -1.6679939e+01,
  1.8480549e+01,  1.7715260e+01,  -3.8370514e+00, 1.6570705e+01,  -1.4831467e+01, 1.7709942e+01,
  2.6670456e-02,  -6.2509480e+00, 1.0977406e+01,  2.2907639e+01,  -3.7326038e+01, -1.3433037e+00,
  -2.2828697e+01, -7.9325237e+00, -2.3776447e+01, -1.7539246e+01, -3.8784523e+00, 1.4898129e+01,
  2.7151598e+01,  -3.9495945e+00, 2.1426613e+01,  -8.7861347e+00, 2.2362137e-01,  -7.5345058e+00};
} // namespace pack_float

namespace pack_int
{
/*
 * Pack Kernel:
 *
 * Input(2, 8)        Input(2, 8)
 *        \             /
 *          \         /
 *              Pack
 *                |
 *          Output(2, 2, 8)
 */
const unsigned char test_kernel_model_circle[] = {
  0x18, 0x00, 0x00, 0x00, 0x43, 0x49, 0x52, 0x30, 0x00, 0x00, 0x0e, 0x00, 0x14, 0x00, 0x00, 0x00,
  0x0c, 0x00, 0x08, 0x00, 0x10, 0x00, 0x04, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
  0xb8, 0x00, 0x00, 0x00, 0x24, 0x02, 0x00, 0x00, 0x40, 0x02, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00,
  0xa4, 0x00, 0x00, 0x00, 0x9c, 0x00, 0x00, 0x00, 0x94, 0x00, 0x00, 0x00, 0x8c, 0x00, 0x00, 0x00,
  0x6c, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x06, 0xff, 0xff, 0xff, 0x04, 0x00, 0x00, 0x00,
  0x58, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x08, 0x00, 0x0c, 0x00, 0x08, 0x00, 0x04, 0x00,
  0x08, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x08, 0x00, 0x0c, 0x00,
  0x08, 0x00, 0x07, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x04, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0a, 0x00, 0x10, 0x00, 0x0c, 0x00, 0x08, 0x00, 0x04, 0x00,
  0x0a, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
  0x06, 0x00, 0x00, 0x00, 0x32, 0x2e, 0x31, 0x31, 0x2e, 0x30, 0x00, 0x00, 0x6a, 0xff, 0xff, 0xff,
  0x04, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x31, 0x2e, 0x31, 0x31, 0x2e, 0x30, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xa4, 0xfe, 0xff, 0xff, 0xa8, 0xfe, 0xff, 0xff,
  0xac, 0xfe, 0xff, 0xff, 0xb0, 0xfe, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x0e, 0x00, 0x18, 0x00, 0x14, 0x00, 0x10, 0x00, 0x0c, 0x00, 0x08, 0x00, 0x04, 0x00,
  0x0e, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x68, 0x00, 0x00, 0x00,
  0x6c, 0x00, 0x00, 0x00, 0x74, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x6d, 0x61, 0x69, 0x6e,
  0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x00,
  0x16, 0x00, 0x00, 0x00, 0x10, 0x00, 0x0c, 0x00, 0x07, 0x00, 0x08, 0x00, 0x0e, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x3b, 0x14, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x06, 0x00, 0x08, 0x00, 0x04, 0x00, 0x06, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
  0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x90, 0x00, 0x00, 0x00,
  0x40, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x8a, 0xff, 0xff, 0xff, 0x14, 0x00, 0x00, 0x00,
  0x14, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x14, 0x00, 0x00, 0x00,
  0x7c, 0xff, 0xff, 0xff, 0x05, 0x00, 0x00, 0x00, 0x73, 0x74, 0x61, 0x63, 0x6b, 0x00, 0x00, 0x00,
  0x03, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00,
  0xc2, 0xff, 0xff, 0xff, 0x14, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x02, 0x1c, 0x00, 0x00, 0x00, 0xb4, 0xff, 0xff, 0xff, 0x0d, 0x00, 0x00, 0x00,
  0x50, 0x6c, 0x61, 0x63, 0x65, 0x68, 0x6f, 0x6c, 0x64, 0x65, 0x72, 0x5f, 0x31, 0x00, 0x00, 0x00,
  0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x00,
  0x18, 0x00, 0x14, 0x00, 0x13, 0x00, 0x0c, 0x00, 0x08, 0x00, 0x04, 0x00, 0x0e, 0x00, 0x00, 0x00,
  0x18, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
  0x1c, 0x00, 0x00, 0x00, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x00, 0x00, 0x0b, 0x00, 0x00, 0x00,
  0x50, 0x6c, 0x61, 0x63, 0x65, 0x68, 0x6f, 0x6c, 0x64, 0x65, 0x72, 0x00, 0x02, 0x00, 0x00, 0x00,
  0x02, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
  0x0c, 0x00, 0x0c, 0x00, 0x0b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x0c, 0x00, 0x00, 0x00,
  0x53, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x53, 0x11, 0x00, 0x00, 0x00, 0x4f, 0x4e, 0x45, 0x2d,
  0x74, 0x66, 0x6c, 0x69, 0x74, 0x65, 0x32, 0x63, 0x69, 0x72, 0x63, 0x6c, 0x65, 0x00, 0x00, 0x00};

const std::vector<int32_t> input_data_1 = {-5, 5, -5, -5, 15, 13, -4, 14,
                                           5,  5, 5,  5,  12, 21, -5, 6};
const std::vector<int32_t> input_data_2 = {4, 5, 5, 5, 5, 5, 15, 4, -3, 11, 15, 32, -13, 13, -3, 5};

const std::vector<int32_t> reference_output_data = {-5, 5,  -5, -5, 15, 13, -4,  14, 5,  5, 5,
                                                    5,  12, 21, -5, 6,  4,  5,   5,  5,  5, 5,
                                                    15, 4,  -3, 11, 15, 32, -13, 13, -3, 5};

} // namespace pack_int

namespace pack_quant_u8
{
/*
 * Pack Kernel:
 *
 * Input(2, 4, 3)        Input(2, 4, 3)
 *        \             /
 *          \         /
 *              Pack
 *                |
 *          Output(2, 2, 4, 3)
 */
const unsigned char test_kernel_model_circle[] = {
  0x18, 0x00, 0x00, 0x00, 0x43, 0x49, 0x52, 0x30, 0x00, 0x00, 0x0e, 0x00, 0x14, 0x00, 0x00, 0x00,
  0x0c, 0x00, 0x08, 0x00, 0x10, 0x00, 0x04, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
  0x34, 0x00, 0x00, 0x00, 0x54, 0x02, 0x00, 0x00, 0x70, 0x02, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
  0x20, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
  0xf4, 0xff, 0xff, 0xff, 0xf8, 0xff, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xff, 0x04, 0x00, 0x04, 0x00,
  0x04, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x00,
  0x18, 0x00, 0x14, 0x00, 0x10, 0x00, 0x0c, 0x00, 0x08, 0x00, 0x04, 0x00, 0x0e, 0x00, 0x00, 0x00,
  0x14, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x6c, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00,
  0x78, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x6d, 0x61, 0x69, 0x6e, 0x00, 0x00, 0x00, 0x00,
  0x01, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x14, 0x00, 0x00, 0x00,
  0x10, 0x00, 0x0c, 0x00, 0x07, 0x00, 0x08, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3b,
  0x14, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x08, 0x00, 0x0c, 0x00,
  0x08, 0x00, 0x04, 0x00, 0x08, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
  0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00,
  0x80, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x1a, 0xff, 0xff, 0xff, 0x14, 0x00, 0x00, 0x00,
  0x4c, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x50, 0x00, 0x00, 0x00,
  0x0c, 0xff, 0xff, 0xff, 0x30, 0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00,
  0x04, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3f, 0x01, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x7f, 0x43, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00,
  0x73, 0x74, 0x61, 0x63, 0x6b, 0x5f, 0x34, 0x64, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
  0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
  0x92, 0xff, 0xff, 0xff, 0x14, 0x00, 0x00, 0x00, 0x48, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x03, 0x48, 0x00, 0x00, 0x00, 0x84, 0xff, 0xff, 0xff, 0x2c, 0x00, 0x00, 0x00,
  0x20, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3f,
  0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x43, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x07, 0x00, 0x00, 0x00, 0x69, 0x6e, 0x70, 0x75, 0x74, 0x5f, 0x31, 0x00, 0x03, 0x00, 0x00, 0x00,
  0x02, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x00,
  0x18, 0x00, 0x14, 0x00, 0x13, 0x00, 0x0c, 0x00, 0x08, 0x00, 0x04, 0x00, 0x0e, 0x00, 0x00, 0x00,
  0x20, 0x00, 0x00, 0x00, 0x58, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03,
  0x58, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x14, 0x00, 0x04, 0x00, 0x08, 0x00, 0x0c, 0x00, 0x10, 0x00,
  0x0c, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00,
  0x04, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3f, 0x01, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x7f, 0x43, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00,
  0x69, 0x6e, 0x70, 0x75, 0x74, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
  0x04, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
  0x0c, 0x00, 0x0c, 0x00, 0x0b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x0c, 0x00, 0x00, 0x00,
  0x53, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x53, 0x11, 0x00, 0x00, 0x00, 0x4f, 0x4e, 0x45, 0x2d,
  0x74, 0x66, 0x6c, 0x69, 0x74, 0x65, 0x32, 0x63, 0x69, 0x72, 0x63, 0x6c, 0x65, 0x00, 0x00, 0x00};

const std::vector<uint8_t> input_data_1 = {5, 243, 251, 5, 6, 7,   13,  23,  23, 5, 13, 5,
                                           7, 244, 13,  5, 5, 244, 252, 253, 5,  5, 5,  5};

const std::vector<uint8_t> input_data_2 = {15, 30,  252, 7, 252, 40,  245, 13,  13, 14, 21, 5,
                                           5,  245, 251, 5, 251, 223, 5,   251, 22, 15, 15, 15};

const std::vector<uint8_t> reference_output_data = {
  5,   243, 251, 5,  6,  7,   13,  23, 23,  5,   13, 5,   15, 30,  252, 7,
  252, 40,  245, 13, 13, 14,  21,  5,  7,   244, 13, 5,   5,  244, 252, 253,
  5,   5,   5,   5,  5,  245, 251, 5,  251, 223, 5,  251, 22, 15,  15,  15};

} // namespace pack_quant_u8

class TestDataFloatPack : public TestDataPackBase<float>
{
public:
  TestDataFloatPack()
  {
    _input_data_1 = pack_float::input_data_1;
    _input_data_2 = pack_float::input_data_2;
    _reference_output_data = pack_float::reference_output_data;
    _test_kernel_model_circle = pack_float::test_kernel_model_circle;
  }

  ~TestDataFloatPack() override = default;
};

class TestDataIntPack : public TestDataPackBase<int32_t>
{
public:
  TestDataIntPack()
  {
    _input_data_1 = pack_int::input_data_1;
    _input_data_2 = pack_int::input_data_2;
    _reference_output_data = pack_int::reference_output_data;
    _test_kernel_model_circle = pack_int::test_kernel_model_circle;
  }

  ~TestDataIntPack() override = default;
};

class TestDataQuantU8Pack : public TestDataPackBase<uint8_t>
{
public:
  TestDataQuantU8Pack()
  {
    _input_data_1 = pack_quant_u8::input_data_1;
    _input_data_2 = pack_quant_u8::input_data_2;
    _reference_output_data = pack_quant_u8::reference_output_data;
    _test_kernel_model_circle = pack_quant_u8::test_kernel_model_circle;
  }

  ~TestDataQuantU8Pack() override = default;
};

} // namespace test_kernel
} // namespace luci_interpreter

#endif // LUCI_INTERPRETER_TEST_MODELS_PACK_KERNEL_H