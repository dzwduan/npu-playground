#include "config.h"
#include <cassert>
#include <cstdio>
#include <iostream>
#include <spdlog/spdlog.h>
#include "mapping.h"
#include "operation.h"


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
    std::string fc_mapping = "[T] B1 IC4096 OC1000 - [O] B1 IC6 OC7 - [I] B1 IC816 OC152";
    // input info
    uint32_t n = 1, c = 4096, m = 1000;
    auto config = get_default_config();
    OperationFactory::initialize(config);

    // Mapping mapping(fc_mapping);

        


}