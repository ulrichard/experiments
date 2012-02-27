/// Vector addition simple kernel
__kernel void VectorAddition(__global double* A, __global double* B, __global double* C)
{
    // Get the index of the current element
    const int i = get_global_id(0);

    // Do the operation
    C[i] = A[i] + B[i];
}
