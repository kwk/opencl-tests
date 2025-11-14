#include <CL/cl.h>
#include <iostream>
#include <vector>

const char *kernel_source = R"(
__kernel void test_any_int2(__global const int2 *input, __global int *output, const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = any(input[i]);
}

__kernel void test_all_int2(__global const int2 *input, __global int *output, const unsigned int count) {
    int i = get_global_id(0);
    if (i < count)
        output[i] = all(input[i]);
}
)";

int main() {
  // Initialize OpenCL
  cl_platform_id platform;
  clGetPlatformIDs(1, &platform, NULL);

  cl_device_id device;
  clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, NULL);

  cl_context context = clCreateContext(NULL, 1, &device, NULL, NULL, NULL);
  cl_command_queue queue = clCreateCommandQueue(context, device, 0, NULL);

  // Create program
  cl_program program =
      clCreateProgramWithSource(context, 1, &kernel_source, NULL, NULL);
  clBuildProgram(program, 1, &device, NULL, NULL, NULL);

  // Test vectors
  typedef struct {
    int s[2];
  } cl_int2;
  std::vector<cl_int2> test_inputs = {
      {{0, 0}},   // Test 0
      {{1, 0}},   // Test 1
      {{0, 1}},   // Test 2
      {{1, 1}},   // Test 3
      {{-1, 0}},  // Test 4
      {{0, -1}},  // Test 5
      {{-1, -1}}, // Test 6
      {{5, 5}},   // Test 7
  };

  std::vector<int> any_output(test_inputs.size());
  std::vector<int> all_output(test_inputs.size());

  // Test any()
  cl_kernel any_kernel = clCreateKernel(program, "test_any_int2", NULL);
  cl_mem input_buf = clCreateBuffer(
      context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
      test_inputs.size() * sizeof(cl_int2), test_inputs.data(), NULL);
  cl_mem any_output_buf = clCreateBuffer(
      context, CL_MEM_WRITE_ONLY, test_inputs.size() * sizeof(int), NULL, NULL);

  unsigned int count = test_inputs.size();
  clSetKernelArg(any_kernel, 0, sizeof(cl_mem), &input_buf);
  clSetKernelArg(any_kernel, 1, sizeof(cl_mem), &any_output_buf);
  clSetKernelArg(any_kernel, 2, sizeof(unsigned int), &count);

  size_t global_size = count;
  clEnqueueNDRangeKernel(queue, any_kernel, 1, NULL, &global_size, NULL, 0,
                         NULL, NULL);
  clEnqueueReadBuffer(queue, any_output_buf, CL_TRUE, 0, count * sizeof(int),
                      any_output.data(), 0, NULL, NULL);

  // Test all()
  cl_kernel all_kernel = clCreateKernel(program, "test_all_int2", NULL);
  cl_mem all_output_buf = clCreateBuffer(
      context, CL_MEM_WRITE_ONLY, test_inputs.size() * sizeof(int), NULL, NULL);

  clSetKernelArg(all_kernel, 0, sizeof(cl_mem), &input_buf);
  clSetKernelArg(all_kernel, 1, sizeof(cl_mem), &all_output_buf);
  clSetKernelArg(all_kernel, 2, sizeof(unsigned int), &count);

  clEnqueueNDRangeKernel(queue, all_kernel, 1, NULL, &global_size, NULL, 0,
                         NULL, NULL);
  clEnqueueReadBuffer(queue, all_output_buf, CL_TRUE, 0, count * sizeof(int),
                      all_output.data(), 0, NULL, NULL);

  // Print results
  std::cout << "any() results:" << std::endl;
  for (size_t i = 0; i < test_inputs.size(); i++) {
    std::cout << "  Test " << i << ": input=[" << test_inputs[i].s[0] << ", "
              << test_inputs[i].s[1] << "] -> any() = " << any_output[i]
              << std::endl;
  }

  std::cout << "\nall() results:" << std::endl;
  for (size_t i = 0; i < test_inputs.size(); i++) {
    std::cout << "  Test " << i << ": input=[" << test_inputs[i].s[0] << ", "
              << test_inputs[i].s[1] << "] -> all() = " << all_output[i]
              << std::endl;
  }

  // Cleanup
  clReleaseMemObject(input_buf);
  clReleaseMemObject(any_output_buf);
  clReleaseMemObject(all_output_buf);
  clReleaseKernel(any_kernel);
  clReleaseKernel(all_kernel);
  clReleaseProgram(program);
  clReleaseCommandQueue(queue);
  clReleaseContext(context);

  return 0;
}
