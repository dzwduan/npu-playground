#include <gtest/gtest.h>
#include "../src/dff_base.hpp"

// Test fixture for DffBase
class DffBaseTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup code before each test if needed
    }

    void TearDown() override {
        // Cleanup code after each test if needed
    }
};

// Test default constructor
TEST_F(DffBaseTest, DefaultConstructor) {
    DffBase<int> dff;
    EXPECT_EQ(dff.get(), 0);
    EXPECT_EQ(dff.get_d(), 0);
    EXPECT_TRUE(dff.rst_n);
}

// Test parameterized constructor
TEST_F(DffBaseTest, ParameterizedConstructor) {
    DffBase<int> dff(42);
    EXPECT_EQ(dff.get(), 42);
    EXPECT_EQ(dff.get_d(), 42);
    EXPECT_TRUE(dff.rst_n);
}

// Test reset method
TEST_F(DffBaseTest, Reset) {
    DffBase<int> dff(42);
    dff.reset(true);  // Active reset
    EXPECT_FALSE(dff.rst_n);
    EXPECT_EQ(dff.get(), 0); // Should be reset to default value

    dff.set(42);
    dff.clock();
    EXPECT_EQ(dff.get(), 0); // Should remain at default due to active reset

    dff.reset(false);  // Inactive reset
    EXPECT_TRUE(dff.rst_n);
    dff.set(42);
    dff.clock();
    EXPECT_EQ(dff.get(), 42); // Should update normally
}

// Test set method
TEST_F(DffBaseTest, Set) {
    DffBase<int> dff;
    dff.set(42);
    EXPECT_EQ(dff.get_d(), 42);
    EXPECT_EQ(dff.get(), 0); // Q shouldn't change until clock
}

// Test clock method
TEST_F(DffBaseTest, Clock) {
    DffBase<int> dff;
    dff.set(42);
    dff.clock();
    EXPECT_EQ(dff.get(), 42);

    // Test with reset active
    dff.reset(true);
    dff.set(24);
    dff.clock();
    EXPECT_EQ(dff.get(), 0); // Should remain at default due to reset
}

// Test get and get_d methods
TEST_F(DffBaseTest, GetMethods) {
    DffBase<int> dff(42);
    EXPECT_EQ(dff.get(), 42);
    EXPECT_EQ(dff.get_d(), 42);
    
    dff.set(24);
    EXPECT_EQ(dff.get_d(), 24);
    EXPECT_EQ(dff.get(), 42); // Q shouldn't change until clock
    
    dff.clock();
    EXPECT_EQ(dff.get(), 24);
}

// Test addition operator with scalar
TEST_F(DffBaseTest, AdditionWithScalar) {
    DffBase<int> dff(42);
    EXPECT_EQ(dff + 8, 50);
}

// Test addition operator with another DffBase
TEST_F(DffBaseTest, AdditionWithDff) {
    DffBase<int> dff1(42);
    DffBase<int> dff2(8);
    EXPECT_EQ(dff1 + dff2, 50);
}

// Test subtraction operator with scalar
TEST_F(DffBaseTest, SubtractionWithScalar) {
    DffBase<int> dff(42);
    EXPECT_EQ(dff - 8, 34);
}

// Test subtraction operator with another DffBase
TEST_F(DffBaseTest, SubtractionWithDff) {
    DffBase<int> dff1(42);
    DffBase<int> dff2(8);
    EXPECT_EQ(dff1 - dff2, 34);
}

// Test equality operator with scalar
TEST_F(DffBaseTest, EqualityWithScalar) {
    DffBase<int> dff(42);
    EXPECT_TRUE(dff == 42);
    EXPECT_FALSE(dff == 24);
}

// Test equality operator with another DffBase
TEST_F(DffBaseTest, EqualityWithDff) {
    DffBase<int> dff1(42);
    DffBase<int> dff2(42);
    DffBase<int> dff3(24);
    EXPECT_TRUE(dff1 == dff2);
    EXPECT_FALSE(dff1 == dff3);
}

// Test assignment operator with scalar
TEST_F(DffBaseTest, AssignmentWithScalar) {
    DffBase<int> dff;
    dff <<= 42;
    EXPECT_EQ(dff.get_d(), 42);
    dff.clock();
    EXPECT_EQ(dff.get(), 42);
    dff <<= 24;
    EXPECT_EQ(dff.get(), 42);
    dff.clock();
    EXPECT_EQ(dff.get(), 24);
}

// Test assignment operator with another DffBase
TEST_F(DffBaseTest, AssignmentWithDff) {
    DffBase<int> dff1;
    DffBase<int> dff2(42);
    dff1 <<= dff2;
    EXPECT_EQ(dff1.get_d(), 42);
}
