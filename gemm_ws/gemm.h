#pragma once
#include "mapping.h"
#include "operation.h"
#include <memory>
#include <vector>

class Gemm : public Operation {
public:
  Gemm(SimulationConfig config, MappingTable mapping_table,
       std::vector<uint32_t> output_shape, std::vector<uint32_t> input_shape,
       std::vector<uint32_t> weight_shape);

  virtual ~Gemm() = default;

protected:
  std::vector<uint32_t> _output_shape;
  std::vector<uint32_t> _input_shape;
  std::vector<uint32_t> _weight_shape;

private:
  uint32_t _alpha;
  uint32_t _beta;
  bool _transA;
  bool _transB;
};