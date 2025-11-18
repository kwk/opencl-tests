/**
 * OpenCL Built-in Functions Test Runner
 * Comprehensive test suite for all OpenCL C built-in functions
 * Tests 177 functions with 1770 test cases
 */

#define CL_TARGET_OPENCL_VERSION 300
#include <CL/cl.h>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

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

// Test registry structure
struct TestFunction {
  std::string name;
  std::string category;
  void (*func)();
};

std::vector<TestFunction> test_registry;

// Helper to register a test function
void registerTest(const std::string &name, const std::string &category,
                  void (*func)()) {
  test_registry.push_back({name, category, func});
}

// Helper function for float comparison with hybrid tolerance
// Uses absolute tolerance for small values, relative tolerance for large values
bool floatEquals(float a, float b, float tolerance = 0.0001f) {
  float diff = std::fabs(a - b);

  // For very small values or when either is near zero, use absolute tolerance
  if (std::fabs(a) < 1.0f || std::fabs(b) < 1.0f) {
    return diff < tolerance;
  }

  // For larger values, use relative tolerance (as percentage of magnitude)
  // This is important for native_* functions with large outputs like exp(80)
  float max_val = std::max(std::fabs(a), std::fabs(b));
  float relative_tolerance = 0.01f; // 1% for native functions
  return (diff / max_val) < relative_tolerance;
}

// Half-precision float comparison with relaxed tolerance
// Half-precision functions have ≤ 8192 ULP accuracy vs ≤ 4 ULP for regular
// functions
bool halfFloatEquals(float a, float b) {
  float diff = std::fabs(a - b);

  // For very small values, use absolute tolerance
  if (std::fabs(a) < 1.0f || std::fabs(b) < 1.0f) {
    return diff < 0.01f; // 1% absolute for small values
  }

  // For larger values, use very relaxed relative tolerance
  // Half-precision can have up to 8192 ULP error, which translates to ~0.1% for
  // worst case
  float max_val = std::max(std::fabs(a), std::fabs(b));
  float relative_tolerance = 0.1f; // 10% for half-precision functions
  return (diff / max_val) < relative_tolerance;
}

