#pragma once
#include <cstdint>
#include <memory>
#include <sys/types.h>
#include "dff_base.hpp"

using accType = int8_t;
using inputType = int8_t;
using weightType = int8_t;
using cType = int32_t;
using dType = int32_t;

enum class dataFlowType {
    WS,
    OS
};


auto mac(inputType a, weightType b, cType c, dType &sum) -> dType {
    sum = a * b + c;
    return sum;
}



class PE {
private:
    inputType in_a;
    weightType in_b;
    cType in_d;
    inputType out_a;
    weightType out_b;
    dType out_c;
    dataFlowType dataFlow;

protected:
    DffBase<cType> dff_c1;
    DffBase<dType> dff_c2;

};