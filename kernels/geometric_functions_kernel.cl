// OpenCL Geometric Functions
// Reference:
// https://registry.khronos.org/OpenCL/specs/3.0-unified/html/OpenCL_C.html#geometric-functions

__kernel void test_dot_float2(__global const float2 *a, __global const float2 *b,
                              __global float *output, const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = dot(a[i], b[i]);
}

__kernel void test_dot_float3(__global const float3 *a, __global const float3 *b,
                              __global float *output, const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = dot(a[i], b[i]);
}

__kernel void test_dot_float4(__global const float4 *a, __global const float4 *b,
                              __global float *output, const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = dot(a[i], b[i]);
}

__kernel void test_cross(__global const float3 *a, __global const float3 *b,
                         __global float3 *output, const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = cross(a[i], b[i]);
}

__kernel void test_cross_float4(__global const float4 *a, __global const float4 *b,
                                __global float4 *output, const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = cross(a[i], b[i]);
}

__kernel void test_distance_float2(__global const float2 *a, __global const float2 *b,
                                   __global float *output, const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = distance(a[i], b[i]);
}

__kernel void test_distance_float3(__global const float3 *a, __global const float3 *b,
                                   __global float *output, const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = distance(a[i], b[i]);
}

__kernel void test_distance_float4(__global const float4 *a, __global const float4 *b,
                                   __global float *output, const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = distance(a[i], b[i]);
}

__kernel void test_length_float2(__global const float2 *input, __global float *output,
                                 const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = length(input[i]);
}

__kernel void test_length_float3(__global const float3 *input, __global float *output,
                                 const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = length(input[i]);
}

__kernel void test_length_float4(__global const float4 *input, __global float *output,
                                 const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = length(input[i]);
}

__kernel void test_normalize_float2(__global const float2 *input, __global float2 *output,
                                    const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = normalize(input[i]);
}

__kernel void test_normalize_float3(__global const float3 *input, __global float3 *output,
                                    const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = normalize(input[i]);
}

__kernel void test_normalize_float4(__global const float4 *input, __global float4 *output,
                                    const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = normalize(input[i]);
}

__kernel void test_fast_distance_float2(__global const float2 *a, __global const float2 *b,
                                        __global float *output, const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = fast_distance(a[i], b[i]);
}

__kernel void test_fast_distance_float3(__global const float3 *a, __global const float3 *b,
                                        __global float *output, const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = fast_distance(a[i], b[i]);
}

__kernel void test_fast_distance_float4(__global const float4 *a, __global const float4 *b,
                                        __global float *output, const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = fast_distance(a[i], b[i]);
}

__kernel void test_fast_length_float2(__global const float2 *input, __global float *output,
                                      const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = fast_length(input[i]);
}

__kernel void test_fast_length_float3(__global const float3 *input, __global float *output,
                                      const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = fast_length(input[i]);
}

__kernel void test_fast_length_float4(__global const float4 *input, __global float *output,
                                      const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = fast_length(input[i]);
}

__kernel void test_fast_normalize_float2(__global const float2 *input, __global float2 *output,
                                         const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = fast_normalize(input[i]);
}

__kernel void test_fast_normalize_float3(__global const float3 *input, __global float3 *output,
                                         const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = fast_normalize(input[i]);
}

__kernel void test_fast_normalize_float4(__global const float4 *input, __global float4 *output,
                                         const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = fast_normalize(input[i]);
}
