/**
 * OpenCL Image Functions Tests
 * Tests image query, read, and write operations
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

// Helper to load kernel source
std::string loadImageKernel(const std::string &filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "ERROR: Failed to open kernel file: " << filename << std::endl;
    return "";
  }
  std::stringstream buffer;
  buffer << file.rdbuf();
  return buffer.str();
}

// Test image query functions
void test_image_query_functions() {
  std::cout << "Testing image query functions..." << std::endl;

  // Load and build kernel
  std::string kernelSource =
      loadImageKernel("kernels/image_functions_kernel.cl");
  if (kernelSource.empty())
    return;

  const char *source = kernelSource.c_str();
  size_t sourceSize = kernelSource.length();

  cl_int err;
  cl_program program =
      clCreateProgramWithSource(context, 1, &source, &sourceSize, &err);
  if (err != CL_SUCCESS) {
    std::cerr << "ERROR: Failed to create program" << std::endl;
    return;
  }

  err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
  if (err != CL_SUCCESS) {
    std::cerr << "ERROR: Failed to build program" << std::endl;
    // Print build log
    char buildLog[16384];
    clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG,
                          sizeof(buildLog), buildLog, NULL);
    std::cerr << "Build log:\n" << buildLog << std::endl;
    clReleaseProgram(program);
    return;
  }

  // Test dimensions
  const size_t test_width = 64;
  const size_t test_height = 32;

  // Create a simple 2D image (RGBA, FLOAT)
  cl_image_format format;
  format.image_channel_order = CL_RGBA;
  format.image_channel_data_type = CL_FLOAT;

  cl_image_desc desc;
  memset(&desc, 0, sizeof(desc));
  desc.image_type = CL_MEM_OBJECT_IMAGE2D;
  desc.image_width = test_width;
  desc.image_height = test_height;

  cl_mem image =
      clCreateImage(context, CL_MEM_READ_ONLY, &format, &desc, NULL, &err);
  if (err != CL_SUCCESS) {
    std::cerr << "ERROR: Failed to create image: " << err << std::endl;
    clReleaseProgram(program);
    return;
  }

  // Create output buffer
  cl_mem outputBuffer =
      clCreateBuffer(context, CL_MEM_WRITE_ONLY, sizeof(int), NULL, &err);
  if (err != CL_SUCCESS) {
    std::cerr << "ERROR: Failed to create output buffer" << std::endl;
    clReleaseMemObject(image);
    clReleaseProgram(program);
    return;
  }

  // Test get_image_width
  {
    cl_kernel kernel = clCreateKernel(program, "test_get_image_width", &err);
    if (err != CL_SUCCESS) {
      std::cerr << "ERROR: Failed to create get_image_width kernel"
                << std::endl;
    } else {
      unsigned int count = 1;
      clSetKernelArg(kernel, 0, sizeof(cl_mem), &image);
      clSetKernelArg(kernel, 1, sizeof(cl_mem), &outputBuffer);
      clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);

      size_t globalSize = 1;
      err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0,
                                   NULL, NULL);
      if (err != CL_SUCCESS) {
        std::cerr << "ERROR: Failed to execute get_image_width kernel"
                  << std::endl;
      } else {
        int result;
        clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, sizeof(int),
                            &result, 0, NULL, NULL);

        bool passed = (result == (int)test_width);
        test_results.push_back(TestResult{"get_image_width", 1, passed,
                                          passed ? "" : "Width mismatch"});

        if (passed) {
          std::cout << "  get_image_width: PASS (" << result << ")"
                    << std::endl;
        } else {
          std::cout << "  get_image_width: FAIL (expected " << test_width
                    << ", got " << result << ")" << std::endl;
        }
      }
      clReleaseKernel(kernel);
    }
  }

  // Test get_image_height
  {
    cl_kernel kernel = clCreateKernel(program, "test_get_image_height", &err);
    if (err != CL_SUCCESS) {
      std::cerr << "ERROR: Failed to create get_image_height kernel"
                << std::endl;
    } else {
      unsigned int count = 1;
      clSetKernelArg(kernel, 0, sizeof(cl_mem), &image);
      clSetKernelArg(kernel, 1, sizeof(cl_mem), &outputBuffer);
      clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);

      size_t globalSize = 1;
      err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0,
                                   NULL, NULL);
      if (err != CL_SUCCESS) {
        std::cerr << "ERROR: Failed to execute get_image_height kernel"
                  << std::endl;
      } else {
        int result;
        clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, sizeof(int),
                            &result, 0, NULL, NULL);

        bool passed = (result == (int)test_height);
        test_results.push_back(TestResult{"get_image_height", 1, passed,
                                          passed ? "" : "Height mismatch"});

        if (passed) {
          std::cout << "  get_image_height: PASS (" << result << ")"
                    << std::endl;
        } else {
          std::cout << "  get_image_height: FAIL (expected " << test_height
                    << ", got " << result << ")" << std::endl;
        }
      }
      clReleaseKernel(kernel);
    }
  }

  // Test get_image_channel_data_type
  {
    cl_kernel kernel =
        clCreateKernel(program, "test_get_image_channel_data_type", &err);
    if (err != CL_SUCCESS) {
      std::cerr << "ERROR: Failed to create get_image_channel_data_type kernel"
                << std::endl;
    } else {
      unsigned int count = 1;
      clSetKernelArg(kernel, 0, sizeof(cl_mem), &image);
      clSetKernelArg(kernel, 1, sizeof(cl_mem), &outputBuffer);
      clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);

      size_t globalSize = 1;
      err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0,
                                   NULL, NULL);
      if (err != CL_SUCCESS) {
        std::cerr
            << "ERROR: Failed to execute get_image_channel_data_type kernel"
            << std::endl;
      } else {
        int result;
        clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, sizeof(int),
                            &result, 0, NULL, NULL);

        bool passed = (result == (int)CL_FLOAT);
        test_results.push_back(TestResult{"get_image_channel_data_type", 1,
                                          passed,
                                          passed ? "" : "Data type mismatch"});

        if (passed) {
          std::cout << "  get_image_channel_data_type: PASS (0x" << std::hex
                    << result << std::dec << ")" << std::endl;
        } else {
          std::cout << "  get_image_channel_data_type: FAIL (expected 0x"
                    << std::hex << CL_FLOAT << ", got 0x" << result << std::dec
                    << ")" << std::endl;
        }
      }
      clReleaseKernel(kernel);
    }
  }

  // Test get_image_channel_order
  {
    cl_kernel kernel =
        clCreateKernel(program, "test_get_image_channel_order", &err);
    if (err != CL_SUCCESS) {
      std::cerr << "ERROR: Failed to create get_image_channel_order kernel"
                << std::endl;
    } else {
      unsigned int count = 1;
      clSetKernelArg(kernel, 0, sizeof(cl_mem), &image);
      clSetKernelArg(kernel, 1, sizeof(cl_mem), &outputBuffer);
      clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);

      size_t globalSize = 1;
      err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0,
                                   NULL, NULL);
      if (err != CL_SUCCESS) {
        std::cerr << "ERROR: Failed to execute get_image_channel_order kernel"
                  << std::endl;
      } else {
        int result;
        clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, sizeof(int),
                            &result, 0, NULL, NULL);

        bool passed = (result == (int)CL_RGBA);
        test_results.push_back(
            TestResult{"get_image_channel_order", 1, passed,
                       passed ? "" : "Channel order mismatch"});

        if (passed) {
          std::cout << "  get_image_channel_order: PASS (0x" << std::hex
                    << result << std::dec << ")" << std::endl;
        } else {
          std::cout << "  get_image_channel_order: FAIL (expected 0x"
                    << std::hex << CL_RGBA << ", got 0x" << result << std::dec
                    << ")" << std::endl;
        }
      }
      clReleaseKernel(kernel);
    }
  }

  // Cleanup
  clReleaseMemObject(outputBuffer);
  clReleaseMemObject(image);
  clReleaseProgram(program);

  std::cout << "Image query functions tests complete\n" << std::endl;
}

// Test image read functions
void test_image_read_functions() {
  std::cout << "Testing image read functions..." << std::endl;

  // Load and build kernel
  std::string kernelSource =
      loadImageKernel("kernels/image_functions_kernel.cl");
  if (kernelSource.empty())
    return;

  const char *source = kernelSource.c_str();
  size_t sourceSize = kernelSource.length();

  cl_int err;
  cl_program program =
      clCreateProgramWithSource(context, 1, &source, &sourceSize, &err);
  if (err != CL_SUCCESS) {
    std::cerr << "ERROR: Failed to create program" << std::endl;
    return;
  }

  err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
  if (err != CL_SUCCESS) {
    std::cerr << "ERROR: Failed to build program" << std::endl;
    clReleaseProgram(program);
    return;
  }

  // Create a small 2D image with known pixel values
  const size_t width = 4;
  const size_t height = 4;

  cl_image_format format;
  format.image_channel_order = CL_RGBA;
  format.image_channel_data_type = CL_FLOAT;

  cl_image_desc desc;
  memset(&desc, 0, sizeof(desc));
  desc.image_type = CL_MEM_OBJECT_IMAGE2D;
  desc.image_width = width;
  desc.image_height = height;

  // Create test image data (4x4 pixels, each RGBA float4)
  std::vector<float> imageData(width * height * 4, 0.0f);
  // Set (0,0) to red
  imageData[0] = 1.0f; // R
  imageData[1] = 0.0f; // G
  imageData[2] = 0.0f; // B
  imageData[3] = 1.0f; // A
  // Set (1,0) to green
  imageData[4] = 0.0f; // R
  imageData[5] = 1.0f; // G
  imageData[6] = 0.0f; // B
  imageData[7] = 1.0f; // A

  cl_mem image = clCreateImage(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                               &format, &desc, imageData.data(), &err);
  if (err != CL_SUCCESS) {
    std::cerr << "ERROR: Failed to create image: " << err << std::endl;
    clReleaseProgram(program);
    return;
  }

  // Create kernel
  cl_kernel kernel = clCreateKernel(program, "test_read_imagef_2d", &err);
  if (err != CL_SUCCESS) {
    std::cerr << "ERROR: Failed to create kernel" << std::endl;
    clReleaseMemObject(image);
    clReleaseProgram(program);
    return;
  }

  // Test reading pixel at (0,0) - should be red
  {
    int x_coord = 0, y_coord = 0;
    cl_mem x_buf =
        clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                       sizeof(int), &x_coord, &err);
    cl_mem y_buf =
        clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                       sizeof(int), &y_coord, &err);
    cl_mem output = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                   sizeof(cl_float4), NULL, &err);

    unsigned int count = 1;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &image);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &x_buf);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &y_buf);
    clSetKernelArg(kernel, 3, sizeof(cl_mem), &output);
    clSetKernelArg(kernel, 4, sizeof(unsigned int), &count);

    size_t globalSize = 1;
    clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL,
                           NULL);

    cl_float4 result;
    clEnqueueReadBuffer(queue, output, CL_TRUE, 0, sizeof(cl_float4), &result,
                        0, NULL, NULL);

    bool passed = (fabs(result.s[0] - 1.0f) < 0.001f &&
                   fabs(result.s[1] - 0.0f) < 0.001f &&
                   fabs(result.s[2] - 0.0f) < 0.001f &&
                   fabs(result.s[3] - 1.0f) < 0.001f);

    test_results.push_back(
        TestResult{"read_imagef_2d", 1, passed,
                   passed ? "" : "Pixel color mismatch at (0,0)"});

    if (passed) {
      std::cout << "  read_imagef_2d (0,0): PASS (red)" << std::endl;
    } else {
      std::cout << "  read_imagef_2d (0,0): FAIL (expected red, got RGBA="
                << result.s[0] << "," << result.s[1] << "," << result.s[2]
                << "," << result.s[3] << ")" << std::endl;
    }

    clReleaseMemObject(x_buf);
    clReleaseMemObject(y_buf);
    clReleaseMemObject(output);
  }

  // Test reading pixel at (1,0) - should be green
  {
    int x_coord = 1, y_coord = 0;
    cl_mem x_buf =
        clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                       sizeof(int), &x_coord, &err);
    cl_mem y_buf =
        clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                       sizeof(int), &y_coord, &err);
    cl_mem output = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                   sizeof(cl_float4), NULL, &err);

    unsigned int count = 1;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &image);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &x_buf);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &y_buf);
    clSetKernelArg(kernel, 3, sizeof(cl_mem), &output);
    clSetKernelArg(kernel, 4, sizeof(unsigned int), &count);

    size_t globalSize = 1;
    clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL,
                           NULL);

    cl_float4 result;
    clEnqueueReadBuffer(queue, output, CL_TRUE, 0, sizeof(cl_float4), &result,
                        0, NULL, NULL);

    bool passed = (fabs(result.s[0] - 0.0f) < 0.001f &&
                   fabs(result.s[1] - 1.0f) < 0.001f &&
                   fabs(result.s[2] - 0.0f) < 0.001f &&
                   fabs(result.s[3] - 1.0f) < 0.001f);

    test_results.push_back(
        TestResult{"read_imagef_2d", 2, passed,
                   passed ? "" : "Pixel color mismatch at (1,0)"});

    if (passed) {
      std::cout << "  read_imagef_2d (1,0): PASS (green)" << std::endl;
    } else {
      std::cout << "  read_imagef_2d (1,0): FAIL (expected green, got RGBA="
                << result.s[0] << "," << result.s[1] << "," << result.s[2]
                << "," << result.s[3] << ")" << std::endl;
    }

    clReleaseMemObject(x_buf);
    clReleaseMemObject(y_buf);
    clReleaseMemObject(output);
  }

  clReleaseKernel(kernel);
  clReleaseMemObject(image);
  clReleaseProgram(program);

  std::cout << "Image read functions tests complete\n" << std::endl;
}

// Test image write functions
void test_image_write_functions() {
  std::cout << "Testing image write functions..." << std::endl;

  // Load and build kernel
  std::string kernelSource =
      loadImageKernel("kernels/image_functions_kernel.cl");
  if (kernelSource.empty())
    return;

  const char *source = kernelSource.c_str();
  size_t sourceSize = kernelSource.length();

  cl_int err;
  cl_program program =
      clCreateProgramWithSource(context, 1, &source, &sourceSize, &err);
  if (err != CL_SUCCESS) {
    std::cerr << "ERROR: Failed to create program" << std::endl;
    return;
  }

  err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
  if (err != CL_SUCCESS) {
    std::cerr << "ERROR: Failed to build program" << std::endl;
    clReleaseProgram(program);
    return;
  }

  // Create a small 2D image for writing
  const size_t width = 4;
  const size_t height = 4;

  cl_image_format format;
  format.image_channel_order = CL_RGBA;
  format.image_channel_data_type = CL_FLOAT;

  cl_image_desc desc;
  memset(&desc, 0, sizeof(desc));
  desc.image_type = CL_MEM_OBJECT_IMAGE2D;
  desc.image_width = width;
  desc.image_height = height;

  cl_mem image =
      clCreateImage(context, CL_MEM_WRITE_ONLY, &format, &desc, NULL, &err);
  if (err != CL_SUCCESS) {
    std::cerr << "ERROR: Failed to create image: " << err << std::endl;
    clReleaseProgram(program);
    return;
  }

  // Create kernel
  cl_kernel kernel = clCreateKernel(program, "test_write_imagef_2d", &err);
  if (err != CL_SUCCESS) {
    std::cerr << "ERROR: Failed to create kernel" << std::endl;
    clReleaseMemObject(image);
    clReleaseProgram(program);
    return;
  }

  // Test writing red pixel at (0,0)
  {
    int x_coord = 0, y_coord = 0;
    cl_float4 red_color = {{1.0f, 0.0f, 0.0f, 1.0f}};

    cl_mem x_buf =
        clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                       sizeof(int), &x_coord, &err);
    cl_mem y_buf =
        clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                       sizeof(int), &y_coord, &err);
    cl_mem color_buf =
        clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                       sizeof(cl_float4), &red_color, &err);

    unsigned int count = 1;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &image);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &x_buf);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &y_buf);
    clSetKernelArg(kernel, 3, sizeof(cl_mem), &color_buf);
    clSetKernelArg(kernel, 4, sizeof(unsigned int), &count);

    size_t globalSize = 1;
    clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL,
                           NULL);
    clFinish(queue);

    // Read back the image to verify
    std::vector<float> readback(width * height * 4, 0.0f);
    size_t origin[3] = {0, 0, 0};
    size_t region[3] = {width, height, 1};
    clEnqueueReadImage(queue, image, CL_TRUE, origin, region, 0, 0,
                       readback.data(), 0, NULL, NULL);

    // Check pixel at (0,0)
    bool passed = (fabs(readback[0] - 1.0f) < 0.001f && // R
                   fabs(readback[1] - 0.0f) < 0.001f && // G
                   fabs(readback[2] - 0.0f) < 0.001f && // B
                   fabs(readback[3] - 1.0f) < 0.001f);  // A

    test_results.push_back(
        TestResult{"write_imagef_2d", 1, passed,
                   passed ? "" : "Written pixel color mismatch at (0,0)"});

    if (passed) {
      std::cout << "  write_imagef_2d (0,0): PASS (red)" << std::endl;
    } else {
      std::cout << "  write_imagef_2d (0,0): FAIL (expected red, got RGBA="
                << readback[0] << "," << readback[1] << "," << readback[2]
                << "," << readback[3] << ")" << std::endl;
    }

    clReleaseMemObject(x_buf);
    clReleaseMemObject(y_buf);
    clReleaseMemObject(color_buf);
  }

  clReleaseKernel(kernel);
  clReleaseMemObject(image);
  clReleaseProgram(program);

  std::cout << "Image write functions tests complete\n" << std::endl;
}
