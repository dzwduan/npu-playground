#pragma once

#include "Reg.h"

enum class DataFlow {
    WS, OS
};

enum class MODE {
   COMPUTE, PROPAGATE
};

template<typename T>
class MAC {
    public:
    T a, b ,c, d;

    void eval() {
        d = a + b + c;
    }
};


template<typename T>
class PE {
    public:
    Reg<T> c1, c2;
    DataFlow dataFlow;
    MODE mode;
    MAC<T> mac;

    // input
    T a, b, d;
    T out_a, out_b, out_c;


    void eval() {
        if (dataFlow == DataFlow::WS && mode == MODE::PROPAGATE) {
            out_c = c1;
            mac.b = c2;
            mac.c = b;
            out_b = mac.d;
            c1 <= d;
        } else {
            out_c = c2;
            mac.b = c1;
            mac.c = b;
            out_b = mac.d;
            c1 <= a;
            c2 <= d;
        }
    }

};