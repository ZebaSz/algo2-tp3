#/bin/sh
mkdir build
cd build
cmake ..
make
valgrind --leak-check=full ./correrTests
cd ..