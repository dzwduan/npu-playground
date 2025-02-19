#include <gtest/gtest.h>
#include "../csrc/dff_updater.hpp"

class DFFUpdaterTest : public ::testing::Test {
protected:
    DFFUpdater<int> updater;
    DFF<int> dff1;
    DFF<int> dff2;

    void SetUp() override {
        // 测试前的初始化
        dff1.sete(true);
        dff2.sete(true);
        updater.register_dff(&dff1);
        updater.register_dff(&dff2);
    }
};

// 测试DFF注册功能
TEST_F(DFFUpdaterTest, RegisterDFF) {
    EXPECT_EQ(updater.get_dff_count(), 2);
    
    DFF<int> dff3;
    updater.register_dff(&dff3);
    EXPECT_EQ(updater.get_dff_count(), 3);
}

// 测试全局复位功能
TEST_F(DFFUpdaterTest, GlobalReset) {
    dff1 <= 10;
    dff2 <= 20;
    updater.global_clock();
    
    updater.global_reset(true);
    EXPECT_EQ(dff1.get(), 0);
    EXPECT_EQ(dff2.get(), 0);
}

// 测试全局使能控制
TEST_F(DFFUpdaterTest, GlobalEnable) {
    updater.global_enable(false);
    
    dff1 <= 10;
    dff2 <= 20;
    updater.global_clock();
    
    EXPECT_EQ(dff1.get(), 0);
    EXPECT_EQ(dff2.get(), 0);
}

// 测试全局时钟更新
TEST_F(DFFUpdaterTest, GlobalClock) {
    dff1 <= 10;
    dff2 <= 20;
    updater.global_clock();
    
    EXPECT_EQ(dff1.get(), 10);
    EXPECT_EQ(dff2.get(), 20);
}

// 测试清除功能
TEST_F(DFFUpdaterTest, Clear) {
    EXPECT_EQ(updater.get_dff_count(), 2);
    
    updater.clear();
    EXPECT_EQ(updater.get_dff_count(), 0);
}

// 添加main函数
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
  }