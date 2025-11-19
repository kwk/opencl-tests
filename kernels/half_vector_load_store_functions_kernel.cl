/**
 * OpenCL Half-Precision Vector Load and Store Functions Test Kernels
 * Tests vload_half*, vstore_half*, vloada_half*, vstorea_half* functions
 */

// ============================================================================
// vload_half* - Load half precision values, convert to float
// ============================================================================

// vload_half - load single half, return as float
// Input: half array (4 elements per test)
// Input: size_t offset (which half to load)
// Output: float result
__kernel void test_vload_half(__global const half *input_array,
                               __global const size_t *input_offset,
                               __global float *output,
                               const unsigned int count) {
    int i = get_global_id(0);
    if (i < count) {
        size_t offset = input_offset[i];
        __global const half *base = &input_array[i * 4];
        output[i] = vload_half(offset, base);
    }
}

// vload_half2 - load float2 from half array
__kernel void test_vload_half2(__global const half *input_array,
                                __global const size_t *input_offset,
                                __global float2 *output,
                                const unsigned int count) {
    int i = get_global_id(0);
    if (i < count) {
        size_t offset = input_offset[i];
        __global const half *base = &input_array[i * 4];
        output[i] = vload_half2(offset, base);
    }
}

// vload_half3 - load float3 from half array
__kernel void test_vload_half3(__global const half *input_array,
                                __global const size_t *input_offset,
                                __global float3 *output,
                                const unsigned int count) {
    int i = get_global_id(0);
    if (i < count) {
        size_t offset = input_offset[i];
        __global const half *base = &input_array[i * 6];
        output[i] = vload_half3(offset, base);
    }
}

// vload_half4 - load float4 from half array
__kernel void test_vload_half4(__global const half *input_array,
                                __global const size_t *input_offset,
                                __global float4 *output,
                                const unsigned int count) {
    int i = get_global_id(0);
    if (i < count) {
        size_t offset = input_offset[i];
        __global const half *base = &input_array[i * 8];
        output[i] = vload_half4(offset, base);
    }
}

// vload_half8 - load float8 from half array
__kernel void test_vload_half8(__global const half *input_array,
                                __global const size_t *input_offset,
                                __global float8 *output,
                                const unsigned int count) {
    int i = get_global_id(0);
    if (i < count) {
        size_t offset = input_offset[i];
        __global const half *base = &input_array[i * 16];
        output[i] = vload_half8(offset, base);
    }
}

// vload_half16 - load float16 from half array
__kernel void test_vload_half16(__global const half *input_array,
                                 __global const size_t *input_offset,
                                 __global float16 *output,
                                 const unsigned int count) {
    int i = get_global_id(0);
    if (i < count) {
        size_t offset = input_offset[i];
        __global const half *base = &input_array[i * 32];
        output[i] = vload_half16(offset, base);
    }
}

// ============================================================================
// vstore_half* - Store float values as half precision
// ============================================================================

// vstore_half - store single float as half
// Input: float value to store
// Input: size_t offset (where to store in output array)
// Output: half array (4 elements per test)
__kernel void test_vstore_half(__global const float *input_value,
                                __global const size_t *input_offset,
                                __global half *output,
                                const unsigned int count) {
    int i = get_global_id(0);
    if (i < count) {
        float value = input_value[i];
        size_t offset = input_offset[i];
        __global half *base = &output[i * 4];
        // Initialize output to zero using vstore_half
        for (int j = 0; j < 4; j++) {
            vstore_half(0.0f, j, base);
        }
        vstore_half(value, offset, base);
    }
}

// vstore_half2 - store float2 as half array
__kernel void test_vstore_half2(__global const float2 *input_vector,
                                 __global const size_t *input_offset,
                                 __global half *output,
                                 const unsigned int count) {
    int i = get_global_id(0);
    if (i < count) {
        float2 vector = input_vector[i];
        size_t offset = input_offset[i];
        __global half *base = &output[i * 4];
        // Initialize output to zero using vstore_half
        for (int j = 0; j < 4; j++) {
            vstore_half(0.0f, j, base);
        }
        vstore_half2(vector, offset, base);
    }
}

