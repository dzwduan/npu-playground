// design counter with reg

#include <iostream>
#include <string>
#include <unordered_map>
#include "Reg.h"


int main() {
    Reg<int> counter{0};
    int max = 16;
    int reset = 0;

    RegBase::global_clock();
    
    for (int i = 0; i < 15; i++) {
        counter <<= counter + 10;
        if (counter == max) {
            counter <<= (reset+10);
        }

        std::cout << "cycle " << i << "=" << counter << std::endl;

        RegBase::global_clock();
    }

}