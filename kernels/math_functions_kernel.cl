// OpenCL Math Functions - Built-in Scalar and Vector Math Functions
// Reference:
// https://registry.khronos.org/OpenCL/specs/3.0-unified/html/OpenCL_C.html#math-functions

// Trigonometric Functions
__kernel void test_acos(__global const float *input, __global float *output,
                        const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = acos(input[i]);
}

__kernel void test_asin(__global const float *input, __global float *output,
                        const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = asin(input[i]);
}

__kernel void test_atan(__global const float *input, __global float *output,
                        const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = atan(input[i]);
}

__kernel void test_atan2(__global const float *y, __global const float *x, __global float *output,
                         const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = atan2(y[i], x[i]);
}

__kernel void test_cos(__global const float *input, __global float *output,
                       const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = cos(input[i]);
}

__kernel void test_sin(__global const float *input, __global float *output,
                       const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = sin(input[i]);
}

__kernel void test_tan(__global const float *input, __global float *output,
                       const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = tan(input[i]);
}

// Hyperbolic Functions
__kernel void test_acosh(__global const float *input, __global float *output,
                         const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = acosh(input[i]);
}

__kernel void test_asinh(__global const float *input, __global float *output,
                         const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = asinh(input[i]);
}

__kernel void test_atanh(__global const float *input, __global float *output,
                         const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = atanh(input[i]);
}

__kernel void test_cosh(__global const float *input, __global float *output,
                        const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = cosh(input[i]);
}

__kernel void test_sinh(__global const float *input, __global float *output,
                        const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = sinh(input[i]);
}

__kernel void test_tanh(__global const float *input, __global float *output,
                        const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = tanh(input[i]);
}

// Exponential and Logarithmic Functions
__kernel void test_exp(__global const float *input, __global float *output,
                       const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = exp(input[i]);
}

__kernel void test_exp2(__global const float *input, __global float *output,
                        const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = exp2(input[i]);
}

__kernel void test_exp10(__global const float *input, __global float *output,
                         const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = exp10(input[i]);
}

__kernel void test_expm1(__global const float *input, __global float *output,
                         const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = expm1(input[i]);
}

__kernel void test_log(__global const float *input, __global float *output,
                       const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = log(input[i]);
}

__kernel void test_log2(__global const float *input, __global float *output,
                        const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = log2(input[i]);
}

__kernel void test_log10(__global const float *input, __global float *output,
                         const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = log10(input[i]);
}

__kernel void test_log1p(__global const float *input, __global float *output,
                         const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = log1p(input[i]);
}

// Power Functions
__kernel void test_cbrt(__global const float *input, __global float *output,
                        const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = cbrt(input[i]);
}

__kernel void test_pow(__global const float *x, __global const float *y, __global float *output,
                       const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = pow(x[i], y[i]);
}

__kernel void test_pown(__global const float *x, __global const int *y, __global float *output,
                        const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = pown(x[i], y[i]);
}

__kernel void test_powr(__global const float *x, __global const float *y, __global float *output,
                        const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = powr(x[i], y[i]);
}

__kernel void test_sqrt(__global const float *input, __global float *output,
                        const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = sqrt(input[i]);
}

__kernel void test_rsqrt(__global const float *input, __global float *output,
                         const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = rsqrt(input[i]);
}

// Rounding and Remainder Functions
__kernel void test_ceil(__global const float *input, __global float *output,
                        const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = ceil(input[i]);
}

__kernel void test_floor(__global const float *input, __global float *output,
                         const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = floor(input[i]);
}

__kernel void test_fmod(__global const float *x, __global const float *y, __global float *output,
                        const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = fmod(x[i], y[i]);
}

__kernel void test_remainder(__global const float *x, __global const float *y,
                             __global float *output, const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = remainder(x[i], y[i]);
}

__kernel void test_rint(__global const float *input, __global float *output,
                        const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = rint(input[i]);
}

__kernel void test_round(__global const float *input, __global float *output,
                         const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = round(input[i]);
}

__kernel void test_trunc(__global const float *input, __global float *output,
                         const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = trunc(input[i]);
}

// Other Math Functions
__kernel void test_fabs(__global const float *input, __global float *output,
                        const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = fabs(input[i]);
}

__kernel void test_fmax(__global const float *x, __global const float *y, __global float *output,
                        const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = fmax(x[i], y[i]);
}

