#include "operation.h"

#include <utility>

void OperationFactory::initialize(SimulationConfig _config) {
  OperationFactory::config = std::move(_config);
}

Operation::Operation(SimulationConfig _config) {
  config = std::move(_config);
  // 这里指的是输入的维度
  if (config.layout == "NHWC") {
    Bdim = 0;
    IHdim = 1;
    IWdim = 2;
    ICdim = 3;
  } else {
    Bdim = 0;
    IHdim = 1;
    IWdim = 2;
    ICdim = 3;
  }
}