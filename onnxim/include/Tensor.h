#pragma once

#include "common.h"
#include "common/tensor.h"
#include <cstdint>
#include <vector>
#include <string>
#include <type_traits>



/**
一个硬件的Tensor类需要哪些功能?
1. dimension
2. data type
3. shape
4. data
5. transpose
6. reshape
7. name
*/


class Tensor {
    private:
        std::vector<uint32_t> dims;
        int data_type{};
        std::string name{};
        uint32_t id{};
    public:
        void transpose();
        void reshape();
};
