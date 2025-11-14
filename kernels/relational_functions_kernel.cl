// OpenCL Relational Functions
// Reference:
// https://registry.khronos.org/OpenCL/specs/3.0-unified/html/OpenCL_C.html#relational-functions

// Comparison Functions
__kernel void test_isequal(__global const float *x, __global const float *y, __global int *output,
                           const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = isequal(x[i], y[i]);
}

__kernel void test_isnotequal(__global const float *x, __global const float *y,
                              __global int *output, const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = isnotequal(x[i], y[i]);
}

__kernel void test_isgreater(__global const float *x, __global const float *y, __global int *output,
                             const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = isgreater(x[i], y[i]);
}

__kernel void test_isgreaterequal(__global const float *x, __global const float *y,
                                  __global int *output, const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = isgreaterequal(x[i], y[i]);
}

__kernel void test_isless(__global const float *x, __global const float *y, __global int *output,
                          const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = isless(x[i], y[i]);
}

__kernel void test_islessequal(__global const float *x, __global const float *y,
                               __global int *output, const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = islessequal(x[i], y[i]);
}

__kernel void test_islessgreater(__global const float *x, __global const float *y,
                                 __global int *output, const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = islessgreater(x[i], y[i]);
}

__kernel void test_isfinite(__global const float *input, __global int *output,
                            const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = isfinite(input[i]);
}

__kernel void test_isinf(__global const float *input, __global int *output,
                         const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = isinf(input[i]);
}

__kernel void test_isnan(__global const float *input, __global int *output,
                         const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = isnan(input[i]);
}

__kernel void test_isnormal(__global const float *input, __global int *output,
                            const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = isnormal(input[i]);
}

__kernel void test_isordered(__global const float *x, __global const float *y, __global int *output,
                             const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = isordered(x[i], y[i]);
}

__kernel void test_isunordered(__global const float *x, __global const float *y,
                               __global int *output, const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = isunordered(x[i], y[i]);
}

__kernel void test_signbit(__global const float *input, __global int *output,
                           const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = signbit(input[i]);
}

// Logical Functions for vectors
__kernel void test_any_int2(__global const int2 *input, __global int *output,
                            const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = any(input[i]);
}

__kernel void test_any_int4(__global const int4 *input, __global int *output,
                            const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = any(input[i]);
}

__kernel void test_all_int2(__global const int2 *input, __global int *output,
                            const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = all(input[i]);
}

__kernel void test_all_int4(__global const int4 *input, __global int *output,
                            const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = all(input[i]);
}

// Select function
__kernel void test_select_float(__global const float *a, __global const float *b,
                                __global const int *c, __global float *output,
                                const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = select(a[i], b[i], c[i]);
}

__kernel void test_select_int(__global const int *a, __global const int *b, __global const int *c,
                              __global int *output, const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = select(a[i], b[i], c[i]);
}

__kernel void test_bitselect_float(__global const float *a, __global const float *b,
                                   __global const float *c, __global float *output,
                                   const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = bitselect(a[i], b[i], c[i]);
}

__kernel void test_bitselect_int(__global const int *a, __global const int *b,
                                 __global const int *c, __global int *output,
                                 const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = bitselect(a[i], b[i], c[i]);
}
