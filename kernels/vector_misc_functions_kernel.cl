/**
 * OpenCL Miscellaneous Vector Functions Test Kernels
 * Tests shuffle and shuffle2 built-in functions
 */

// Shuffle function - rearrange elements from a single vector
// shuffle(x, mask) selects elements from x according to mask indices
__kernel void test_shuffle_float4(__global const float4 *input0,
                                   __global const uint4 *input1,
                                   __global float4 *output,
                                   const unsigned int count) {
    int i = get_global_id(0);
    if (i < count) {
        // input0 is the data vector, input1 is the mask
        output[i] = shuffle(input0[i], input1[i]);
    }
}

// Shuffle2 function - select elements from two vectors
// shuffle2(x, y, mask) selects from x (indices 0-3) or y (indices 4-7)
__kernel void test_shuffle2_float4(__global const float4 *input0,
                                    __global const float4 *input1,
                                    __global const uint4 *input2,
                                    __global float4 *output,
                                    const unsigned int count) {
    int i = get_global_id(0);
    if (i < count) {
        // input0 and input1 are the data vectors, input2 is the mask
        output[i] = shuffle2(input0[i], input1[i], input2[i]);
    }
}
