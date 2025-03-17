#pragma once

#include "config.h"
#include "mapping.h"
#include <memory>
class Operation {
public:
  Operation(SimulationConfig config);

protected:
  int Bdim;
  int OCdim;
  int ICdim;
  int ICdim_w;
  int IHdim;
  int IWdim;
  int WHdim;
  int WWdim;

private:
  SimulationConfig config;
};

// 使用创建的所有op共享一个config
class OperationFactory {
public:
  static void initialize(SimulationConfig config);
  // static std::unique_ptr<Operation> create_operation();
  // static std::unique_ptr<Operation> copy_operation(Operation* operation);

private:
  static SimulationConfig config;
};