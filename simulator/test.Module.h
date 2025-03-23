#include <gtest/gtest.h>
#include <memory>
#include "Module.h"

// Test fixture for Module
class ModuleTest : public ::testing::Test {
protected:
    std::shared_ptr<Module> simpleModule;
    std::shared_ptr<Module> complexModule;
    
    void SetUp() override {
        // Initialize modules for testing
        simpleModule = std::make_shared<Module>("SimpleModule");
        complexModule = std::make_shared<Module>("ComplexModule", /* additional params */);
    }
};

// Test default constructor
TEST_F(ModuleTest, DefaultConstructor) {
    Module(add) {
        // Add logic here
        INPUT(int, a);
        INPUT(int, b);
        OUTPUT(int, sum);

        
    }

    
}
