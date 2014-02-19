
#include "main.h"
// boost
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/foreach.hpp>
#include <boost/timer.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
// std lib
#include <map>
#include <iostream>
#include <iterator>
#include <sstream>
#include <cmath>
#include <limits>
#include <thread>

namespace bfs = boost::filesystem;


int main(void)
{
    try
    {
        // Load the kernel source code into a string
        const bfs::path kernelfile(bfs::path(__FILE__).parent_path() / "calc_addrs.cl");
        if(!bfs::exists(kernelfile))
            throw std::runtime_error(("OpenCL source file not found!" + kernelfile.string()).c_str());
        bfs::ifstream ifs(kernelfile);
        const std::string sourcecode(std::istreambuf_iterator<char>(ifs), (std::istreambuf_iterator<char>()));
        ifs.close();
        if(sourcecode.length() < 20)
            throw std::runtime_error("OpenCL source file was empty!");

        // Get available platforms
        std::vector<cl::Platform>   platforms;
        cl::Platform::get(&platforms);

        // report the found platforms and create an adder
        std::cout << "available platforms: " << std::endl;
        boost::ptr_vector<OpenClVectorAdder> clAdders;
        BOOST_FOREACH(cl::Platform& plfrm, platforms)
        {
            std::cout << " "  << plfrm.getInfo<CL_PLATFORM_NAME>() << std::endl
                      << "  " << plfrm.getInfo<CL_PLATFORM_VENDOR>() << std::endl
                      << "  " << plfrm.getInfo<CL_PLATFORM_EXTENSIONS>() << std::endl;

            // Select the default platform and create a context using this platform and the GPU
            cl_context_properties cps[3] = {
                CL_CONTEXT_PLATFORM,
                (cl_context_properties)(plfrm)(),
                0
            };
            cl::Context context = cl::Context(CL_DEVICE_TYPE_GPU, cps);

            // Get a list of devices attached to the context
            std::vector<cl::Device> devices = context.getInfo<CL_CONTEXT_DEVICES>();

            // Make program of the source code in the context
            cl::Program::Sources source(1, std::make_pair(sourcecode.c_str(), sourcecode.length() + 1));
            cl::Program program(context, source);

            // Build program for these specific devices
            try
            {
                program.build(devices);
            }
            catch(cl::Error& err)
            {
                std::stringstream sstr;
                sstr << err.what() << std::endl
                     << "Build Status: "   << program.getBuildInfo<CL_PROGRAM_BUILD_STATUS>(devices[0]) << std::endl
                     << "Build Options:\t" << program.getBuildInfo<CL_PROGRAM_BUILD_OPTIONS>(devices[0]).c_str() << std::endl
                     << "Build Log:\t "    << program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(devices[0]).c_str() << std::endl;
                throw cl::Error(CL_BUILD_PROGRAM_FAILURE, sstr.str().c_str());
            }

	    	std::cout << " devices found: " << std::endl;
            // report the found devices for the selected platform
            BOOST_FOREACH(cl::Device& device, devices)
            {
                std::cout << "   "  << device.getInfo<CL_DEVICE_NAME>() << std::endl
                          << "    " << device.getInfo<CL_DEVICE_VENDOR>() << std::endl
                          << "    " << device.getInfo<CL_DEVICE_EXTENSIONS>() << std::endl;

//                clAdders.push_back(new OpenClVectorAdder(context, device, program));
            }
        }

        // now that everything is prepared, run the stuff
		std::cout << "now run the stuff" << std::endl;

        const size_t vecSizeCap = 1e7;
        for(size_t i=10, j=0; i<=vecSizeCap; i = i << 2)
        {
            boost::timer btim;

            BOOST_FOREACH(OpenClVectorAdder& adder, clAdders)
            {
                for(j=0, btim.restart(); btim.elapsed() < 5.0; ++j)
                {
                    auto name = adder.Device().getInfo<CL_DEVICE_NAME>();
                    auto res  = VectorAdderGPU(i, adder).Exec();
                }
            }
        }
    }
    catch(cl::Error& err)
    {
        std::cout << "OpenCL error: " << err.what() << "(" << err.err() << ")" << std::endl;
    }
    catch(std::exception& ex)
    {
        std::cout << "Error: " << ex.what() << std::endl;
    }

    return 0;
}

VectorAdderBase::VectorAdderBase(size_t vecSize)
    : vecSize_(vecSize)
{
    arrA.resize(vecSize_);
    arrB.resize(vecSize_);
    arrC.resize(vecSize_);

    for(size_t i=0; i<vecSize_; ++i)
    {
        arrA[i] = i;
        arrB[i] = vecSize - i;
        arrC[i] = 3.14;
    }
}

double VectorAdderBase::Exec()
{
    boost::timer btim;

    DoExec();

    const double used = btim.elapsed();

    // validate the result
    for(size_t i = 0; i < vecSize_; i++)
    {
//        std::cout << arrA[i] << " + " << arrB[i] << " = " << arrC[i] << std::endl;
        if(fabs(arrC[i] - vecSize_) > 1e-3)
        {
            std::stringstream sstr;
            sstr << "wrong result at vector size " << vecSize_ << " pos "  << i << "  " << arrC[i] << "!= " << vecSize_;
            throw std::runtime_error(sstr.str());
        }
    }

    return used;
}

OpenClVectorAdder::OpenClVectorAdder(cl::Context& context, cl::Device& device, cl::Program& program)
    : context_(context)
    , device_(device)
    , program_(program)
{
    // Create a command queue and use the first device
    queue_ = cl::CommandQueue(context_, device_);
}


VectorAdderGPU::VectorAdderGPU(size_t vecSize, OpenClVectorAdder& ocl)
    : VectorAdderBase(vecSize)
    , OCLAdder(ocl)
{

}

void VectorAdderGPU::DoExec()
{
    try
	{
		// Create memory buffers
        cl::Buffer bufferA = cl::Buffer(OCLAdder.Context(), CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, vecSize_ * sizeof(cl_float), reinterpret_cast<void*>(&arrA[0]));
        cl::Buffer bufferB = cl::Buffer(OCLAdder.Context(), CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, vecSize_ * sizeof(cl_float), reinterpret_cast<void*>(&arrB[0]));
        cl::Buffer bufferC = cl::Buffer(OCLAdder.Context(), CL_MEM_WRITE_ONLY,                       vecSize_ * sizeof(cl_float), reinterpret_cast<void*>(&arrC[0]));

        // Make kernel
        cl::Kernel kernel(OCLAdder.Program(), "VectorAddition");

        // Set arguments to kernel
        kernel.setArg(0, bufferA);
        kernel.setArg(1, bufferB);
        kernel.setArg(2, bufferC);

		// Execute the OpenCL kernel on the list
        OCLAdder.Queue().enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(vecSize_), cl::NullRange);

        // Read the memory buffer C on the device to the local vector C
        OCLAdder.Queue().enqueueReadBuffer(bufferC, CL_TRUE, 0, vecSize_ * sizeof(cl_float), &arrC[0]);
	}
	catch(cl::Error& err)
	{
	    std::cout << "OpenCL error: " << err.what() << "(" << err.err() << ")" << std::endl;
	}
	catch(std::exception& ex)
	{
		std::cout << "Error: " << ex.what() << std::endl;
	}

}

void VectorAdderCPU::DoExec()
{
    for(size_t i=0; i<vecSize_; ++i)
    {
        arrC[i] = arrA[i] + arrB[i];
    }
}

