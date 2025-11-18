// OpenCL Native Math Functions
// These functions use float inputs/outputs with implementation-defined precision
// for maximum performance. Accuracy is implementation-defined.
// Reference: https://registry.khronos.org/OpenCL/specs/3.0-unified/html/OpenCL_C.html#math-functions

// Single-input functions
__kernel void test_native_cos(__global const float *input, __global float *output,
                              const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = native_cos(input[i]);
}

__kernel void test_native_sin(__global const float *input, __global float *output,
                              const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = native_sin(input[i]);
}

__kernel void test_native_tan(__global const float *input, __global float *output,
                              const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = native_tan(input[i]);
}

__kernel void test_native_recip(__global const float *input, __global float *output,
                                const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = native_recip(input[i]);
}

// Two-input functions
__kernel void test_native_divide(__global const float *input0, __global const float *input1,
                                 __global float *output, const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = native_divide(input0[i], input1[i]);
}

__kernel void test_native_powr(__global const float *input0, __global const float *input1,
                               __global float *output, const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = native_powr(input0[i], input1[i]);
}
