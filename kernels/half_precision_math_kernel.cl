// OpenCL Half-Precision Math Functions
// These functions use float inputs/outputs but with reduced precision (≤ 8192 ULP)
// Reference: https://registry.khronos.org/OpenCL/specs/3.0-unified/html/OpenCL_C.html#math-functions

// Single-input functions
__kernel void test_half_cos(__global const float *input, __global float *output,
                            const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = half_cos(input[i]);
}

__kernel void test_half_sin(__global const float *input, __global float *output,
                            const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = half_sin(input[i]);
}

__kernel void test_half_tan(__global const float *input, __global float *output,
                            const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = half_tan(input[i]);
}

__kernel void test_half_exp(__global const float *input, __global float *output,
                            const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = half_exp(input[i]);
}

__kernel void test_half_exp2(__global const float *input, __global float *output,
                             const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = half_exp2(input[i]);
}

__kernel void test_half_exp10(__global const float *input, __global float *output,
                              const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = half_exp10(input[i]);
}

__kernel void test_half_log(__global const float *input, __global float *output,
                            const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = half_log(input[i]);
}

__kernel void test_half_log2(__global const float *input, __global float *output,
                             const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = half_log2(input[i]);
}

__kernel void test_half_log10(__global const float *input, __global float *output,
                              const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = half_log10(input[i]);
}

__kernel void test_half_sqrt(__global const float *input, __global float *output,
                             const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = half_sqrt(input[i]);
}

__kernel void test_half_rsqrt(__global const float *input, __global float *output,
                              const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = half_rsqrt(input[i]);
}

__kernel void test_half_recip(__global const float *input, __global float *output,
                              const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = half_recip(input[i]);
}

// Two-input functions
__kernel void test_half_divide(__global const float *input0, __global const float *input1,
                               __global float *output, const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = half_divide(input0[i], input1[i]);
}

__kernel void test_half_powr(__global const float *input0, __global const float *input1,
                             __global float *output, const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = half_powr(input0[i], input1[i]);
}