__kernel void test_fmin(__global const float *x, __global const float *y, __global float *output,
                        const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = fmin(x[i], y[i]);
}

__kernel void test_fma(__global const float *a, __global const float *b, __global const float *c,
                       __global float *output, const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = fma(a[i], b[i], c[i]);
}

__kernel void test_hypot(__global const float *x, __global const float *y, __global float *output,
                         const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = hypot(x[i], y[i]);
}

__kernel void test_erf(__global const float *input, __global float *output,
                       const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = erf(input[i]);
}

__kernel void test_erfc(__global const float *input, __global float *output,
                        const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = erfc(input[i]);
}

__kernel void test_tgamma(__global const float *input, __global float *output,
                          const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = tgamma(input[i]);
}

__kernel void test_lgamma(__global const float *input, __global float *output,
                          const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = lgamma(input[i]);
}

// Native Functions (fast, lower precision variants)
__kernel void test_native_exp(__global const float *input, __global float *output,
                              const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = native_exp(input[i]);
}

__kernel void test_native_exp2(__global const float *input, __global float *output,
                               const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = native_exp2(input[i]);
}

__kernel void test_native_exp10(__global const float *input, __global float *output,
                                const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = native_exp10(input[i]);
}

__kernel void test_native_log(__global const float *input, __global float *output,
                              const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = native_log(input[i]);
}

__kernel void test_native_log2(__global const float *input, __global float *output,
                               const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = native_log2(input[i]);
}

__kernel void test_native_log10(__global const float *input, __global float *output,
                                const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = native_log10(input[i]);
}

__kernel void test_native_sqrt(__global const float *input, __global float *output,
                               const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = native_sqrt(input[i]);
}

__kernel void test_native_rsqrt(__global const float *input, __global float *output,
                                const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = native_rsqrt(input[i]);
}

// Phase 1 additions - Pi variants
__kernel void test_acospi(__global const float *input, __global float *output,
                          const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = acospi(input[i]);
}

__kernel void test_asinpi(__global const float *input, __global float *output,
                          const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = asinpi(input[i]);
}

__kernel void test_atanpi(__global const float *input, __global float *output,
                          const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = atanpi(input[i]);
}

__kernel void test_atan2pi(__global const float *y, __global const float *x,
                           __global float *output, const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = atan2pi(y[i], x[i]);
}

__kernel void test_cospi(__global const float *input, __global float *output,
                         const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = cospi(input[i]);
}

__kernel void test_sinpi(__global const float *input, __global float *output,
                         const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = sinpi(input[i]);
}

__kernel void test_tanpi(__global const float *input, __global float *output,
                         const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = tanpi(input[i]);
}

// Phase 1 additions - Math other functions
__kernel void test_copysign(__global const float *x, __global const float *y,
                            __global float *output, const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = copysign(x[i], y[i]);
}

__kernel void test_fdim(__global const float *x, __global const float *y,
                        __global float *output, const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = fdim(x[i], y[i]);
}

__kernel void test_fract(__global const float *input, __global float *output,
                         const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = fract(input[i], (__global float*)0);
}

__kernel void test_ilogb(__global const float *input, __global int *output,
                         const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = ilogb(input[i]);
}

__kernel void test_ldexp(__global const float *x, __global const int *n,
                         __global float *output, const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = ldexp(x[i], n[i]);
}

__kernel void test_logb(__global const float *input, __global float *output,
                        const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = logb(input[i]);
}

__kernel void test_mad(__global const float *a, __global const float *b,
                       __global const float *c, __global float *output,
                       const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = mad(a[i], b[i], c[i]);
}

__kernel void test_maxmag(__global const float *x, __global const float *y,
                          __global float *output, const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = maxmag(x[i], y[i]);
}

__kernel void test_minmag(__global const float *x, __global const float *y,
                          __global float *output, const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = minmag(x[i], y[i]);
}

__kernel void test_nan(__global const unsigned int *input, __global float *output,
                       const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = nan(input[i]);
}

__kernel void test_nextafter(__global const float *x, __global const float *y,
                             __global float *output, const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = nextafter(x[i], y[i]);
}

__kernel void test_rootn(__global const float *x, __global const int *n,
                         __global float *output, const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = rootn(x[i], n[i]);
}
