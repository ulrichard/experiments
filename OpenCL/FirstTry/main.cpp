// My first try of OpenCL
#define __CL_ENABLE_EXCEPTIONS
// OpenCL
#include <CL/cl.hpp>
// boost
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/foreach.hpp>
// std lib
#include <vector>
#include <iostream>
#include <iterator>
#include <sstream>

namespace bfs = boost::filesystem;

int main(void)
{
    // Create the two input vectors
    const size_t LIST_SIZE = 1024;
	std::vector<cl_float> A(LIST_SIZE), B(LIST_SIZE), C(LIST_SIZE);
    for(size_t i=0; i<LIST_SIZE; ++i)
	{
        A[i] = i;
        B[i] = LIST_SIZE - i;
        C[i] = 3.14;
    }

	try
	{
		// Load the kernel source code into a string
		const bfs::path kernelfile(bfs::path(__FILE__).parent_path() / "vector_addition.cl");
		if(!bfs::exists(kernelfile))
            throw std::runtime_error(("OpenCL source file not found!" + kernelfile.string()).c_str());
		bfs::ifstream ifs(kernelfile);
		const std::string sourcecode(std::istreambuf_iterator<char>(ifs), (std::istreambuf_iterator<char>()));
		ifs.close();
		if(sourcecode.length() < 20)
            throw std::runtime_error("OpenCL source file was empty!");

		// Get available platforms
        std::vector<cl::Platform> platforms;
        cl::Platform::get(&platforms);

        // report the found platforms
        BOOST_FOREACH(const cl::Platform& plfrm, platforms)
        {
            std::cout << plfrm.getInfo<CL_PLATFORM_NAME>() << std::endl
                      << plfrm.getInfo<CL_PLATFORM_VENDOR>() << std::endl
                      << plfrm.getInfo<CL_PLATFORM_EXTENSIONS>() << std::endl;
        }

        // Select the default platform and create a context using this platform and the GPU
        cl_context_properties cps[3] = {
			CL_CONTEXT_PLATFORM,
            (cl_context_properties)(platforms[0])(),
            0
        };
        cl::Context context(CL_DEVICE_TYPE_GPU, cps);

        // Get a list of devices attached to the context
        std::vector<cl::Device> devices = context.getInfo<CL_CONTEXT_DEVICES>();

        // report the found devices for the selected platform
        BOOST_FOREACH(const cl::Device& device, devices)
        {
            std::cout << device.getInfo<CL_DEVICE_NAME>() << std::endl
                      << device.getInfo<CL_DEVICE_VENDOR>() << std::endl
                      << device.getInfo<CL_DEVICE_EXTENSIONS>() << std::endl;
        }

        // Create a command queue and use the first device
        cl::CommandQueue queue(context, devices[0]);

		// Make program of the source code in the context
		cl::Program::Sources source(1, std::make_pair(sourcecode.c_str(), sourcecode.length() + 1));
        cl::Program program = cl::Program(context, source);

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

		// Create memory buffers
        cl::Buffer bufferA = cl::Buffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, LIST_SIZE * sizeof(cl_float), reinterpret_cast<void*>(&A[0]));
        cl::Buffer bufferB = cl::Buffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, LIST_SIZE * sizeof(cl_float), reinterpret_cast<void*>(&B[0]));
        cl::Buffer bufferC = cl::Buffer(context, CL_MEM_WRITE_ONLY | CL_MEM_USE_HOST_PTR, LIST_SIZE * sizeof(cl_float), reinterpret_cast<void*>(&C[0]));

        // Make kernel
        cl::Kernel kernel(program, "VectorAddition");

        // Set arguments to kernel
        kernel.setArg(0, bufferA);
        kernel.setArg(1, bufferB);
        kernel.setArg(2, bufferC);

		// Execute the OpenCL kernel on the list
        queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(LIST_SIZE), cl::NullRange);

        // map bufferC to host pointer. This enforces sync with the host backing space. Remember, we chose a GPU device.
        cl_float* output = reinterpret_cast<cl_float*>(queue.enqueueMapBuffer(bufferC, CL_TRUE, CL_MAP_READ, 0, LIST_SIZE * sizeof(cl_float)));

		// Display the result to the screen
		for(size_t i = 0; i < LIST_SIZE; i++)
		    std::cout << A[i] << " + " << B[i] << " = " << C[i] << std::endl;

        // finally, release our hold on accessing the memory
        cl_int ret = queue.enqueueUnmapMemObject(bufferC, reinterpret_cast<void*>(output));
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

