#include <fmt/base.h>
#include <gtest/gtest.h>
#include "Reg.h"
#include <fmt/printf.h>

// Test fixture for Reg class
class RegTest : public ::testing::Test {
protected:
    Reg<int> reg1{10};
    Reg<int> reg2{20};
    Reg<double> reg3{30.5};
};

// Test constructor initialization
TEST_F(RegTest, ConstructorInitialization) {
    EXPECT_EQ(reg1, 10);
    EXPECT_EQ(reg2, 20);
    EXPECT_EQ(reg3, 30.5);
}

// Test assignment operation
TEST_F(RegTest, AssignmentOperation) {
    reg1 <<= 100;
    reg2 <<= 200;
    reg3 <<= 300.5;
    
    // Before update, values should remain unchanged
    EXPECT_EQ(reg1, 10);
    EXPECT_EQ(reg2, 20);
    EXPECT_EQ(reg3, 30.5);

    // After update, values should be updated
    RegBase::global_clock();
    EXPECT_EQ(reg1, 100);
    EXPECT_EQ(reg2, 200);
    EXPECT_EQ(reg3, 300.5);
}

// Test update method
TEST_F(RegTest, UpdateMethod) {
    reg1 <<= 100;
    reg2 <<= 200;
    
    reg1.update();
    reg2.update();
    
    EXPECT_EQ(reg1, 100);
    EXPECT_EQ(reg2, 200);
}

// Test global clock
TEST_F(RegTest, GlobalClock) {
    reg1 <<= 100;
    reg2 <<= 200;
    reg3 <<= 300.5;
    
    RegBase::global_clock();
    
    EXPECT_EQ(reg1, 100);
    EXPECT_EQ(reg2, 200);
    EXPECT_EQ(reg3, 300.5);
}

// Test implicit conversion
TEST_F(RegTest, ImplicitConversion) {
    reg1 <<= 100;
    RegBase::global_clock();
    
    int value = reg1;
    EXPECT_EQ(value, 100);
}

// Test equality operators
TEST_F(RegTest, EqualityOperators) {
    Reg<int> reg_copy{10};
    
    // Test equality with T
    EXPECT_TRUE(reg1 == 10);
    EXPECT_TRUE(10 == reg1);
    EXPECT_FALSE(reg1 == 20);
    
    // Test equality with Reg<T>
    EXPECT_TRUE(reg1 == reg_copy);
    EXPECT_FALSE(reg1 == reg2);
    
    // Test inequality with T
    EXPECT_TRUE(reg1 != 20);
    EXPECT_TRUE(20 != reg1);
    EXPECT_FALSE(reg1 != 10);
    
    // Test inequality with Reg<T>
    EXPECT_TRUE(reg1 != reg2);
    EXPECT_FALSE(reg1 != reg_copy);
}

// Test multiple updates
TEST_F(RegTest, MultipleUpdates) {
    reg1 <<= 100;
    RegBase::global_clock();
    EXPECT_EQ(reg1, 100);
    
    reg1 <<= 200;
    RegBase::global_clock();
    EXPECT_EQ(reg1, 200);
    
    // Test without assignment
    RegBase::global_clock();
    EXPECT_EQ(reg1, 200);
}

// Test updated flag behavior
TEST_F(RegTest, UpdatedFlagBehavior) {
    // Initial update
    reg1 <<= 100;
    RegBase::global_clock();
    EXPECT_EQ(reg1, 100);
    
    // Update with same value
    reg1 <<= 100;
    RegBase::global_clock();
    EXPECT_EQ(reg1, 100);
    
    // No assignment, should not change
    RegBase::global_clock();
    EXPECT_EQ(reg1, 100);
}

// Test scoping and registration
TEST_F(RegTest, ScopingAndRegistration) {
    {
        Reg<int> temp_reg{50};
        temp_reg <<= 150;
        
        RegBase::global_clock();
        EXPECT_EQ(temp_reg, 150);
        
        // Both registers should update
        reg1 <<= 100;
        RegBase::global_clock();
        EXPECT_EQ(reg1, 100);
        EXPECT_EQ(temp_reg, 150);
    }
    
    // temp_reg now out of scope
    reg1 <<= 200;
    RegBase::global_clock();
    EXPECT_EQ(reg1, 200);
}

// test gcd
