#pragma once

#include<cstdint>
#include<string>

enum class PEType {OS, WS};
enum class DramType {SIMPLE, RAMULATOR};

struct SimulationConfig {
    // core config
    uint32_t PE_num ;
    PEType   pe_type;
    uint32_t pe_freq;
    uint32_t pe_width;
    uint32_t pe_height;

    // vector config
    uint32_t vector_width;

    // SRAM config
    uint32_t sram_width;
    uint32_t sram_size;
    uint32_t spad_size;
    uint32_t accum_spad_size;

    // DRAM config
    DramType dram_type;
    uint32_t dram_freq;
    uint32_t dram_channel;
    uint32_t dram_req_size;
    uint32_t dram_latency;

    // other config
    uint32_t precision; // 精度

    std::string layout;
};