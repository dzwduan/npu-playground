#include "config.h"
#include <map>
#include <vector>
#include <string>
#include <cstdint>

   
// enum class LoopType {B, IC, OC, WH, WW, IH, IW};

struct LoopCount {
    uint32_t B = 1;
    uint32_t IC = 1;
    uint32_t OC = 1;
    uint32_t WH = 1;
    uint32_t WW = 1;
    uint32_t IH = 1;
    uint32_t IW = 1;

    auto operator==(const LoopCount &other) const noexcept -> bool {
        return   B == other.B  && 
                IC == other.IC &&
                OC == other.OC &&
                WH == other.WH &&
                WW == other.WW &&
                IH == other.IH &&
                IW == other.IW;
    }

    auto operator<(const LoopCount &other) const noexcept -> bool {
        if (B != other.B)   return B < other.B;
        if (IC != other.IC) return IC < other.IC;
        if (OC != other.OC) return OC < other.OC;
        if (WH != other.WH) return WH < other.WH;
        if (WW != other.WW) return WW < other.WW;
        if (IH != other.IH) return IH < other.IH;
        return IW < other.IW;
    }

    // auto get_loop(LoopType name) -> uint32_t;
};

struct Mapping {
    Mapping() = default;
    Mapping(std::string mapping_line);
    LoopCount total_loop;
    LoopCount tile_in_loop;
    LoopCount tile_out_loop;

    uint32_t spatial_IC = 0;
    uint32_t spatial_OC = 0;
    uint32_t spatial_WH = 0;
    uint32_t spatial_WW = 0;
    uint32_t spatial_IH = 0;
    uint32_t spatial_IW = 0;

    // struct LoopCount loop_count;
};



class MappingTable {
    public:
    MappingTable() = default;
    MappingTable(SimulationConfig config);

    void gemm_mapping(LoopCount &key);

    private:
    SimulationConfig config;
    using mp_t = std::map<LoopCount, Mapping>;
    mp_t mapping_table;
};