/**
 * OpenCL Half-Precision Vector Load/Store Functions Tests
 * Tests all 22 vload_half*, vstore_half*, vloada_half*, vstorea_half* functions
 */

#define CL_TARGET_OPENCL_VERSION 300
#include <CL/cl.h>
#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// Test result structure (must match main test runner)
struct TestResult {
  std::string function_name;
  int test_number;
  bool passed;
  std::string error_message;
};

// External global OpenCL objects (from main test runner)
extern cl_platform_id platform;
extern cl_device_id device;
extern cl_context context;
extern cl_command_queue queue;
extern std::vector<TestResult> test_results;

// External float comparison function (from main test runner)
extern bool floatEquals(float a, float b, float tolerance);

// Helper to load kernel source
std::string loadHalfKernel(const std::string &filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "ERROR: Failed to open kernel file: " << filename << std::endl;
    return "";
  }
  std::stringstream buffer;
  buffer << file.rdbuf();
  return buffer.str();
}

// Helper to convert float array to half buffer
cl_mem createHalfBufferFromFloats(const float *floats, size_t count,
                                  cl_int *err) {
  // Create half buffer
  cl_mem halfBuffer = clCreateBuffer(context, CL_MEM_READ_WRITE,
                                     count * sizeof(cl_half), NULL, err);

  // Convert floats to halves using a temporary kernel
  const char *convertKernel = R"(
    __kernel void float_to_half(__global const float *input,
                                 __global half *output,
                                 const unsigned int count) {
      for (unsigned int i = 0; i < count; i++) {
        vstore_half(input[i], i, output);
      }
    }
  )";

  cl_program prog =
      clCreateProgramWithSource(context, 1, &convertKernel, NULL, err);
  clBuildProgram(prog, 1, &device, NULL, NULL, NULL);
  cl_kernel kern = clCreateKernel(prog, "float_to_half", err);

  cl_mem floatBuf =
      clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                     count * sizeof(float), (void *)floats, err);
  unsigned int cnt = count;
  clSetKernelArg(kern, 0, sizeof(cl_mem), &floatBuf);
  clSetKernelArg(kern, 1, sizeof(cl_mem), &halfBuffer);
  clSetKernelArg(kern, 2, sizeof(unsigned int), &cnt);

  size_t global = 1;
  clEnqueueNDRangeKernel(queue, kern, 1, NULL, &global, NULL, 0, NULL, NULL);
  clFinish(queue);

  clReleaseMemObject(floatBuf);
  clReleaseKernel(kern);
  clReleaseProgram(prog);

  return halfBuffer;
}

// Helper to convert half buffer to float array
void readHalfBufferAsFloats(cl_mem halfBuffer, float *floats, size_t count) {
  const char *convertKernel = R"(
    __kernel void half_to_float(__global const half *input,
                                 __global float *output,
                                 const unsigned int count) {
      for (unsigned int i = 0; i < count; i++) {
        output[i] = vload_half(i, input);
      }
    }
  )";

  cl_int err;
  cl_program prog =
      clCreateProgramWithSource(context, 1, &convertKernel, NULL, &err);
  clBuildProgram(prog, 1, &device, NULL, NULL, NULL);
  cl_kernel kern = clCreateKernel(prog, "half_to_float", &err);

  cl_mem floatBuf = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                   count * sizeof(float), NULL, &err);
  unsigned int cnt = count;
  clSetKernelArg(kern, 0, sizeof(cl_mem), &halfBuffer);
  clSetKernelArg(kern, 1, sizeof(cl_mem), &floatBuf);
  clSetKernelArg(kern, 2, sizeof(unsigned int), &cnt);

  size_t global = 1;
  clEnqueueNDRangeKernel(queue, kern, 1, NULL, &global, NULL, 0, NULL, NULL);
  clFinish(queue);

  clEnqueueReadBuffer(queue, floatBuf, CL_TRUE, 0, count * sizeof(float),
                      floats, 0, NULL, NULL);

  clReleaseMemObject(floatBuf);
  clReleaseKernel(kern);
  clReleaseProgram(prog);
}

