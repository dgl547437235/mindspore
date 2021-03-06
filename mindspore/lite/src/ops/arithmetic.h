/**
 * Copyright 2019-2020 Huawei Technologies Co., Ltd
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef LITE_MINDSPORE_LITE_C_OPS_ARITHMETIC_H_
#define LITE_MINDSPORE_LITE_C_OPS_ARITHMETIC_H_

#include <vector>
#include <set>
#include <cmath>
#include "ir/dtype/type_id.h"
#include "src/ops/primitive_c.h"

namespace mindspore {
namespace lite {
class Arithmetic : public PrimitiveC {
 public:
#ifdef PRIMITIVE_WRITEABLE
  MS_DECLARE_PARENT(Arithmetic, PrimitiveC);
  Arithmetic() = default;
  explicit Arithmetic(schema::PrimitiveT *primitive) : PrimitiveC(primitive) {}
#else
  //  explicit Arithmetic(schema::Primitive *primitive) : PrimitiveC(primitive) {}
  Arithmetic() = default;
  int UnPackToFlatBuilder(const schema::Primitive *primitive, flatbuffers::FlatBufferBuilder *fbb) override {
    return RET_ERROR;
  }
#endif
  int InferShape(std::vector<lite::Tensor *> inputs_, std::vector<lite::Tensor *> outputs_) override;
  bool Broadcasting() { return this->broadcasting_; }
  int NDims() { return this->ndim_; }
  std::vector<int> InShape0() { return this->in_shape0_; }
  std::vector<int> InShape1() { return this->in_shape1_; }
  std::vector<int> OutputShape() { return this->out_shape_; }

 protected:
  bool broadcasting_ = false;
  int ndim_;
  std::vector<int> in_shape0_;
  std::vector<int> in_shape1_;
  std::vector<int> out_shape_;
};
}  // namespace lite
}  // namespace mindspore

#endif  // LITE_MINDSPORE_LITE_C_OPS_ARITHMETIC_H_