// vstore_half3 - store float3 as half array
__kernel void test_vstore_half3(__global const float3 *input_vector,
                                 __global const size_t *input_offset,
                                 __global half *output,
                                 const unsigned int count) {
    int i = get_global_id(0);
    if (i < count) {
        float3 vector = input_vector[i];
        size_t offset = input_offset[i];
        __global half *base = &output[i * 6];
        // Initialize output to zero using vstore_half
        for (int j = 0; j < 6; j++) {
            vstore_half(0.0f, j, base);
        }
        vstore_half3(vector, offset, base);
    }
}

// vstore_half4 - store float4 as half array
__kernel void test_vstore_half4(__global const float4 *input_vector,
                                 __global const size_t *input_offset,
                                 __global half *output,
                                 const unsigned int count) {
    int i = get_global_id(0);
    if (i < count) {
        float4 vector = input_vector[i];
        size_t offset = input_offset[i];
        __global half *base = &output[i * 8];
        // Initialize output to zero using vstore_half
        for (int j = 0; j < 8; j++) {
            vstore_half(0.0f, j, base);
        }
        vstore_half4(vector, offset, base);
    }
}

// vstore_half8 - store float8 as half array
__kernel void test_vstore_half8(__global const float8 *input_vector,
                                 __global const size_t *input_offset,
                                 __global half *output,
                                 const unsigned int count) {
    int i = get_global_id(0);
    if (i < count) {
        float8 vector = input_vector[i];
        size_t offset = input_offset[i];
        __global half *base = &output[i * 16];
        // Initialize output to zero using vstore_half
        for (int j = 0; j < 16; j++) {
            vstore_half(0.0f, j, base);
        }
        vstore_half8(vector, offset, base);
    }
}

// vstore_half16 - store float16 as half array
__kernel void test_vstore_half16(__global const float16 *input_vector,
                                  __global const size_t *input_offset,
                                  __global half *output,
                                  const unsigned int count) {
    int i = get_global_id(0);
    if (i < count) {
        float16 vector = input_vector[i];
        size_t offset = input_offset[i];
        __global half *base = &output[i * 32];
        // Initialize output to zero using vstore_half
        for (int j = 0; j < 32; j++) {
            vstore_half(0.0f, j, base);
        }
        vstore_half16(vector, offset, base);
    }
}

// ============================================================================
// vloada_half* - Aligned half precision loads
// ============================================================================

// vloada_half2 - aligned load of float2 from half array
__kernel void test_vloada_half2(__global const half *input_array,
                                 __global const size_t *input_offset,
                                 __global float2 *output,
                                 const unsigned int count) {
    int i = get_global_id(0);
    if (i < count) {
        size_t offset = input_offset[i];
        __global const half *base = &input_array[i * 4];
        output[i] = vloada_half2(offset, base);
    }
}

// vloada_half3 - aligned load of float3 from half array
__kernel void test_vloada_half3(__global const half *input_array,
                                 __global const size_t *input_offset,
                                 __global float3 *output,
                                 const unsigned int count) {
    int i = get_global_id(0);
    if (i < count) {
        size_t offset = input_offset[i];
        __global const half *base = &input_array[i * 6];
        output[i] = vloada_half3(offset, base);
    }
}

// vloada_half4 - aligned load of float4 from half array
__kernel void test_vloada_half4(__global const half *input_array,
                                 __global const size_t *input_offset,
                                 __global float4 *output,
                                 const unsigned int count) {
    int i = get_global_id(0);
    if (i < count) {
        size_t offset = input_offset[i];
        __global const half *base = &input_array[i * 8];
        output[i] = vloada_half4(offset, base);
    }
}

