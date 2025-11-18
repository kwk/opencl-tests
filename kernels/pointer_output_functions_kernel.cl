// OpenCL Functions with Pointer Outputs
// Reference:
// https://registry.khronos.org/OpenCL/specs/3.0-unified/html/OpenCL_C.html#math-functions

__kernel void test_frexp(__global const float *input, __global float *output,
                         __global int *ptr_output, const unsigned int count) {
    int i = get_global_id(0);
    if (i < count) {
        int exp;
        output[i] = frexp(input[i], &exp);
        ptr_output[i] = exp;
    }
}

__kernel void test_modf(__global const float *input, __global float *output,
                        __global float *ptr_output, const unsigned int count) {
    int i = get_global_id(0);
    if (i < count) {
        float iptr;
        output[i] = modf(input[i], &iptr);
        ptr_output[i] = iptr;
    }
}

__kernel void test_sincos(__global const float *input, __global float *output,
                          __global float *ptr_output, const unsigned int count) {
    int i = get_global_id(0);
    if (i < count) {
        float cosval;
        output[i] = sincos(input[i], &cosval);
        ptr_output[i] = cosval;
    }
}

__kernel void test_remquo(__global const float *input0, __global const float *input1,
                          __global float *output, __global int *ptr_output,
                          const unsigned int count) {
    int i = get_global_id(0);
    if (i < count) {
        int quo;
        output[i] = remquo(input0[i], input1[i], &quo);
        ptr_output[i] = quo;
    }
}

__kernel void test_lgamma_r(__global const float *input, __global float *output,
                            __global int *ptr_output, const unsigned int count) {
    int i = get_global_id(0);
    if (i < count) {
        int signp;
        output[i] = lgamma_r(input[i], &signp);
        ptr_output[i] = signp;
    }
}
