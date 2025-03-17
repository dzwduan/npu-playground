#pragma once

#include "common.h"

enum class DIM {B, IC, OC, KH, KW, IH, IW};

struct Mapping{

    struct 
};


class MappingTable {
    public:
        static MappingTable parse_model(const std::string& onnx_model_path);
};