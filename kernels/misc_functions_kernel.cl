/**
 * OpenCL Miscellaneous Functions Test Kernels
 *
 * Tests for printf and other miscellaneous built-in functions
 */

// Printf test: Format integer with %d
__kernel void test_printf_int(__global const int* input, __global int* output,
                              const unsigned int count) {
    int i = get_global_id(0);
    if (i < count) {
        output[i] = printf("%d", input[i]);
    }
}

// Printf test: Format integer with %x (hex)
__kernel void test_printf_hex(__global const int* input, __global int* output,
                              const unsigned int count) {
    int i = get_global_id(0);
    if (i < count) {
        output[i] = printf("%x", input[i]);
    }
}

// Printf test: Format integer with width specifier %4d
__kernel void test_printf_int_width(__global const int* input, __global int* output,
                                    const unsigned int count) {
    int i = get_global_id(0);
    if (i < count) {
        output[i] = printf("%4d", input[i]);
    }
}

// Printf test: Format float with %.2f
__kernel void test_printf_float(__global const float* input, __global int* output,
                                const unsigned int count) {
    int i = get_global_id(0);
    if (i < count) {
        output[i] = printf("%.2f", input[i]);
    }
}

// Printf test: String literal "Hello"
__kernel void test_printf_hello(__global const int* input, __global int* output,
                                const unsigned int count) {
    int i = get_global_id(0);
    if (i < count) {
        output[i] = printf("Hello");
    }
}

// Printf test: String literal "Hello, World!"
__kernel void test_printf_hello_world(__global const int* input, __global int* output,
                                      const unsigned int count) {
    int i = get_global_id(0);
    if (i < count) {
        output[i] = printf("Hello, World!");
    }
}

// Printf test: Newline
__kernel void test_printf_newline(__global const int* input, __global int* output,
                                  const unsigned int count) {
    int i = get_global_id(0);
    if (i < count) {
        output[i] = printf("\n");
    }
}

// Printf test: Mixed format "Value is %d"
__kernel void test_printf_value(__global const int* input, __global int* output,
                                const unsigned int count) {
    int i = get_global_id(0);
    if (i < count) {
        output[i] = printf("Value is %d", input[i]);
    }
}

// Printf test: Multiple format specifiers "Number: %d (0x%x)"
__kernel void test_printf_multi(__global const int* input, __global int* output,
                                const unsigned int count) {
    int i = get_global_id(0);
    if (i < count) {
        output[i] = printf("Number: %d (0x%x)", input[i], input[i]);
    }
}
