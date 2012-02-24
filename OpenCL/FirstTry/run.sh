#! /bin/bash

sudo apt-get install libboost-filesystem-dev libboost-system-dev 
sudo apt-get install nvidia-current-dev

mkdir -p build
cd build
cmake -G "CodeBlocks - Unix Makefiles" ..
make

./opencl_primer 

