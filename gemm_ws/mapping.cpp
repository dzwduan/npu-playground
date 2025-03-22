#include "mapping.h"
#include "common.h"
#include <cstddef>
#include <cstdint>
#include <map>
#include <string>
#include <stdexcept>
#include <fmt/format.h>
#include <sstream>
#include <tuple>


auto parse_mapping_file(std::string mapping_path) -> std::map<LoopCount, Mapping> {
    //TODO:
    throw std::runtime_error("Function not implemented yet");
}

auto parse_mapping_string(const std::string& mapping_str) -> std::tuple<LoopCount, LoopCount, LoopCount> {
    LoopCount total_loop, tile_out_loop, tile_in_loop;
    LoopCount* current_loop = nullptr;
    
    std::istringstream ss(mapping_str);
    std::string token;
    
    while (ss >> token) {
        if (token == "[T]") {
            current_loop = &total_loop;
        } else if (token == "[O]") {
            current_loop = &tile_out_loop;
        } else if (token == "[I]") {
            current_loop = &tile_in_loop;
        } else if (current_loop != nullptr) {
            // 找到数字的起始位置
            size_t i = 0;
            while (i < token.size() && !std::isdigit(token[i])) {
                i++;
            }
            
            if (i > 0 && i < token.size()) {
                std::string var_name = token.substr(0, i);
                int value = std::stoi(token.substr(i));
                
                // 根据变量名设置对应的 LoopCount 成员
                if (var_name == "B") {
                    current_loop->B = value;
                } else if (var_name == "IC") {
                    current_loop->IC = value;
                } else if (var_name == "OC") {
                    current_loop->OC = value;
                } else if (var_name == "WH") {
                    current_loop->WH = value;
                } else if (var_name == "WW") {
                    current_loop->WW = value;
                } else if (var_name == "IH") {
                    current_loop->IH = value;
                } else if (var_name == "IW") {
                    current_loop->IW = value;
                }
            }
        }
    }
    
    // 验证解析结果 (可根据需要调整验证逻辑)
    bool valid = true;
    // 这里可以添加更复杂的验证逻辑，例如检查是否所有必需的字段都已设置
    
    if (!valid) {
        throw std::runtime_error(fmt::format("Invalid mapping string: {}", mapping_str));
    }
    
    return {total_loop, tile_out_loop, tile_in_loop};
}


// parse "[T] B1 IC1 OC1 WH2 WW2 IW3 IH4 [O] B1 IC1 OC1 WH2 WW2 IW3 IH4 [I] B1 IC1 OC1 WH2 WW2 IW3 IH4" string to total_loop tile_in_loop tile_out_loop 
Mapping::Mapping(const std::string mapping_str){
    auto [t_loop, o_loop, i_loop] = parse_mapping_string(mapping_str);
    total_loop = t_loop;
    tile_out_loop = o_loop;
    tile_in_loop = i_loop;
}


void MappingTable::gemm_mapping(LoopCount &key) {
    // total dim
    uint32_t dim_I, dim_J, dim_K;
    // core dim , 只考虑单核
    uint32_t dim = config.pe_height;
    // double buffer spd rows , 每行长度是 precision * DIM
    uint32_t max_db_spad_rows = config.spad_size * 1024 / (dim * config.precision * 2);
    // double accumulator rows , 这里是int32 
    uint32_t max_db_acc_rows = config.accum_spad_size * 1024 / (dim * 4 * 2);

    // IxK @ KxJ = IxJ
    dim_I = key.B;
    dim_J = key.OC;
    dim_K = key.IC;

    // 维度对齐到dim
    const uint32_t dim_I_align = (dim_I/dim + (dim_I%dim)) * dim;
    const uint32_t dim_J_align = (dim_J/dim + (dim_J%dim)) * dim;
    const uint32_t dim_K_align = (dim_K/dim + (dim_K%dim)) * dim;
    
    //input weight 各占一半？不过和rocc-tests一致
    uint32_t db_partition_rows = max_db_spad_rows / 2;
    // 一个partition里面的矩阵数量
    uint32_t db_mats_in_partition = db_partition_rows / dim;
    // 一个accumulator里面的可以存的矩阵数量
    uint32_t db_mats_in_acc = max_db_acc_rows / dim;
    // PE阵列的计算height=width, acc是最终存out的地方
    // 采用方形的PE阵列，最多用几个阵列表示
    uint32_t db_max_tile_i_j = (uint32_t)sqrt(db_mats_in_acc);
    // 总的input需要分多少次写入accumulator
    uint32_t db_max_tile_k = db_mats_in_partition / db_max_tile_i_j;

    //out loop
    uint32_t tile_I = std::min(dim_I_align/dim, ceil_div(dim_I, db_max_tile_i_j*dim));
    uint32_t tile_J = std::min(dim_J_align/dim, ceil_div(dim_J, db_max_tile_i_j*dim));
    // 循环次数
    uint32_t tile_K = std::min(dim_K_align/dim, ceil_div(dim_K, db_max_tile_k*dim));


    uint32_t num_tiles = tile_I * tile_J;

    uint32_t inner_I = ceil_div(dim_I_align, tile_I);
    uint32_t inner_J = ceil_div(dim_J_align, tile_J);
    uint32_t inner_K = ceil_div(dim_K_align, tile_K);

    
}