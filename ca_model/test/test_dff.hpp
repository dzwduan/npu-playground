#ifndef TEST_DFF_HPP
#define TEST_DFF_HPP

#include <gtest/gtest.h>
#include "../src/dff_base.hpp"

class DFFTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(DFFTest, BasicFunctionality) {
    Dff<int> dff1;
    Dff<int> dff2(10);

    // Test default value
    EXPECT_EQ(dff1.get_d(), 0);
    EXPECT_EQ(dff2.get_d(), 10);
    EXPECT_EQ(dff1.get(), 0);
    EXPECT_EQ(dff2.get(), 10);

    DffBase<int>::global_reset(false);
    DffBase<int>::global_clock();

    // Test after clock
    EXPECT_EQ(dff1.get(), 0);
    EXPECT_EQ(dff2.get(), 10);
}

#endif // TEST_DFF_HPP