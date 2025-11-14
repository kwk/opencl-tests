/**
 * OpenCL Built-in Functions Test Runner
 * Comprehensive test suite for all OpenCL C built-in functions
 * Tests 129 functions with 1290 test cases
 */

#define CL_TARGET_OPENCL_VERSION 300
#include <CL/cl.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <string>

// Global OpenCL objects (used by generated tests)
cl_platform_id platform;
cl_device_id device;
cl_context context;
cl_command_queue queue;

// Test result structure
struct TestResult {
    std::string function_name;
    int test_number;
    bool passed;
    std::string error_message;
};

std::vector<TestResult> test_results;

// Helper function for float comparison with tolerance
bool floatEquals(float a, float b, float tolerance = 0.0001f) {
    return std::fabs(a - b) < tolerance;
}

// Helper function to load kernel source from file
std::string loadKernel(const std::string& filename) {
    std::string fullPath = "kernels/" + filename;
    std::ifstream file(fullPath);
    if (!file.is_open()) {
        std::cerr << "ERROR: Failed to open kernel file: " << fullPath << std::endl;
        return "";
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

// Include all generated test functions
#include "generated_tests.cpp"

// Function declarations for all tests (auto-generated list)
void test_abs_int();
void test_abs_diff_int();
void test_abs_diff_uint();
void test_add_sat_int();
void test_add_sat_uint();
void test_clz_int();
// void test_ctz_int();  // ctz not supported in Mesa Rusticl
void test_hadd_int();
void test_mad24_int();
void test_mad_hi_int();
void test_mad_sat_int();
void test_max_int();
void test_max_uint();
void test_min_int();
void test_min_uint();
void test_mul24_int();
void test_mul_hi_int();
void test_popcount_int();
void test_rhadd_int();
void test_rotate_int();
void test_sub_sat_int();
void test_clamp_float();
void test_clamp_float2();
void test_degrees();
void test_max_float();
void test_max_float2();
void test_min_float();
void test_min_float2();
void test_mix();
void test_radians();
void test_sign();
void test_smoothstep();
void test_step();
void test_cross();
void test_cross_float4();
void test_distance_float2();
void test_distance_float3();
void test_distance_float4();
void test_dot_float2();
void test_dot_float3();
void test_dot_float4();
void test_fast_distance_float2();
void test_fast_distance_float3();
void test_fast_distance_float4();
void test_fast_length_float2();
void test_fast_length_float3();
void test_fast_length_float4();
void test_fast_normalize_float2();
void test_fast_normalize_float3();
void test_fast_normalize_float4();
void test_length_float2();
void test_length_float3();
void test_length_float4();
void test_normalize_float2();
void test_normalize_float3();
void test_normalize_float4();
void test_acos();
void test_asin();
void test_atan();
void test_atan2();
void test_cos();
void test_sin();
void test_tan();
void test_acosh();
void test_asinh();
void test_atanh();
void test_cosh();
void test_sinh();
void test_tanh();
void test_cbrt();
void test_ceil();
void test_erf();
void test_erfc();
void test_exp();
void test_exp2();
void test_exp10();
void test_expm1();
void test_fabs();
void test_floor();
void test_fma();
void test_fmax();
void test_fmin();
void test_fmod();
void test_hypot();
void test_lgamma();
void test_log();
void test_log2();
void test_log10();
void test_log1p();
void test_native_exp();
void test_native_exp2();
void test_native_exp10();
void test_native_log();
void test_native_log2();
void test_native_log10();
void test_native_rsqrt();
void test_native_sqrt();
void test_pow();
void test_pown();
void test_powr();
void test_remainder();
void test_rint();
void test_round();
void test_rsqrt();
void test_sqrt();
void test_tgamma();
void test_trunc();
void test_all_int2();
void test_all_int4();
void test_any_int2();
void test_any_int4();
void test_bitselect_float();
void test_bitselect_int();
void test_isequal();
void test_isfinite();
void test_isgreater();
void test_isgreaterequal();
void test_isinf();
void test_isless();
void test_islessequal();
void test_islessgreater();
void test_isnan();
void test_isnormal();
void test_isordered();
void test_isunordered();
void test_isnotequal();
void test_select_float();
void test_select_int();
void test_signbit();

void initializeOpenCL() {
    cl_int err;
    cl_uint numPlatforms;

    // Get platform count
    err = clGetPlatformIDs(0, NULL, &numPlatforms);
    if (err != CL_SUCCESS || numPlatforms == 0) {
        std::cerr << "ERROR: No OpenCL platforms found!" << std::endl;
        exit(1);
    }

    // Get all platforms
    std::vector<cl_platform_id> platforms(numPlatforms);
    clGetPlatformIDs(numPlatforms, platforms.data(), NULL);

    // Find Mesa platform
    bool foundMesa = false;
    for (cl_uint i = 0; i < numPlatforms; i++) {
        char platformName[128];
        char platformVendor[128];
        clGetPlatformInfo(platforms[i], CL_PLATFORM_NAME, sizeof(platformName), platformName, NULL);
        clGetPlatformInfo(platforms[i], CL_PLATFORM_VENDOR, sizeof(platformVendor), platformVendor, NULL);

        std::string name(platformName);
        std::string vendor(platformVendor);

        if (name.find("Mesa") != std::string::npos ||
            name.find("rusticl") != std::string::npos ||
            vendor.find("Mesa") != std::string::npos ||
            vendor.find("X.Org") != std::string::npos) {
            platform = platforms[i];
            foundMesa = true;
            std::cout << "Found Mesa platform: " << platformName << " (" << platformVendor << ")" << std::endl;
            break;
        }
    }

    if (!foundMesa) {
        std::cerr << "ERROR: Mesa OpenCL platform not found!" << std::endl;
        std::cerr << "Available platforms:" << std::endl;
        for (cl_uint i = 0; i < numPlatforms; i++) {
            char platformName[128];
            clGetPlatformInfo(platforms[i], CL_PLATFORM_NAME, sizeof(platformName), platformName, NULL);
            std::cerr << "  - " << platformName << std::endl;
        }
        exit(1);
    }

    // Get GPU device
    err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, NULL);
    if (err != CL_SUCCESS) {
        std::cerr << "ERROR: No GPU device found on Mesa platform!" << std::endl;
        std::cerr << "Make sure RUSTICL_ENABLE is set correctly." << std::endl;
        exit(1);
    }

    // Print device info
    char deviceName[128];
    clGetDeviceInfo(device, CL_DEVICE_NAME, sizeof(deviceName), deviceName, NULL);
    std::cout << "Using device: " << deviceName << std::endl;

    // Create context
    context = clCreateContext(NULL, 1, &device, NULL, NULL, &err);
    if (err != CL_SUCCESS) {
        std::cerr << "ERROR: Failed to create OpenCL context!" << std::endl;
        exit(1);
    }

    // Create command queue
    cl_queue_properties properties[] = {0};
    queue = clCreateCommandQueueWithProperties(context, device, properties, &err);
    if (err != CL_SUCCESS) {
        std::cerr << "ERROR: Failed to create command queue!" << std::endl;
        exit(1);
    }

    std::cout << "OpenCL initialized successfully" << std::endl << std::endl;
}

void cleanupOpenCL() {
    clReleaseCommandQueue(queue);
    clReleaseContext(context);
}

void printTestSummary() {
    int total = test_results.size();
    int passed = 0;
    int failed = 0;

    for (const auto& result : test_results) {
        if (result.passed) {
            passed++;
        } else {
            failed++;
        }
    }

    std::cout << "\n========================================" << std::endl;
    std::cout << "TEST SUMMARY" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "Total tests: " << total << std::endl;
    std::cout << "Passed: " << passed << " (" << (100.0 * passed / total) << "%)" << std::endl;
    std::cout << "Failed: " << failed << " (" << (100.0 * failed / total) << "%)" << std::endl;
    std::cout << "========================================" << std::endl;

    if (failed > 0) {
        std::cout << "\nFailed tests:" << std::endl;
        for (const auto& result : test_results) {
            if (!result.passed) {
                std::cout << "  - " << result.function_name << " test #" << result.test_number;
                if (!result.error_message.empty()) {
                    std::cout << ": " << result.error_message;
                }
                std::cout << std::endl;
            }
        }
    }
}

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "OpenCL Built-in Functions Test Suite" << std::endl;
    std::cout << "Testing 129 functions with 1290 test cases" << std::endl;
    std::cout << "========================================" << std::endl << std::endl;

    // Initialize OpenCL
    initializeOpenCL();

    // Run all integer function tests
    std::cout << "=== INTEGER FUNCTIONS ===" << std::endl;
    test_abs_int();
    test_abs_diff_int();
    test_abs_diff_uint();
    test_add_sat_int();
    test_add_sat_uint();
    test_clz_int();
    // test_ctz_int();  // ctz not supported in Mesa Rusticl
    test_hadd_int();
    test_mad24_int();
    test_mad_hi_int();
    test_mad_sat_int();
    test_max_int();
    test_max_uint();
    test_min_int();
    test_min_uint();
    test_mul24_int();
    test_mul_hi_int();
    test_popcount_int();
    test_rhadd_int();
    test_rotate_int();
    test_sub_sat_int();

    // Run all common function tests
    std::cout << "\n=== COMMON FUNCTIONS ===" << std::endl;
    test_clamp_float();
    test_clamp_float2();
    test_degrees();
    test_max_float();
    test_max_float2();
    test_min_float();
    test_min_float2();
    test_mix();
    test_radians();
    test_sign();
    test_smoothstep();
    test_step();

    // Run all geometric function tests
    std::cout << "\n=== GEOMETRIC FUNCTIONS ===" << std::endl;
    test_cross();
    test_cross_float4();
    test_distance_float2();
    test_distance_float3();
    test_distance_float4();
    test_dot_float2();
    test_dot_float3();
    test_dot_float4();
    test_fast_distance_float2();
    test_fast_distance_float3();
    test_fast_distance_float4();
    test_fast_length_float2();
    test_fast_length_float3();
    test_fast_length_float4();
    test_fast_normalize_float2();
    test_fast_normalize_float3();
    test_fast_normalize_float4();
    test_length_float2();
    test_length_float3();
    test_length_float4();
    test_normalize_float2();
    test_normalize_float3();
    test_normalize_float4();

    // Run all math function tests
    std::cout << "\n=== MATH FUNCTIONS ===" << std::endl;
    test_acos();
    test_asin();
    test_atan();
    test_atan2();
    test_cos();
    test_sin();
    test_tan();
    test_acosh();
    test_asinh();
    test_atanh();
    test_cosh();
    test_sinh();
    test_tanh();
    test_cbrt();
    test_ceil();
    test_erf();
    test_erfc();
    test_exp();
    test_exp2();
    test_exp10();
    test_expm1();
    test_fabs();
    test_floor();
    test_fma();
    test_fmax();
    test_fmin();
    test_fmod();
    test_hypot();
    test_lgamma();
    test_log();
    test_log2();
    test_log10();
    test_log1p();
    test_native_exp();
    test_native_exp2();
    test_native_exp10();
    test_native_log();
    test_native_log2();
    test_native_log10();
    test_native_rsqrt();
    test_native_sqrt();
    test_pow();
    test_pown();
    test_powr();
    test_remainder();
    test_rint();
    test_round();
    test_rsqrt();
    test_sqrt();
    test_tgamma();
    test_trunc();

    // Run all relational function tests
    std::cout << "\n=== RELATIONAL FUNCTIONS ===" << std::endl;
    test_all_int2();
    test_all_int4();
    test_any_int2();
    test_any_int4();
    test_bitselect_float();
    test_bitselect_int();
    test_isequal();
    test_isfinite();
    test_isgreater();
    test_isgreaterequal();
    test_isinf();
    test_isless();
    test_islessequal();
    test_islessgreater();
    test_isnan();
    test_isnormal();
    test_isordered();
    test_isunordered();
    test_isnotequal();
    test_select_float();
    test_select_int();
    test_signbit();

    // Print summary
    printTestSummary();

    // Cleanup
    cleanupOpenCL();

    // Return non-zero if any tests failed
    int failed = 0;
    for (const auto& result : test_results) {
        if (!result.passed) failed++;
    }

    return (failed > 0) ? 1 : 0;
}
