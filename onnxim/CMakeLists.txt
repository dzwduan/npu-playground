cmake_minimum_required(VERSION 3.10)
project(onnxim)

# 包含ONNX目录
find_package(ONNX REQUIRED)

include_directories(include)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
find_package(ONNX REQUIRED)


# 如果你要创建可执行文件
add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} onnx)
