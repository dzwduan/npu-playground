# if exist build directory, remove it
if [ -d "build" ]; then
    rm -rf build
fi
# 创建构建目录
mkdir -p build && cd build

# 配置项目（启用静态链接）
cmake .. -DCMAKE_BUILD_TYPE=Debug

# 编译项目
cmake --build . --parallel $(nproc)

# 运行测试
./unit_test