// My first try of OpenCL

// OpenCL
#include <CL/cl.hpp>
// boost
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
// std lib
#include <vector>
#include <iostream>
#include <iterator>

namespace bfs = boost::filesystem;

int main(void)
{
    // Create the two input vectors
    const size_t LIST_SIZE = 1024;
	std::vector<double> A(LIST_SIZE), B(LIST_SIZE), C(LIST_SIZE);
    for(size_t i=0; i<LIST_SIZE; ++i)
	{
        A[i] = i;
        B[i] = LIST_SIZE - i;
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

        // Select the default platform and create a context using this platform and the GPU
        cl_context_properties cps[3] = {
			CL_CONTEXT_PLATFORM,
            (cl_context_properties)(platforms[0])(),
            0
        };
        cl::Context context(CL_DEVICE_TYPE_GPU, cps);

        // Get a list of devices on this platform
        std::vector<cl::Device> devices = context.getInfo<CL_CONTEXT_DEVICES>();

        // Create a command queue and use the first device
        cl::CommandQueue queue = cl::CommandQueue(context, devices[0]);

		// Make program of the source code in the context
		cl::Program::Sources source(1, std::make_pair(sourcecode.c_str(), sourcecode.length() + 1));
        cl::Program program = cl::Program(context, source);

        // Build program for these specific devices
        program.build(devices);

        // Make kernel
        cl::Kernel kernel(program, "vector_addition");

		// Create memory buffers
        cl::Buffer bufferA = cl::Buffer(context, CL_MEM_READ_ONLY,  LIST_SIZE * sizeof(double));
        cl::Buffer bufferB = cl::Buffer(context, CL_MEM_READ_ONLY,  LIST_SIZE * sizeof(double));
        cl::Buffer bufferC = cl::Buffer(context, CL_MEM_WRITE_ONLY, LIST_SIZE * sizeof(double));

        // Copy lists A and B to the memory buffers
        queue.enqueueWriteBuffer(bufferA, CL_TRUE, 0, LIST_SIZE * sizeof(double), &A[0]);
        queue.enqueueWriteBuffer(bufferB, CL_TRUE, 0, LIST_SIZE * sizeof(double), &B[0]);

        // Set arguments to kernel
        kernel.setArg(0, bufferA);
        kernel.setArg(1, bufferB);
        kernel.setArg(2, bufferC);

		// Execute the OpenCL kernel on the list
		cl::NDRange global(LIST_SIZE);
        cl::NDRange local(1);
        queue.enqueueNDRangeKernel(kernel, cl::NullRange, global, local);

	    // Read the memory buffer C on the device to the local vector C
		queue.enqueueReadBuffer(bufferC, CL_TRUE, 0, LIST_SIZE * sizeof(double), &C[0]);


		// Display the result to the screen
		for(size_t i = 0; i < LIST_SIZE; i++)
		    std::cout << A[i] << " + " << B[i] << " = " << C[i] << std::endl;

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

