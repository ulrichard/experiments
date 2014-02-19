#pragma once
// My first try of OpenCL
#define __CL_ENABLE_EXCEPTIONS
// OpenCL
#include <CL/cl.hpp>
// boost
#include <boost/array.hpp>
#include <boost/noncopyable.hpp>
// std lib
#include <vector>


class VectorAdderBase : private boost::noncopyable
{
public:
    VectorAdderBase(size_t vecSize);

    double Exec();

protected:
    virtual void DoExec() = 0;

    const size_t vecSize_;
    std::vector<float> arrA, arrB, arrC;
};

class OpenClVectorAdder : private boost::noncopyable
{
public:
    OpenClVectorAdder(cl::Context& context, cl::Device& device, cl::Program& program);

    cl::Context&      Context() const { return const_cast<cl::Context&>(context_); }
    cl::Device&       Device()  const { return const_cast<cl::Device&>(device_); }
    cl::Program&      Program() const { return const_cast<cl::Program&>(program_); }
    cl::CommandQueue& Queue()   const { return const_cast<cl::CommandQueue&>(queue_); }

private:
    cl::Context                 context_;
    cl::Device                  device_;
    cl::Program                 program_;
    cl::CommandQueue            queue_;
};

class VectorAdderGPU : public VectorAdderBase
{
public:
    VectorAdderGPU(size_t vecSize, OpenClVectorAdder& ocl);

protected:
    virtual void DoExec();

private:
    OpenClVectorAdder& OCLAdder;
};

class VectorAdderCPU : public VectorAdderBase
{
public:
    VectorAdderCPU(size_t vecSize) : VectorAdderBase(vecSize) { }

protected:
    virtual void DoExec();
};

