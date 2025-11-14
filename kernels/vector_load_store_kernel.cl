/**
 * OpenCL Vector Load and Store Functions Test Kernels
 * Tests vload2, vload4, vstore2, vstore4 built-in functions
 */

// vload2 - load float2 from scalar array at given offset
// Input: scalar float array (4 elements per test)
// Input: size_t offset (which float2 to load: 0 or 1)
// Output: float2 result
__kernel void test_vload2_float(__global const float *input_array,
                                 __global const size_t *input_offset,
                                 __global float2 *output,
                                 const unsigned int count) {
    int i = get_global_id(0);
    if (i < count) {
        // Each test has 4 floats in input_array (starting at i*4)
        // offset indicates which float2 to load (0 loads [0,1], 1 loads [2,3])
        size_t offset = input_offset[i];
        __global const float *base = &input_array[i * 4];
        output[i] = vload2(offset, base);
    }
}

// vload4 - load float4 from scalar array at given offset
// Input: scalar float array (8 elements per test)
// Input: size_t offset (which float4 to load: 0 or 1)
// Output: float4 result
__kernel void test_vload4_float(__global const float *input_array,
                                 __global const size_t *input_offset,
                                 __global float4 *output,
                                 const unsigned int count) {
    int i = get_global_id(0);
    if (i < count) {
        // Each test has 8 floats in input_array (starting at i*8)
        // offset indicates which float4 to load (0 loads [0-3], 1 loads [4-7])
        size_t offset = input_offset[i];
        __global const float *base = &input_array[i * 8];
        output[i] = vload4(offset, base);
    }
}

// vstore2 - store float2 to scalar array at given offset
// Input: float2 vector to store
// Input: size_t offset (where to store: 0 stores to [0,1], 1 stores to [2,3])
// Output: scalar float array (4 elements per test, initialized to 0)
__kernel void test_vstore2_float(__global const float2 *input_vector,
                                  __global const size_t *input_offset,
                                  __global float *output,
                                  const unsigned int count) {
    int i = get_global_id(0);
    if (i < count) {
        // Each test has 4 floats in output (starting at i*4), initialized to 0
        // offset indicates where to store (0 stores to [0,1], 1 stores to [2,3])
        size_t offset = input_offset[i];
        __global float *base = &output[i * 4];

        // Initialize output array to 0
        for (int j = 0; j < 4; j++) {
            base[j] = 0.0f;
        }

        // Store the vector at the specified offset
        vstore2(input_vector[i], offset, base);
    }
}

// vstore4 - store float4 to scalar array at given offset
// Input: float4 vector to store
// Input: size_t offset (where to store: 0 stores to [0-3], 1 stores to [4-7])
// Output: scalar float array (8 elements per test, initialized to 0)
__kernel void test_vstore4_float(__global const float4 *input_vector,
                                  __global const size_t *input_offset,
                                  __global float *output,
                                  const unsigned int count) {
    int i = get_global_id(0);
    if (i < count) {
        // Each test has 8 floats in output (starting at i*8), initialized to 0
        // offset indicates where to store (0 stores to [0-3], 1 stores to [4-7])
        size_t offset = input_offset[i];
        __global float *base = &output[i * 8];

        // Initialize output array to 0
        for (int j = 0; j < 8; j++) {
            base[j] = 0.0f;
        }

        // Store the vector at the specified offset
        vstore4(input_vector[i], offset, base);
    }
}
