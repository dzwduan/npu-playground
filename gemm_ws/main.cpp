#include "config.h"
#include <cassert>
#include <cstdio>
#include <iostream>
#include <spdlog/spdlog.h>
#include "mapping.h"


SimulationConfig get_default_config() {
    SimulationConfig config;
    config.pe_type = PEType::WS;
    config.pe_height = 8;
    config.pe_width = 8;
    config.spad_size = 1024;
    config.accum_spad_size = 1024;
    config.precision = 4;  // 32-bit
    config.dram_req_size = 32;
    config.layout = "NHWC";
    return config;
}


int main() {

    // test resnet FC layer
    std::string fc_mapping = "[T] B1 IC512 OC100 - [O] B1 IC1 OC5 - [I] B1 IC512 OC248";
    // test mapping
    Mapping m(fc_mapping);
    assert(m.total_loop.B == 1);
    assert(m.total_loop.IC==512);
    assert(m.total_loop.OC==100);


    assert(m.tile_out_loop.B==1);
    assert(m.tile_out_loop.IC==1);
    assert(m.tile_out_loop.OC==5);

    assert(m.tile_in_loop.B==1);
    assert(m.tile_in_loop.IC==512);
    assert(m.tile_in_loop.OC==248);

    printf("PASS ALL Tests\n");
}