// vloada_half8 - aligned load of float8 from half array
__kernel void test_vloada_half8(__global const half *input_array,
                                 __global const size_t *input_offset,
                                 __global float8 *output,
                                 const unsigned int count) {
    int i = get_global_id(0);
    if (i < count) {
        size_t offset = input_offset[i];
        __global const half *base = &input_array[i * 16];
        output[i] = vloada_half8(offset, base);
    }
}

// vloada_half16 - aligned load of float16 from half array
__kernel void test_vloada_half16(__global const half *input_array,
                                  __global const size_t *input_offset,
                                  __global float16 *output,
                                  const unsigned int count) {
    int i = get_global_id(0);
    if (i < count) {
        size_t offset = input_offset[i];
        __global const half *base = &input_array[i * 32];
        output[i] = vloada_half16(offset, base);
    }
}

// ============================================================================
// vstorea_half* - Aligned half precision stores
// ============================================================================

// vstorea_half2 - aligned store of float2 as half array
__kernel void test_vstorea_half2(__global const float2 *input_vector,
                                  __global const size_t *input_offset,
                                  __global half *output,
                                  const unsigned int count) {
    int i = get_global_id(0);
    if (i < count) {
        float2 vector = input_vector[i];
        size_t offset = input_offset[i];
        __global half *base = &output[i * 4];
        // Initialize output to zero using vstore_half
        for (int j = 0; j < 4; j++) {
            vstore_half(0.0f, j, base);
        }
        vstorea_half2(vector, offset, base);
    }
}

// vstorea_half3 - aligned store of float3 as half array
__kernel void test_vstorea_half3(__global const float3 *input_vector,
                                  __global const size_t *input_offset,
                                  __global half *output,
                                  const unsigned int count) {
    int i = get_global_id(0);
    if (i < count) {
        float3 vector = input_vector[i];
        size_t offset = input_offset[i];
        __global half *base = &output[i * 6];
        // Initialize output to zero using vstore_half
        for (int j = 0; j < 6; j++) {
            vstore_half(0.0f, j, base);
        }
        vstorea_half3(vector, offset, base);
    }
}

// vstorea_half4 - aligned store of float4 as half array
__kernel void test_vstorea_half4(__global const float4 *input_vector,
                                  __global const size_t *input_offset,
                                  __global half *output,
                                  const unsigned int count) {
    int i = get_global_id(0);
    if (i < count) {
        float4 vector = input_vector[i];
        size_t offset = input_offset[i];
        __global half *base = &output[i * 8];
        // Initialize output to zero using vstore_half
        for (int j = 0; j < 8; j++) {
            vstore_half(0.0f, j, base);
        }
        vstorea_half4(vector, offset, base);
    }
}

// vstorea_half8 - aligned store of float8 as half array
__kernel void test_vstorea_half8(__global const float8 *input_vector,
                                  __global const size_t *input_offset,
                                  __global half *output,
                                  const unsigned int count) {
    int i = get_global_id(0);
    if (i < count) {
        float8 vector = input_vector[i];
        size_t offset = input_offset[i];
        __global half *base = &output[i * 16];
        // Initialize output to zero using vstore_half
        for (int j = 0; j < 16; j++) {
            vstore_half(0.0f, j, base);
        }
        vstorea_half8(vector, offset, base);
    }
}

// vstorea_half16 - aligned store of float16 as half array
__kernel void test_vstorea_half16(__global const float16 *input_vector,
                                   __global const size_t *input_offset,
                                   __global half *output,
                                   const unsigned int count) {
    int i = get_global_id(0);
    if (i < count) {
        float16 vector = input_vector[i];
        size_t offset = input_offset[i];
        __global half *base = &output[i * 32];
        // Initialize output to zero using vstore_half
        for (int j = 0; j < 32; j++) {
            vstore_half(0.0f, j, base);
        }
        vstorea_half16(vector, offset, base);
    }
}
