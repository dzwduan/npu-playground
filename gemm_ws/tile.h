#pragma once

#include "common.h"
#include "instr.h"
#include <cstdint>

enum class Status {
    INIT,
    RUNNING,
    FINISH,
    EMPTY
};



using Tile = struct {
    Status stat = Status::EMPTY;
    std::string optype;
    uint32_t batch;
    uint32_t output_channel;
    uint32_t input_channel;
    uint32_t input_height;
    uint32_t input_width;
    uint32_t output_height;
    uint32_t output_width;
    // uint32_t weight_height;
    // uint32_t weight_width;
} ;