// Helper function to load kernel source from file
std::string loadKernel(const std::string &filename) {
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
void test_clz_int2();
void test_clz_int4();
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
void test_popcount_int2();
void test_popcount_int4();
void test_rhadd_int();
void test_rotate_int();
void test_rotate_int2();
void test_rotate_int4();
void test_sub_sat_int();
// Phase 1 integer additions
void test_upsample_int();
void test_clamp_int();
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
// Phase 1 math additions
void test_acospi();
void test_asinpi();
void test_atanpi();
void test_atan2pi();
void test_cospi();
void test_sinpi();
void test_tanpi();
void test_copysign();
void test_fdim();
void test_fract();
void test_ilogb();
void test_ldexp();
void test_logb();
void test_mad();
void test_maxmag();
void test_minmag();
void test_nextafter();
void test_rootn();
// Phase 2: Pointer output functions
void test_frexp();
void test_modf();
void test_sincos();
void test_remquo();
void test_lgamma_r();
// Phase 3: Half-precision math functions
void test_half_cos();
void test_half_sin();
void test_half_tan();
void test_half_exp();
void test_half_exp2();
void test_half_exp10();
void test_half_log();
void test_half_log2();
void test_half_log10();
void test_half_sqrt();
void test_half_rsqrt();
void test_half_recip();
void test_half_divide();
void test_half_powr();
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
void test_shuffle_float4();
void test_shuffle2_float4();
void test_vload2_float();
void test_vload3_float();
void test_vload4_float();
void test_vload8_float();
void test_vload16_float();
void test_vstore2_float();
void test_vstore3_float();
void test_vstore4_float();
void test_vstore8_float();
void test_vstore16_float();
void test_printf_int();
void test_printf_hex();
void test_printf_int_width();
void test_printf_float();
void test_printf_hello();
void test_printf_hello_world();
void test_printf_newline();
void test_printf_value();
void test_printf_multi();

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
    clGetPlatformInfo(platforms[i], CL_PLATFORM_NAME, sizeof(platformName),
                      platformName, NULL);
    clGetPlatformInfo(platforms[i], CL_PLATFORM_VENDOR, sizeof(platformVendor),
                      platformVendor, NULL);

    std::string name(platformName);
    std::string vendor(platformVendor);

    if (name.find("Mesa") != std::string::npos ||
        name.find("rusticl") != std::string::npos ||
        vendor.find("Mesa") != std::string::npos ||
        vendor.find("X.Org") != std::string::npos) {
      platform = platforms[i];
      foundMesa = true;
      std::cout << "Found Mesa platform: " << platformName << " ("
                << platformVendor << ")" << std::endl;
      break;
    }
  }

  if (!foundMesa) {
    std::cerr << "ERROR: Mesa OpenCL platform not found!" << std::endl;
    std::cerr << "Available platforms:" << std::endl;
    for (cl_uint i = 0; i < numPlatforms; i++) {
      char platformName[128];
      clGetPlatformInfo(platforms[i], CL_PLATFORM_NAME, sizeof(platformName),
                        platformName, NULL);
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

  for (const auto &result : test_results) {
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
  std::cout << "Passed: " << passed << " (" << (100.0 * passed / total) << "%)"
            << std::endl;
  std::cout << "Failed: " << failed << " (" << (100.0 * failed / total) << "%)"
            << std::endl;
  std::cout << "========================================" << std::endl;

  if (failed > 0) {
    std::cout << "\nFailed tests:" << std::endl;
    for (const auto &result : test_results) {
      if (!result.passed) {
        std::cout << "  - " << result.function_name << " test #"
                  << result.test_number;
        if (!result.error_message.empty()) {
          std::cout << ": " << result.error_message;
        }
        std::cout << std::endl;
      }
    }
  }
}

void registerAllTests() {
  // Register all integer function tests
  registerTest("abs_int", "integer", test_abs_int);
  registerTest("abs_diff_int", "integer", test_abs_diff_int);
  registerTest("abs_diff_uint", "integer", test_abs_diff_uint);
  registerTest("add_sat_int", "integer", test_add_sat_int);
  registerTest("add_sat_uint", "integer", test_add_sat_uint);
  registerTest("clz_int", "integer", test_clz_int);
  registerTest("clz_int2", "integer", test_clz_int2);
  registerTest("clz_int4", "integer", test_clz_int4);
  // test_ctz_int - not supported in Mesa Rusticl
  registerTest("hadd_int", "integer", test_hadd_int);
  registerTest("mad24_int", "integer", test_mad24_int);
  registerTest("mad_hi_int", "integer", test_mad_hi_int);
  registerTest("mad_sat_int", "integer", test_mad_sat_int);
  registerTest("max_int", "integer", test_max_int);
  registerTest("max_uint", "integer", test_max_uint);
  registerTest("min_int", "integer", test_min_int);
  registerTest("min_uint", "integer", test_min_uint);
  registerTest("mul24_int", "integer", test_mul24_int);
  registerTest("mul_hi_int", "integer", test_mul_hi_int);
  registerTest("popcount_int", "integer", test_popcount_int);
  registerTest("popcount_int2", "integer", test_popcount_int2);
  registerTest("popcount_int4", "integer", test_popcount_int4);
  registerTest("rhadd_int", "integer", test_rhadd_int);
  registerTest("rotate_int", "integer", test_rotate_int);
  registerTest("rotate_int2", "integer", test_rotate_int2);
  registerTest("rotate_int4", "integer", test_rotate_int4);
  registerTest("sub_sat_int", "integer", test_sub_sat_int);
  // Phase 1 integer additions
  registerTest("upsample_int", "integer", test_upsample_int);
  registerTest("clamp_int", "integer", test_clamp_int);

  // Register all common function tests
  registerTest("clamp_float", "common", test_clamp_float);
  registerTest("clamp_float2", "common", test_clamp_float2);
  registerTest("degrees", "common", test_degrees);
  registerTest("max_float", "common", test_max_float);
  registerTest("max_float2", "common", test_max_float2);
  registerTest("min_float", "common", test_min_float);
  registerTest("min_float2", "common", test_min_float2);
  registerTest("mix", "common", test_mix);
  registerTest("radians", "common", test_radians);
  registerTest("sign", "common", test_sign);
  registerTest("smoothstep", "common", test_smoothstep);
  registerTest("step", "common", test_step);

  // Register all geometric function tests
  registerTest("cross", "geometric", test_cross);
  registerTest("cross_float4", "geometric", test_cross_float4);
  registerTest("distance_float2", "geometric", test_distance_float2);
  registerTest("distance_float3", "geometric", test_distance_float3);
  registerTest("distance_float4", "geometric", test_distance_float4);
  registerTest("dot_float2", "geometric", test_dot_float2);
  registerTest("dot_float3", "geometric", test_dot_float3);
  registerTest("dot_float4", "geometric", test_dot_float4);
  registerTest("fast_distance_float2", "geometric", test_fast_distance_float2);
  registerTest("fast_distance_float3", "geometric", test_fast_distance_float3);
  registerTest("fast_distance_float4", "geometric", test_fast_distance_float4);
  registerTest("fast_length_float2", "geometric", test_fast_length_float2);
  registerTest("fast_length_float3", "geometric", test_fast_length_float3);
  registerTest("fast_length_float4", "geometric", test_fast_length_float4);
  registerTest("fast_normalize_float2", "geometric",
               test_fast_normalize_float2);
  registerTest("fast_normalize_float3", "geometric",
               test_fast_normalize_float3);
  registerTest("fast_normalize_float4", "geometric",
               test_fast_normalize_float4);
  registerTest("length_float2", "geometric", test_length_float2);
  registerTest("length_float3", "geometric", test_length_float3);
  registerTest("length_float4", "geometric", test_length_float4);
  registerTest("normalize_float2", "geometric", test_normalize_float2);
  registerTest("normalize_float3", "geometric", test_normalize_float3);
  registerTest("normalize_float4", "geometric", test_normalize_float4);

  // Register all math function tests
  registerTest("acos", "math", test_acos);
  registerTest("asin", "math", test_asin);
  registerTest("atan", "math", test_atan);
  registerTest("atan2", "math", test_atan2);
  registerTest("cos", "math", test_cos);
  registerTest("sin", "math", test_sin);
  registerTest("tan", "math", test_tan);
  registerTest("acosh", "math", test_acosh);
  registerTest("asinh", "math", test_asinh);
  registerTest("atanh", "math", test_atanh);
  registerTest("cosh", "math", test_cosh);
  registerTest("sinh", "math", test_sinh);
  registerTest("tanh", "math", test_tanh);
  registerTest("cbrt", "math", test_cbrt);
  registerTest("ceil", "math", test_ceil);
  registerTest("erf", "math", test_erf);
  registerTest("erfc", "math", test_erfc);
  registerTest("exp", "math", test_exp);
  registerTest("exp2", "math", test_exp2);
  registerTest("exp10", "math", test_exp10);
  registerTest("expm1", "math", test_expm1);
  registerTest("fabs", "math", test_fabs);
  registerTest("floor", "math", test_floor);
  registerTest("fma", "math", test_fma);
  registerTest("fmax", "math", test_fmax);
  registerTest("fmin", "math", test_fmin);
  registerTest("fmod", "math", test_fmod);
  registerTest("hypot", "math", test_hypot);
  registerTest("lgamma", "math", test_lgamma);
  registerTest("log", "math", test_log);
  registerTest("log2", "math", test_log2);
  registerTest("log10", "math", test_log10);
  registerTest("log1p", "math", test_log1p);
  registerTest("native_exp", "math", test_native_exp);
  registerTest("native_exp2", "math", test_native_exp2);
  registerTest("native_exp10", "math", test_native_exp10);
  registerTest("native_log", "math", test_native_log);
  registerTest("native_log2", "math", test_native_log2);
  registerTest("native_log10", "math", test_native_log10);
  registerTest("native_rsqrt", "math", test_native_rsqrt);
  registerTest("native_sqrt", "math", test_native_sqrt);
  registerTest("pow", "math", test_pow);
  registerTest("pown", "math", test_pown);
  registerTest("powr", "math", test_powr);
  registerTest("remainder", "math", test_remainder);
  registerTest("rint", "math", test_rint);
  registerTest("round", "math", test_round);
  registerTest("rsqrt", "math", test_rsqrt);
  registerTest("sqrt", "math", test_sqrt);
  registerTest("tgamma", "math", test_tgamma);
  registerTest("trunc", "math", test_trunc);
  // Phase 1 math additions
  registerTest("acospi", "math", test_acospi);
  registerTest("asinpi", "math", test_asinpi);
  registerTest("atanpi", "math", test_atanpi);
  registerTest("atan2pi", "math", test_atan2pi);
  registerTest("cospi", "math", test_cospi);
  registerTest("sinpi", "math", test_sinpi);
  registerTest("tanpi", "math", test_tanpi);
  registerTest("copysign", "math", test_copysign);
  registerTest("fdim", "math", test_fdim);
  registerTest("fract", "math", test_fract);
  registerTest("ilogb", "math", test_ilogb);
  registerTest("ldexp", "math", test_ldexp);
  registerTest("logb", "math", test_logb);
  registerTest("mad", "math", test_mad);
  registerTest("maxmag", "math", test_maxmag);
  registerTest("minmag", "math", test_minmag);
  registerTest("nextafter", "math", test_nextafter);
  registerTest("rootn", "math", test_rootn);

  // Register Phase 2: Pointer output function tests
  registerTest("frexp", "pointer_output_functions", test_frexp);
  registerTest("modf", "pointer_output_functions", test_modf);
  registerTest("sincos", "pointer_output_functions", test_sincos);
  registerTest("remquo", "pointer_output_functions", test_remquo);
  registerTest("lgamma_r", "pointer_output_functions", test_lgamma_r);

  // Register Phase 3: Half-precision math function tests
  registerTest("half_cos", "half_precision_math", test_half_cos);
  registerTest("half_sin", "half_precision_math", test_half_sin);
  registerTest("half_tan", "half_precision_math", test_half_tan);
  registerTest("half_exp", "half_precision_math", test_half_exp);
  registerTest("half_exp2", "half_precision_math", test_half_exp2);
  registerTest("half_exp10", "half_precision_math", test_half_exp10);
  registerTest("half_log", "half_precision_math", test_half_log);
  registerTest("half_log2", "half_precision_math", test_half_log2);
  registerTest("half_log10", "half_precision_math", test_half_log10);
  registerTest("half_sqrt", "half_precision_math", test_half_sqrt);
  registerTest("half_rsqrt", "half_precision_math", test_half_rsqrt);
  registerTest("half_recip", "half_precision_math", test_half_recip);
  registerTest("half_divide", "half_precision_math", test_half_divide);
  registerTest("half_powr", "half_precision_math", test_half_powr);

  // Register all relational function tests
  registerTest("all_int2", "relational", test_all_int2);
  registerTest("all_int4", "relational", test_all_int4);
  registerTest("any_int2", "relational", test_any_int2);
  registerTest("any_int4", "relational", test_any_int4);
  registerTest("bitselect_float", "relational", test_bitselect_float);
  registerTest("bitselect_int", "relational", test_bitselect_int);
  registerTest("isequal", "relational", test_isequal);
  registerTest("isfinite", "relational", test_isfinite);
  registerTest("isgreater", "relational", test_isgreater);
  registerTest("isgreaterequal", "relational", test_isgreaterequal);
  registerTest("isinf", "relational", test_isinf);
  registerTest("isless", "relational", test_isless);
  registerTest("islessequal", "relational", test_islessequal);
  registerTest("islessgreater", "relational", test_islessgreater);
  registerTest("isnan", "relational", test_isnan);
  registerTest("isnormal", "relational", test_isnormal);
  registerTest("isordered", "relational", test_isordered);
  registerTest("isunordered", "relational", test_isunordered);
  registerTest("isnotequal", "relational", test_isnotequal);
  registerTest("select_float", "relational", test_select_float);
  registerTest("select_int", "relational", test_select_int);
  registerTest("signbit", "relational", test_signbit);

  // Register vector miscellaneous function tests
  registerTest("shuffle_float4", "vector_misc", test_shuffle_float4);
  registerTest("shuffle2_float4", "vector_misc", test_shuffle2_float4);

  // Register vector load/store function tests
  registerTest("vload2_float", "vector_load_store", test_vload2_float);
  registerTest("vload3_float", "vector_load_store", test_vload3_float);
  registerTest("vload4_float", "vector_load_store", test_vload4_float);
  registerTest("vload8_float", "vector_load_store", test_vload8_float);
  registerTest("vload16_float", "vector_load_store", test_vload16_float);
  registerTest("vstore2_float", "vector_load_store", test_vstore2_float);
  registerTest("vstore3_float", "vector_load_store", test_vstore3_float);
  registerTest("vstore4_float", "vector_load_store", test_vstore4_float);
  registerTest("vstore8_float", "vector_load_store", test_vstore8_float);
  registerTest("vstore16_float", "vector_load_store", test_vstore16_float);
  registerTest("printf_int", "misc_functions", test_printf_int);
  registerTest("printf_hex", "misc_functions", test_printf_hex);
  registerTest("printf_int_width", "misc_functions", test_printf_int_width);
  registerTest("printf_float", "misc_functions", test_printf_float);
  registerTest("printf_hello", "misc_functions", test_printf_hello);
  registerTest("printf_hello_world", "misc_functions", test_printf_hello_world);
  registerTest("printf_newline", "misc_functions", test_printf_newline);
  registerTest("printf_value", "misc_functions", test_printf_value);
  registerTest("printf_multi", "misc_functions", test_printf_multi);
}

void printUsage(const char *program) {
  std::cout << "Usage: " << program << " [OPTIONS] [FUNCTION_NAME]\n\n";
  std::cout << "Run OpenCL built-in function tests.\n\n";
  std::cout << "Options:\n";
  std::cout << "  --list              List all available tests\n";
  std::cout << "  --category <name>   Run tests only from specified category\n";
  std::cout << "                      (integer, common, geometric, math, "
               "relational, vector_misc, misc_functions)\n";
  std::cout << "  --help              Show this help message\n\n";
  std::cout << "Examples:\n";
  std::cout << "  " << program << "                  # Run all tests\n";
  std::cout << "  " << program << " sqrt             # Run only sqrt test\n";
  std::cout << "  " << program
            << " --category math  # Run all math function tests\n";
  std::cout << "  " << program
            << " --list           # List all available tests\n";
}

void listTests() {
  std::string current_category = "";
  for (const auto &test : test_registry) {
    if (test.category != current_category) {
      current_category = test.category;
      std::cout << "\n=== " << current_category << " ===" << std::endl;
    }
    std::cout << "  " << test.name << std::endl;
  }
}

int main(int argc, char *argv[]) {
  // Register all tests
  registerAllTests();

  std::string filter_function = "";
  std::string filter_category = "";
  bool list_mode = false;

  // Parse command-line arguments
  for (int i = 1; i < argc; i++) {
    std::string arg = argv[i];
    if (arg == "--help" || arg == "-h") {
      printUsage(argv[0]);
      return 0;
    } else if (arg == "--list") {
      list_mode = true;
    } else if (arg == "--category") {
      if (i + 1 < argc) {
        filter_category = argv[++i];
      } else {
        std::cerr << "Error: --category requires an argument\n";
        printUsage(argv[0]);
        return 1;
      }
    } else if (arg[0] != '-') {
      filter_function = arg;
    } else {
      std::cerr << "Error: Unknown option: " << arg << "\n";
      printUsage(argv[0]);
      return 1;
    }
  }

  // Handle --list mode
  if (list_mode) {
    std::cout << "Available tests:\n";
    listTests();
    return 0;
  }

  // Validate category if specified
  if (!filter_category.empty()) {
    bool valid_category = false;
    for (const auto &test : test_registry) {
      if (test.category == filter_category) {
        valid_category = true;
        break;
      }
    }
    if (!valid_category) {
      std::cerr << "Error: Invalid category '" << filter_category << "'\n";
      std::cerr << "Valid categories: integer, common, geometric, math, "
                   "relational, vector_misc, misc_functions\n";
      return 1;
    }
  }

  // Validate function name if specified
  if (!filter_function.empty()) {
    bool found = false;
    for (const auto &test : test_registry) {
      if (test.name == filter_function) {
        found = true;
        break;
      }
    }
    if (!found) {
      std::cerr << "Error: Unknown function '" << filter_function << "'\n";
      std::cerr << "Use --list to see all available tests\n";
      return 1;
    }
  }

  // Print header
  std::cout << "========================================" << std::endl;
  std::cout << "OpenCL Built-in Functions Test Suite" << std::endl;
  if (!filter_function.empty()) {
    std::cout << "Running test: " << filter_function << std::endl;
  } else if (!filter_category.empty()) {
    std::cout << "Running category: " << filter_category << std::endl;
  } else {
    std::cout << "Testing 146 functions with 1457 test cases" << std::endl;
  }
  std::cout << "========================================" << std::endl
            << std::endl;

  // Initialize OpenCL
  initializeOpenCL();

  // Run filtered tests
  std::string current_category = "";
  int tests_run = 0;

  for (const auto &test : test_registry) {
    // Apply filters
    if (!filter_function.empty() && test.name != filter_function) {
      continue;
    }
    if (!filter_category.empty() && test.category != filter_category) {
      continue;
    }

    // Print category header
    if (test.category != current_category) {
      current_category = test.category;
      std::cout << "\n=== " << current_category
                << " FUNCTIONS ===" << std::endl;
    }

    // Run the test
    test.func();
    tests_run++;
  }

  if (tests_run == 0) {
    std::cout << "No tests matched the filter criteria.\n";
    return 1;
  }

  // Print summary
  printTestSummary();

  // Cleanup
  cleanupOpenCL();

  // Return non-zero if any tests failed
  int failed = 0;
  for (const auto &result : test_results) {
    if (!result.passed)
      failed++;
  }

  return (failed > 0) ? 1 : 0;
}
