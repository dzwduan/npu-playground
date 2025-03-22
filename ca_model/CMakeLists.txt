cmake_minimum_required(VERSION 3.15)  # 提升最低版本要求
project(ca_model LANGUAGES CXX)

# 严格C++标准配置
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath=/usr/lib/x86_64-linux-gnu")

# 生成编译命令数据库
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 现代方式查找GTest
find_package(GTest REQUIRED)  # 优先使用CONFIG模式

# 单元测试配置
add_executable(unit_test test/main.cpp)


target_link_libraries(unit_test PRIVATE GTest::GTest GTest::Main )

target_link_libraries(unit_test
    PRIVATE
        GTest::GTest
        GTest::Main
)

# 条件性静态链接（仅在需要时启用）
# if(STATIC_LINK_STDCPP)
#     target_link_options(unit_test
#         PRIVATE
#             "-static-libgcc"
#             "-static-libstdc++"
#     )
# endif()