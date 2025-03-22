#include "gtest/gtest.h"
#include "../src/dff_base.hpp"
#include "test_dff_base.hpp"


// unit test main
int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}