#pragma once

#include "gemm.h"
#include "tile.h"
#include "operation.h"


class GemmWs : public Gemm {
    public:

    GemmWs(SimulationConfig config, MappingTable mapping_table,
        std::vector<uint32_t> input_shape, std::vector<uint32_t> weight_shape,
        std::vector<uint32_t> output_shape);
    virtual void initialize_tiles(MappingTable mp) override;

    protected:
    virtual void initialize_instr(Tile& tile, Mapping mp) override;
};