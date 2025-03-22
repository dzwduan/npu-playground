#pragma once

#include "config.h"
#include "mapping.h"
#include "tile.h"
#include <deque>

class Operation {
public:
  Operation(SimulationConfig config);

  virtual void initialize_tiles(MappingTable mp) = 0;

protected:
  virtual void initialize_instr(Tile& tile, Mapping mp) = 0;
  std::deque<Tile> tiles;

  int Bdim;
  int OCdim;
  int ICdim;
  int ICdim_w;
  int IHdim;
  int IWdim;
  int WHdim;
  int WWdim;

  SimulationConfig config;

private:

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