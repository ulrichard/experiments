// My first try of OpenCL

// OpenCL
#include <CL/cl.hpp>
// boost
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
// std lib
#include <vector>
#include <iostream>

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
		const bfs::path kernelfile(bfs::path(__FILE__) / "vector_addition.cl");
		bfs::ifstream ifs(kernelfile);
		std::string sourcecode;
		ifs >> sourcecode;
		ifs.close();

		// Get available platforms
        vector<Platform> platforms;
        Platform::get(&platforms);
 
        // Select the default platform and create a context using this platform and the GPU
        cl_context_properties cps[3] = {
			CL_CONTEXT_PLATFORM, 
            (cl_context_properties)(platforms[0])(), 
            0 
        };
        Context context(CL_DEVICE_TYPE_GPU, cps);
 
        // Get a list of devices on this platform
        vector<Device> devices = context.getInfo<CL_CONTEXT_DEVICES>();
 
        // Create a command queue and use the first device
        CommandQueue queue = CommandQueue(context, devices[0]);

		// Make program of the source code in the context
		Program::Sources source(1, std::make_pair(sourcecode.c_str(), sourcecode.length() + 1));
        Program program = Program(context, source);
 
        // Build program for these specific devices
        program.build(devices);
 
        // Make kernel
        Kernel kernel(program, "vector_addition");

		// Create memory buffers
        Buffer bufferA = Buffer(context, CL_MEM_READ_ONLY,  LIST_SIZE * sizeof(int));
        Buffer bufferB = Buffer(context, CL_MEM_READ_ONLY,  LIST_SIZE * sizeof(int));
        Buffer bufferC = Buffer(context, CL_MEM_WRITE_ONLY, LIST_SIZE * sizeof(int));
 
        // Copy lists A and B to the memory buffers
        queue.enqueueWriteBuffer(bufferA, CL_TRUE, 0, LIST_SIZE * sizeof(int), &A[0]);
        queue.enqueueWriteBuffer(bufferB, CL_TRUE, 0, LIST_SIZE * sizeof(int), &B[0]);
 
        // Set arguments to kernel
        kernel.setArg(0, bufferA);
        kernel.setArg(1, bufferB);
        kernel.setArg(2, bufferC);

		// Execute the OpenCL kernel on the list
		NDRange global(LIST_SIZE);
        NDRange local(1);
        queue.enqueueNDRangeKernel(kernel, NullRange, global, local);
    
	    // Read the memory buffer C on the device to the local vector C
		queue.enqueueReadBuffer(bufferC, CL_TRUE, 0, LIST_SIZE * sizeof(int), &C[0]);


		// Display the result to the screen
		for(size_t i = 0; i < LIST_SIZE; i++)
		    std::cout << A[i] << " + " << B[i] << " = " << C[i] << std::endl;

	}
	catch(cl::Error& err)
	{
		std::cout << error.what() << "(" << error.err() << ")" << std::endl;
	}
    return 0;
}

