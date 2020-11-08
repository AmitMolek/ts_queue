#!/bin/sh

cd ..
mkdir build 2> /dev/null
cd build
cmake ..
make
cd ~ 2> /dev/null