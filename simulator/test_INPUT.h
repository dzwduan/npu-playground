#pragma once
#include "INPUT.h"
#include "Reg.h"
#include <cassert>
#include <iostream>

// test INPUT and Module
MODULE(test_INPUT)
{
    INPUT(int, a);
    INPUT(int, b);
    INPUT(bool, valid);

    Reg<int> reg_a{0};
    Reg<int> reg_b{0};
    Reg<bool> busy{false};

    void eval() {
        if (valid == true && busy == false) {
            reg_a <<= a;
            reg_b <<= b;
            busy <<= true;
            done <<= false;
        } else if (busy == true) {
            if (reg_b != 0) {
                int temp = reg_b;
                reg_b <<= reg_a % reg_b;
                reg_a <<= temp;
            } else {
                result <<= reg_a;
                done <<= true;
                busy <<= false;
            }
        }
    }
};