// Generic test for vload_half variants
void test_vload_half_generic(const std::string &func_name,
                             const std::string &kernel_name, int vec_size,
                             bool is_aligned) {
  std::string kernelSource =
      loadHalfKernel("kernels/half_vector_load_store_functions_kernel.cl");
  if (kernelSource.empty())
    return;

  const char *source = kernelSource.c_str();
  size_t sourceSize = kernelSource.length();

  cl_int err;
  cl_program program =
      clCreateProgramWithSource(context, 1, &source, &sourceSize, &err);
  if (err != CL_SUCCESS) {
    std::cerr << "ERROR: Failed to create program for " << func_name
              << std::endl;
    return;
  }

  err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
  if (err != CL_SUCCESS) {
    std::cerr << "ERROR: Failed to build program for " << func_name
              << std::endl;
    char buildLog[4096];
    clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG,
                          sizeof(buildLog), buildLog, NULL);
    std::cerr << "Build log:\n" << buildLog << std::endl;
    clReleaseProgram(program);
    return;
  }

  cl_kernel kernel = clCreateKernel(program, kernel_name.c_str(), &err);
  if (err != CL_SUCCESS) {
    std::cerr << "ERROR: Failed to create kernel " << kernel_name << std::endl;
    clReleaseProgram(program);
    return;
  }

  // Test data
  int array_size = vec_size * 2;
  if (vec_size == 1)
    array_size = 4;

  std::vector<float> test_data(array_size);
  for (int i = 0; i < array_size; i++) {
    test_data[i] = (float)(i + 1) * 0.5f;
  }

  size_t offset = 0;

  // Create buffers
  cl_mem halfBuffer =
      createHalfBufferFromFloats(test_data.data(), array_size, &err);
  cl_mem offsetBuffer =
      clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                     sizeof(size_t), &offset, &err);
  cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                       vec_size * sizeof(float), NULL, &err);

  unsigned int count = 1;
  clSetKernelArg(kernel, 0, sizeof(cl_mem), &halfBuffer);
  clSetKernelArg(kernel, 1, sizeof(cl_mem), &offsetBuffer);
  clSetKernelArg(kernel, 2, sizeof(cl_mem), &outputBuffer);
  clSetKernelArg(kernel, 3, sizeof(unsigned int), &count);

  size_t global = 1;
  err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &global, NULL, 0, NULL,
                               NULL);

  std::vector<float> result(vec_size);
  clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, vec_size * sizeof(float),
                      result.data(), 0, NULL, NULL);

  // Verify
  bool passed = true;
  for (int i = 0; i < vec_size; i++) {
    if (!floatEquals(result[i], test_data[i], 0.001f)) {
      passed = false;
      break;
    }
  }

  test_results.push_back(
      TestResult{func_name, 0, passed, passed ? "" : "Value mismatch"});

  if (passed) {
    std::cout << "  " << func_name << ": PASS" << std::endl;
  } else {
    std::cout << "  " << func_name << ": FAIL" << std::endl;
  }

  clReleaseMemObject(halfBuffer);
  clReleaseMemObject(offsetBuffer);
  clReleaseMemObject(outputBuffer);
  clReleaseKernel(kernel);
  clReleaseProgram(program);
}

