#! /bin/bash

# main repo
sudo apt-get install libboost-filesystem-dev libboost-system-dev 
# if you have an nvidia card, get the driver along with the opencl implementation from the restricted repository.
sudo apt-get install nvidia-current-dev
# I didn't find a package containing the OpenCL C++ wrapper header, so I just download it to the project directory for the time being.
mkdir -p CL
rm -rf CL/*
cd CL
wget http://www.khronos.org/registry/cl/api/1.1/cl_d3d10.h \
	http://www.khronos.org/registry/cl/api/1.1/cl_ext.h \
	http://www.khronos.org/registry/cl/api/1.1/cl_gl_ext.h \
	http://www.khronos.org/registry/cl/api/1.1/cl_gl.h \
	http://www.khronos.org/registry/cl/api/1.1/cl.h \
	http://www.khronos.org/registry/cl/api/1.1/cl_platform.h \
	http://www.khronos.org/registry/cl/api/1.1/opencl.h \
	http://www.khronos.org/registry/cl/api/1.1/cl.hpp
#wget http://www.khronos.org/registry/cl/api/1.2/cl_d3d10.h \
#	http://www.khronos.org/registry/cl/api/1.2/cl_d3d11.h \
#	http://www.khronos.org/registry/cl/api/1.2/cl_dx9_media_sharing.h \
#	http://www.khronos.org/registry/cl/api/1.2/cl_ext.h \
#	http://www.khronos.org/registry/cl/api/1.2/cl_gl_ext.h \
#	http://www.khronos.org/registry/cl/api/1.2/cl_gl.h \
#	http://www.khronos.org/registry/cl/api/1.2/cl.h \
#	http://www.khronos.org/registry/cl/api/1.2/cl_platform.h \
#	http://www.khronos.org/registry/cl/api/1.2/opencl.h \
#	http://www.khronos.org/registry/cl/api/1.2/cl.hpp
cd ..

mkdir -p build
cd build
cmake -G "CodeBlocks - Unix Makefiles" ..
make

./opencl_primer 

