cmake_minimum_required(VERSION 3.10)
project(dff_test)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加GoogleTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# 添加测试可执行文件
add_executable(dff_test test/dff_test.cpp)
target_link_libraries(dff_test ${GTEST_LIBRARIES} pthread)

# 添加dff_updater测试可执行文件
add_executable(dff_updater_test test/dff_updater_test.cpp)
target_link_libraries(dff_updater_test ${GTEST_LIBRARIES} pthread)

# 启用测试
enable_testing()
add_test(NAME dff_test COMMAND dff_test)
add_test(NAME dff_updater_test COMMAND dff_updater_test)