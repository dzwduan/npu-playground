# if exist build directory, remove it
if [ -d "build" ]; then
    rm -rf build
fi
# else create build directory
mkdir build
# enter build directory
cd build
# cmake
cmake ..
# make
make -j
# run
./ca_model
