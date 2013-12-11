/// Vector addition simple kernel

// must define this macro to being able to use double -> my system doesnt support this extension
// #pragma OPENCL EXTENSION cl_khr_fp64: enable


__kernel void VectorAddition(__global float* A, __global float* B, __global float* C)
{
    // Get the index of the current element
    const int i = get_global_id(0);

    // Do the operation
    C[i] = A[i] + B[i];
}
