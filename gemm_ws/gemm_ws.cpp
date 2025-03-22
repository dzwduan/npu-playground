#include "gemm_ws.h"
#include "common.h"
#include "config.h"
#include "gemm.h"
#include "tile.h"
#include <cstdint>
#include <fmt/base.h>
#include <fmt/printf.h>


GemmWs::GemmWs(SimulationConfig config, MappingTable mapping_table,
    std::vector<uint32_t> input_shape,
    std::vector<uint32_t> weight_shape,
    std::vector<uint32_t> output_shape)
: Gemm(config, mapping_table, input_shape, weight_shape, output_shape) {}



void GemmWs::initialize_tiles(MappingTable mp) {
    LoopCount key {
        .B = _output_shape[Bdim],
        .IC = _input_shape[ICdim],
        .OC = _output_shape[OCdim],
        .WH = _weight_shape[WHdim],
        .WW = _weight_shape[WWdim],
        .IH = _input_shape[IHdim],
        .IW = _input_shape[IWdim]
    };

    Mapping mapping = mp[key];

    for (uint32_t b = 0; b < mapping.tile_out_loop.B; b++) {
        for (uint32_t oc = 0; oc < mapping.tile_out_loop.OC; oc++) {
            for (uint32_t ic = 0; ic < mapping.tile_in_loop.IC; ic++) {
                
                tiles.push_back(Tile{
                    .stat = Status::INIT,
                    .optype = "gemm",
                    .batch = b,
                    .output_channel = oc,
                    .input_channel = ic,
                    .input_height = 1,
                    .input_width = 1,
                    .output_height = 1,
                    .output_width = 1
                });
                fmt::print("tile: {}, {}, {}\n", b, oc, ic);

                initialize_instr(tiles.back(), mapping);
            }
        }
    }
}

void GemmWs::initialize_instr(Tile& tile, Mapping mapping) {
    int out_b_offset = tile.batch * mapping.tile_in_loop.B;
    int out_ic_offset = tile.input_channel * mapping.tile_in_loop.IC;
    int out_oc_offset = tile.output_channel * mapping.tile_out_loop.OC;

    fmt::print("tile_out_offset: outb={}, out_ic={}, out_oc={}\n", out_b_offset, out_ic_offset, out_oc_offset);

    addr_type act_spd_base_adddr = SPAD_BASE;
    addr_type weight_spd_base_addr = SPAD_BASE ;

    auto loop_size = config.pe_width;

    // movin bias
    for (int ic = 0; ic < mapping.tile_in_loop.IC; ic+= loop_size) {
        
    }


    // movin activation


    // movin weight



    // compute


    // movout at last loop
}