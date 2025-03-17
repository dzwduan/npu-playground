#include "common.h"
#include "model.h"
#include "Tensor.h"
#include <chrono>
#include <filesystem>
#include <memory>

namespace fs = std::filesystem;



int main(int argc, char* argv[]) -> int {
  // 用于perf
  auto start = std::chrono::high_resolution_clock::now();
  // 1. parse command line arguments ， 解析path, config暂时不做
  
  // 2. load onnx model to memory
  std::string onnx_model_path = "../model/matmul.onnx";
  // 3. parse onnx model to MappingTable
  MappingTable mt = MappingTable::parse_model(onnx_model_path);
  // 4. create model
  auto model = std::make_unique<Model>(onnx_model_path, mt);
  // 5. simulator register model , simulator cycle 是核心功能
  auto simulator = std::make_unique<Simulator>(config);
  simulator->register_model(std::move(model));
  // 6. run simulator
  simulator->run();

  return 0;
}