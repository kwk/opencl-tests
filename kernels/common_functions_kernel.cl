// OpenCL Common Functions
// Reference: https://registry.khronos.org/OpenCL/specs/3.0-unified/html/OpenCL_C.html#common-functions

__kernel void test_clamp_float(__global const float* x, __global const float* minval, __global const float* maxval, __global float* output, const unsigned int count) {
    int i = get_global_id(0);
    if (i < count) output[i] = clamp(x[i], minval[i], maxval[i]);
}

__kernel void test_clamp_float2(__global const float2* x, __global const float2* minval, __global const float2* maxval, __global float2* output, const unsigned int count) {
    int i = get_global_id(0);
    if (i < count) output[i] = clamp(x[i], minval[i], maxval[i]);
}

__kernel void test_degrees(__global const float* input, __global float* output, const unsigned int count) {
    int i = get_global_id(0);
    if (i < count) output[i] = degrees(input[i]);
}

__kernel void test_max_float(__global const float* x, __global const float* y, __global float* output, const unsigned int count) {
    int i = get_global_id(0);
    if (i < count) output[i] = max(x[i], y[i]);
}

__kernel void test_max_float2(__global const float2* x, __global const float2* y, __global float2* output, const unsigned int count) {
    int i = get_global_id(0);
    if (i < count) output[i] = max(x[i], y[i]);
}

__kernel void test_min_float(__global const float* x, __global const float* y, __global float* output, const unsigned int count) {
    int i = get_global_id(0);
    if (i < count) output[i] = min(x[i], y[i]);
}

__kernel void test_min_float2(__global const float2* x, __global const float2* y, __global float2* output, const unsigned int count) {
    int i = get_global_id(0);
    if (i < count) output[i] = min(x[i], y[i]);
}

__kernel void test_mix(__global const float* x, __global const float* y, __global const float* a, __global float* output, const unsigned int count) {
    int i = get_global_id(0);
    if (i < count) output[i] = mix(x[i], y[i], a[i]);
}

__kernel void test_radians(__global const float* input, __global float* output, const unsigned int count) {
    int i = get_global_id(0);
    if (i < count) output[i] = radians(input[i]);
}

__kernel void test_step(__global const float* edge, __global const float* x, __global float* output, const unsigned int count) {
    int i = get_global_id(0);
    if (i < count) output[i] = step(edge[i], x[i]);
}

__kernel void test_smoothstep(__global const float* edge0, __global const float* edge1, __global const float* x, __global float* output, const unsigned int count) {
    int i = get_global_id(0);
    if (i < count) output[i] = smoothstep(edge0[i], edge1[i], x[i]);
}

__kernel void test_sign(__global const float* input, __global float* output, const unsigned int count) {
    int i = get_global_id(0);
    if (i < count) output[i] = sign(input[i]);
}
