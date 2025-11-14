// OpenCL Integer Functions
// Reference: https://registry.khronos.org/OpenCL/specs/3.0-unified/html/OpenCL_C.html#integer-functions

__kernel void test_abs_int(__global const int* input, __global uint* output, const unsigned int count) {
    int i = get_global_id(0);
    if (i < count) output[i] = abs(input[i]);
}

__kernel void test_abs_diff_int(__global const int* x, __global const int* y, __global uint* output, const unsigned int count) {
    int i = get_global_id(0);
    if (i < count) output[i] = abs_diff(x[i], y[i]);
}

__kernel void test_abs_diff_uint(__global const uint* x, __global const uint* y, __global uint* output, const unsigned int count) {
    int i = get_global_id(0);
    if (i < count) output[i] = abs_diff(x[i], y[i]);
}

__kernel void test_add_sat_int(__global const int* x, __global const int* y, __global int* output, const unsigned int count) {
    int i = get_global_id(0);
    if (i < count) output[i] = add_sat(x[i], y[i]);
}

__kernel void test_add_sat_uint(__global const uint* x, __global const uint* y, __global uint* output, const unsigned int count) {
    int i = get_global_id(0);
    if (i < count) output[i] = add_sat(x[i], y[i]);
}

__kernel void test_hadd_int(__global const int* x, __global const int* y, __global int* output, const unsigned int count) {
    int i = get_global_id(0);
    if (i < count) output[i] = hadd(x[i], y[i]);
}

__kernel void test_rhadd_int(__global const int* x, __global const int* y, __global int* output, const unsigned int count) {
    int i = get_global_id(0);
    if (i < count) output[i] = rhadd(x[i], y[i]);
}

__kernel void test_clz_int(__global const int* input, __global int* output, const unsigned int count) {
    int i = get_global_id(0);
    if (i < count) output[i] = clz(input[i]);
}

// Note: ctz (count trailing zeros) is not supported in Mesa Rusticl OpenCL 3.0
// __kernel void test_ctz_int(__global const int* input, __global int* output, const unsigned int count) {
//     int i = get_global_id(0);
//     if (i < count) output[i] = ctz(input[i]);
// }

__kernel void test_mad_hi_int(__global const int* a, __global const int* b, __global const int* c, __global int* output, const unsigned int count) {
    int i = get_global_id(0);
    if (i < count) output[i] = mad_hi(a[i], b[i], c[i]);
}

__kernel void test_mad_sat_int(__global const int* a, __global const int* b, __global const int* c, __global int* output, const unsigned int count) {
    int i = get_global_id(0);
    if (i < count) output[i] = mad_sat(a[i], b[i], c[i]);
}

__kernel void test_max_int(__global const int* x, __global const int* y, __global int* output, const unsigned int count) {
    int i = get_global_id(0);
    if (i < count) output[i] = max(x[i], y[i]);
}

__kernel void test_max_uint(__global const uint* x, __global const uint* y, __global uint* output, const unsigned int count) {
    int i = get_global_id(0);
    if (i < count) output[i] = max(x[i], y[i]);
}

__kernel void test_min_int(__global const int* x, __global const int* y, __global int* output, const unsigned int count) {
    int i = get_global_id(0);
    if (i < count) output[i] = min(x[i], y[i]);
}

__kernel void test_min_uint(__global const uint* x, __global const uint* y, __global uint* output, const unsigned int count) {
    int i = get_global_id(0);
    if (i < count) output[i] = min(x[i], y[i]);
}

__kernel void test_mul_hi_int(__global const int* x, __global const int* y, __global int* output, const unsigned int count) {
    int i = get_global_id(0);
    if (i < count) output[i] = mul_hi(x[i], y[i]);
}

__kernel void test_rotate_int(__global const int* v, __global const int* i, __global int* output, const unsigned int count) {
    int idx = get_global_id(0);
    if (idx < count) output[idx] = rotate(v[idx], i[idx]);
}

__kernel void test_sub_sat_int(__global const int* x, __global const int* y, __global int* output, const unsigned int count) {
    int i = get_global_id(0);
    if (i < count) output[i] = sub_sat(x[i], y[i]);
}

__kernel void test_popcount_int(__global const int* input, __global int* output, const unsigned int count) {
    int i = get_global_id(0);
    if (i < count) output[i] = popcount(input[i]);
}

__kernel void test_mad24_int(__global const int* a, __global const int* b, __global const int* c, __global int* output, const unsigned int count) {
    int i = get_global_id(0);
    if (i < count) output[i] = mad24(a[i], b[i], c[i]);
}

__kernel void test_mul24_int(__global const int* x, __global const int* y, __global int* output, const unsigned int count) {
    int i = get_global_id(0);
    if (i < count) output[i] = mul24(x[i], y[i]);
}
