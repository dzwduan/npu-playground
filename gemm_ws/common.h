#pragma once
#include <cstdint>


using addr_type = uint64_t;
constexpr addr_type SPAD_BASE = 0x10000000;
// accumulator 
constexpr addr_type ASPAD_BASE = 0x20000000;
using cycle_type = uint64_t;

uint32_t ceil_div(uint32_t src, uint32_t div);