// Generic test for vstore_half variants
void test_vstore_half_generic(const std::string &func_name,
                              const std::string &kernel_name, int vec_size,
                              bool is_aligned) {
  std::string kernelSource =
      loadHalfKernel("kernels/half_vector_load_store_functions_kernel.cl");
  if (kernelSource.empty())
    return;

  const char *source = kernelSource.c_str();
  size_t sourceSize = kernelSource.length();

  cl_int err;
  cl_program program =
      clCreateProgramWithSource(context, 1, &source, &sourceSize, &err);
  err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
  if (err != CL_SUCCESS) {
    clReleaseProgram(program);
    return;
  }

  cl_kernel kernel = clCreateKernel(program, kernel_name.c_str(), &err);
  if (err != CL_SUCCESS) {
    clReleaseProgram(program);
    return;
  }

  // Test data
  std::vector<float> test_vector(vec_size);
  for (int i = 0; i < vec_size; i++) {
    test_vector[i] = (float)(i + 1) * 1.5f;
  }

  size_t offset = 0;
  int output_size = vec_size * 2;
  if (vec_size == 1)
    output_size = 4;

  // Create buffers
  cl_mem valueBuffer =
      clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                     vec_size * sizeof(float), test_vector.data(), &err);
  cl_mem offsetBuffer =
      clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                     sizeof(size_t), &offset, &err);
  cl_mem halfBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                     output_size * sizeof(cl_half), NULL, &err);

  unsigned int count = 1;
  clSetKernelArg(kernel, 0, sizeof(cl_mem), &valueBuffer);
  clSetKernelArg(kernel, 1, sizeof(cl_mem), &offsetBuffer);
  clSetKernelArg(kernel, 2, sizeof(cl_mem), &halfBuffer);
  clSetKernelArg(kernel, 3, sizeof(unsigned int), &count);

  size_t global = 1;
  clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &global, NULL, 0, NULL, NULL);
  clFinish(queue);

  // Read back as floats
  std::vector<float> result(output_size);
  readHalfBufferAsFloats(halfBuffer, result.data(), output_size);

  // Verify - values should be stored at offset
  bool passed = true;
  for (int i = 0; i < vec_size; i++) {
    if (!floatEquals(result[i], test_vector[i], 0.001f)) {
      passed = false;
      break;
    }
  }

  test_results.push_back(
      TestResult{func_name, 0, passed, passed ? "" : "Value mismatch"});

  if (passed) {
    std::cout << "  " << func_name << ": PASS" << std::endl;
  } else {
    std::cout << "  " << func_name << ": FAIL" << std::endl;
  }

  clReleaseMemObject(valueBuffer);
  clReleaseMemObject(offsetBuffer);
  clReleaseMemObject(halfBuffer);
  clReleaseKernel(kernel);
  clReleaseProgram(program);
}

// Test all vload_half* functions
void test_half_vload_functions() {
  std::cout << "Testing vload_half* functions..." << std::endl;

  test_vload_half_generic("vload_half", "test_vload_half", 1, false);
  test_vload_half_generic("vload_half2", "test_vload_half2", 2, false);
  test_vload_half_generic("vload_half3", "test_vload_half3", 3, false);
  test_vload_half_generic("vload_half4", "test_vload_half4", 4, false);
  test_vload_half_generic("vload_half8", "test_vload_half8", 8, false);
  test_vload_half_generic("vload_half16", "test_vload_half16", 16, false);

  std::cout << "vload_half* tests complete\n" << std::endl;
}

// Test all vstore_half* functions
void test_half_vstore_functions() {
  std::cout << "Testing vstore_half* functions..." << std::endl;

  test_vstore_half_generic("vstore_half", "test_vstore_half", 1, false);
  test_vstore_half_generic("vstore_half2", "test_vstore_half2", 2, false);
  test_vstore_half_generic("vstore_half3", "test_vstore_half3", 3, false);
  test_vstore_half_generic("vstore_half4", "test_vstore_half4", 4, false);
  test_vstore_half_generic("vstore_half8", "test_vstore_half8", 8, false);
  test_vstore_half_generic("vstore_half16", "test_vstore_half16", 16, false);

  std::cout << "vstore_half* tests complete\n" << std::endl;
}

// Test all vloada_half* functions (aligned loads)
void test_half_vloada_functions() {
  std::cout << "Testing vloada_half* functions..." << std::endl;

  // No scalar version for vloada_half
  test_vload_half_generic("vloada_half2", "test_vloada_half2", 2, true);
  test_vload_half_generic("vloada_half3", "test_vloada_half3", 3, true);
  test_vload_half_generic("vloada_half4", "test_vloada_half4", 4, true);
  test_vload_half_generic("vloada_half8", "test_vloada_half8", 8, true);
  test_vload_half_generic("vloada_half16", "test_vloada_half16", 16, true);

  std::cout << "vloada_half* tests complete\n" << std::endl;
}

// Test all vstorea_half* functions (aligned stores)
void test_half_vstorea_functions() {
  std::cout << "Testing vstorea_half* functions..." << std::endl;

  // No scalar version for vstorea_half
  test_vstore_half_generic("vstorea_half2", "test_vstorea_half2", 2, true);
  test_vstore_half_generic("vstorea_half3", "test_vstorea_half3", 3, true);
  test_vstore_half_generic("vstorea_half4", "test_vstorea_half4", 4, true);
  test_vstore_half_generic("vstorea_half8", "test_vstorea_half8", 8, true);
  test_vstore_half_generic("vstorea_half16", "test_vstorea_half16", 16, true);

  std::cout << "vstorea_half* tests complete\n" << std::endl;
}
