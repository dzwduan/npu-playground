#include "mapping.h"
#include <cstddef>
#include <cstdint>
#include <map>
#include <string>
#include <stdexcept>
#include <fmt/format.h>
#include <fstream>
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