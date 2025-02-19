#include "../csrc/dff.hpp"
#include <gtest/gtest.h>

// 基本功能测试固件
class DFFTest : public ::testing::Test {
protected:
  DFF<int> dff;  // 使用int类型进行测试
  DFF<int> dff2; // 用于测试operator+重载

  void SetUp() override {
    dff.sete(true);   // 默认使能
    dff.reset(false); // 释放复位
  }
};

// 测试复位功能
TEST_F(DFFTest, ResetTest) {
  // 设置初始值
  dff <= 42;
  EXPECT_EQ(dff.get(), 0);
  dff.clock();
  EXPECT_EQ(dff.get(), 42);

  // 测试复位
  dff.reset(true);
  dff.clock();
  EXPECT_EQ(dff.get(), 0);
}

// 测试使能控制
TEST_F(DFFTest, EnableTest) {
  // 使能时可以更新数据
  dff <= 100;
  dff.clock();
  EXPECT_EQ(dff.get(), 100);

  // 禁用后数据保持
  dff.sete(false);
  dff <= 200;
  dff.clock();
  EXPECT_EQ(dff.get(), 100);
}

// 测试时钟触发
TEST_F(DFFTest, ClockTest) {
  dff <= 50;
  // 在时钟前检查输出
  EXPECT_EQ(dff.get(), 0);
  // 时钟触发后检查
  dff.clock();
  EXPECT_EQ(dff.get(), 50);
}

// 测试数据保持
TEST_F(DFFTest, DataHoldTest) {
  // 第一个时钟周期
  dff <= 10;
  dff.clock();
  EXPECT_EQ(dff.get(), 10);

  // 在没有新数据时保持原值
  dff.clock();
  EXPECT_EQ(dff.get(), 10);
}

// 测试操作符重载
TEST_F(DFFTest, OperatorTest) {
  dff <= 30;
  dff.clock();
  EXPECT_EQ(dff.get(), 30);

  // 链式操作
  (dff <= 40).clock();
  EXPECT_EQ(dff.get(), 40);
}

// 测试operator+重载
TEST_F(DFFTest, OperatorPlusTest) {
    dff <= 10;
    dff <= dff + 20;
    dff.clock();
    EXPECT_EQ(dff.get(), 30);

    dff2 <= 40;
    dff <= dff + dff2;
    dff.clock();
    EXPECT_EQ(dff.get(), 70);
    // test dff and dff2 all changed
    dff2 <= 100;
    dff <= dff2;
    dff.clock();
    EXPECT_EQ(dff.get(), 100);
}   

// test ==
TEST_F(DFFTest, OperatorEqualTest) {
    dff <= 10;
    dff2 <= 10;
    dff.clock();
    dff2.clock();
    EXPECT_EQ(dff == dff2, true);
    dff2 <= 20;
    dff2.clock();
    EXPECT_EQ(dff == dff2, false);
}

// 添加main函数
int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}