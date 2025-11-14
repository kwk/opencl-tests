/**
 * OpenCL Vector Load and Store Functions Test Kernels
 * Tests vload2/3/4/8/16, vstore2/3/4/8/16 built-in functions
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

// vload3 - load float3 from scalar array at given offset
// Input: scalar float array (6 elements per test)
// Input: size_t offset (which float3 to load: 0 or 1)
// Output: float3 result
__kernel void test_vload3_float(__global const float *input_array,
                                 __global const size_t *input_offset,
                                 __global float3 *output,
                                 const unsigned int count) {
    int i = get_global_id(0);
    if (i < count) {
        // Each test has 6 floats in input_array (starting at i*6)
        // offset indicates which float3 to load (0 loads [0,1,2], 1 loads [3,4,5])
        size_t offset = input_offset[i];
        __global const float *base = &input_array[i * 6];
        output[i] = vload3(offset, base);
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

// vload8 - load float8 from scalar array at given offset
// Input: scalar float array (16 elements per test)
// Input: size_t offset (which float8 to load: 0 or 1)
// Output: float8 result
__kernel void test_vload8_float(__global const float *input_array,
                                 __global const size_t *input_offset,
                                 __global float8 *output,
                                 const unsigned int count) {
    int i = get_global_id(0);
    if (i < count) {
        // Each test has 16 floats in input_array (starting at i*16)
        // offset indicates which float8 to load (0 loads [0-7], 1 loads [8-15])
        size_t offset = input_offset[i];
        __global const float *base = &input_array[i * 16];
        output[i] = vload8(offset, base);
    }
}

// vload16 - load float16 from scalar array at given offset
// Input: scalar float array (32 elements per test)
// Input: size_t offset (which float16 to load: 0 or 1)
// Output: float16 result
__kernel void test_vload16_float(__global const float *input_array,
                                  __global const size_t *input_offset,
                                  __global float16 *output,
                                  const unsigned int count) {
    int i = get_global_id(0);
    if (i < count) {
        // Each test has 32 floats in input_array (starting at i*32)
        // offset indicates which float16 to load (0 loads [0-15], 1 loads [16-31])
        size_t offset = input_offset[i];
        __global const float *base = &input_array[i * 32];
        output[i] = vload16(offset, base);
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

// vstore3 - store float3 to scalar array at given offset
// Input: float3 vector to store
// Input: size_t offset (where to store: 0 stores to [0,1,2], 1 stores to [3,4,5])
// Output: scalar float array (6 elements per test, initialized to 0)
__kernel void test_vstore3_float(__global const float3 *input_vector,
                                  __global const size_t *input_offset,
                                  __global float *output,
                                  const unsigned int count) {
    int i = get_global_id(0);
    if (i < count) {
        // Each test has 6 floats in output (starting at i*6), initialized to 0
        // offset indicates where to store (0 stores to [0,1,2], 1 stores to [3,4,5])
        size_t offset = input_offset[i];
        __global float *base = &output[i * 6];

        // Initialize output array to 0
        for (int j = 0; j < 6; j++) {
            base[j] = 0.0f;
        }

        // Store the vector at the specified offset
        vstore3(input_vector[i], offset, base);
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

// vstore8 - store float8 to scalar array at given offset
// Input: float8 vector to store
// Input: size_t offset (where to store: 0 stores to [0-7], 1 stores to [8-15])
// Output: scalar float array (16 elements per test, initialized to 0)
__kernel void test_vstore8_float(__global const float8 *input_vector,
                                  __global const size_t *input_offset,
                                  __global float *output,
                                  const unsigned int count) {
    int i = get_global_id(0);
    if (i < count) {
        // Each test has 16 floats in output (starting at i*16), initialized to 0
        // offset indicates where to store (0 stores to [0-7], 1 stores to [8-15])
        size_t offset = input_offset[i];
        __global float *base = &output[i * 16];

        // Initialize output array to 0
        for (int j = 0; j < 16; j++) {
            base[j] = 0.0f;
        }

        // Store the vector at the specified offset
        vstore8(input_vector[i], offset, base);
    }
}

// vstore16 - store float16 to scalar array at given offset
// Input: float16 vector to store
// Input: size_t offset (where to store: 0 stores to [0-15], 1 stores to [16-31])
// Output: scalar float array (32 elements per test, initialized to 0)
__kernel void test_vstore16_float(__global const float16 *input_vector,
                                   __global const size_t *input_offset,
                                   __global float *output,
                                   const unsigned int count) {
    int i = get_global_id(0);
    if (i < count) {
        // Each test has 32 floats in output (starting at i*32), initialized to 0
        // offset indicates where to store (0 stores to [0-15], 1 stores to [16-31])
        size_t offset = input_offset[i];
        __global float *base = &output[i * 32];

        // Initialize output array to 0
        for (int j = 0; j < 32; j++) {
            base[j] = 0.0f;
        }

        // Store the vector at the specified offset
        vstore16(input_vector[i], offset, base);
    }
}
