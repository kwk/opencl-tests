// AUTO-GENERATED TEST CODE
// Generated from JSON test data files

void test_abs_int() {
    std::cout << "Testing abs_int()..." << std::endl;

    const int NUM_TESTS = 10;
    int input0[NUM_TESTS];
    unsigned int output[NUM_TESTS];
    unsigned int expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 0;
    expected[0] = 0;
    input0[1] = 5;
    expected[1] = 5;
    input0[2] = -5;
    expected[2] = 5;
    input0[3] = 100;
    expected[3] = 100;
    input0[4] = -100;
    expected[4] = 100;
    input0[5] = 1;
    expected[5] = 1;
    input0[6] = -1;
    expected[6] = 1;
    input0[7] = 2147483647;
    expected[7] = 2147483647;
    input0[8] = -2147483647;
    expected[8] = 2147483647;
    input0[9] = 42;
    expected[9] = 42;

    std::string kernelSource = loadKernel("integer_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_abs_int", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(int), input0, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(unsigned int), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(unsigned int), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = (output[i] == expected[i]);
        test_results.push_back({"abs_int", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "abs_int() tests complete" << std::endl << std::endl;
}

void test_add_sat_int() {
    std::cout << "Testing add_sat_int()..." << std::endl;

    const int NUM_TESTS = 10;
    int input0[NUM_TESTS];
    int input1[NUM_TESTS];
    int output[NUM_TESTS];
    int expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 0;
    input1[0] = 0;
    expected[0] = 0;
    input0[1] = 5;
    input1[1] = 10;
    expected[1] = 15;
    input0[2] = -5;
    input1[2] = 10;
    expected[2] = 5;
    input0[3] = 10;
    input1[3] = -5;
    expected[3] = 5;
    input0[4] = -10;
    input1[4] = -5;
    expected[4] = -15;
    input0[5] = 2147483647;
    input1[5] = 1;
    expected[5] = 2147483647;
    input0[6] = 2147483646;
    input1[6] = 1;
    expected[6] = 2147483647;
    input0[7] = -2147483648;
    input1[7] = -1;
    expected[7] = -2147483648;
    input0[8] = 1000000;
    input1[8] = 2000000;
    expected[8] = 3000000;
    input0[9] = 100;
    input1[9] = 200;
    expected[9] = 300;

    std::string kernelSource = loadKernel("integer_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_add_sat_int", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(int), input0, &err);
    cl_mem inputBuffer1 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(int), input1, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(int), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &inputBuffer1);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 3, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(int), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = (output[i] == expected[i]);
        test_results.push_back({"add_sat_int", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(inputBuffer1);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "add_sat_int() tests complete" << std::endl << std::endl;
}

void test_clz_int() {
    std::cout << "Testing clz_int()..." << std::endl;

    const int NUM_TESTS = 10;
    int input0[NUM_TESTS];
    int output[NUM_TESTS];
    int expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 0;
    expected[0] = 32;
    input0[1] = 1;
    expected[1] = 31;
    input0[2] = 2;
    expected[2] = 30;
    input0[3] = 4;
    expected[3] = 29;
    input0[4] = 8;
    expected[4] = 28;
    input0[5] = 16;
    expected[5] = 27;
    input0[6] = 255;
    expected[6] = 24;
    input0[7] = 256;
    expected[7] = 23;
    input0[8] = 65536;
    expected[8] = 15;
    input0[9] = -1;
    expected[9] = 0;

    std::string kernelSource = loadKernel("integer_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_clz_int", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(int), input0, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(int), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(int), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = (output[i] == expected[i]);
        test_results.push_back({"clz_int", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "clz_int() tests complete" << std::endl << std::endl;
}

void test_max_int() {
    std::cout << "Testing max_int()..." << std::endl;

    const int NUM_TESTS = 10;
    int input0[NUM_TESTS];
    int input1[NUM_TESTS];
    int output[NUM_TESTS];
    int expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 1;
    input1[0] = 2;
    expected[0] = 2;
    input0[1] = 2;
    input1[1] = 1;
    expected[1] = 2;
    input0[2] = 5;
    input1[2] = 5;
    expected[2] = 5;
    input0[3] = -1;
    input1[3] = 1;
    expected[3] = 1;
    input0[4] = 0;
    input1[4] = 0;
    expected[4] = 0;
    input0[5] = -5;
    input1[5] = -3;
    expected[5] = -3;
    input0[6] = 10;
    input1[6] = 100;
    expected[6] = 100;
    input0[7] = 100;
    input1[7] = 10;
    expected[7] = 100;
    input0[8] = -10;
    input1[8] = 10;
    expected[8] = 10;
    input0[9] = 999;
    input1[9] = 1000;
    expected[9] = 1000;

    std::string kernelSource = loadKernel("integer_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_max_int", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(int), input0, &err);
    cl_mem inputBuffer1 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(int), input1, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(int), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &inputBuffer1);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 3, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(int), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = (output[i] == expected[i]);
        test_results.push_back({"max_int", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(inputBuffer1);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "max_int() tests complete" << std::endl << std::endl;
}

void test_min_int() {
    std::cout << "Testing min_int()..." << std::endl;

    const int NUM_TESTS = 10;
    int input0[NUM_TESTS];
    int input1[NUM_TESTS];
    int output[NUM_TESTS];
    int expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 1;
    input1[0] = 2;
    expected[0] = 1;
    input0[1] = 2;
    input1[1] = 1;
    expected[1] = 1;
    input0[2] = 5;
    input1[2] = 5;
    expected[2] = 5;
    input0[3] = -1;
    input1[3] = 1;
    expected[3] = -1;
    input0[4] = 0;
    input1[4] = 0;
    expected[4] = 0;
    input0[5] = -5;
    input1[5] = -3;
    expected[5] = -5;
    input0[6] = 10;
    input1[6] = 100;
    expected[6] = 10;
    input0[7] = 100;
    input1[7] = 10;
    expected[7] = 10;
    input0[8] = -10;
    input1[8] = 10;
    expected[8] = -10;
    input0[9] = 999;
    input1[9] = 1000;
    expected[9] = 999;

    std::string kernelSource = loadKernel("integer_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_min_int", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(int), input0, &err);
    cl_mem inputBuffer1 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(int), input1, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(int), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &inputBuffer1);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 3, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(int), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = (output[i] == expected[i]);
        test_results.push_back({"min_int", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(inputBuffer1);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "min_int() tests complete" << std::endl << std::endl;
}

void test_popcount_int() {
    std::cout << "Testing popcount_int()..." << std::endl;

    const int NUM_TESTS = 10;
    int input0[NUM_TESTS];
    int output[NUM_TESTS];
    int expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 0;
    expected[0] = 0;
    input0[1] = 1;
    expected[1] = 1;
    input0[2] = 2;
    expected[2] = 1;
    input0[3] = 3;
    expected[3] = 2;
    input0[4] = 7;
    expected[4] = 3;
    input0[5] = 15;
    expected[5] = 4;
    input0[6] = 255;
    expected[6] = 8;
    input0[7] = 256;
    expected[7] = 1;
    input0[8] = -1;
    expected[8] = 32;
    input0[9] = 1023;
    expected[9] = 10;

    std::string kernelSource = loadKernel("integer_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_popcount_int", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(int), input0, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(int), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(int), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = (output[i] == expected[i]);
        test_results.push_back({"popcount_int", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "popcount_int() tests complete" << std::endl << std::endl;
}

void test_mul24_int() {
    std::cout << "Testing mul24_int()..." << std::endl;

    const int NUM_TESTS = 10;
    int input0[NUM_TESTS];
    int input1[NUM_TESTS];
    int output[NUM_TESTS];
    int expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 0;
    input1[0] = 0;
    expected[0] = 0;
    input0[1] = 1;
    input1[1] = 1;
    expected[1] = 1;
    input0[2] = 5;
    input1[2] = 10;
    expected[2] = 50;
    input0[3] = 10;
    input1[3] = 5;
    expected[3] = 50;
    input0[4] = 100;
    input1[4] = 200;
    expected[4] = 20000;
    input0[5] = -5;
    input1[5] = 10;
    expected[5] = -50;
    input0[6] = 10;
    input1[6] = -5;
    expected[6] = -50;
    input0[7] = -10;
    input1[7] = -5;
    expected[7] = 50;
    input0[8] = 123;
    input1[8] = 456;
    expected[8] = 56088;
    input0[9] = 1000;
    input1[9] = 1000;
    expected[9] = 1000000;

    std::string kernelSource = loadKernel("integer_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_mul24_int", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(int), input0, &err);
    cl_mem inputBuffer1 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(int), input1, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(int), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &inputBuffer1);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 3, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(int), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = (output[i] == expected[i]);
        test_results.push_back({"mul24_int", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(inputBuffer1);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "mul24_int() tests complete" << std::endl << std::endl;
}

void test_abs_diff_int() {
    std::cout << "Testing abs_diff_int()..." << std::endl;

    const int NUM_TESTS = 10;
    int input0[NUM_TESTS];
    int input1[NUM_TESTS];
    unsigned int output[NUM_TESTS];
    unsigned int expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 5;
    input1[0] = 3;
    expected[0] = 2;
    input0[1] = 3;
    input1[1] = 5;
    expected[1] = 2;
    input0[2] = 0;
    input1[2] = 0;
    expected[2] = 0;
    input0[3] = 10;
    input1[3] = -5;
    expected[3] = 15;
    input0[4] = -5;
    input1[4] = 10;
    expected[4] = 15;
    input0[5] = -10;
    input1[5] = -5;
    expected[5] = 5;
    input0[6] = 100;
    input1[6] = 50;
    expected[6] = 50;
    input0[7] = 2147483647;
    input1[7] = 0;
    expected[7] = 2147483647;
    input0[8] = 0;
    input1[8] = -2147483648;
    expected[8] = 2147483648;
    input0[9] = 1000;
    input1[9] = 999;
    expected[9] = 1;

    std::string kernelSource = loadKernel("integer_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_abs_diff_int", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(int), input0, &err);
    cl_mem inputBuffer1 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(int), input1, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(unsigned int), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &inputBuffer1);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 3, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(unsigned int), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = (output[i] == expected[i]);
        test_results.push_back({"abs_diff_int", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(inputBuffer1);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "abs_diff_int() tests complete" << std::endl << std::endl;
}

void test_abs_diff_uint() {
    std::cout << "Testing abs_diff_uint()..." << std::endl;

    const int NUM_TESTS = 10;
    unsigned int input0[NUM_TESTS];
    unsigned int input1[NUM_TESTS];
    unsigned int output[NUM_TESTS];
    unsigned int expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 5;
    input1[0] = 3;
    expected[0] = 2;
    input0[1] = 3;
    input1[1] = 5;
    expected[1] = 2;
    input0[2] = 0;
    input1[2] = 0;
    expected[2] = 0;
    input0[3] = 10;
    input1[3] = 5;
    expected[3] = 5;
    input0[4] = 100;
    input1[4] = 50;
    expected[4] = 50;
    input0[5] = 4294967295;
    input1[5] = 0;
    expected[5] = 4294967295;
    input0[6] = 1000;
    input1[6] = 999;
    expected[6] = 1;
    input0[7] = 50;
    input1[7] = 100;
    expected[7] = 50;
    input0[8] = 255;
    input1[8] = 128;
    expected[8] = 127;
    input0[9] = 1024;
    input1[9] = 512;
    expected[9] = 512;

    std::string kernelSource = loadKernel("integer_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_abs_diff_uint", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(unsigned int), input0, &err);
    cl_mem inputBuffer1 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(unsigned int), input1, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(unsigned int), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &inputBuffer1);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 3, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(unsigned int), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = (output[i] == expected[i]);
        test_results.push_back({"abs_diff_uint", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(inputBuffer1);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "abs_diff_uint() tests complete" << std::endl << std::endl;
}

void test_add_sat_uint() {
    std::cout << "Testing add_sat_uint()..." << std::endl;

    const int NUM_TESTS = 10;
    unsigned int input0[NUM_TESTS];
    unsigned int input1[NUM_TESTS];
    unsigned int output[NUM_TESTS];
    unsigned int expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 0;
    input1[0] = 0;
    expected[0] = 0;
    input0[1] = 5;
    input1[1] = 10;
    expected[1] = 15;
    input0[2] = 100;
    input1[2] = 200;
    expected[2] = 300;
    input0[3] = 4294967295;
    input1[3] = 1;
    expected[3] = 4294967295;
    input0[4] = 4294967294;
    input1[4] = 1;
    expected[4] = 4294967295;
    input0[5] = 4294967295;
    input1[5] = 4294967295;
    expected[5] = 4294967295;
    input0[6] = 1000000;
    input1[6] = 2000000;
    expected[6] = 3000000;
    input0[7] = 2147483647;
    input1[7] = 2147483647;
    expected[7] = 4294967294;
    input0[8] = 1000;
    input1[8] = 2000;
    expected[8] = 3000;
    input0[9] = 500;
    input1[9] = 500;
    expected[9] = 1000;

    std::string kernelSource = loadKernel("integer_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_add_sat_uint", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(unsigned int), input0, &err);
    cl_mem inputBuffer1 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(unsigned int), input1, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(unsigned int), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &inputBuffer1);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 3, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(unsigned int), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = (output[i] == expected[i]);
        test_results.push_back({"add_sat_uint", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(inputBuffer1);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "add_sat_uint() tests complete" << std::endl << std::endl;
}

void test_hadd_int() {
    std::cout << "Testing hadd_int()..." << std::endl;

    const int NUM_TESTS = 10;
    int input0[NUM_TESTS];
    int input1[NUM_TESTS];
    int output[NUM_TESTS];
    int expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 0;
    input1[0] = 0;
    expected[0] = 0;
    input0[1] = 2;
    input1[1] = 4;
    expected[1] = 3;
    input0[2] = 4;
    input1[2] = 2;
    expected[2] = 3;
    input0[3] = 1;
    input1[3] = 1;
    expected[3] = 1;
    input0[4] = 10;
    input1[4] = 20;
    expected[4] = 15;
    input0[5] = -10;
    input1[5] = 10;
    expected[5] = 0;
    input0[6] = 5;
    input1[6] = 7;
    expected[6] = 6;
    input0[7] = 100;
    input1[7] = 200;
    expected[7] = 150;
    input0[8] = -5;
    input1[8] = -15;
    expected[8] = -10;
    input0[9] = 3;
    input1[9] = 5;
    expected[9] = 4;

    std::string kernelSource = loadKernel("integer_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_hadd_int", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(int), input0, &err);
    cl_mem inputBuffer1 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(int), input1, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(int), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &inputBuffer1);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 3, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(int), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = (output[i] == expected[i]);
        test_results.push_back({"hadd_int", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(inputBuffer1);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "hadd_int() tests complete" << std::endl << std::endl;
}

void test_rhadd_int() {
    std::cout << "Testing rhadd_int()..." << std::endl;

    const int NUM_TESTS = 10;
    int input0[NUM_TESTS];
    int input1[NUM_TESTS];
    int output[NUM_TESTS];
    int expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 0;
    input1[0] = 0;
    expected[0] = 0;
    input0[1] = 2;
    input1[1] = 4;
    expected[1] = 3;
    input0[2] = 4;
    input1[2] = 2;
    expected[2] = 3;
    input0[3] = 1;
    input1[3] = 1;
    expected[3] = 1;
    input0[4] = 10;
    input1[4] = 20;
    expected[4] = 15;
    input0[5] = -10;
    input1[5] = 10;
    expected[5] = 0;
    input0[6] = 5;
    input1[6] = 7;
    expected[6] = 6;
    input0[7] = 100;
    input1[7] = 200;
    expected[7] = 150;
    input0[8] = -5;
    input1[8] = -15;
    expected[8] = -10;
    input0[9] = 3;
    input1[9] = 5;
    expected[9] = 4;

    std::string kernelSource = loadKernel("integer_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_rhadd_int", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(int), input0, &err);
    cl_mem inputBuffer1 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(int), input1, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(int), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &inputBuffer1);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 3, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(int), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = (output[i] == expected[i]);
        test_results.push_back({"rhadd_int", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(inputBuffer1);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "rhadd_int() tests complete" << std::endl << std::endl;
}

void test_ctz_int() {
    std::cout << "Testing ctz_int()..." << std::endl;

    const int NUM_TESTS = 10;
    int input0[NUM_TESTS];
    int output[NUM_TESTS];
    int expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 1;
    expected[0] = 0;
    input0[1] = 2;
    expected[1] = 1;
    input0[2] = 4;
    expected[2] = 2;
    input0[3] = 8;
    expected[3] = 3;
    input0[4] = 16;
    expected[4] = 4;
    input0[5] = 32;
    expected[5] = 5;
    input0[6] = 64;
    expected[6] = 6;
    input0[7] = 128;
    expected[7] = 7;
    input0[8] = 256;
    expected[8] = 8;
    input0[9] = 3;
    expected[9] = 0;

    std::string kernelSource = loadKernel("integer_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_ctz_int", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(int), input0, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(int), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(int), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = (output[i] == expected[i]);
        test_results.push_back({"ctz_int", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "ctz_int() tests complete" << std::endl << std::endl;
}

void test_mad_hi_int() {
    std::cout << "Testing mad_hi_int()..." << std::endl;

    const int NUM_TESTS = 10;
    int input0[NUM_TESTS];
    int input1[NUM_TESTS];
    int input2[NUM_TESTS];
    int output[NUM_TESTS];
    int expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 0;
    input1[0] = 0;
    input2[0] = 0;
    expected[0] = 0;
    input0[1] = 1;
    input1[1] = 1;
    input2[1] = 0;
    expected[1] = 0;
    input0[2] = 2;
    input1[2] = 2;
    input2[2] = 1;
    expected[2] = 1;
    input0[3] = 65536;
    input1[3] = 65536;
    input2[3] = 0;
    expected[3] = 1;
    input0[4] = 100;
    input1[4] = 200;
    input2[4] = 5;
    expected[4] = 5;
    input0[5] = 1000;
    input1[5] = 1000;
    input2[5] = 10;
    expected[5] = 10;
    input0[6] = 10000;
    input1[6] = 10000;
    input2[6] = 100;
    expected[6] = 100;
    input0[7] = 32768;
    input1[7] = 65536;
    input2[7] = 0;
    expected[7] = 0;
    input0[8] = 50000;
    input1[8] = 50000;
    input2[8] = 50;
    expected[8] = 50;
    input0[9] = 100000;
    input1[9] = 100000;
    input2[9] = 1000;
    expected[9] = 1000;

    std::string kernelSource = loadKernel("integer_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_mad_hi_int", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(int), input0, &err);
    cl_mem inputBuffer1 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(int), input1, &err);
    cl_mem inputBuffer2 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(int), input2, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(int), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &inputBuffer1);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &inputBuffer2);
    clSetKernelArg(kernel, 3, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 4, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(int), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = (output[i] == expected[i]);
        test_results.push_back({"mad_hi_int", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(inputBuffer1);
    clReleaseMemObject(inputBuffer2);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "mad_hi_int() tests complete" << std::endl << std::endl;
}

void test_mad_sat_int() {
    std::cout << "Testing mad_sat_int()..." << std::endl;

    const int NUM_TESTS = 10;
    int input0[NUM_TESTS];
    int input1[NUM_TESTS];
    int input2[NUM_TESTS];
    int output[NUM_TESTS];
    int expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 0;
    input1[0] = 0;
    input2[0] = 0;
    expected[0] = 0;
    input0[1] = 1;
    input1[1] = 1;
    input2[1] = 1;
    expected[1] = 2;
    input0[2] = 2;
    input1[2] = 3;
    input2[2] = 4;
    expected[2] = 10;
    input0[3] = 10;
    input1[3] = 20;
    input2[3] = 30;
    expected[3] = 230;
    input0[4] = 100;
    input1[4] = 200;
    input2[4] = 300;
    expected[4] = 20300;
    input0[5] = 5;
    input1[5] = 5;
    input2[5] = 5;
    expected[5] = 30;
    input0[6] = 1000;
    input1[6] = 1000;
    input2[6] = 1000;
    expected[6] = 1001000;
    input0[7] = 50;
    input1[7] = 100;
    input2[7] = 50;
    expected[7] = 5050;
    input0[8] = 3;
    input1[8] = 4;
    input2[8] = 5;
    expected[8] = 17;
    input0[9] = 7;
    input1[9] = 8;
    input2[9] = 9;
    expected[9] = 65;

    std::string kernelSource = loadKernel("integer_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_mad_sat_int", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(int), input0, &err);
    cl_mem inputBuffer1 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(int), input1, &err);
    cl_mem inputBuffer2 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(int), input2, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(int), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &inputBuffer1);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &inputBuffer2);
    clSetKernelArg(kernel, 3, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 4, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(int), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = (output[i] == expected[i]);
        test_results.push_back({"mad_sat_int", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(inputBuffer1);
    clReleaseMemObject(inputBuffer2);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "mad_sat_int() tests complete" << std::endl << std::endl;
}

void test_max_uint() {
    std::cout << "Testing max_uint()..." << std::endl;

    const int NUM_TESTS = 10;
    unsigned int input0[NUM_TESTS];
    unsigned int input1[NUM_TESTS];
    unsigned int output[NUM_TESTS];
    unsigned int expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 1;
    input1[0] = 2;
    expected[0] = 2;
    input0[1] = 2;
    input1[1] = 1;
    expected[1] = 2;
    input0[2] = 5;
    input1[2] = 5;
    expected[2] = 5;
    input0[3] = 0;
    input1[3] = 1;
    expected[3] = 1;
    input0[4] = 0;
    input1[4] = 0;
    expected[4] = 0;
    input0[5] = 10;
    input1[5] = 100;
    expected[5] = 100;
    input0[6] = 100;
    input1[6] = 10;
    expected[6] = 100;
    input0[7] = 999;
    input1[7] = 1000;
    expected[7] = 1000;
    input0[8] = 4294967295;
    input1[8] = 0;
    expected[8] = 4294967295;
    input0[9] = 1000000;
    input1[9] = 2000000;
    expected[9] = 2000000;

    std::string kernelSource = loadKernel("integer_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_max_uint", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(unsigned int), input0, &err);
    cl_mem inputBuffer1 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(unsigned int), input1, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(unsigned int), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &inputBuffer1);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 3, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(unsigned int), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = (output[i] == expected[i]);
        test_results.push_back({"max_uint", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(inputBuffer1);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "max_uint() tests complete" << std::endl << std::endl;
}

void test_min_uint() {
    std::cout << "Testing min_uint()..." << std::endl;

    const int NUM_TESTS = 10;
    unsigned int input0[NUM_TESTS];
    unsigned int input1[NUM_TESTS];
    unsigned int output[NUM_TESTS];
    unsigned int expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 1;
    input1[0] = 2;
    expected[0] = 1;
    input0[1] = 2;
    input1[1] = 1;
    expected[1] = 1;
    input0[2] = 5;
    input1[2] = 5;
    expected[2] = 5;
    input0[3] = 0;
    input1[3] = 1;
    expected[3] = 0;
    input0[4] = 0;
    input1[4] = 0;
    expected[4] = 0;
    input0[5] = 10;
    input1[5] = 100;
    expected[5] = 10;
    input0[6] = 100;
    input1[6] = 10;
    expected[6] = 10;
    input0[7] = 999;
    input1[7] = 1000;
    expected[7] = 999;
    input0[8] = 4294967295;
    input1[8] = 0;
    expected[8] = 0;
    input0[9] = 1000000;
    input1[9] = 2000000;
    expected[9] = 1000000;

    std::string kernelSource = loadKernel("integer_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_min_uint", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(unsigned int), input0, &err);
    cl_mem inputBuffer1 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(unsigned int), input1, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(unsigned int), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &inputBuffer1);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 3, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(unsigned int), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = (output[i] == expected[i]);
        test_results.push_back({"min_uint", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(inputBuffer1);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "min_uint() tests complete" << std::endl << std::endl;
}

void test_mul_hi_int() {
    std::cout << "Testing mul_hi_int()..." << std::endl;

    const int NUM_TESTS = 10;
    int input0[NUM_TESTS];
    int input1[NUM_TESTS];
    int output[NUM_TESTS];
    int expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 0;
    input1[0] = 0;
    expected[0] = 0;
    input0[1] = 1;
    input1[1] = 1;
    expected[1] = 0;
    input0[2] = 65536;
    input1[2] = 65536;
    expected[2] = 1;
    input0[3] = 32768;
    input1[3] = 65536;
    expected[3] = 0;
    input0[4] = 100000;
    input1[4] = 100000;
    expected[4] = 2;
    input0[5] = 50000;
    input1[5] = 50000;
    expected[5] = 0;
    input0[6] = 200000;
    input1[6] = 200000;
    expected[6] = 9;
    input0[7] = 1000000;
    input1[7] = 1000;
    expected[7] = 0;
    input0[8] = 65535;
    input1[8] = 65536;
    expected[8] = 0;
    input0[9] = 131072;
    input1[9] = 65536;
    expected[9] = 2;

    std::string kernelSource = loadKernel("integer_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_mul_hi_int", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(int), input0, &err);
    cl_mem inputBuffer1 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(int), input1, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(int), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &inputBuffer1);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 3, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(int), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = (output[i] == expected[i]);
        test_results.push_back({"mul_hi_int", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(inputBuffer1);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "mul_hi_int() tests complete" << std::endl << std::endl;
}

void test_rotate_int() {
    std::cout << "Testing rotate_int()..." << std::endl;

    const int NUM_TESTS = 10;
    int input0[NUM_TESTS];
    int input1[NUM_TESTS];
    int output[NUM_TESTS];
    int expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 1;
    input1[0] = 0;
    expected[0] = 1;
    input0[1] = 1;
    input1[1] = 1;
    expected[1] = 2;
    input0[2] = 1;
    input1[2] = 2;
    expected[2] = 4;
    input0[3] = 1;
    input1[3] = 31;
    expected[3] = -2147483648;
    input0[4] = 15;
    input1[4] = 4;
    expected[4] = 240;
    input0[5] = 255;
    input1[5] = 8;
    expected[5] = 65280;
    input0[6] = 1;
    input1[6] = 32;
    expected[6] = 1;
    input0[7] = 7;
    input1[7] = 1;
    expected[7] = 14;
    input0[8] = 128;
    input1[8] = 1;
    expected[8] = 256;
    input0[9] = 3;
    input1[9] = 2;
    expected[9] = 12;

    std::string kernelSource = loadKernel("integer_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_rotate_int", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(int), input0, &err);
    cl_mem inputBuffer1 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(int), input1, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(int), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &inputBuffer1);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 3, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(int), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = (output[i] == expected[i]);
        test_results.push_back({"rotate_int", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(inputBuffer1);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "rotate_int() tests complete" << std::endl << std::endl;
}

void test_sub_sat_int() {
    std::cout << "Testing sub_sat_int()..." << std::endl;

    const int NUM_TESTS = 10;
    int input0[NUM_TESTS];
    int input1[NUM_TESTS];
    int output[NUM_TESTS];
    int expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 0;
    input1[0] = 0;
    expected[0] = 0;
    input0[1] = 10;
    input1[1] = 5;
    expected[1] = 5;
    input0[2] = 5;
    input1[2] = 10;
    expected[2] = -5;
    input0[3] = 100;
    input1[3] = 50;
    expected[3] = 50;
    input0[4] = -10;
    input1[4] = 5;
    expected[4] = -15;
    input0[5] = 10;
    input1[5] = -5;
    expected[5] = 15;
    input0[6] = -2147483648;
    input1[6] = 1;
    expected[6] = -2147483648;
    input0[7] = 2147483647;
    input1[7] = -1;
    expected[7] = 2147483647;
    input0[8] = 1000;
    input1[8] = 500;
    expected[8] = 500;
    input0[9] = 0;
    input1[9] = 100;
    expected[9] = -100;

    std::string kernelSource = loadKernel("integer_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_sub_sat_int", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(int), input0, &err);
    cl_mem inputBuffer1 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(int), input1, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(int), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &inputBuffer1);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 3, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(int), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = (output[i] == expected[i]);
        test_results.push_back({"sub_sat_int", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(inputBuffer1);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "sub_sat_int() tests complete" << std::endl << std::endl;
}

void test_mad24_int() {
    std::cout << "Testing mad24_int()..." << std::endl;

    const int NUM_TESTS = 10;
    int input0[NUM_TESTS];
    int input1[NUM_TESTS];
    int input2[NUM_TESTS];
    int output[NUM_TESTS];
    int expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 0;
    input1[0] = 0;
    input2[0] = 0;
    expected[0] = 0;
    input0[1] = 1;
    input1[1] = 1;
    input2[1] = 1;
    expected[1] = 2;
    input0[2] = 2;
    input1[2] = 3;
    input2[2] = 4;
    expected[2] = 10;
    input0[3] = 5;
    input1[3] = 10;
    input2[3] = 15;
    expected[3] = 65;
    input0[4] = 10;
    input1[4] = 20;
    input2[4] = 30;
    expected[4] = 230;
    input0[5] = 100;
    input1[5] = 200;
    input2[5] = 300;
    expected[5] = 20300;
    input0[6] = 7;
    input1[6] = 8;
    input2[6] = 9;
    expected[6] = 65;
    input0[7] = 3;
    input1[7] = 4;
    input2[7] = 5;
    expected[7] = 17;
    input0[8] = 50;
    input1[8] = 100;
    input2[8] = 50;
    expected[8] = 5050;
    input0[9] = 123;
    input1[9] = 456;
    input2[9] = 789;
    expected[9] = 56877;

    std::string kernelSource = loadKernel("integer_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_mad24_int", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(int), input0, &err);
    cl_mem inputBuffer1 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(int), input1, &err);
    cl_mem inputBuffer2 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(int), input2, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(int), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &inputBuffer1);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &inputBuffer2);
    clSetKernelArg(kernel, 3, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 4, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(int), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = (output[i] == expected[i]);
        test_results.push_back({"mad24_int", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(inputBuffer1);
    clReleaseMemObject(inputBuffer2);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "mad24_int() tests complete" << std::endl << std::endl;
}

void test_clamp_float() {
    std::cout << "Testing clamp_float()..." << std::endl;

    const int NUM_TESTS = 10;
    float input0[NUM_TESTS];
    float input1[NUM_TESTS];
    float input2[NUM_TESTS];
    float output[NUM_TESTS];
    float expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 0.5f;
    input1[0] = 0.0f;
    input2[0] = 1.0f;
    expected[0] = 0.5f;
    input0[1] = -0.5f;
    input1[1] = 0.0f;
    input2[1] = 1.0f;
    expected[1] = 0.0f;
    input0[2] = 1.5f;
    input1[2] = 0.0f;
    input2[2] = 1.0f;
    expected[2] = 1.0f;
    input0[3] = 5.0f;
    input1[3] = 0.0f;
    input2[3] = 10.0f;
    expected[3] = 5.0f;
    input0[4] = -5.0f;
    input1[4] = 0.0f;
    input2[4] = 10.0f;
    expected[4] = 0.0f;
    input0[5] = 15.0f;
    input1[5] = 0.0f;
    input2[5] = 10.0f;
    expected[5] = 10.0f;
    input0[6] = 7.0f;
    input1[6] = 5.0f;
    input2[6] = 10.0f;
    expected[6] = 7.0f;
    input0[7] = 3.0f;
    input1[7] = 5.0f;
    input2[7] = 10.0f;
    expected[7] = 5.0f;
    input0[8] = 12.0f;
    input1[8] = 5.0f;
    input2[8] = 10.0f;
    expected[8] = 10.0f;
    input0[9] = 0.0f;
    input1[9] = -1.0f;
    input2[9] = 1.0f;
    expected[9] = 0.0f;

    std::string kernelSource = loadKernel("common_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_clamp_float", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input0, &err);
    cl_mem inputBuffer1 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input1, &err);
    cl_mem inputBuffer2 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input2, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(float), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &inputBuffer1);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &inputBuffer2);
    clSetKernelArg(kernel, 3, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 4, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(float), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i], expected[i]);
        test_results.push_back({"clamp_float", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(inputBuffer1);
    clReleaseMemObject(inputBuffer2);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "clamp_float() tests complete" << std::endl << std::endl;
}

void test_degrees() {
    std::cout << "Testing degrees()..." << std::endl;

    const int NUM_TESTS = 10;
    float input0[NUM_TESTS];
    float output[NUM_TESTS];
    float expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 0.0f;
    expected[0] = 0.0f;
    input0[1] = 3.14159265359f;
    expected[1] = 180.0f;
    input0[2] = 1.57079632679f;
    expected[2] = 90.0f;
    input0[3] = 6.28318530718f;
    expected[3] = 360.0f;
    input0[4] = 0.7853981634f;
    expected[4] = 45.0f;
    input0[5] = -3.14159265359f;
    expected[5] = -180.0f;
    input0[6] = -1.57079632679f;
    expected[6] = -90.0f;
    input0[7] = 0.52359877559f;
    expected[7] = 30.0f;
    input0[8] = 1.0471975512f;
    expected[8] = 60.0f;
    input0[9] = 0.2617993878f;
    expected[9] = 15.0f;

    std::string kernelSource = loadKernel("common_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_degrees", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input0, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(float), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(float), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i], expected[i]);
        test_results.push_back({"degrees", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "degrees() tests complete" << std::endl << std::endl;
}

void test_radians() {
    std::cout << "Testing radians()..." << std::endl;

    const int NUM_TESTS = 10;
    float input0[NUM_TESTS];
    float output[NUM_TESTS];
    float expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 0.0f;
    expected[0] = 0.0f;
    input0[1] = 180.0f;
    expected[1] = 3.14159265359f;
    input0[2] = 90.0f;
    expected[2] = 1.57079632679f;
    input0[3] = 360.0f;
    expected[3] = 6.28318530718f;
    input0[4] = 45.0f;
    expected[4] = 0.7853981634f;
    input0[5] = -180.0f;
    expected[5] = -3.14159265359f;
    input0[6] = -90.0f;
    expected[6] = -1.57079632679f;
    input0[7] = 30.0f;
    expected[7] = 0.52359877559f;
    input0[8] = 60.0f;
    expected[8] = 1.0471975512f;
    input0[9] = 15.0f;
    expected[9] = 0.2617993878f;

    std::string kernelSource = loadKernel("common_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_radians", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input0, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(float), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(float), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i], expected[i]);
        test_results.push_back({"radians", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "radians() tests complete" << std::endl << std::endl;
}

void test_max_float() {
    std::cout << "Testing max_float()..." << std::endl;

    const int NUM_TESTS = 10;
    float input0[NUM_TESTS];
    float input1[NUM_TESTS];
    float output[NUM_TESTS];
    float expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 1.0f;
    input1[0] = 2.0f;
    expected[0] = 2.0f;
    input0[1] = 2.0f;
    input1[1] = 1.0f;
    expected[1] = 2.0f;
    input0[2] = 5.0f;
    input1[2] = 5.0f;
    expected[2] = 5.0f;
    input0[3] = -1.0f;
    input1[3] = 1.0f;
    expected[3] = 1.0f;
    input0[4] = 0.0f;
    input1[4] = 0.0f;
    expected[4] = 0.0f;
    input0[5] = -5.0f;
    input1[5] = -3.0f;
    expected[5] = -3.0f;
    input0[6] = 10.0f;
    input1[6] = 100.0f;
    expected[6] = 100.0f;
    input0[7] = 3.14f;
    input1[7] = 2.71f;
    expected[7] = 3.14f;
    input0[8] = -10.0f;
    input1[8] = 10.0f;
    expected[8] = 10.0f;
    input0[9] = 0.5f;
    input1[9] = 0.25f;
    expected[9] = 0.5f;

    std::string kernelSource = loadKernel("common_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_max_float", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input0, &err);
    cl_mem inputBuffer1 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input1, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(float), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &inputBuffer1);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 3, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(float), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i], expected[i]);
        test_results.push_back({"max_float", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(inputBuffer1);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "max_float() tests complete" << std::endl << std::endl;
}

void test_min_float() {
    std::cout << "Testing min_float()..." << std::endl;

    const int NUM_TESTS = 10;
    float input0[NUM_TESTS];
    float input1[NUM_TESTS];
    float output[NUM_TESTS];
    float expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 1.0f;
    input1[0] = 2.0f;
    expected[0] = 1.0f;
    input0[1] = 2.0f;
    input1[1] = 1.0f;
    expected[1] = 1.0f;
    input0[2] = 5.0f;
    input1[2] = 5.0f;
    expected[2] = 5.0f;
    input0[3] = -1.0f;
    input1[3] = 1.0f;
    expected[3] = -1.0f;
    input0[4] = 0.0f;
    input1[4] = 0.0f;
    expected[4] = 0.0f;
    input0[5] = -5.0f;
    input1[5] = -3.0f;
    expected[5] = -5.0f;
    input0[6] = 10.0f;
    input1[6] = 100.0f;
    expected[6] = 10.0f;
    input0[7] = 3.14f;
    input1[7] = 2.71f;
    expected[7] = 2.71f;
    input0[8] = -10.0f;
    input1[8] = 10.0f;
    expected[8] = -10.0f;
    input0[9] = 0.5f;
    input1[9] = 0.25f;
    expected[9] = 0.25f;

    std::string kernelSource = loadKernel("common_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_min_float", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input0, &err);
    cl_mem inputBuffer1 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input1, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(float), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &inputBuffer1);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 3, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(float), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i], expected[i]);
        test_results.push_back({"min_float", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(inputBuffer1);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "min_float() tests complete" << std::endl << std::endl;
}

void test_mix() {
    std::cout << "Testing mix()..." << std::endl;

    const int NUM_TESTS = 10;
    float input0[NUM_TESTS];
    float input1[NUM_TESTS];
    float input2[NUM_TESTS];
    float output[NUM_TESTS];
    float expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 0.0f;
    input1[0] = 10.0f;
    input2[0] = 0.0f;
    expected[0] = 0.0f;
    input0[1] = 0.0f;
    input1[1] = 10.0f;
    input2[1] = 1.0f;
    expected[1] = 10.0f;
    input0[2] = 0.0f;
    input1[2] = 10.0f;
    input2[2] = 0.5f;
    expected[2] = 5.0f;
    input0[3] = 0.0f;
    input1[3] = 10.0f;
    input2[3] = 0.25f;
    expected[3] = 2.5f;
    input0[4] = 0.0f;
    input1[4] = 10.0f;
    input2[4] = 0.75f;
    expected[4] = 7.5f;
    input0[5] = 5.0f;
    input1[5] = 15.0f;
    input2[5] = 0.0f;
    expected[5] = 5.0f;
    input0[6] = 5.0f;
    input1[6] = 15.0f;
    input2[6] = 1.0f;
    expected[6] = 15.0f;
    input0[7] = 5.0f;
    input1[7] = 15.0f;
    input2[7] = 0.5f;
    expected[7] = 10.0f;
    input0[8] = -10.0f;
    input1[8] = 10.0f;
    input2[8] = 0.5f;
    expected[8] = 0.0f;
    input0[9] = 2.0f;
    input1[9] = 8.0f;
    input2[9] = 0.333333f;
    expected[9] = 4.0f;

    std::string kernelSource = loadKernel("common_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_mix", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input0, &err);
    cl_mem inputBuffer1 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input1, &err);
    cl_mem inputBuffer2 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input2, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(float), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &inputBuffer1);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &inputBuffer2);
    clSetKernelArg(kernel, 3, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 4, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(float), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i], expected[i]);
        test_results.push_back({"mix", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(inputBuffer1);
    clReleaseMemObject(inputBuffer2);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "mix() tests complete" << std::endl << std::endl;
}

void test_step() {
    std::cout << "Testing step()..." << std::endl;

    const int NUM_TESTS = 10;
    float input0[NUM_TESTS];
    float input1[NUM_TESTS];
    float output[NUM_TESTS];
    float expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 0.0f;
    input1[0] = -1.0f;
    expected[0] = 0.0f;
    input0[1] = 0.0f;
    input1[1] = 0.0f;
    expected[1] = 1.0f;
    input0[2] = 0.0f;
    input1[2] = 1.0f;
    expected[2] = 1.0f;
    input0[3] = 5.0f;
    input1[3] = 3.0f;
    expected[3] = 0.0f;
    input0[4] = 5.0f;
    input1[4] = 5.0f;
    expected[4] = 1.0f;
    input0[5] = 5.0f;
    input1[5] = 7.0f;
    expected[5] = 1.0f;
    input0[6] = -5.0f;
    input1[6] = -10.0f;
    expected[6] = 0.0f;
    input0[7] = -5.0f;
    input1[7] = -5.0f;
    expected[7] = 1.0f;
    input0[8] = -5.0f;
    input1[8] = 0.0f;
    expected[8] = 1.0f;
    input0[9] = 1.0f;
    input1[9] = 0.999999f;
    expected[9] = 0.0f;

    std::string kernelSource = loadKernel("common_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_step", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input0, &err);
    cl_mem inputBuffer1 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input1, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(float), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &inputBuffer1);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 3, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(float), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i], expected[i]);
        test_results.push_back({"step", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(inputBuffer1);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "step() tests complete" << std::endl << std::endl;
}

void test_smoothstep() {
    std::cout << "Testing smoothstep()..." << std::endl;

    const int NUM_TESTS = 10;
    float input0[NUM_TESTS];
    float input1[NUM_TESTS];
    float input2[NUM_TESTS];
    float output[NUM_TESTS];
    float expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 0.0f;
    input1[0] = 1.0f;
    input2[0] = -1.0f;
    expected[0] = 0.0f;
    input0[1] = 0.0f;
    input1[1] = 1.0f;
    input2[1] = 0.0f;
    expected[1] = 0.0f;
    input0[2] = 0.0f;
    input1[2] = 1.0f;
    input2[2] = 1.0f;
    expected[2] = 1.0f;
    input0[3] = 0.0f;
    input1[3] = 1.0f;
    input2[3] = 2.0f;
    expected[3] = 1.0f;
    input0[4] = 0.0f;
    input1[4] = 1.0f;
    input2[4] = 0.5f;
    expected[4] = 0.5f;
    input0[5] = 0.0f;
    input1[5] = 10.0f;
    input2[5] = 5.0f;
    expected[5] = 0.5f;
    input0[6] = 0.0f;
    input1[6] = 10.0f;
    input2[6] = 2.5f;
    expected[6] = 0.15625f;
    input0[7] = 0.0f;
    input1[7] = 10.0f;
    input2[7] = 7.5f;
    expected[7] = 0.84375f;
    input0[8] = 5.0f;
    input1[8] = 10.0f;
    input2[8] = 7.5f;
    expected[8] = 0.5f;
    input0[9] = -5.0f;
    input1[9] = 5.0f;
    input2[9] = 0.0f;
    expected[9] = 0.5f;

    std::string kernelSource = loadKernel("common_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_smoothstep", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input0, &err);
    cl_mem inputBuffer1 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input1, &err);
    cl_mem inputBuffer2 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input2, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(float), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &inputBuffer1);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &inputBuffer2);
    clSetKernelArg(kernel, 3, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 4, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(float), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i], expected[i]);
        test_results.push_back({"smoothstep", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(inputBuffer1);
    clReleaseMemObject(inputBuffer2);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "smoothstep() tests complete" << std::endl << std::endl;
}

void test_sign() {
    std::cout << "Testing sign()..." << std::endl;

    const int NUM_TESTS = 10;
    float input0[NUM_TESTS];
    float output[NUM_TESTS];
    float expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 0.0f;
    expected[0] = 0.0f;
    input0[1] = 1.0f;
    expected[1] = 1.0f;
    input0[2] = -1.0f;
    expected[2] = -1.0f;
    input0[3] = 5.5f;
    expected[3] = 1.0f;
    input0[4] = -5.5f;
    expected[4] = -1.0f;
    input0[5] = 100.0f;
    expected[5] = 1.0f;
    input0[6] = -100.0f;
    expected[6] = -1.0f;
    input0[7] = 1e-05f;
    expected[7] = 1.0f;
    input0[8] = -1e-05f;
    expected[8] = -1.0f;
    input0[9] = 999999.9f;
    expected[9] = 1.0f;

    std::string kernelSource = loadKernel("common_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_sign", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input0, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(float), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(float), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i], expected[i]);
        test_results.push_back({"sign", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "sign() tests complete" << std::endl << std::endl;
}

void test_clamp_float2() {
    std::cout << "Testing clamp_float2()..." << std::endl;

    const int NUM_TESTS = 10;
    cl_float2 input0[NUM_TESTS];
    cl_float2 input1[NUM_TESTS];
    cl_float2 input2[NUM_TESTS];
    cl_float2 output[NUM_TESTS];
    cl_float2 expected[NUM_TESTS];

    // Initialize test data
    input0[0] = (cl_float2){0.5f, 0.5f};
    input1[0] = (cl_float2){0.0f, 0.0f};
    input2[0] = (cl_float2){1.0f, 1.0f};
    expected[0] = (cl_float2){0.5f, 0.5f};
    input0[1] = (cl_float2){-0.5f, -0.5f};
    input1[1] = (cl_float2){0.0f, 0.0f};
    input2[1] = (cl_float2){1.0f, 1.0f};
    expected[1] = (cl_float2){0.0f, 0.0f};
    input0[2] = (cl_float2){1.5f, 1.5f};
    input1[2] = (cl_float2){0.0f, 0.0f};
    input2[2] = (cl_float2){1.0f, 1.0f};
    expected[2] = (cl_float2){1.0f, 1.0f};
    input0[3] = (cl_float2){0.2f, 0.8f};
    input1[3] = (cl_float2){0.0f, 0.0f};
    input2[3] = (cl_float2){1.0f, 1.0f};
    expected[3] = (cl_float2){0.2f, 0.8f};
    input0[4] = (cl_float2){5.0f, 15.0f};
    input1[4] = (cl_float2){0.0f, 10.0f};
    input2[4] = (cl_float2){10.0f, 20.0f};
    expected[4] = (cl_float2){5.0f, 15.0f};
    input0[5] = (cl_float2){-5.0f, 5.0f};
    input1[5] = (cl_float2){0.0f, 10.0f};
    input2[5] = (cl_float2){10.0f, 20.0f};
    expected[5] = (cl_float2){0.0f, 10.0f};
    input0[6] = (cl_float2){15.0f, 25.0f};
    input1[6] = (cl_float2){0.0f, 10.0f};
    input2[6] = (cl_float2){10.0f, 20.0f};
    expected[6] = (cl_float2){10.0f, 20.0f};
    input0[7] = (cl_float2){3.0f, 7.0f};
    input1[7] = (cl_float2){5.0f, 5.0f};
    input2[7] = (cl_float2){10.0f, 10.0f};
    expected[7] = (cl_float2){5.0f, 7.0f};
    input0[8] = (cl_float2){12.0f, 12.0f};
    input1[8] = (cl_float2){5.0f, 5.0f};
    input2[8] = (cl_float2){10.0f, 10.0f};
    expected[8] = (cl_float2){10.0f, 10.0f};
    input0[9] = (cl_float2){0.0f, 0.5f};
    input1[9] = (cl_float2){-1.0f, 0.0f};
    input2[9] = (cl_float2){1.0f, 1.0f};
    expected[9] = (cl_float2){0.0f, 0.5f};

    std::string kernelSource = loadKernel("common_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_clamp_float2", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(cl_float2), input0, &err);
    cl_mem inputBuffer1 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(cl_float2), input1, &err);
    cl_mem inputBuffer2 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(cl_float2), input2, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(cl_float2), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &inputBuffer1);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &inputBuffer2);
    clSetKernelArg(kernel, 3, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 4, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(cl_float2), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i].s[0], expected[i].s[0]) &&
                       floatEquals(output[i].s[1], expected[i].s[1]);
        test_results.push_back({"clamp_float2", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(inputBuffer1);
    clReleaseMemObject(inputBuffer2);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "clamp_float2() tests complete" << std::endl << std::endl;
}

void test_max_float2() {
    std::cout << "Testing max_float2()..." << std::endl;

    const int NUM_TESTS = 10;
    cl_float2 input0[NUM_TESTS];
    cl_float2 input1[NUM_TESTS];
    cl_float2 output[NUM_TESTS];
    cl_float2 expected[NUM_TESTS];

    // Initialize test data
    input0[0] = (cl_float2){1.0f, 2.0f};
    input1[0] = (cl_float2){2.0f, 1.0f};
    expected[0] = (cl_float2){2.0f, 2.0f};
    input0[1] = (cl_float2){2.0f, 1.0f};
    input1[1] = (cl_float2){1.0f, 2.0f};
    expected[1] = (cl_float2){2.0f, 2.0f};
    input0[2] = (cl_float2){5.0f, 5.0f};
    input1[2] = (cl_float2){5.0f, 5.0f};
    expected[2] = (cl_float2){5.0f, 5.0f};
    input0[3] = (cl_float2){-1.0f, 1.0f};
    input1[3] = (cl_float2){1.0f, -1.0f};
    expected[3] = (cl_float2){1.0f, 1.0f};
    input0[4] = (cl_float2){0.0f, 0.0f};
    input1[4] = (cl_float2){0.0f, 0.0f};
    expected[4] = (cl_float2){0.0f, 0.0f};
    input0[5] = (cl_float2){-5.0f, -3.0f};
    input1[5] = (cl_float2){-3.0f, -5.0f};
    expected[5] = (cl_float2){-3.0f, -3.0f};
    input0[6] = (cl_float2){10.0f, 100.0f};
    input1[6] = (cl_float2){100.0f, 10.0f};
    expected[6] = (cl_float2){100.0f, 100.0f};
    input0[7] = (cl_float2){3.14f, 2.71f};
    input1[7] = (cl_float2){2.71f, 3.14f};
    expected[7] = (cl_float2){3.14f, 3.14f};
    input0[8] = (cl_float2){-10.0f, 10.0f};
    input1[8] = (cl_float2){10.0f, -10.0f};
    expected[8] = (cl_float2){10.0f, 10.0f};
    input0[9] = (cl_float2){0.5f, 0.25f};
    input1[9] = (cl_float2){0.25f, 0.5f};
    expected[9] = (cl_float2){0.5f, 0.5f};

    std::string kernelSource = loadKernel("common_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_max_float2", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(cl_float2), input0, &err);
    cl_mem inputBuffer1 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(cl_float2), input1, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(cl_float2), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &inputBuffer1);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 3, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(cl_float2), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i].s[0], expected[i].s[0]) &&
                       floatEquals(output[i].s[1], expected[i].s[1]);
        test_results.push_back({"max_float2", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(inputBuffer1);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "max_float2() tests complete" << std::endl << std::endl;
}

void test_min_float2() {
    std::cout << "Testing min_float2()..." << std::endl;

    const int NUM_TESTS = 10;
    cl_float2 input0[NUM_TESTS];
    cl_float2 input1[NUM_TESTS];
    cl_float2 output[NUM_TESTS];
    cl_float2 expected[NUM_TESTS];

    // Initialize test data
    input0[0] = (cl_float2){1.0f, 2.0f};
    input1[0] = (cl_float2){2.0f, 1.0f};
    expected[0] = (cl_float2){1.0f, 1.0f};
    input0[1] = (cl_float2){2.0f, 1.0f};
    input1[1] = (cl_float2){1.0f, 2.0f};
    expected[1] = (cl_float2){1.0f, 1.0f};
    input0[2] = (cl_float2){5.0f, 5.0f};
    input1[2] = (cl_float2){5.0f, 5.0f};
    expected[2] = (cl_float2){5.0f, 5.0f};
    input0[3] = (cl_float2){-1.0f, 1.0f};
    input1[3] = (cl_float2){1.0f, -1.0f};
    expected[3] = (cl_float2){-1.0f, -1.0f};
    input0[4] = (cl_float2){0.0f, 0.0f};
    input1[4] = (cl_float2){0.0f, 0.0f};
    expected[4] = (cl_float2){0.0f, 0.0f};
    input0[5] = (cl_float2){-5.0f, -3.0f};
    input1[5] = (cl_float2){-3.0f, -5.0f};
    expected[5] = (cl_float2){-5.0f, -5.0f};
    input0[6] = (cl_float2){10.0f, 100.0f};
    input1[6] = (cl_float2){100.0f, 10.0f};
    expected[6] = (cl_float2){10.0f, 10.0f};
    input0[7] = (cl_float2){3.14f, 2.71f};
    input1[7] = (cl_float2){2.71f, 3.14f};
    expected[7] = (cl_float2){2.71f, 2.71f};
    input0[8] = (cl_float2){-10.0f, 10.0f};
    input1[8] = (cl_float2){10.0f, -10.0f};
    expected[8] = (cl_float2){-10.0f, -10.0f};
    input0[9] = (cl_float2){0.5f, 0.25f};
    input1[9] = (cl_float2){0.25f, 0.5f};
    expected[9] = (cl_float2){0.25f, 0.25f};

    std::string kernelSource = loadKernel("common_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_min_float2", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(cl_float2), input0, &err);
    cl_mem inputBuffer1 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(cl_float2), input1, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(cl_float2), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &inputBuffer1);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 3, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(cl_float2), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i].s[0], expected[i].s[0]) &&
                       floatEquals(output[i].s[1], expected[i].s[1]);
        test_results.push_back({"min_float2", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(inputBuffer1);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "min_float2() tests complete" << std::endl << std::endl;
}

void test_sqrt() {
    std::cout << "Testing sqrt()..." << std::endl;

    const int NUM_TESTS = 10;
    float input0[NUM_TESTS];
    float output[NUM_TESTS];
    float expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 0.0f;
    expected[0] = 0.0f;
    input0[1] = 1.0f;
    expected[1] = 1.0f;
    input0[2] = 4.0f;
    expected[2] = 2.0f;
    input0[3] = 9.0f;
    expected[3] = 3.0f;
    input0[4] = 16.0f;
    expected[4] = 4.0f;
    input0[5] = 25.0f;
    expected[5] = 5.0f;
    input0[6] = 36.0f;
    expected[6] = 6.0f;
    input0[7] = 49.0f;
    expected[7] = 7.0f;
    input0[8] = 64.0f;
    expected[8] = 8.0f;
    input0[9] = 81.0f;
    expected[9] = 9.0f;

    std::string kernelSource = loadKernel("math_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_sqrt", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input0, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(float), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(float), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i], expected[i]);
        test_results.push_back({"sqrt", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "sqrt() tests complete" << std::endl << std::endl;
}

void test_sin() {
    std::cout << "Testing sin()..." << std::endl;

    const int NUM_TESTS = 10;
    float input0[NUM_TESTS];
    float output[NUM_TESTS];
    float expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 0.0f;
    expected[0] = 0.0f;
    input0[1] = 0.5235987756f;
    expected[1] = 0.5f;
    input0[2] = 0.7853981634f;
    expected[2] = 0.7071067812f;
    input0[3] = 1.0471975512f;
    expected[3] = 0.8660254038f;
    input0[4] = 1.5707963268f;
    expected[4] = 1.0f;
    input0[5] = 3.1415926536f;
    expected[5] = 0.0f;
    input0[6] = 4.7123889804f;
    expected[6] = -1.0f;
    input0[7] = 6.2831853072f;
    expected[7] = 0.0f;
    input0[8] = -1.5707963268f;
    expected[8] = -1.0f;
    input0[9] = -3.1415926536f;
    expected[9] = 0.0f;

    std::string kernelSource = loadKernel("math_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_sin", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input0, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(float), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(float), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i], expected[i]);
        test_results.push_back({"sin", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "sin() tests complete" << std::endl << std::endl;
}

void test_cos() {
    std::cout << "Testing cos()..." << std::endl;

    const int NUM_TESTS = 10;
    float input0[NUM_TESTS];
    float output[NUM_TESTS];
    float expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 0.0f;
    expected[0] = 1.0f;
    input0[1] = 0.5235987756f;
    expected[1] = 0.8660254038f;
    input0[2] = 0.7853981634f;
    expected[2] = 0.7071067812f;
    input0[3] = 1.0471975512f;
    expected[3] = 0.5f;
    input0[4] = 1.5707963268f;
    expected[4] = 0.0f;
    input0[5] = 3.1415926536f;
    expected[5] = -1.0f;
    input0[6] = 4.7123889804f;
    expected[6] = 0.0f;
    input0[7] = 6.2831853072f;
    expected[7] = 1.0f;
    input0[8] = -1.5707963268f;
    expected[8] = 0.0f;
    input0[9] = -3.1415926536f;
    expected[9] = -1.0f;

    std::string kernelSource = loadKernel("math_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_cos", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input0, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(float), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(float), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i], expected[i]);
        test_results.push_back({"cos", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "cos() tests complete" << std::endl << std::endl;
}

void test_tan() {
    std::cout << "Testing tan()..." << std::endl;

    const int NUM_TESTS = 10;
    float input0[NUM_TESTS];
    float output[NUM_TESTS];
    float expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 0.0f;
    expected[0] = 0.0f;
    input0[1] = 0.7853981634f;
    expected[1] = 1.0f;
    input0[2] = 0.463647609f;
    expected[2] = 0.5f;
    input0[3] = 1.1071487178f;
    expected[3] = 2.0f;
    input0[4] = -0.7853981634f;
    expected[4] = -1.0f;
    input0[5] = 0.3217505544f;
    expected[5] = 0.333333333f;
    input0[6] = 1.2490457724f;
    expected[6] = 3.0f;
    input0[7] = 1.3734008f;
    expected[7] = 4.0f;
    input0[8] = -0.463647609f;
    expected[8] = -0.5f;
    input0[9] = 0.19739555984988078f;
    expected[9] = 0.2f;

    std::string kernelSource = loadKernel("math_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_tan", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input0, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(float), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(float), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i], expected[i]);
        test_results.push_back({"tan", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "tan() tests complete" << std::endl << std::endl;
}

void test_asin() {
    std::cout << "Testing asin()..." << std::endl;

    const int NUM_TESTS = 10;
    float input0[NUM_TESTS];
    float output[NUM_TESTS];
    float expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 0.0f;
    expected[0] = 0.0f;
    input0[1] = 0.5f;
    expected[1] = 0.5235987756f;
    input0[2] = 0.7071067812f;
    expected[2] = 0.7853981634f;
    input0[3] = 0.8660254038f;
    expected[3] = 1.0471975512f;
    input0[4] = 1.0f;
    expected[4] = 1.5707963268f;
    input0[5] = -0.5f;
    expected[5] = -0.5235987756f;
    input0[6] = -1.0f;
    expected[6] = -1.5707963268f;
    input0[7] = 0.25f;
    expected[7] = 0.2526802551f;
    input0[8] = 0.75f;
    expected[8] = 0.8480620789f;
    input0[9] = 0.3f;
    expected[9] = 0.304692654f;

    std::string kernelSource = loadKernel("math_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_asin", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input0, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(float), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(float), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i], expected[i]);
        test_results.push_back({"asin", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "asin() tests complete" << std::endl << std::endl;
}

void test_acos() {
    std::cout << "Testing acos()..." << std::endl;

    const int NUM_TESTS = 10;
    float input0[NUM_TESTS];
    float output[NUM_TESTS];
    float expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 1.0f;
    expected[0] = 0.0f;
    input0[1] = 0.8660254038f;
    expected[1] = 0.5235987756f;
    input0[2] = 0.7071067812f;
    expected[2] = 0.7853981634f;
    input0[3] = 0.5f;
    expected[3] = 1.0471975512f;
    input0[4] = 0.0f;
    expected[4] = 1.5707963268f;
    input0[5] = -1.0f;
    expected[5] = 3.1415926536f;
    input0[6] = 0.25f;
    expected[6] = 1.3181160716f;
    input0[7] = 0.75f;
    expected[7] = 0.7227342478f;
    input0[8] = -0.5f;
    expected[8] = 2.0943951024f;
    input0[9] = 0.9f;
    expected[9] = 0.4510268118f;

    std::string kernelSource = loadKernel("math_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_acos", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input0, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(float), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(float), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i], expected[i]);
        test_results.push_back({"acos", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "acos() tests complete" << std::endl << std::endl;
}

void test_atan() {
    std::cout << "Testing atan()..." << std::endl;

    const int NUM_TESTS = 10;
    float input0[NUM_TESTS];
    float output[NUM_TESTS];
    float expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 0.0f;
    expected[0] = 0.0f;
    input0[1] = 1.0f;
    expected[1] = 0.7853981634f;
    input0[2] = 2.0f;
    expected[2] = 1.1071487178f;
    input0[3] = 3.0f;
    expected[3] = 1.2490457724f;
    input0[4] = -1.0f;
    expected[4] = -0.7853981634f;
    input0[5] = 0.5f;
    expected[5] = 0.463647609f;
    input0[6] = 10.0f;
    expected[6] = 1.4711276743f;
    input0[7] = -2.0f;
    expected[7] = -1.1071487178f;
    input0[8] = 0.1f;
    expected[8] = 0.0996686525f;
    input0[9] = 100.0f;
    expected[9] = 1.5607966601f;

    std::string kernelSource = loadKernel("math_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_atan", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input0, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(float), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(float), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i], expected[i]);
        test_results.push_back({"atan", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "atan() tests complete" << std::endl << std::endl;
}

void test_exp() {
    std::cout << "Testing exp()..." << std::endl;

    const int NUM_TESTS = 10;
    float input0[NUM_TESTS];
    float output[NUM_TESTS];
    float expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 0.0f;
    expected[0] = 1.0f;
    input0[1] = 1.0f;
    expected[1] = 2.7182818285f;
    input0[2] = 2.0f;
    expected[2] = 7.3890560989f;
    input0[3] = -1.0f;
    expected[3] = 0.3678794412f;
    input0[4] = 0.5f;
    expected[4] = 1.6487212707f;
    input0[5] = 3.0f;
    expected[5] = 20.0855369232f;
    input0[6] = -2.0f;
    expected[6] = 0.1353352832f;
    input0[7] = 0.1f;
    expected[7] = 1.1051709181f;
    input0[8] = 4.0f;
    expected[8] = 54.5981500331f;
    input0[9] = -0.5f;
    expected[9] = 0.6065306597f;

    std::string kernelSource = loadKernel("math_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_exp", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input0, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(float), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(float), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i], expected[i]);
        test_results.push_back({"exp", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "exp() tests complete" << std::endl << std::endl;
}

void test_log() {
    std::cout << "Testing log()..." << std::endl;

    const int NUM_TESTS = 10;
    float input0[NUM_TESTS];
    float output[NUM_TESTS];
    float expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 1.0f;
    expected[0] = 0.0f;
    input0[1] = 2.7182818285f;
    expected[1] = 1.0f;
    input0[2] = 7.3890560989f;
    expected[2] = 2.0f;
    input0[3] = 2.0f;
    expected[3] = 0.6931471806f;
    input0[4] = 10.0f;
    expected[4] = 2.302585093f;
    input0[5] = 0.5f;
    expected[5] = -0.6931471806f;
    input0[6] = 100.0f;
    expected[6] = 4.605170186f;
    input0[7] = 0.1f;
    expected[7] = -2.302585093f;
    input0[8] = 5.0f;
    expected[8] = 1.6094379124f;
    input0[9] = 0.01f;
    expected[9] = -4.605170186f;

    std::string kernelSource = loadKernel("math_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_log", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input0, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(float), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(float), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i], expected[i]);
        test_results.push_back({"log", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "log() tests complete" << std::endl << std::endl;
}

void test_pow() {
    std::cout << "Testing pow()..." << std::endl;

    const int NUM_TESTS = 10;
    float input0[NUM_TESTS];
    float input1[NUM_TESTS];
    float output[NUM_TESTS];
    float expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 2.0f;
    input1[0] = 3.0f;
    expected[0] = 8.0f;
    input0[1] = 3.0f;
    input1[1] = 2.0f;
    expected[1] = 9.0f;
    input0[2] = 10.0f;
    input1[2] = 2.0f;
    expected[2] = 100.0f;
    input0[3] = 2.0f;
    input1[3] = 10.0f;
    expected[3] = 1024.0f;
    input0[4] = 5.0f;
    input1[4] = 3.0f;
    expected[4] = 125.0f;
    input0[5] = 2.0f;
    input1[5] = 0.5f;
    expected[5] = 1.4142135624f;
    input0[6] = 4.0f;
    input1[6] = 0.5f;
    expected[6] = 2.0f;
    input0[7] = 2.0f;
    input1[7] = -1.0f;
    expected[7] = 0.5f;
    input0[8] = 10.0f;
    input1[8] = 3.0f;
    expected[8] = 1000.0f;
    input0[9] = 3.0f;
    input1[9] = 4.0f;
    expected[9] = 81.0f;

    std::string kernelSource = loadKernel("math_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_pow", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input0, &err);
    cl_mem inputBuffer1 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input1, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(float), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &inputBuffer1);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 3, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(float), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i], expected[i]);
        test_results.push_back({"pow", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(inputBuffer1);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "pow() tests complete" << std::endl << std::endl;
}

void test_atan2() {
    std::cout << "Testing atan2()..." << std::endl;

    const int NUM_TESTS = 10;
    float input0[NUM_TESTS];
    float input1[NUM_TESTS];
    float output[NUM_TESTS];
    float expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 1.0f;
    input1[0] = 1.0f;
    expected[0] = 0.7853981633974483f;
    input0[1] = 2.0f;
    input1[1] = 3.0f;
    expected[1] = 0.5880026035475675f;
    input0[2] = 5.0f;
    input1[2] = 2.0f;
    expected[2] = 1.1902899496825317f;
    input0[3] = 10.0f;
    input1[3] = 0.5f;
    expected[3] = 1.5208379310729538f;
    input0[4] = 3.0f;
    input1[4] = 4.0f;
    expected[4] = 0.6435011087932844f;
    input0[5] = -1.0f;
    input1[5] = 1.0f;
    expected[5] = -0.7853981633974483f;
    input0[6] = 1.0f;
    input1[6] = -1.0f;
    expected[6] = 2.356194490192345f;
    input0[7] = 0.5f;
    input1[7] = 0.5f;
    expected[7] = 0.7853981633974483f;
    input0[8] = 100.0f;
    input1[8] = 10.0f;
    expected[8] = 1.4711276743037347f;
    input0[9] = 7.0f;
    input1[9] = 3.0f;
    expected[9] = 1.1659045405098132f;

    std::string kernelSource = loadKernel("math_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_atan2", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input0, &err);
    cl_mem inputBuffer1 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input1, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(float), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &inputBuffer1);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 3, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(float), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i], expected[i]);
        test_results.push_back({"atan2", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(inputBuffer1);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "atan2() tests complete" << std::endl << std::endl;
}

void test_sinh() {
    std::cout << "Testing sinh()..." << std::endl;

    const int NUM_TESTS = 10;
    float input0[NUM_TESTS];
    float output[NUM_TESTS];
    float expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 0.0f;
    expected[0] = 0.0f;
    input0[1] = 1.0f;
    expected[1] = 1.1752011936438014f;
    input0[2] = -1.0f;
    expected[2] = -1.1752011936438014f;
    input0[3] = 0.5f;
    expected[3] = 0.5210953054937474f;
    input0[4] = -0.5f;
    expected[4] = -0.5210953054937474f;
    input0[5] = 2.0f;
    expected[5] = 3.626860407847019f;
    input0[6] = -2.0f;
    expected[6] = -3.626860407847019f;
    input0[7] = 10.0f;
    expected[7] = 11013.232874703393f;
    input0[8] = -10.0f;
    expected[8] = -11013.232874703393f;
    input0[9] = 100.0f;
    expected[9] = 1.3440585709080678e+43f;

    std::string kernelSource = loadKernel("math_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_sinh", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input0, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(float), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(float), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i], expected[i]);
        test_results.push_back({"sinh", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "sinh() tests complete" << std::endl << std::endl;
}

void test_cosh() {
    std::cout << "Testing cosh()..." << std::endl;

    const int NUM_TESTS = 10;
    float input0[NUM_TESTS];
    float output[NUM_TESTS];
    float expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 0.0f;
    expected[0] = 1.0f;
    input0[1] = 1.0f;
    expected[1] = 1.5430806348152437f;
    input0[2] = -1.0f;
    expected[2] = 1.5430806348152437f;
    input0[3] = 0.5f;
    expected[3] = 1.1276259652063807f;
    input0[4] = -0.5f;
    expected[4] = 1.1276259652063807f;
    input0[5] = 2.0f;
    expected[5] = 3.7621956910836314f;
    input0[6] = -2.0f;
    expected[6] = 3.7621956910836314f;
    input0[7] = 10.0f;
    expected[7] = 11013.232920103324f;
    input0[8] = -10.0f;
    expected[8] = 11013.232920103324f;
    input0[9] = 100.0f;
    expected[9] = 1.3440585709080678e+43f;

    std::string kernelSource = loadKernel("math_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_cosh", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input0, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(float), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(float), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i], expected[i]);
        test_results.push_back({"cosh", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "cosh() tests complete" << std::endl << std::endl;
}

void test_tanh() {
    std::cout << "Testing tanh()..." << std::endl;

    const int NUM_TESTS = 10;
    float input0[NUM_TESTS];
    float output[NUM_TESTS];
    float expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 0.0f;
    expected[0] = 0.0f;
    input0[1] = 1.0f;
    expected[1] = 0.7615941559557649f;
    input0[2] = -1.0f;
    expected[2] = -0.7615941559557649f;
    input0[3] = 0.5f;
    expected[3] = 0.46211715726000974f;
    input0[4] = -0.5f;
    expected[4] = -0.46211715726000974f;
    input0[5] = 2.0f;
    expected[5] = 0.9640275800758169f;
    input0[6] = -2.0f;
    expected[6] = -0.9640275800758169f;
    input0[7] = 10.0f;
    expected[7] = 0.9999999958776927f;
    input0[8] = -10.0f;
    expected[8] = -0.9999999958776927f;
    input0[9] = 100.0f;
    expected[9] = 1.0f;

    std::string kernelSource = loadKernel("math_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_tanh", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input0, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(float), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(float), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i], expected[i]);
        test_results.push_back({"tanh", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "tanh() tests complete" << std::endl << std::endl;
}

void test_asinh() {
    std::cout << "Testing asinh()..." << std::endl;

    const int NUM_TESTS = 10;
    float input0[NUM_TESTS];
    float output[NUM_TESTS];
    float expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 0.0f;
    expected[0] = 0.0f;
    input0[1] = 1.0f;
    expected[1] = 0.881373587019543f;
    input0[2] = -1.0f;
    expected[2] = -0.881373587019543f;
    input0[3] = 0.5f;
    expected[3] = 0.48121182505960347f;
    input0[4] = -0.5f;
    expected[4] = -0.48121182505960347f;
    input0[5] = 2.0f;
    expected[5] = 1.4436354751788103f;
    input0[6] = -2.0f;
    expected[6] = -1.4436354751788103f;
    input0[7] = 10.0f;
    expected[7] = 2.99822295029797f;
    input0[8] = -10.0f;
    expected[8] = -2.99822295029797f;
    input0[9] = 100.0f;
    expected[9] = 5.298342365610589f;

    std::string kernelSource = loadKernel("math_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_asinh", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input0, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(float), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(float), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i], expected[i]);
        test_results.push_back({"asinh", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "asinh() tests complete" << std::endl << std::endl;
}

void test_acosh() {
    std::cout << "Testing acosh()..." << std::endl;

    const int NUM_TESTS = 10;
    float input0[NUM_TESTS];
    float output[NUM_TESTS];
    float expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 0.0f;
    expected[0] = 0.0f;
    input0[1] = 1.0f;
    expected[1] = 0.0f;
    input0[2] = -1.0f;
    expected[2] = 0.0f;
    input0[3] = 0.5f;
    expected[3] = 0.0f;
    input0[4] = -0.5f;
    expected[4] = 0.0f;
    input0[5] = 2.0f;
    expected[5] = 1.3169578969248166f;
    input0[6] = -2.0f;
    expected[6] = 0.0f;
    input0[7] = 10.0f;
    expected[7] = 2.993222846126381f;
    input0[8] = -10.0f;
    expected[8] = 0.0f;
    input0[9] = 100.0f;
    expected[9] = 5.298292365610484f;

    std::string kernelSource = loadKernel("math_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_acosh", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input0, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(float), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(float), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i], expected[i]);
        test_results.push_back({"acosh", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "acosh() tests complete" << std::endl << std::endl;
}

void test_atanh() {
    std::cout << "Testing atanh()..." << std::endl;

    const int NUM_TESTS = 10;
    float input0[NUM_TESTS];
    float output[NUM_TESTS];
    float expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 0.0f;
    expected[0] = 0.0f;
    input0[1] = 1.0f;
    expected[1] = 2.6466524123622457f;
    input0[2] = -1.0f;
    expected[2] = -2.6466524123622457f;
    input0[3] = 0.5f;
    expected[3] = 0.5493061443340548f;
    input0[4] = -0.5f;
    expected[4] = -0.5493061443340548f;
    input0[5] = 2.0f;
    expected[5] = 2.6466524123622457f;
    input0[6] = -2.0f;
    expected[6] = -2.6466524123622457f;
    input0[7] = 10.0f;
    expected[7] = 2.6466524123622457f;
    input0[8] = -10.0f;
    expected[8] = -2.6466524123622457f;
    input0[9] = 100.0f;
    expected[9] = 2.6466524123622457f;

    std::string kernelSource = loadKernel("math_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_atanh", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input0, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(float), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(float), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i], expected[i]);
        test_results.push_back({"atanh", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "atanh() tests complete" << std::endl << std::endl;
}

void test_exp2() {
    std::cout << "Testing exp2()..." << std::endl;

    const int NUM_TESTS = 10;
    float input0[NUM_TESTS];
    float output[NUM_TESTS];
    float expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 0.0f;
    expected[0] = 1.0f;
    input0[1] = 1.0f;
    expected[1] = 2.0f;
    input0[2] = -1.0f;
    expected[2] = 0.5f;
    input0[3] = 0.5f;
    expected[3] = 1.4142135623730951f;
    input0[4] = -0.5f;
    expected[4] = 0.7071067811865476f;
    input0[5] = 2.0f;
    expected[5] = 4.0f;
    input0[6] = -2.0f;
    expected[6] = 0.25f;
    input0[7] = 10.0f;
    expected[7] = 1024.0f;
    input0[8] = -10.0f;
    expected[8] = 0.0009765625f;
    input0[9] = 100.0f;
    expected[9] = 1.2676506002282294e+30f;

    std::string kernelSource = loadKernel("math_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_exp2", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input0, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(float), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(float), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i], expected[i]);
        test_results.push_back({"exp2", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "exp2() tests complete" << std::endl << std::endl;
}

void test_exp10() {
    std::cout << "Testing exp10()..." << std::endl;

    const int NUM_TESTS = 10;
    float input0[NUM_TESTS];
    float output[NUM_TESTS];
    float expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 0.0f;
    expected[0] = 1.0f;
    input0[1] = 1.0f;
    expected[1] = 10.0f;
    input0[2] = -1.0f;
    expected[2] = 0.1f;
    input0[3] = 0.5f;
    expected[3] = 3.1622776601683795f;
    input0[4] = -0.5f;
    expected[4] = 0.31622776601683794f;
    input0[5] = 2.0f;
    expected[5] = 100.0f;
    input0[6] = -2.0f;
    expected[6] = 0.01f;
    input0[7] = 10.0f;
    expected[7] = 10000000000.0f;
    input0[8] = -10.0f;
    expected[8] = 1e-10f;
    input0[9] = 100.0f;
    expected[9] = 1e+100f;

    std::string kernelSource = loadKernel("math_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_exp10", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input0, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(float), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(float), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i], expected[i]);
        test_results.push_back({"exp10", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "exp10() tests complete" << std::endl << std::endl;
}

void test_expm1() {
    std::cout << "Testing expm1()..." << std::endl;

    const int NUM_TESTS = 10;
    float input0[NUM_TESTS];
    float output[NUM_TESTS];
    float expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 0.0f;
    expected[0] = 0.0f;
    input0[1] = 1.0f;
    expected[1] = 1.718281828459045f;
    input0[2] = -1.0f;
    expected[2] = -0.6321205588285577f;
    input0[3] = 0.5f;
    expected[3] = 0.6487212707001282f;
    input0[4] = -0.5f;
    expected[4] = -0.3934693402873666f;
    input0[5] = 2.0f;
    expected[5] = 6.38905609893065f;
    input0[6] = -2.0f;
    expected[6] = -0.8646647167633873f;
    input0[7] = 10.0f;
    expected[7] = 22025.465794806718f;
    input0[8] = -10.0f;
    expected[8] = -0.9999546000702375f;
    input0[9] = 100.0f;
    expected[9] = 2.6881171418161356e+43f;

    std::string kernelSource = loadKernel("math_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_expm1", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input0, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(float), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(float), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i], expected[i]);
        test_results.push_back({"expm1", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "expm1() tests complete" << std::endl << std::endl;
}

void test_log2() {
    std::cout << "Testing log2()..." << std::endl;

    const int NUM_TESTS = 10;
    float input0[NUM_TESTS];
    float output[NUM_TESTS];
    float expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 0.0f;
    expected[0] = -9.965784284662087f;
    input0[1] = 1.0f;
    expected[1] = 0.0f;
    input0[2] = -1.0f;
    expected[2] = -9.965784284662087f;
    input0[3] = 0.5f;
    expected[3] = -1.0f;
    input0[4] = -0.5f;
    expected[4] = -9.965784284662087f;
    input0[5] = 2.0f;
    expected[5] = 1.0f;
    input0[6] = -2.0f;
    expected[6] = -9.965784284662087f;
    input0[7] = 10.0f;
    expected[7] = 3.321928094887362f;
    input0[8] = -10.0f;
    expected[8] = -9.965784284662087f;
    input0[9] = 100.0f;
    expected[9] = 6.643856189774724f;

    std::string kernelSource = loadKernel("math_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_log2", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input0, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(float), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(float), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i], expected[i]);
        test_results.push_back({"log2", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "log2() tests complete" << std::endl << std::endl;
}

void test_log10() {
    std::cout << "Testing log10()..." << std::endl;

    const int NUM_TESTS = 10;
    float input0[NUM_TESTS];
    float output[NUM_TESTS];
    float expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 0.0f;
    expected[0] = -3.0f;
    input0[1] = 1.0f;
    expected[1] = 0.0f;
    input0[2] = -1.0f;
    expected[2] = -3.0f;
    input0[3] = 0.5f;
    expected[3] = -0.3010299956639812f;
    input0[4] = -0.5f;
    expected[4] = -3.0f;
    input0[5] = 2.0f;
    expected[5] = 0.3010299956639812f;
    input0[6] = -2.0f;
    expected[6] = -3.0f;
    input0[7] = 10.0f;
    expected[7] = 1.0f;
    input0[8] = -10.0f;
    expected[8] = -3.0f;
    input0[9] = 100.0f;
    expected[9] = 2.0f;

    std::string kernelSource = loadKernel("math_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_log10", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input0, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(float), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(float), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i], expected[i]);
        test_results.push_back({"log10", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "log10() tests complete" << std::endl << std::endl;
}

void test_log1p() {
    std::cout << "Testing log1p()..." << std::endl;

    const int NUM_TESTS = 10;
    float input0[NUM_TESTS];
    float output[NUM_TESTS];
    float expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 0.0f;
    expected[0] = 0.0f;
    input0[1] = 1.0f;
    expected[1] = 0.6931471805599453f;
    input0[2] = -1.0f;
    expected[2] = -4.60517018598809f;
    input0[3] = 0.5f;
    expected[3] = 0.4054651081081644f;
    input0[4] = -0.5f;
    expected[4] = -0.6931471805599453f;
    input0[5] = 2.0f;
    expected[5] = 1.0986122886681096f;
    input0[6] = -2.0f;
    expected[6] = -4.60517018598809f;
    input0[7] = 10.0f;
    expected[7] = 2.3978952727983707f;
    input0[8] = -10.0f;
    expected[8] = -4.60517018598809f;
    input0[9] = 100.0f;
    expected[9] = 4.61512051684126f;

    std::string kernelSource = loadKernel("math_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_log1p", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input0, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(float), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(float), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i], expected[i]);
        test_results.push_back({"log1p", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "log1p() tests complete" << std::endl << std::endl;
}

void test_cbrt() {
    std::cout << "Testing cbrt()..." << std::endl;

    const int NUM_TESTS = 10;
    float input0[NUM_TESTS];
    float output[NUM_TESTS];
    float expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 0.0f;
    expected[0] = 0.0f;
    input0[1] = 1.0f;
    expected[1] = 1.0f;
    input0[2] = -1.0f;
    expected[2] = -1.0f;
    input0[3] = 0.5f;
    expected[3] = 0.7937005259840998f;
    input0[4] = -0.5f;
    expected[4] = -0.7937005259840998f;
    input0[5] = 2.0f;
    expected[5] = 1.2599210498948732f;
    input0[6] = -2.0f;
    expected[6] = -1.2599210498948732f;
    input0[7] = 10.0f;
    expected[7] = 2.154434690031884f;
    input0[8] = -10.0f;
    expected[8] = -2.154434690031884f;
    input0[9] = 100.0f;
    expected[9] = 4.641588833612778f;

    std::string kernelSource = loadKernel("math_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_cbrt", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input0, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(float), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(float), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i], expected[i]);
        test_results.push_back({"cbrt", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "cbrt() tests complete" << std::endl << std::endl;
}

void test_rsqrt() {
    std::cout << "Testing rsqrt()..." << std::endl;

    const int NUM_TESTS = 10;
    float input0[NUM_TESTS];
    float output[NUM_TESTS];
    float expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 0.0f;
    expected[0] = 31.622776601683796f;
    input0[1] = 1.0f;
    expected[1] = 1.0f;
    input0[2] = -1.0f;
    expected[2] = 31.622776601683796f;
    input0[3] = 0.5f;
    expected[3] = 1.414213562373095f;
    input0[4] = -0.5f;
    expected[4] = 31.622776601683796f;
    input0[5] = 2.0f;
    expected[5] = 0.7071067811865475f;
    input0[6] = -2.0f;
    expected[6] = 31.622776601683796f;
    input0[7] = 10.0f;
    expected[7] = 0.31622776601683794f;
    input0[8] = -10.0f;
    expected[8] = 31.622776601683796f;
    input0[9] = 100.0f;
    expected[9] = 0.1f;

    std::string kernelSource = loadKernel("math_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_rsqrt", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input0, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(float), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(float), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i], expected[i]);
        test_results.push_back({"rsqrt", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "rsqrt() tests complete" << std::endl << std::endl;
}

void test_pown() {
    std::cout << "Testing pown()..." << std::endl;

    const int NUM_TESTS = 10;
    float input0[NUM_TESTS];
    float input1[NUM_TESTS];
    float output[NUM_TESTS];
    float expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 1.0f;
    input1[0] = 1.0f;
    expected[0] = 1.0f;
    input0[1] = 2.0f;
    input1[1] = 3.0f;
    expected[1] = 8.0f;
    input0[2] = 5.0f;
    input1[2] = 2.0f;
    expected[2] = 25.0f;
    input0[3] = 10.0f;
    input1[3] = 0.5f;
    expected[3] = 3.1622776601683795f;
    input0[4] = 3.0f;
    input1[4] = 4.0f;
    expected[4] = 81.0f;
    input0[5] = -1.0f;
    input1[5] = 1.0f;
    expected[5] = -1.0f;
    input0[6] = 1.0f;
    input1[6] = -1.0f;
    expected[6] = 1.0f;
    input0[7] = 0.5f;
    input1[7] = 0.5f;
    expected[7] = 0.7071067811865476f;
    input0[8] = 100.0f;
    input1[8] = 10.0f;
    expected[8] = 1e+20f;
    input0[9] = 7.0f;
    input1[9] = 3.0f;
    expected[9] = 343.0f;

    std::string kernelSource = loadKernel("math_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_pown", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input0, &err);
    cl_mem inputBuffer1 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input1, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(float), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &inputBuffer1);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 3, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(float), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i], expected[i]);
        test_results.push_back({"pown", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(inputBuffer1);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "pown() tests complete" << std::endl << std::endl;
}

void test_powr() {
    std::cout << "Testing powr()..." << std::endl;

    const int NUM_TESTS = 10;
    float input0[NUM_TESTS];
    float input1[NUM_TESTS];
    float output[NUM_TESTS];
    float expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 1.0f;
    input1[0] = 1.0f;
    expected[0] = 1.0f;
    input0[1] = 2.0f;
    input1[1] = 3.0f;
    expected[1] = 8.0f;
    input0[2] = 5.0f;
    input1[2] = 2.0f;
    expected[2] = 25.0f;
    input0[3] = 10.0f;
    input1[3] = 0.5f;
    expected[3] = 3.1622776601683795f;
    input0[4] = 3.0f;
    input1[4] = 4.0f;
    expected[4] = 81.0f;
    input0[5] = -1.0f;
    input1[5] = 1.0f;
    expected[5] = 0.001f;
    input0[6] = 1.0f;
    input1[6] = -1.0f;
    expected[6] = 1.0f;
    input0[7] = 0.5f;
    input1[7] = 0.5f;
    expected[7] = 0.7071067811865476f;
    input0[8] = 100.0f;
    input1[8] = 10.0f;
    expected[8] = 1e+20f;
    input0[9] = 7.0f;
    input1[9] = 3.0f;
    expected[9] = 343.0f;

    std::string kernelSource = loadKernel("math_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_powr", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input0, &err);
    cl_mem inputBuffer1 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input1, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(float), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &inputBuffer1);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 3, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(float), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i], expected[i]);
        test_results.push_back({"powr", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(inputBuffer1);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "powr() tests complete" << std::endl << std::endl;
}

void test_ceil() {
    std::cout << "Testing ceil()..." << std::endl;

    const int NUM_TESTS = 10;
    float input0[NUM_TESTS];
    float output[NUM_TESTS];
    float expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 0.0f;
    expected[0] = 0.0f;
    input0[1] = 1.0f;
    expected[1] = 1.0f;
    input0[2] = -1.0f;
    expected[2] = -1.0f;
    input0[3] = 0.5f;
    expected[3] = 1.0f;
    input0[4] = -0.5f;
    expected[4] = 0.0f;
    input0[5] = 2.0f;
    expected[5] = 2.0f;
    input0[6] = -2.0f;
    expected[6] = -2.0f;
    input0[7] = 10.0f;
    expected[7] = 10.0f;
    input0[8] = -10.0f;
    expected[8] = -10.0f;
    input0[9] = 100.0f;
    expected[9] = 100.0f;

    std::string kernelSource = loadKernel("math_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_ceil", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input0, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(float), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(float), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i], expected[i]);
        test_results.push_back({"ceil", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "ceil() tests complete" << std::endl << std::endl;
}

void test_floor() {
    std::cout << "Testing floor()..." << std::endl;

    const int NUM_TESTS = 10;
    float input0[NUM_TESTS];
    float output[NUM_TESTS];
    float expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 0.0f;
    expected[0] = 0.0f;
    input0[1] = 1.0f;
    expected[1] = 1.0f;
    input0[2] = -1.0f;
    expected[2] = -1.0f;
    input0[3] = 0.5f;
    expected[3] = 0.0f;
    input0[4] = -0.5f;
    expected[4] = -1.0f;
    input0[5] = 2.0f;
    expected[5] = 2.0f;
    input0[6] = -2.0f;
    expected[6] = -2.0f;
    input0[7] = 10.0f;
    expected[7] = 10.0f;
    input0[8] = -10.0f;
    expected[8] = -10.0f;
    input0[9] = 100.0f;
    expected[9] = 100.0f;

    std::string kernelSource = loadKernel("math_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_floor", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input0, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(float), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(float), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i], expected[i]);
        test_results.push_back({"floor", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "floor() tests complete" << std::endl << std::endl;
}

void test_trunc() {
    std::cout << "Testing trunc()..." << std::endl;

    const int NUM_TESTS = 10;
    float input0[NUM_TESTS];
    float output[NUM_TESTS];
    float expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 0.0f;
    expected[0] = 0.0f;
    input0[1] = 1.0f;
    expected[1] = 1.0f;
    input0[2] = -1.0f;
    expected[2] = -1.0f;
    input0[3] = 0.5f;
    expected[3] = 0.0f;
    input0[4] = -0.5f;
    expected[4] = 0.0f;
    input0[5] = 2.0f;
    expected[5] = 2.0f;
    input0[6] = -2.0f;
    expected[6] = -2.0f;
    input0[7] = 10.0f;
    expected[7] = 10.0f;
    input0[8] = -10.0f;
    expected[8] = -10.0f;
    input0[9] = 100.0f;
    expected[9] = 100.0f;

    std::string kernelSource = loadKernel("math_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_trunc", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input0, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(float), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(float), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i], expected[i]);
        test_results.push_back({"trunc", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "trunc() tests complete" << std::endl << std::endl;
}

void test_round() {
    std::cout << "Testing round()..." << std::endl;

    const int NUM_TESTS = 10;
    float input0[NUM_TESTS];
    float output[NUM_TESTS];
    float expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 0.0f;
    expected[0] = 0.0f;
    input0[1] = 1.0f;
    expected[1] = 1.0f;
    input0[2] = -1.0f;
    expected[2] = -1.0f;
    input0[3] = 0.5f;
    expected[3] = 0.0f;
    input0[4] = -0.5f;
    expected[4] = 0.0f;
    input0[5] = 2.0f;
    expected[5] = 2.0f;
    input0[6] = -2.0f;
    expected[6] = -2.0f;
    input0[7] = 10.0f;
    expected[7] = 10.0f;
    input0[8] = -10.0f;
    expected[8] = -10.0f;
    input0[9] = 100.0f;
    expected[9] = 100.0f;

    std::string kernelSource = loadKernel("math_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_round", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input0, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(float), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(float), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i], expected[i]);
        test_results.push_back({"round", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "round() tests complete" << std::endl << std::endl;
}

void test_rint() {
    std::cout << "Testing rint()..." << std::endl;

    const int NUM_TESTS = 10;
    float input0[NUM_TESTS];
    float output[NUM_TESTS];
    float expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 0.0f;
    expected[0] = 0.0f;
    input0[1] = 1.0f;
    expected[1] = 1.0f;
    input0[2] = -1.0f;
    expected[2] = -1.0f;
    input0[3] = 0.5f;
    expected[3] = 0.0f;
    input0[4] = -0.5f;
    expected[4] = 0.0f;
    input0[5] = 2.0f;
    expected[5] = 2.0f;
    input0[6] = -2.0f;
    expected[6] = -2.0f;
    input0[7] = 10.0f;
    expected[7] = 10.0f;
    input0[8] = -10.0f;
    expected[8] = -10.0f;
    input0[9] = 100.0f;
    expected[9] = 100.0f;

    std::string kernelSource = loadKernel("math_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_rint", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input0, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(float), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(float), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i], expected[i]);
        test_results.push_back({"rint", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "rint() tests complete" << std::endl << std::endl;
}

void test_fmod() {
    std::cout << "Testing fmod()..." << std::endl;

    const int NUM_TESTS = 10;
    float input0[NUM_TESTS];
    float input1[NUM_TESTS];
    float output[NUM_TESTS];
    float expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 1.0f;
    input1[0] = 1.0f;
    expected[0] = 0.0f;
    input0[1] = 2.0f;
    input1[1] = 3.0f;
    expected[1] = 2.0f;
    input0[2] = 5.0f;
    input1[2] = 2.0f;
    expected[2] = 1.0f;
    input0[3] = 10.0f;
    input1[3] = 0.5f;
    expected[3] = 0.0f;
    input0[4] = 3.0f;
    input1[4] = 4.0f;
    expected[4] = 3.0f;
    input0[5] = -1.0f;
    input1[5] = 1.0f;
    expected[5] = -0.0f;
    input0[6] = 1.0f;
    input1[6] = -1.0f;
    expected[6] = 0.09999999999999995f;
    input0[7] = 0.5f;
    input1[7] = 0.5f;
    expected[7] = 0.0f;
    input0[8] = 100.0f;
    input1[8] = 10.0f;
    expected[8] = 0.0f;
    input0[9] = 7.0f;
    input1[9] = 3.0f;
    expected[9] = 1.0f;

    std::string kernelSource = loadKernel("math_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_fmod", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input0, &err);
    cl_mem inputBuffer1 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input1, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(float), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &inputBuffer1);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 3, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(float), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i], expected[i]);
        test_results.push_back({"fmod", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(inputBuffer1);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "fmod() tests complete" << std::endl << std::endl;
}

void test_remainder() {
    std::cout << "Testing remainder()..." << std::endl;

    const int NUM_TESTS = 10;
    float input0[NUM_TESTS];
    float input1[NUM_TESTS];
    float output[NUM_TESTS];
    float expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 1.0f;
    input1[0] = 1.0f;
    expected[0] = 0.0f;
    input0[1] = 2.0f;
    input1[1] = 3.0f;
    expected[1] = -1.0f;
    input0[2] = 5.0f;
    input1[2] = 2.0f;
    expected[2] = 1.0f;
    input0[3] = 10.0f;
    input1[3] = 0.5f;
    expected[3] = 0.0f;
    input0[4] = 3.0f;
    input1[4] = 4.0f;
    expected[4] = -1.0f;
    input0[5] = -1.0f;
    input1[5] = 1.0f;
    expected[5] = -0.0f;
    input0[6] = 1.0f;
    input1[6] = -1.0f;
    expected[6] = -5.551115123125783e-17f;
    input0[7] = 0.5f;
    input1[7] = 0.5f;
    expected[7] = 0.0f;
    input0[8] = 100.0f;
    input1[8] = 10.0f;
    expected[8] = 0.0f;
    input0[9] = 7.0f;
    input1[9] = 3.0f;
    expected[9] = 1.0f;

    std::string kernelSource = loadKernel("math_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_remainder", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input0, &err);
    cl_mem inputBuffer1 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input1, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(float), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &inputBuffer1);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 3, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(float), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i], expected[i]);
        test_results.push_back({"remainder", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(inputBuffer1);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "remainder() tests complete" << std::endl << std::endl;
}

void test_fabs() {
    std::cout << "Testing fabs()..." << std::endl;

    const int NUM_TESTS = 10;
    float input0[NUM_TESTS];
    float output[NUM_TESTS];
    float expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 0.0f;
    expected[0] = 0.0f;
    input0[1] = 1.0f;
    expected[1] = 1.0f;
    input0[2] = -1.0f;
    expected[2] = 1.0f;
    input0[3] = 0.5f;
    expected[3] = 0.5f;
    input0[4] = -0.5f;
    expected[4] = 0.5f;
    input0[5] = 2.0f;
    expected[5] = 2.0f;
    input0[6] = -2.0f;
    expected[6] = 2.0f;
    input0[7] = 10.0f;
    expected[7] = 10.0f;
    input0[8] = -10.0f;
    expected[8] = 10.0f;
    input0[9] = 100.0f;
    expected[9] = 100.0f;

    std::string kernelSource = loadKernel("math_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_fabs", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input0, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(float), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(float), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i], expected[i]);
        test_results.push_back({"fabs", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "fabs() tests complete" << std::endl << std::endl;
}

void test_fmax() {
    std::cout << "Testing fmax()..." << std::endl;

    const int NUM_TESTS = 10;
    float input0[NUM_TESTS];
    float input1[NUM_TESTS];
    float output[NUM_TESTS];
    float expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 1.0f;
    input1[0] = 1.0f;
    expected[0] = 1.0f;
    input0[1] = 2.0f;
    input1[1] = 3.0f;
    expected[1] = 3.0f;
    input0[2] = 5.0f;
    input1[2] = 2.0f;
    expected[2] = 5.0f;
    input0[3] = 10.0f;
    input1[3] = 0.5f;
    expected[3] = 10.0f;
    input0[4] = 3.0f;
    input1[4] = 4.0f;
    expected[4] = 4.0f;
    input0[5] = -1.0f;
    input1[5] = 1.0f;
    expected[5] = 1.0f;
    input0[6] = 1.0f;
    input1[6] = -1.0f;
    expected[6] = 1.0f;
    input0[7] = 0.5f;
    input1[7] = 0.5f;
    expected[7] = 0.5f;
    input0[8] = 100.0f;
    input1[8] = 10.0f;
    expected[8] = 100.0f;
    input0[9] = 7.0f;
    input1[9] = 3.0f;
    expected[9] = 7.0f;

    std::string kernelSource = loadKernel("math_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_fmax", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input0, &err);
    cl_mem inputBuffer1 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input1, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(float), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &inputBuffer1);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 3, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(float), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i], expected[i]);
        test_results.push_back({"fmax", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(inputBuffer1);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "fmax() tests complete" << std::endl << std::endl;
}

void test_fmin() {
    std::cout << "Testing fmin()..." << std::endl;

    const int NUM_TESTS = 10;
    float input0[NUM_TESTS];
    float input1[NUM_TESTS];
    float output[NUM_TESTS];
    float expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 1.0f;
    input1[0] = 1.0f;
    expected[0] = 1.0f;
    input0[1] = 2.0f;
    input1[1] = 3.0f;
    expected[1] = 2.0f;
    input0[2] = 5.0f;
    input1[2] = 2.0f;
    expected[2] = 2.0f;
    input0[3] = 10.0f;
    input1[3] = 0.5f;
    expected[3] = 0.5f;
    input0[4] = 3.0f;
    input1[4] = 4.0f;
    expected[4] = 3.0f;
    input0[5] = -1.0f;
    input1[5] = 1.0f;
    expected[5] = -1.0f;
    input0[6] = 1.0f;
    input1[6] = -1.0f;
    expected[6] = -1.0f;
    input0[7] = 0.5f;
    input1[7] = 0.5f;
    expected[7] = 0.5f;
    input0[8] = 100.0f;
    input1[8] = 10.0f;
    expected[8] = 10.0f;
    input0[9] = 7.0f;
    input1[9] = 3.0f;
    expected[9] = 3.0f;

    std::string kernelSource = loadKernel("math_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_fmin", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input0, &err);
    cl_mem inputBuffer1 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input1, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(float), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &inputBuffer1);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 3, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(float), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i], expected[i]);
        test_results.push_back({"fmin", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(inputBuffer1);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "fmin() tests complete" << std::endl << std::endl;
}

void test_fma() {
    std::cout << "Testing fma()..." << std::endl;

    const int NUM_TESTS = 10;
    float input0[NUM_TESTS];
    float input1[NUM_TESTS];
    float input2[NUM_TESTS];
    float output[NUM_TESTS];
    float expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 1.0f;
    input1[0] = 2.0f;
    input2[0] = 3.0f;
    expected[0] = 5.0f;
    input0[1] = 2.0f;
    input1[1] = 3.0f;
    input2[1] = 4.0f;
    expected[1] = 10.0f;
    input0[2] = 5.0f;
    input1[2] = 2.0f;
    input2[2] = 1.0f;
    expected[2] = 11.0f;
    input0[3] = 10.0f;
    input1[3] = 0.5f;
    input2[3] = 0.1f;
    expected[3] = 5.1f;
    input0[4] = 3.0f;
    input1[4] = 4.0f;
    input2[4] = 5.0f;
    expected[4] = 17.0f;
    input0[5] = -1.0f;
    input1[5] = 1.0f;
    input2[5] = 0.0f;
    expected[5] = -1.0f;
    input0[6] = 1.0f;
    input1[6] = -1.0f;
    input2[6] = 2.0f;
    expected[6] = 1.0f;
    input0[7] = 0.5f;
    input1[7] = 0.5f;
    input2[7] = 0.5f;
    expected[7] = 0.75f;
    input0[8] = 100.0f;
    input1[8] = 10.0f;
    input2[8] = 1.0f;
    expected[8] = 1001.0f;
    input0[9] = 7.0f;
    input1[9] = 3.0f;
    input2[9] = 2.0f;
    expected[9] = 23.0f;

    std::string kernelSource = loadKernel("math_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_fma", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input0, &err);
    cl_mem inputBuffer1 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input1, &err);
    cl_mem inputBuffer2 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input2, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(float), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &inputBuffer1);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &inputBuffer2);
    clSetKernelArg(kernel, 3, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 4, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(float), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i], expected[i]);
        test_results.push_back({"fma", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(inputBuffer1);
    clReleaseMemObject(inputBuffer2);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "fma() tests complete" << std::endl << std::endl;
}

void test_hypot() {
    std::cout << "Testing hypot()..." << std::endl;

    const int NUM_TESTS = 10;
    float input0[NUM_TESTS];
    float input1[NUM_TESTS];
    float output[NUM_TESTS];
    float expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 1.0f;
    input1[0] = 1.0f;
    expected[0] = 1.4142135623730951f;
    input0[1] = 2.0f;
    input1[1] = 3.0f;
    expected[1] = 3.605551275463989f;
    input0[2] = 5.0f;
    input1[2] = 2.0f;
    expected[2] = 5.385164807134504f;
    input0[3] = 10.0f;
    input1[3] = 0.5f;
    expected[3] = 10.012492197250394f;
    input0[4] = 3.0f;
    input1[4] = 4.0f;
    expected[4] = 5.0f;
    input0[5] = -1.0f;
    input1[5] = 1.0f;
    expected[5] = 1.4142135623730951f;
    input0[6] = 1.0f;
    input1[6] = -1.0f;
    expected[6] = 1.4142135623730951f;
    input0[7] = 0.5f;
    input1[7] = 0.5f;
    expected[7] = 0.7071067811865476f;
    input0[8] = 100.0f;
    input1[8] = 10.0f;
    expected[8] = 100.4987562112089f;
    input0[9] = 7.0f;
    input1[9] = 3.0f;
    expected[9] = 7.615773105863909f;

    std::string kernelSource = loadKernel("math_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_hypot", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input0, &err);
    cl_mem inputBuffer1 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input1, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(float), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &inputBuffer1);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 3, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(float), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i], expected[i]);
        test_results.push_back({"hypot", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(inputBuffer1);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "hypot() tests complete" << std::endl << std::endl;
}

void test_erf() {
    std::cout << "Testing erf()..." << std::endl;

    const int NUM_TESTS = 10;
    float input0[NUM_TESTS];
    float output[NUM_TESTS];
    float expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 0.0f;
    expected[0] = 0.0f;
    input0[1] = 1.0f;
    expected[1] = 0.8427007929497149f;
    input0[2] = -1.0f;
    expected[2] = -0.8427007929497149f;
    input0[3] = 0.5f;
    expected[3] = 0.5204998778130465f;
    input0[4] = -0.5f;
    expected[4] = -0.5204998778130465f;
    input0[5] = 2.0f;
    expected[5] = 0.9953222650189527f;
    input0[6] = -2.0f;
    expected[6] = -0.9953222650189527f;
    input0[7] = 10.0f;
    expected[7] = 1.0f;
    input0[8] = -10.0f;
    expected[8] = -1.0f;
    input0[9] = 100.0f;
    expected[9] = 1.0f;

    std::string kernelSource = loadKernel("math_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_erf", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input0, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(float), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(float), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i], expected[i]);
        test_results.push_back({"erf", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "erf() tests complete" << std::endl << std::endl;
}

void test_erfc() {
    std::cout << "Testing erfc()..." << std::endl;

    const int NUM_TESTS = 10;
    float input0[NUM_TESTS];
    float output[NUM_TESTS];
    float expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 0.0f;
    expected[0] = 1.0f;
    input0[1] = 1.0f;
    expected[1] = 0.15729920705028513f;
    input0[2] = -1.0f;
    expected[2] = 1.842700792949715f;
    input0[3] = 0.5f;
    expected[3] = 0.4795001221869535f;
    input0[4] = -0.5f;
    expected[4] = 1.5204998778130465f;
    input0[5] = 2.0f;
    expected[5] = 0.004677734981047265f;
    input0[6] = -2.0f;
    expected[6] = 1.9953222650189528f;
    input0[7] = 10.0f;
    expected[7] = 2.088487583762545e-45f;
    input0[8] = -10.0f;
    expected[8] = 2.0f;
    input0[9] = 100.0f;
    expected[9] = 0.0f;

    std::string kernelSource = loadKernel("math_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_erfc", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input0, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(float), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(float), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i], expected[i]);
        test_results.push_back({"erfc", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "erfc() tests complete" << std::endl << std::endl;
}

void test_tgamma() {
    std::cout << "Testing tgamma()..." << std::endl;

    const int NUM_TESTS = 10;
    float input0[NUM_TESTS];
    float output[NUM_TESTS];
    float expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 0.0f;
    expected[0] = 9.513507698668732f;
    input0[1] = 1.0f;
    expected[1] = 1.0f;
    input0[2] = -1.0f;
    expected[2] = 9.513507698668732f;
    input0[3] = 0.5f;
    expected[3] = 1.7724538509055159f;
    input0[4] = -0.5f;
    expected[4] = 9.513507698668732f;
    input0[5] = 2.0f;
    expected[5] = 1.0f;
    input0[6] = -2.0f;
    expected[6] = 9.513507698668732f;
    input0[7] = 10.0f;
    expected[7] = 362880.0f;
    input0[8] = -10.0f;
    expected[8] = 9.513507698668732f;
    input0[9] = 100.0f;
    expected[9] = 9.332621544394415e+155f;

    std::string kernelSource = loadKernel("math_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_tgamma", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input0, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(float), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(float), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i], expected[i]);
        test_results.push_back({"tgamma", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "tgamma() tests complete" << std::endl << std::endl;
}

void test_lgamma() {
    std::cout << "Testing lgamma()..." << std::endl;

    const int NUM_TESTS = 10;
    float input0[NUM_TESTS];
    float output[NUM_TESTS];
    float expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 0.0f;
    expected[0] = 2.2527126517342055f;
    input0[1] = 1.0f;
    expected[1] = 0.0f;
    input0[2] = -1.0f;
    expected[2] = 2.2527126517342055f;
    input0[3] = 0.5f;
    expected[3] = 0.5723649429247004f;
    input0[4] = -0.5f;
    expected[4] = 2.2527126517342055f;
    input0[5] = 2.0f;
    expected[5] = 0.0f;
    input0[6] = -2.0f;
    expected[6] = 2.2527126517342055f;
    input0[7] = 10.0f;
    expected[7] = 12.801827480081467f;
    input0[8] = -10.0f;
    expected[8] = 2.2527126517342055f;
    input0[9] = 100.0f;
    expected[9] = 359.1342053695754f;

    std::string kernelSource = loadKernel("math_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_lgamma", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input0, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(float), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(float), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i], expected[i]);
        test_results.push_back({"lgamma", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "lgamma() tests complete" << std::endl << std::endl;
}

void test_native_exp() {
    std::cout << "Testing native_exp()..." << std::endl;

    const int NUM_TESTS = 10;
    float input0[NUM_TESTS];
    float output[NUM_TESTS];
    float expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 0.0f;
    expected[0] = 1.0f;
    input0[1] = 1.0f;
    expected[1] = 2.718281828459045f;
    input0[2] = -1.0f;
    expected[2] = 0.36787944117144233f;
    input0[3] = 0.5f;
    expected[3] = 1.6487212707001282f;
    input0[4] = -0.5f;
    expected[4] = 0.6065306597126334f;
    input0[5] = 2.0f;
    expected[5] = 7.38905609893065f;
    input0[6] = -2.0f;
    expected[6] = 0.1353352832366127f;
    input0[7] = 10.0f;
    expected[7] = 22026.465794806718f;
    input0[8] = -10.0f;
    expected[8] = 4.5399929762484854e-05f;
    input0[9] = 100.0f;
    expected[9] = 2.6881171418161356e+43f;

    std::string kernelSource = loadKernel("math_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_native_exp", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input0, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(float), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(float), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i], expected[i]);
        test_results.push_back({"native_exp", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "native_exp() tests complete" << std::endl << std::endl;
}

void test_native_exp2() {
    std::cout << "Testing native_exp2()..." << std::endl;

    const int NUM_TESTS = 10;
    float input0[NUM_TESTS];
    float output[NUM_TESTS];
    float expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 0.0f;
    expected[0] = 1.0f;
    input0[1] = 1.0f;
    expected[1] = 2.0f;
    input0[2] = -1.0f;
    expected[2] = 0.5f;
    input0[3] = 0.5f;
    expected[3] = 1.4142135623730951f;
    input0[4] = -0.5f;
    expected[4] = 0.7071067811865476f;
    input0[5] = 2.0f;
    expected[5] = 4.0f;
    input0[6] = -2.0f;
    expected[6] = 0.25f;
    input0[7] = 10.0f;
    expected[7] = 1024.0f;
    input0[8] = -10.0f;
    expected[8] = 0.0009765625f;
    input0[9] = 100.0f;
    expected[9] = 1.2676506002282294e+30f;

    std::string kernelSource = loadKernel("math_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_native_exp2", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input0, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(float), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(float), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i], expected[i]);
        test_results.push_back({"native_exp2", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "native_exp2() tests complete" << std::endl << std::endl;
}

void test_native_exp10() {
    std::cout << "Testing native_exp10()..." << std::endl;

    const int NUM_TESTS = 10;
    float input0[NUM_TESTS];
    float output[NUM_TESTS];
    float expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 0.0f;
    expected[0] = 1.0f;
    input0[1] = 1.0f;
    expected[1] = 10.0f;
    input0[2] = -1.0f;
    expected[2] = 0.1f;
    input0[3] = 0.5f;
    expected[3] = 3.1622776601683795f;
    input0[4] = -0.5f;
    expected[4] = 0.31622776601683794f;
    input0[5] = 2.0f;
    expected[5] = 100.0f;
    input0[6] = -2.0f;
    expected[6] = 0.01f;
    input0[7] = 10.0f;
    expected[7] = 10000000000.0f;
    input0[8] = -10.0f;
    expected[8] = 1e-10f;
    input0[9] = 100.0f;
    expected[9] = 1e+100f;

    std::string kernelSource = loadKernel("math_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_native_exp10", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input0, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(float), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(float), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i], expected[i]);
        test_results.push_back({"native_exp10", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "native_exp10() tests complete" << std::endl << std::endl;
}

void test_native_log() {
    std::cout << "Testing native_log()..." << std::endl;

    const int NUM_TESTS = 10;
    float input0[NUM_TESTS];
    float output[NUM_TESTS];
    float expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 0.0f;
    expected[0] = -6.907755278982137f;
    input0[1] = 1.0f;
    expected[1] = 0.0f;
    input0[2] = -1.0f;
    expected[2] = -6.907755278982137f;
    input0[3] = 0.5f;
    expected[3] = -0.6931471805599453f;
    input0[4] = -0.5f;
    expected[4] = -6.907755278982137f;
    input0[5] = 2.0f;
    expected[5] = 0.6931471805599453f;
    input0[6] = -2.0f;
    expected[6] = -6.907755278982137f;
    input0[7] = 10.0f;
    expected[7] = 2.302585092994046f;
    input0[8] = -10.0f;
    expected[8] = -6.907755278982137f;
    input0[9] = 100.0f;
    expected[9] = 4.605170185988092f;

    std::string kernelSource = loadKernel("math_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_native_log", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input0, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(float), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(float), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i], expected[i]);
        test_results.push_back({"native_log", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "native_log() tests complete" << std::endl << std::endl;
}

void test_native_log2() {
    std::cout << "Testing native_log2()..." << std::endl;

    const int NUM_TESTS = 10;
    float input0[NUM_TESTS];
    float output[NUM_TESTS];
    float expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 0.0f;
    expected[0] = -9.965784284662087f;
    input0[1] = 1.0f;
    expected[1] = 0.0f;
    input0[2] = -1.0f;
    expected[2] = -9.965784284662087f;
    input0[3] = 0.5f;
    expected[3] = -1.0f;
    input0[4] = -0.5f;
    expected[4] = -9.965784284662087f;
    input0[5] = 2.0f;
    expected[5] = 1.0f;
    input0[6] = -2.0f;
    expected[6] = -9.965784284662087f;
    input0[7] = 10.0f;
    expected[7] = 3.321928094887362f;
    input0[8] = -10.0f;
    expected[8] = -9.965784284662087f;
    input0[9] = 100.0f;
    expected[9] = 6.643856189774724f;

    std::string kernelSource = loadKernel("math_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_native_log2", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input0, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(float), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(float), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i], expected[i]);
        test_results.push_back({"native_log2", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "native_log2() tests complete" << std::endl << std::endl;
}

void test_native_log10() {
    std::cout << "Testing native_log10()..." << std::endl;

    const int NUM_TESTS = 10;
    float input0[NUM_TESTS];
    float output[NUM_TESTS];
    float expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 0.0f;
    expected[0] = -3.0f;
    input0[1] = 1.0f;
    expected[1] = 0.0f;
    input0[2] = -1.0f;
    expected[2] = -3.0f;
    input0[3] = 0.5f;
    expected[3] = -0.3010299956639812f;
    input0[4] = -0.5f;
    expected[4] = -3.0f;
    input0[5] = 2.0f;
    expected[5] = 0.3010299956639812f;
    input0[6] = -2.0f;
    expected[6] = -3.0f;
    input0[7] = 10.0f;
    expected[7] = 1.0f;
    input0[8] = -10.0f;
    expected[8] = -3.0f;
    input0[9] = 100.0f;
    expected[9] = 2.0f;

    std::string kernelSource = loadKernel("math_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_native_log10", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input0, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(float), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(float), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i], expected[i]);
        test_results.push_back({"native_log10", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "native_log10() tests complete" << std::endl << std::endl;
}

void test_native_sqrt() {
    std::cout << "Testing native_sqrt()..." << std::endl;

    const int NUM_TESTS = 10;
    float input0[NUM_TESTS];
    float output[NUM_TESTS];
    float expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 0.0f;
    expected[0] = 0.0f;
    input0[1] = 1.0f;
    expected[1] = 1.0f;
    input0[2] = -1.0f;
    expected[2] = 0.0f;
    input0[3] = 0.5f;
    expected[3] = 0.7071067811865476f;
    input0[4] = -0.5f;
    expected[4] = 0.0f;
    input0[5] = 2.0f;
    expected[5] = 1.4142135623730951f;
    input0[6] = -2.0f;
    expected[6] = 0.0f;
    input0[7] = 10.0f;
    expected[7] = 3.1622776601683795f;
    input0[8] = -10.0f;
    expected[8] = 0.0f;
    input0[9] = 100.0f;
    expected[9] = 10.0f;

    std::string kernelSource = loadKernel("math_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_native_sqrt", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input0, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(float), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(float), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i], expected[i]);
        test_results.push_back({"native_sqrt", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "native_sqrt() tests complete" << std::endl << std::endl;
}

void test_native_rsqrt() {
    std::cout << "Testing native_rsqrt()..." << std::endl;

    const int NUM_TESTS = 10;
    float input0[NUM_TESTS];
    float output[NUM_TESTS];
    float expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 0.0f;
    expected[0] = 31.622776601683796f;
    input0[1] = 1.0f;
    expected[1] = 1.0f;
    input0[2] = -1.0f;
    expected[2] = 31.622776601683796f;
    input0[3] = 0.5f;
    expected[3] = 1.414213562373095f;
    input0[4] = -0.5f;
    expected[4] = 31.622776601683796f;
    input0[5] = 2.0f;
    expected[5] = 0.7071067811865475f;
    input0[6] = -2.0f;
    expected[6] = 31.622776601683796f;
    input0[7] = 10.0f;
    expected[7] = 0.31622776601683794f;
    input0[8] = -10.0f;
    expected[8] = 31.622776601683796f;
    input0[9] = 100.0f;
    expected[9] = 0.1f;

    std::string kernelSource = loadKernel("math_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_native_rsqrt", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input0, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(float), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(float), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i], expected[i]);
        test_results.push_back({"native_rsqrt", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "native_rsqrt() tests complete" << std::endl << std::endl;
}

void test_isequal() {
    std::cout << "Testing isequal()..." << std::endl;

    const int NUM_TESTS = 10;
    float input0[NUM_TESTS];
    float input1[NUM_TESTS];
    int output[NUM_TESTS];
    int expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 1.0f;
    input1[0] = 1.0f;
    expected[0] = -1;
    input0[1] = 1.0f;
    input1[1] = 2.0f;
    expected[1] = 0;
    input0[2] = 2.0f;
    input1[2] = 1.0f;
    expected[2] = 0;
    input0[3] = 0.0f;
    input1[3] = 0.0f;
    expected[3] = -1;
    input0[4] = 0.0f;
    input1[4] = 1.0f;
    expected[4] = 0;
    input0[5] = -1.0f;
    input1[5] = -1.0f;
    expected[5] = -1;
    input0[6] = 3.14f;
    input1[6] = 3.14f;
    expected[6] = -1;
    input0[7] = 3.14f;
    input1[7] = 2.71f;
    expected[7] = 0;
    input0[8] = 100.0f;
    input1[8] = 100.0f;
    expected[8] = -1;
    input0[9] = 100.0f;
    input1[9] = 99.0f;
    expected[9] = 0;

    std::string kernelSource = loadKernel("relational_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_isequal", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input0, &err);
    cl_mem inputBuffer1 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input1, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(int), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &inputBuffer1);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 3, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(int), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = (output[i] == expected[i]);
        test_results.push_back({"isequal", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(inputBuffer1);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "isequal() tests complete" << std::endl << std::endl;
}

void test_isnotequal() {
    std::cout << "Testing isnotequal()..." << std::endl;

    const int NUM_TESTS = 10;
    float input0[NUM_TESTS];
    float input1[NUM_TESTS];
    int output[NUM_TESTS];
    int expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 1.0f;
    input1[0] = 1.0f;
    expected[0] = 0;
    input0[1] = 1.0f;
    input1[1] = 2.0f;
    expected[1] = -1;
    input0[2] = 2.0f;
    input1[2] = 1.0f;
    expected[2] = -1;
    input0[3] = 0.0f;
    input1[3] = 0.0f;
    expected[3] = 0;
    input0[4] = 0.0f;
    input1[4] = 1.0f;
    expected[4] = -1;
    input0[5] = -1.0f;
    input1[5] = -1.0f;
    expected[5] = 0;
    input0[6] = 3.14f;
    input1[6] = 3.14f;
    expected[6] = 0;
    input0[7] = 3.14f;
    input1[7] = 2.71f;
    expected[7] = -1;
    input0[8] = 100.0f;
    input1[8] = 100.0f;
    expected[8] = 0;
    input0[9] = 100.0f;
    input1[9] = 99.0f;
    expected[9] = -1;

    std::string kernelSource = loadKernel("relational_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_isnotequal", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input0, &err);
    cl_mem inputBuffer1 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input1, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(int), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &inputBuffer1);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 3, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(int), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = (output[i] == expected[i]);
        test_results.push_back({"isnotequal", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(inputBuffer1);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "isnotequal() tests complete" << std::endl << std::endl;
}

void test_isgreater() {
    std::cout << "Testing isgreater()..." << std::endl;

    const int NUM_TESTS = 10;
    float input0[NUM_TESTS];
    float input1[NUM_TESTS];
    int output[NUM_TESTS];
    int expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 2.0f;
    input1[0] = 1.0f;
    expected[0] = -1;
    input0[1] = 1.0f;
    input1[1] = 2.0f;
    expected[1] = 0;
    input0[2] = 1.0f;
    input1[2] = 1.0f;
    expected[2] = 0;
    input0[3] = 0.0f;
    input1[3] = -1.0f;
    expected[3] = -1;
    input0[4] = -1.0f;
    input1[4] = 0.0f;
    expected[4] = 0;
    input0[5] = 10.0f;
    input1[5] = 5.0f;
    expected[5] = -1;
    input0[6] = 5.0f;
    input1[6] = 10.0f;
    expected[6] = 0;
    input0[7] = 3.14f;
    input1[7] = 2.71f;
    expected[7] = -1;
    input0[8] = 2.71f;
    input1[8] = 3.14f;
    expected[8] = 0;
    input0[9] = 100.0f;
    input1[9] = 100.0f;
    expected[9] = 0;

    std::string kernelSource = loadKernel("relational_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_isgreater", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input0, &err);
    cl_mem inputBuffer1 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input1, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(int), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &inputBuffer1);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 3, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(int), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = (output[i] == expected[i]);
        test_results.push_back({"isgreater", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(inputBuffer1);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "isgreater() tests complete" << std::endl << std::endl;
}

void test_isgreaterequal() {
    std::cout << "Testing isgreaterequal()..." << std::endl;

    const int NUM_TESTS = 10;
    float input0[NUM_TESTS];
    float input1[NUM_TESTS];
    int output[NUM_TESTS];
    int expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 2.0f;
    input1[0] = 1.0f;
    expected[0] = -1;
    input0[1] = 1.0f;
    input1[1] = 2.0f;
    expected[1] = 0;
    input0[2] = 1.0f;
    input1[2] = 1.0f;
    expected[2] = -1;
    input0[3] = 0.0f;
    input1[3] = -1.0f;
    expected[3] = -1;
    input0[4] = -1.0f;
    input1[4] = 0.0f;
    expected[4] = 0;
    input0[5] = 10.0f;
    input1[5] = 5.0f;
    expected[5] = -1;
    input0[6] = 5.0f;
    input1[6] = 10.0f;
    expected[6] = 0;
    input0[7] = 3.14f;
    input1[7] = 2.71f;
    expected[7] = -1;
    input0[8] = 2.71f;
    input1[8] = 3.14f;
    expected[8] = 0;
    input0[9] = 100.0f;
    input1[9] = 100.0f;
    expected[9] = -1;

    std::string kernelSource = loadKernel("relational_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_isgreaterequal", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input0, &err);
    cl_mem inputBuffer1 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input1, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(int), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &inputBuffer1);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 3, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(int), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = (output[i] == expected[i]);
        test_results.push_back({"isgreaterequal", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(inputBuffer1);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "isgreaterequal() tests complete" << std::endl << std::endl;
}

void test_isless() {
    std::cout << "Testing isless()..." << std::endl;

    const int NUM_TESTS = 10;
    float input0[NUM_TESTS];
    float input1[NUM_TESTS];
    int output[NUM_TESTS];
    int expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 1.0f;
    input1[0] = 2.0f;
    expected[0] = -1;
    input0[1] = 2.0f;
    input1[1] = 1.0f;
    expected[1] = 0;
    input0[2] = 1.0f;
    input1[2] = 1.0f;
    expected[2] = 0;
    input0[3] = -1.0f;
    input1[3] = 0.0f;
    expected[3] = -1;
    input0[4] = 0.0f;
    input1[4] = -1.0f;
    expected[4] = 0;
    input0[5] = 5.0f;
    input1[5] = 10.0f;
    expected[5] = -1;
    input0[6] = 10.0f;
    input1[6] = 5.0f;
    expected[6] = 0;
    input0[7] = 2.71f;
    input1[7] = 3.14f;
    expected[7] = -1;
    input0[8] = 3.14f;
    input1[8] = 2.71f;
    expected[8] = 0;
    input0[9] = 100.0f;
    input1[9] = 100.0f;
    expected[9] = 0;

    std::string kernelSource = loadKernel("relational_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_isless", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input0, &err);
    cl_mem inputBuffer1 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input1, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(int), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &inputBuffer1);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 3, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(int), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = (output[i] == expected[i]);
        test_results.push_back({"isless", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(inputBuffer1);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "isless() tests complete" << std::endl << std::endl;
}

void test_islessequal() {
    std::cout << "Testing islessequal()..." << std::endl;

    const int NUM_TESTS = 10;
    float input0[NUM_TESTS];
    float input1[NUM_TESTS];
    int output[NUM_TESTS];
    int expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 1.0f;
    input1[0] = 2.0f;
    expected[0] = -1;
    input0[1] = 2.0f;
    input1[1] = 1.0f;
    expected[1] = 0;
    input0[2] = 1.0f;
    input1[2] = 1.0f;
    expected[2] = -1;
    input0[3] = -1.0f;
    input1[3] = 0.0f;
    expected[3] = -1;
    input0[4] = 0.0f;
    input1[4] = -1.0f;
    expected[4] = 0;
    input0[5] = 5.0f;
    input1[5] = 10.0f;
    expected[5] = -1;
    input0[6] = 10.0f;
    input1[6] = 5.0f;
    expected[6] = 0;
    input0[7] = 2.71f;
    input1[7] = 3.14f;
    expected[7] = -1;
    input0[8] = 3.14f;
    input1[8] = 2.71f;
    expected[8] = 0;
    input0[9] = 100.0f;
    input1[9] = 100.0f;
    expected[9] = -1;

    std::string kernelSource = loadKernel("relational_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_islessequal", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input0, &err);
    cl_mem inputBuffer1 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input1, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(int), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &inputBuffer1);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 3, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(int), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = (output[i] == expected[i]);
        test_results.push_back({"islessequal", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(inputBuffer1);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "islessequal() tests complete" << std::endl << std::endl;
}

void test_islessgreater() {
    std::cout << "Testing islessgreater()..." << std::endl;

    const int NUM_TESTS = 10;
    float input0[NUM_TESTS];
    float input1[NUM_TESTS];
    int output[NUM_TESTS];
    int expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 1.0f;
    input1[0] = 2.0f;
    expected[0] = -1;
    input0[1] = 2.0f;
    input1[1] = 1.0f;
    expected[1] = -1;
    input0[2] = 1.0f;
    input1[2] = 1.0f;
    expected[2] = 0;
    input0[3] = -1.0f;
    input1[3] = 0.0f;
    expected[3] = -1;
    input0[4] = 0.0f;
    input1[4] = -1.0f;
    expected[4] = -1;
    input0[5] = 5.0f;
    input1[5] = 10.0f;
    expected[5] = -1;
    input0[6] = 10.0f;
    input1[6] = 5.0f;
    expected[6] = -1;
    input0[7] = 2.71f;
    input1[7] = 3.14f;
    expected[7] = -1;
    input0[8] = 3.14f;
    input1[8] = 2.71f;
    expected[8] = -1;
    input0[9] = 100.0f;
    input1[9] = 100.0f;
    expected[9] = 0;

    std::string kernelSource = loadKernel("relational_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_islessgreater", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input0, &err);
    cl_mem inputBuffer1 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input1, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(int), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &inputBuffer1);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 3, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(int), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = (output[i] == expected[i]);
        test_results.push_back({"islessgreater", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(inputBuffer1);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "islessgreater() tests complete" << std::endl << std::endl;
}

void test_isfinite() {
    std::cout << "Testing isfinite()..." << std::endl;

    const int NUM_TESTS = 10;
    float input0[NUM_TESTS];
    int output[NUM_TESTS];
    int expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 0.0f;
    expected[0] = -1;
    input0[1] = 1.0f;
    expected[1] = -1;
    input0[2] = -1.0f;
    expected[2] = -1;
    input0[3] = 100.0f;
    expected[3] = -1;
    input0[4] = -100.0f;
    expected[4] = -1;
    input0[5] = 3.14159f;
    expected[5] = -1;
    input0[6] = 1e-05f;
    expected[6] = -1;
    input0[7] = 1000000.0f;
    expected[7] = -1;
    input0[8] = -1000000.0f;
    expected[8] = -1;
    input0[9] = 2.71828f;
    expected[9] = -1;

    std::string kernelSource = loadKernel("relational_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_isfinite", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input0, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(int), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(int), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = (output[i] == expected[i]);
        test_results.push_back({"isfinite", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "isfinite() tests complete" << std::endl << std::endl;
}

void test_isinf() {
    std::cout << "Testing isinf()..." << std::endl;

    const int NUM_TESTS = 10;
    float input0[NUM_TESTS];
    int output[NUM_TESTS];
    int expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 0.0f;
    expected[0] = 0;
    input0[1] = 1.0f;
    expected[1] = 0;
    input0[2] = -1.0f;
    expected[2] = 0;
    input0[3] = 100.0f;
    expected[3] = 0;
    input0[4] = -100.0f;
    expected[4] = 0;
    input0[5] = 3.14159f;
    expected[5] = 0;
    input0[6] = 1e-05f;
    expected[6] = 0;
    input0[7] = 1000000.0f;
    expected[7] = 0;
    input0[8] = -1000000.0f;
    expected[8] = 0;
    input0[9] = 2.71828f;
    expected[9] = 0;

    std::string kernelSource = loadKernel("relational_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_isinf", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input0, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(int), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(int), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = (output[i] == expected[i]);
        test_results.push_back({"isinf", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "isinf() tests complete" << std::endl << std::endl;
}

void test_isnan() {
    std::cout << "Testing isnan()..." << std::endl;

    const int NUM_TESTS = 10;
    float input0[NUM_TESTS];
    int output[NUM_TESTS];
    int expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 0.0f;
    expected[0] = 0;
    input0[1] = 1.0f;
    expected[1] = 0;
    input0[2] = -1.0f;
    expected[2] = 0;
    input0[3] = 100.0f;
    expected[3] = 0;
    input0[4] = -100.0f;
    expected[4] = 0;
    input0[5] = 3.14159f;
    expected[5] = 0;
    input0[6] = 1e-05f;
    expected[6] = 0;
    input0[7] = 1000000.0f;
    expected[7] = 0;
    input0[8] = -1000000.0f;
    expected[8] = 0;
    input0[9] = 2.71828f;
    expected[9] = 0;

    std::string kernelSource = loadKernel("relational_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_isnan", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input0, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(int), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(int), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = (output[i] == expected[i]);
        test_results.push_back({"isnan", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "isnan() tests complete" << std::endl << std::endl;
}

void test_isnormal() {
    std::cout << "Testing isnormal()..." << std::endl;

    const int NUM_TESTS = 10;
    float input0[NUM_TESTS];
    int output[NUM_TESTS];
    int expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 1.0f;
    expected[0] = -1;
    input0[1] = -1.0f;
    expected[1] = -1;
    input0[2] = 100.0f;
    expected[2] = -1;
    input0[3] = -100.0f;
    expected[3] = -1;
    input0[4] = 3.14159f;
    expected[4] = -1;
    input0[5] = 1e-05f;
    expected[5] = -1;
    input0[6] = 1000000.0f;
    expected[6] = -1;
    input0[7] = -1000000.0f;
    expected[7] = -1;
    input0[8] = 2.71828f;
    expected[8] = -1;
    input0[9] = 0.5f;
    expected[9] = -1;

    std::string kernelSource = loadKernel("relational_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_isnormal", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input0, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(int), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(int), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = (output[i] == expected[i]);
        test_results.push_back({"isnormal", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "isnormal() tests complete" << std::endl << std::endl;
}

void test_isordered() {
    std::cout << "Testing isordered()..." << std::endl;

    const int NUM_TESTS = 10;
    float input0[NUM_TESTS];
    float input1[NUM_TESTS];
    int output[NUM_TESTS];
    int expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 1.0f;
    input1[0] = 2.0f;
    expected[0] = -1;
    input0[1] = 2.0f;
    input1[1] = 1.0f;
    expected[1] = -1;
    input0[2] = 0.0f;
    input1[2] = 0.0f;
    expected[2] = -1;
    input0[3] = -1.0f;
    input1[3] = 1.0f;
    expected[3] = -1;
    input0[4] = 100.0f;
    input1[4] = 50.0f;
    expected[4] = -1;
    input0[5] = 3.14f;
    input1[5] = 2.71f;
    expected[5] = -1;
    input0[6] = 0.0f;
    input1[6] = 1.0f;
    expected[6] = -1;
    input0[7] = 5.0f;
    input1[7] = 5.0f;
    expected[7] = -1;
    input0[8] = -5.0f;
    input1[8] = -10.0f;
    expected[8] = -1;
    input0[9] = 1000.0f;
    input1[9] = 1.0f;
    expected[9] = -1;

    std::string kernelSource = loadKernel("relational_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_isordered", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input0, &err);
    cl_mem inputBuffer1 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input1, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(int), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &inputBuffer1);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 3, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(int), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = (output[i] == expected[i]);
        test_results.push_back({"isordered", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(inputBuffer1);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "isordered() tests complete" << std::endl << std::endl;
}

void test_isunordered() {
    std::cout << "Testing isunordered()..." << std::endl;

    const int NUM_TESTS = 10;
    float input0[NUM_TESTS];
    float input1[NUM_TESTS];
    int output[NUM_TESTS];
    int expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 1.0f;
    input1[0] = 2.0f;
    expected[0] = 0;
    input0[1] = 2.0f;
    input1[1] = 1.0f;
    expected[1] = 0;
    input0[2] = 0.0f;
    input1[2] = 0.0f;
    expected[2] = 0;
    input0[3] = -1.0f;
    input1[3] = 1.0f;
    expected[3] = 0;
    input0[4] = 100.0f;
    input1[4] = 50.0f;
    expected[4] = 0;
    input0[5] = 3.14f;
    input1[5] = 2.71f;
    expected[5] = 0;
    input0[6] = 0.0f;
    input1[6] = 1.0f;
    expected[6] = 0;
    input0[7] = 5.0f;
    input1[7] = 5.0f;
    expected[7] = 0;
    input0[8] = -5.0f;
    input1[8] = -10.0f;
    expected[8] = 0;
    input0[9] = 1000.0f;
    input1[9] = 1.0f;
    expected[9] = 0;

    std::string kernelSource = loadKernel("relational_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_isunordered", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input0, &err);
    cl_mem inputBuffer1 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input1, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(int), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &inputBuffer1);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 3, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(int), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = (output[i] == expected[i]);
        test_results.push_back({"isunordered", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(inputBuffer1);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "isunordered() tests complete" << std::endl << std::endl;
}

void test_signbit() {
    std::cout << "Testing signbit()..." << std::endl;

    const int NUM_TESTS = 10;
    float input0[NUM_TESTS];
    int output[NUM_TESTS];
    int expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 0.0f;
    expected[0] = 0;
    input0[1] = 1.0f;
    expected[1] = 0;
    input0[2] = -1.0f;
    expected[2] = -1;
    input0[3] = 100.0f;
    expected[3] = 0;
    input0[4] = -100.0f;
    expected[4] = -1;
    input0[5] = 3.14159f;
    expected[5] = 0;
    input0[6] = -3.14159f;
    expected[6] = -1;
    input0[7] = 1e-05f;
    expected[7] = 0;
    input0[8] = -1e-05f;
    expected[8] = -1;
    input0[9] = 1000000.0f;
    expected[9] = 0;

    std::string kernelSource = loadKernel("relational_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_signbit", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input0, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(int), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(int), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = (output[i] == expected[i]);
        test_results.push_back({"signbit", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "signbit() tests complete" << std::endl << std::endl;
}

void test_any_int2() {
    std::cout << "Testing any_int2()..." << std::endl;

    const int NUM_TESTS = 10;
    cl_int2 input0[NUM_TESTS];
    int output[NUM_TESTS];
    int expected[NUM_TESTS];

    // Initialize test data
    input0[0] = (cl_int2){0, 0};
    expected[0] = 0;
    input0[1] = (cl_int2){1, 0};
    expected[1] = 1;
    input0[2] = (cl_int2){0, 1};
    expected[2] = 1;
    input0[3] = (cl_int2){1, 1};
    expected[3] = 1;
    input0[4] = (cl_int2){-1, 0};
    expected[4] = 1;
    input0[5] = (cl_int2){0, -1};
    expected[5] = 1;
    input0[6] = (cl_int2){-1, -1};
    expected[6] = 1;
    input0[7] = (cl_int2){5, 0};
    expected[7] = 1;
    input0[8] = (cl_int2){0, 5};
    expected[8] = 1;
    input0[9] = (cl_int2){5, 5};
    expected[9] = 1;

    std::string kernelSource = loadKernel("relational_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_any_int2", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(cl_int2), input0, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(int), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(int), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = (output[i] == expected[i]);
        test_results.push_back({"any_int2", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "any_int2() tests complete" << std::endl << std::endl;
}

void test_any_int4() {
    std::cout << "Testing any_int4()..." << std::endl;

    const int NUM_TESTS = 10;
    cl_int4 input0[NUM_TESTS];
    int output[NUM_TESTS];
    int expected[NUM_TESTS];

    // Initialize test data
    input0[0] = (cl_int4){0, 0, 0, 0};
    expected[0] = 0;
    input0[1] = (cl_int4){1, 0, 0, 0};
    expected[1] = 1;
    input0[2] = (cl_int4){0, 1, 0, 0};
    expected[2] = 1;
    input0[3] = (cl_int4){0, 0, 1, 0};
    expected[3] = 1;
    input0[4] = (cl_int4){0, 0, 0, 1};
    expected[4] = 1;
    input0[5] = (cl_int4){1, 1, 1, 1};
    expected[5] = 1;
    input0[6] = (cl_int4){-1, 0, 0, 0};
    expected[6] = 1;
    input0[7] = (cl_int4){0, -1, 0, 0};
    expected[7] = 1;
    input0[8] = (cl_int4){5, 5, 0, 0};
    expected[8] = 1;
    input0[9] = (cl_int4){5, 5, 5, 5};
    expected[9] = 1;

    std::string kernelSource = loadKernel("relational_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_any_int4", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(cl_int4), input0, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(int), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(int), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = (output[i] == expected[i]);
        test_results.push_back({"any_int4", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "any_int4() tests complete" << std::endl << std::endl;
}

void test_all_int2() {
    std::cout << "Testing all_int2()..." << std::endl;

    const int NUM_TESTS = 10;
    cl_int2 input0[NUM_TESTS];
    int output[NUM_TESTS];
    int expected[NUM_TESTS];

    // Initialize test data
    input0[0] = (cl_int2){0, 0};
    expected[0] = 0;
    input0[1] = (cl_int2){1, 0};
    expected[1] = 0;
    input0[2] = (cl_int2){0, 1};
    expected[2] = 0;
    input0[3] = (cl_int2){1, 1};
    expected[3] = 1;
    input0[4] = (cl_int2){-1, -1};
    expected[4] = 1;
    input0[5] = (cl_int2){-1, 0};
    expected[5] = 0;
    input0[6] = (cl_int2){0, -1};
    expected[6] = 0;
    input0[7] = (cl_int2){5, 5};
    expected[7] = 1;
    input0[8] = (cl_int2){5, 0};
    expected[8] = 0;
    input0[9] = (cl_int2){-5, -5};
    expected[9] = 1;

    std::string kernelSource = loadKernel("relational_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_all_int2", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(cl_int2), input0, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(int), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(int), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = (output[i] == expected[i]);
        test_results.push_back({"all_int2", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "all_int2() tests complete" << std::endl << std::endl;
}

void test_all_int4() {
    std::cout << "Testing all_int4()..." << std::endl;

    const int NUM_TESTS = 10;
    cl_int4 input0[NUM_TESTS];
    int output[NUM_TESTS];
    int expected[NUM_TESTS];

    // Initialize test data
    input0[0] = (cl_int4){0, 0, 0, 0};
    expected[0] = 0;
    input0[1] = (cl_int4){1, 1, 1, 1};
    expected[1] = 1;
    input0[2] = (cl_int4){1, 1, 1, 0};
    expected[2] = 0;
    input0[3] = (cl_int4){1, 1, 0, 1};
    expected[3] = 0;
    input0[4] = (cl_int4){1, 0, 1, 1};
    expected[4] = 0;
    input0[5] = (cl_int4){0, 1, 1, 1};
    expected[5] = 0;
    input0[6] = (cl_int4){-1, -1, -1, -1};
    expected[6] = 1;
    input0[7] = (cl_int4){5, 5, 5, 5};
    expected[7] = 1;
    input0[8] = (cl_int4){5, 5, 5, 0};
    expected[8] = 0;
    input0[9] = (cl_int4){-5, -5, -5, -5};
    expected[9] = 1;

    std::string kernelSource = loadKernel("relational_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_all_int4", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(cl_int4), input0, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(int), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(int), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = (output[i] == expected[i]);
        test_results.push_back({"all_int4", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "all_int4() tests complete" << std::endl << std::endl;
}

void test_select_float() {
    std::cout << "Testing select_float()..." << std::endl;

    const int NUM_TESTS = 10;
    float input0[NUM_TESTS];
    float input1[NUM_TESTS];
    int input2[NUM_TESTS];
    float output[NUM_TESTS];
    float expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 1.0f;
    input1[0] = 2.0f;
    input2[0] = 0;
    expected[0] = 1.0f;
    input0[1] = 1.0f;
    input1[1] = 2.0f;
    input2[1] = 1;
    expected[1] = 2.0f;
    input0[2] = 1.0f;
    input1[2] = 2.0f;
    input2[2] = -1;
    expected[2] = 2.0f;
    input0[3] = 5.0f;
    input1[3] = 10.0f;
    input2[3] = 0;
    expected[3] = 5.0f;
    input0[4] = 5.0f;
    input1[4] = 10.0f;
    input2[4] = 1;
    expected[4] = 10.0f;
    input0[5] = 3.14f;
    input1[5] = 2.71f;
    input2[5] = 0;
    expected[5] = 3.14f;
    input0[6] = 3.14f;
    input1[6] = 2.71f;
    input2[6] = -1;
    expected[6] = 2.71f;
    input0[7] = 100.0f;
    input1[7] = 200.0f;
    input2[7] = 1;
    expected[7] = 200.0f;
    input0[8] = 100.0f;
    input1[8] = 200.0f;
    input2[8] = 0;
    expected[8] = 100.0f;
    input0[9] = 0.5f;
    input1[9] = 1.5f;
    input2[9] = 5;
    expected[9] = 1.5f;

    std::string kernelSource = loadKernel("relational_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_select_float", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input0, &err);
    cl_mem inputBuffer1 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input1, &err);
    cl_mem inputBuffer2 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(int), input2, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(float), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &inputBuffer1);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &inputBuffer2);
    clSetKernelArg(kernel, 3, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 4, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(float), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i], expected[i]);
        test_results.push_back({"select_float", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(inputBuffer1);
    clReleaseMemObject(inputBuffer2);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "select_float() tests complete" << std::endl << std::endl;
}

void test_select_int() {
    std::cout << "Testing select_int()..." << std::endl;

    const int NUM_TESTS = 10;
    int input0[NUM_TESTS];
    int input1[NUM_TESTS];
    int input2[NUM_TESTS];
    int output[NUM_TESTS];
    int expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 1;
    input1[0] = 2;
    input2[0] = 0;
    expected[0] = 1;
    input0[1] = 1;
    input1[1] = 2;
    input2[1] = 1;
    expected[1] = 2;
    input0[2] = 1;
    input1[2] = 2;
    input2[2] = -1;
    expected[2] = 2;
    input0[3] = 5;
    input1[3] = 10;
    input2[3] = 0;
    expected[3] = 5;
    input0[4] = 5;
    input1[4] = 10;
    input2[4] = 1;
    expected[4] = 10;
    input0[5] = 100;
    input1[5] = 200;
    input2[5] = 0;
    expected[5] = 100;
    input0[6] = 100;
    input1[6] = 200;
    input2[6] = -1;
    expected[6] = 200;
    input0[7] = 42;
    input1[7] = 84;
    input2[7] = 1;
    expected[7] = 84;
    input0[8] = 42;
    input1[8] = 84;
    input2[8] = 0;
    expected[8] = 42;
    input0[9] = 7;
    input1[9] = 11;
    input2[9] = 5;
    expected[9] = 11;

    std::string kernelSource = loadKernel("relational_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_select_int", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(int), input0, &err);
    cl_mem inputBuffer1 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(int), input1, &err);
    cl_mem inputBuffer2 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(int), input2, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(int), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &inputBuffer1);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &inputBuffer2);
    clSetKernelArg(kernel, 3, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 4, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(int), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = (output[i] == expected[i]);
        test_results.push_back({"select_int", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(inputBuffer1);
    clReleaseMemObject(inputBuffer2);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "select_int() tests complete" << std::endl << std::endl;
}

void test_bitselect_float() {
    std::cout << "Testing bitselect_float()..." << std::endl;

    const int NUM_TESTS = 10;
    float input0[NUM_TESTS];
    float input1[NUM_TESTS];
    int input2[NUM_TESTS];
    float output[NUM_TESTS];
    float expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 1.0f;
    input1[0] = 2.0f;
    input2[0] = 0;
    expected[0] = 1.0f;
    input0[1] = 1.0f;
    input1[1] = 2.0f;
    input2[1] = 1;
    expected[1] = 1.0f;
    input0[2] = 5.0f;
    input1[2] = 10.0f;
    input2[2] = 0;
    expected[2] = 5.0f;
    input0[3] = 5.0f;
    input1[3] = 10.0f;
    input2[3] = 1;
    expected[3] = 5.0f;
    input0[4] = 3.14f;
    input1[4] = 2.71f;
    input2[4] = 0;
    expected[4] = 3.14f;
    input0[5] = 3.14f;
    input1[5] = 2.71f;
    input2[5] = 1;
    expected[5] = 3.14f;
    input0[6] = 100.0f;
    input1[6] = 200.0f;
    input2[6] = 0;
    expected[6] = 100.0f;
    input0[7] = 100.0f;
    input1[7] = 200.0f;
    input2[7] = 1;
    expected[7] = 100.0f;
    input0[8] = 0.5f;
    input1[8] = 1.5f;
    input2[8] = 0;
    expected[8] = 0.5f;
    input0[9] = 0.5f;
    input1[9] = 1.5f;
    input2[9] = 1;
    expected[9] = 0.5f;

    std::string kernelSource = loadKernel("relational_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_bitselect_float", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input0, &err);
    cl_mem inputBuffer1 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(float), input1, &err);
    cl_mem inputBuffer2 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(int), input2, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(float), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &inputBuffer1);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &inputBuffer2);
    clSetKernelArg(kernel, 3, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 4, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(float), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i], expected[i]);
        test_results.push_back({"bitselect_float", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(inputBuffer1);
    clReleaseMemObject(inputBuffer2);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "bitselect_float() tests complete" << std::endl << std::endl;
}

void test_bitselect_int() {
    std::cout << "Testing bitselect_int()..." << std::endl;

    const int NUM_TESTS = 10;
    int input0[NUM_TESTS];
    int input1[NUM_TESTS];
    int input2[NUM_TESTS];
    int output[NUM_TESTS];
    int expected[NUM_TESTS];

    // Initialize test data
    input0[0] = 0;
    input1[0] = 255;
    input2[0] = 0;
    expected[0] = 0;
    input0[1] = 0;
    input1[1] = 255;
    input2[1] = 255;
    expected[1] = 255;
    input0[2] = 255;
    input1[2] = 0;
    input2[2] = 0;
    expected[2] = 255;
    input0[3] = 255;
    input1[3] = 0;
    input2[3] = 255;
    expected[3] = 0;
    input0[4] = 15;
    input1[4] = 240;
    input2[4] = 15;
    expected[4] = 240;
    input0[5] = 15;
    input1[5] = 240;
    input2[5] = 240;
    expected[5] = 15;
    input0[6] = 170;
    input1[6] = 85;
    input2[6] = 255;
    expected[6] = 85;
    input0[7] = 170;
    input1[7] = 85;
    input2[7] = 0;
    expected[7] = 170;
    input0[8] = 12;
    input1[8] = 3;
    input2[8] = 15;
    expected[8] = 3;
    input0[9] = 12;
    input1[9] = 3;
    input2[9] = 0;
    expected[9] = 12;

    std::string kernelSource = loadKernel("relational_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_bitselect_int", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(int), input0, &err);
    cl_mem inputBuffer1 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(int), input1, &err);
    cl_mem inputBuffer2 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(int), input2, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(int), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &inputBuffer1);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &inputBuffer2);
    clSetKernelArg(kernel, 3, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 4, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(int), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = (output[i] == expected[i]);
        test_results.push_back({"bitselect_int", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(inputBuffer1);
    clReleaseMemObject(inputBuffer2);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "bitselect_int() tests complete" << std::endl << std::endl;
}

void test_dot_float2() {
    std::cout << "Testing dot_float2()..." << std::endl;

    const int NUM_TESTS = 10;
    cl_float2 input0[NUM_TESTS];
    cl_float2 input1[NUM_TESTS];
    float output[NUM_TESTS];
    float expected[NUM_TESTS];

    // Initialize test data
    input0[0] = (cl_float2){1.0f, 0.0f};
    input1[0] = (cl_float2){1.0f, 0.0f};
    expected[0] = 1.0f;
    input0[1] = (cl_float2){0.0f, 1.0f};
    input1[1] = (cl_float2){0.0f, 1.0f};
    expected[1] = 1.0f;
    input0[2] = (cl_float2){1.0f, 1.0f};
    input1[2] = (cl_float2){1.0f, 1.0f};
    expected[2] = 2.0f;
    input0[3] = (cl_float2){2.0f, 3.0f};
    input1[3] = (cl_float2){4.0f, 5.0f};
    expected[3] = 23.0f;
    input0[4] = (cl_float2){-1.0f, 2.0f};
    input1[4] = (cl_float2){3.0f, -4.0f};
    expected[4] = -11.0f;
    input0[5] = (cl_float2){0.5f, 0.5f};
    input1[5] = (cl_float2){0.5f, 0.5f};
    expected[5] = 0.5f;
    input0[6] = (cl_float2){1.0f, 0.0f};
    input1[6] = (cl_float2){0.0f, 1.0f};
    expected[6] = 0.0f;
    input0[7] = (cl_float2){3.0f, 4.0f};
    input1[7] = (cl_float2){3.0f, 4.0f};
    expected[7] = 25.0f;
    input0[8] = (cl_float2){1.0f, 2.0f};
    input1[8] = (cl_float2){2.0f, 1.0f};
    expected[8] = 4.0f;
    input0[9] = (cl_float2){10.0f, 20.0f};
    input1[9] = (cl_float2){5.0f, 2.5f};
    expected[9] = 100.0f;

    std::string kernelSource = loadKernel("geometric_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_dot_float2", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(cl_float2), input0, &err);
    cl_mem inputBuffer1 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(cl_float2), input1, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(float), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &inputBuffer1);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 3, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(float), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i], expected[i]);
        test_results.push_back({"dot_float2", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(inputBuffer1);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "dot_float2() tests complete" << std::endl << std::endl;
}

void test_dot_float3() {
    std::cout << "Testing dot_float3()..." << std::endl;

    const int NUM_TESTS = 10;
    cl_float3 input0[NUM_TESTS];
    cl_float3 input1[NUM_TESTS];
    float output[NUM_TESTS];
    float expected[NUM_TESTS];

    // Initialize test data
    input0[0] = (cl_float3){1.0f, 0.0f, 0.0f};
    input1[0] = (cl_float3){1.0f, 0.0f, 0.0f};
    expected[0] = 1.0f;
    input0[1] = (cl_float3){0.0f, 1.0f, 0.0f};
    input1[1] = (cl_float3){0.0f, 1.0f, 0.0f};
    expected[1] = 1.0f;
    input0[2] = (cl_float3){0.0f, 0.0f, 1.0f};
    input1[2] = (cl_float3){0.0f, 0.0f, 1.0f};
    expected[2] = 1.0f;
    input0[3] = (cl_float3){1.0f, 1.0f, 1.0f};
    input1[3] = (cl_float3){1.0f, 1.0f, 1.0f};
    expected[3] = 3.0f;
    input0[4] = (cl_float3){2.0f, 3.0f, 4.0f};
    input1[4] = (cl_float3){5.0f, 6.0f, 7.0f};
    expected[4] = 56.0f;
    input0[5] = (cl_float3){1.0f, 0.0f, 0.0f};
    input1[5] = (cl_float3){0.0f, 1.0f, 0.0f};
    expected[5] = 0.0f;
    input0[6] = (cl_float3){3.0f, 4.0f, 0.0f};
    input1[6] = (cl_float3){3.0f, 4.0f, 0.0f};
    expected[6] = 25.0f;
    input0[7] = (cl_float3){1.0f, 2.0f, 3.0f};
    input1[7] = (cl_float3){3.0f, 2.0f, 1.0f};
    expected[7] = 10.0f;
    input0[8] = (cl_float3){-1.0f, 2.0f, -3.0f};
    input1[8] = (cl_float3){4.0f, -5.0f, 6.0f};
    expected[8] = -32.0f;
    input0[9] = (cl_float3){0.5f, 0.5f, 0.5f};
    input1[9] = (cl_float3){2.0f, 2.0f, 2.0f};
    expected[9] = 3.0f;

    std::string kernelSource = loadKernel("geometric_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_dot_float3", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(cl_float3), input0, &err);
    cl_mem inputBuffer1 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(cl_float3), input1, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(float), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &inputBuffer1);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 3, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(float), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i], expected[i]);
        test_results.push_back({"dot_float3", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(inputBuffer1);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "dot_float3() tests complete" << std::endl << std::endl;
}

void test_length_float2() {
    std::cout << "Testing length_float2()..." << std::endl;

    const int NUM_TESTS = 10;
    cl_float2 input0[NUM_TESTS];
    float output[NUM_TESTS];
    float expected[NUM_TESTS];

    // Initialize test data
    input0[0] = (cl_float2){3.0f, 4.0f};
    expected[0] = 5.0f;
    input0[1] = (cl_float2){0.0f, 0.0f};
    expected[1] = 0.0f;
    input0[2] = (cl_float2){1.0f, 0.0f};
    expected[2] = 1.0f;
    input0[3] = (cl_float2){0.0f, 1.0f};
    expected[3] = 1.0f;
    input0[4] = (cl_float2){1.0f, 1.0f};
    expected[4] = 1.4142135624f;
    input0[5] = (cl_float2){5.0f, 12.0f};
    expected[5] = 13.0f;
    input0[6] = (cl_float2){8.0f, 15.0f};
    expected[6] = 17.0f;
    input0[7] = (cl_float2){2.0f, 2.0f};
    expected[7] = 2.8284271247f;
    input0[8] = (cl_float2){6.0f, 8.0f};
    expected[8] = 10.0f;
    input0[9] = (cl_float2){1.0f, 2.0f};
    expected[9] = 2.2360679775f;

    std::string kernelSource = loadKernel("geometric_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_length_float2", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(cl_float2), input0, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(float), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(float), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i], expected[i]);
        test_results.push_back({"length_float2", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "length_float2() tests complete" << std::endl << std::endl;
}

void test_length_float3() {
    std::cout << "Testing length_float3()..." << std::endl;

    const int NUM_TESTS = 10;
    cl_float3 input0[NUM_TESTS];
    float output[NUM_TESTS];
    float expected[NUM_TESTS];

    // Initialize test data
    input0[0] = (cl_float3){0.0f, 0.0f, 0.0f};
    expected[0] = 0.0f;
    input0[1] = (cl_float3){1.0f, 0.0f, 0.0f};
    expected[1] = 1.0f;
    input0[2] = (cl_float3){0.0f, 1.0f, 0.0f};
    expected[2] = 1.0f;
    input0[3] = (cl_float3){0.0f, 0.0f, 1.0f};
    expected[3] = 1.0f;
    input0[4] = (cl_float3){1.0f, 1.0f, 1.0f};
    expected[4] = 1.7320508076f;
    input0[5] = (cl_float3){3.0f, 4.0f, 0.0f};
    expected[5] = 5.0f;
    input0[6] = (cl_float3){2.0f, 3.0f, 6.0f};
    expected[6] = 7.0f;
    input0[7] = (cl_float3){1.0f, 2.0f, 2.0f};
    expected[7] = 3.0f;
    input0[8] = (cl_float3){2.0f, 2.0f, 1.0f};
    expected[8] = 3.0f;
    input0[9] = (cl_float3){4.0f, 4.0f, 2.0f};
    expected[9] = 6.0f;

    std::string kernelSource = loadKernel("geometric_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_length_float3", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(cl_float3), input0, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(float), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(float), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i], expected[i]);
        test_results.push_back({"length_float3", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "length_float3() tests complete" << std::endl << std::endl;
}

void test_distance_float2() {
    std::cout << "Testing distance_float2()..." << std::endl;

    const int NUM_TESTS = 10;
    cl_float2 input0[NUM_TESTS];
    cl_float2 input1[NUM_TESTS];
    float output[NUM_TESTS];
    float expected[NUM_TESTS];

    // Initialize test data
    input0[0] = (cl_float2){0.0f, 0.0f};
    input1[0] = (cl_float2){3.0f, 4.0f};
    expected[0] = 5.0f;
    input0[1] = (cl_float2){0.0f, 0.0f};
    input1[1] = (cl_float2){0.0f, 0.0f};
    expected[1] = 0.0f;
    input0[2] = (cl_float2){1.0f, 1.0f};
    input1[2] = (cl_float2){1.0f, 1.0f};
    expected[2] = 0.0f;
    input0[3] = (cl_float2){0.0f, 0.0f};
    input1[3] = (cl_float2){1.0f, 0.0f};
    expected[3] = 1.0f;
    input0[4] = (cl_float2){0.0f, 0.0f};
    input1[4] = (cl_float2){0.0f, 1.0f};
    expected[4] = 1.0f;
    input0[5] = (cl_float2){1.0f, 2.0f};
    input1[5] = (cl_float2){4.0f, 6.0f};
    expected[5] = 5.0f;
    input0[6] = (cl_float2){2.0f, 3.0f};
    input1[6] = (cl_float2){5.0f, 7.0f};
    expected[6] = 5.0f;
    input0[7] = (cl_float2){-1.0f, -1.0f};
    input1[7] = (cl_float2){2.0f, 3.0f};
    expected[7] = 5.0f;
    input0[8] = (cl_float2){0.0f, 0.0f};
    input1[8] = (cl_float2){1.0f, 1.0f};
    expected[8] = 1.4142135624f;
    input0[9] = (cl_float2){5.0f, 5.0f};
    input1[9] = (cl_float2){8.0f, 9.0f};
    expected[9] = 5.0f;

    std::string kernelSource = loadKernel("geometric_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_distance_float2", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(cl_float2), input0, &err);
    cl_mem inputBuffer1 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(cl_float2), input1, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(float), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &inputBuffer1);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 3, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(float), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i], expected[i]);
        test_results.push_back({"distance_float2", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(inputBuffer1);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "distance_float2() tests complete" << std::endl << std::endl;
}

void test_dot_float4() {
    std::cout << "Testing dot_float4()..." << std::endl;

    const int NUM_TESTS = 10;
    cl_float4 input0[NUM_TESTS];
    cl_float4 input1[NUM_TESTS];
    float output[NUM_TESTS];
    float expected[NUM_TESTS];

    // Initialize test data
    input0[0] = (cl_float4){1.0f, 0.0f, 0.0f, 0.0f};
    input1[0] = (cl_float4){0.0f, 1.0f, 0.0f, 0.0f};
    expected[0] = 0.0f;
    input0[1] = (cl_float4){0.0f, 1.0f, 0.0f, 0.0f};
    input1[1] = (cl_float4){0.0f, 0.0f, 1.0f, 0.0f};
    expected[1] = 0.0f;
    input0[2] = (cl_float4){0.0f, 0.0f, 1.0f, 0.0f};
    input1[2] = (cl_float4){0.0f, 0.0f, 0.0f, 1.0f};
    expected[2] = 0.0f;
    input0[3] = (cl_float4){0.0f, 0.0f, 0.0f, 1.0f};
    input1[3] = (cl_float4){1.0f, 1.0f, 1.0f, 1.0f};
    expected[3] = 1.0f;
    input0[4] = (cl_float4){1.0f, 1.0f, 1.0f, 1.0f};
    input1[4] = (cl_float4){2.0f, 3.0f, 4.0f, 5.0f};
    expected[4] = 14.0f;
    input0[5] = (cl_float4){2.0f, 3.0f, 4.0f, 5.0f};
    input1[5] = (cl_float4){3.0f, 4.0f, 0.0f, 0.0f};
    expected[5] = 18.0f;
    input0[6] = (cl_float4){3.0f, 4.0f, 0.0f, 0.0f};
    input1[6] = (cl_float4){-1.0f, 2.0f, -3.0f, 4.0f};
    expected[6] = 5.0f;
    input0[7] = (cl_float4){-1.0f, 2.0f, -3.0f, 4.0f};
    input1[7] = (cl_float4){0.5f, 0.5f, 0.5f, 0.5f};
    expected[7] = 1.0f;
    input0[8] = (cl_float4){0.5f, 0.5f, 0.5f, 0.5f};
    input1[8] = (cl_float4){1.0f, 2.0f, 2.0f, 3.0f};
    expected[8] = 4.0f;
    input0[9] = (cl_float4){1.0f, 2.0f, 2.0f, 3.0f};
    input1[9] = (cl_float4){1.0f, 0.0f, 0.0f, 0.0f};
    expected[9] = 1.0f;

    std::string kernelSource = loadKernel("geometric_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_dot_float4", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(cl_float4), input0, &err);
    cl_mem inputBuffer1 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(cl_float4), input1, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(float), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &inputBuffer1);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 3, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(float), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i], expected[i]);
        test_results.push_back({"dot_float4", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(inputBuffer1);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "dot_float4() tests complete" << std::endl << std::endl;
}

void test_cross() {
    std::cout << "Testing cross()..." << std::endl;

    const int NUM_TESTS = 10;
    cl_float3 input0[NUM_TESTS];
    cl_float3 input1[NUM_TESTS];
    cl_float3 output[NUM_TESTS];
    cl_float3 expected[NUM_TESTS];

    // Initialize test data
    input0[0] = (cl_float3){1.0f, 0.0f, 0.0f};
    input1[0] = (cl_float3){0.0f, 1.0f, 0.0f};
    expected[0] = (cl_float3){0.0f, 0.0f, 1.0f};
    input0[1] = (cl_float3){0.0f, 1.0f, 0.0f};
    input1[1] = (cl_float3){0.0f, 0.0f, 1.0f};
    expected[1] = (cl_float3){1.0f, 0.0f, 0.0f};
    input0[2] = (cl_float3){0.0f, 0.0f, 1.0f};
    input1[2] = (cl_float3){1.0f, 1.0f, 1.0f};
    expected[2] = (cl_float3){-1.0f, 1.0f, 0.0f};
    input0[3] = (cl_float3){1.0f, 1.0f, 1.0f};
    input1[3] = (cl_float3){3.0f, 4.0f, 0.0f};
    expected[3] = (cl_float3){-4.0f, 3.0f, 1.0f};
    input0[4] = (cl_float3){3.0f, 4.0f, 0.0f};
    input1[4] = (cl_float3){2.0f, 3.0f, 6.0f};
    expected[4] = (cl_float3){24.0f, -18.0f, 1.0f};
    input0[5] = (cl_float3){2.0f, 3.0f, 6.0f};
    input1[5] = (cl_float3){-1.0f, 2.0f, -3.0f};
    expected[5] = (cl_float3){-21.0f, 0.0f, 7.0f};
    input0[6] = (cl_float3){-1.0f, 2.0f, -3.0f};
    input1[6] = (cl_float3){0.5f, 0.5f, 0.5f};
    expected[6] = (cl_float3){2.5f, -1.0f, -1.5f};
    input0[7] = (cl_float3){0.5f, 0.5f, 0.5f};
    input1[7] = (cl_float3){1.0f, 2.0f, 2.0f};
    expected[7] = (cl_float3){0.0f, -0.5f, 0.5f};
    input0[8] = (cl_float3){1.0f, 2.0f, 2.0f};
    input1[8] = (cl_float3){4.0f, 4.0f, 2.0f};
    expected[8] = (cl_float3){-4.0f, 6.0f, -4.0f};
    input0[9] = (cl_float3){4.0f, 4.0f, 2.0f};
    input1[9] = (cl_float3){1.0f, 0.0f, 0.0f};
    expected[9] = (cl_float3){0.0f, 2.0f, -4.0f};

    std::string kernelSource = loadKernel("geometric_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_cross", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(cl_float3), input0, &err);
    cl_mem inputBuffer1 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(cl_float3), input1, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(cl_float3), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &inputBuffer1);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 3, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(cl_float3), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i].s[0], expected[i].s[0]) &&
                       floatEquals(output[i].s[1], expected[i].s[1]) &&
                       floatEquals(output[i].s[2], expected[i].s[2]);
        test_results.push_back({"cross", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(inputBuffer1);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "cross() tests complete" << std::endl << std::endl;
}

void test_cross_float4() {
    std::cout << "Testing cross_float4()..." << std::endl;

    const int NUM_TESTS = 10;
    cl_float4 input0[NUM_TESTS];
    cl_float4 input1[NUM_TESTS];
    cl_float4 output[NUM_TESTS];
    cl_float4 expected[NUM_TESTS];

    // Initialize test data
    input0[0] = (cl_float4){1.0f, 0.0f, 0.0f, 0.0f};
    input1[0] = (cl_float4){0.0f, 1.0f, 0.0f, 0.0f};
    expected[0] = (cl_float4){0.0f, 0.0f, 1.0f, 0.0f};
    input0[1] = (cl_float4){0.0f, 1.0f, 0.0f, 0.0f};
    input1[1] = (cl_float4){0.0f, 0.0f, 1.0f, 0.0f};
    expected[1] = (cl_float4){1.0f, 0.0f, 0.0f, 0.0f};
    input0[2] = (cl_float4){0.0f, 0.0f, 1.0f, 0.0f};
    input1[2] = (cl_float4){0.0f, 0.0f, 0.0f, 1.0f};
    expected[2] = (cl_float4){0.0f, 0.0f, 0.0f, 0.0f};
    input0[3] = (cl_float4){0.0f, 0.0f, 0.0f, 1.0f};
    input1[3] = (cl_float4){1.0f, 1.0f, 1.0f, 1.0f};
    expected[3] = (cl_float4){0.0f, 0.0f, 0.0f, 0.0f};
    input0[4] = (cl_float4){1.0f, 1.0f, 1.0f, 1.0f};
    input1[4] = (cl_float4){2.0f, 3.0f, 4.0f, 5.0f};
    expected[4] = (cl_float4){1.0f, -2.0f, 1.0f, 0.0f};
    input0[5] = (cl_float4){2.0f, 3.0f, 4.0f, 5.0f};
    input1[5] = (cl_float4){3.0f, 4.0f, 0.0f, 0.0f};
    expected[5] = (cl_float4){-16.0f, 12.0f, -1.0f, 0.0f};
    input0[6] = (cl_float4){3.0f, 4.0f, 0.0f, 0.0f};
    input1[6] = (cl_float4){-1.0f, 2.0f, -3.0f, 4.0f};
    expected[6] = (cl_float4){-12.0f, 9.0f, 10.0f, 0.0f};
    input0[7] = (cl_float4){-1.0f, 2.0f, -3.0f, 4.0f};
    input1[7] = (cl_float4){0.5f, 0.5f, 0.5f, 0.5f};
    expected[7] = (cl_float4){2.5f, -1.0f, -1.5f, 0.0f};
    input0[8] = (cl_float4){0.5f, 0.5f, 0.5f, 0.5f};
    input1[8] = (cl_float4){1.0f, 2.0f, 2.0f, 3.0f};
    expected[8] = (cl_float4){0.0f, -0.5f, 0.5f, 0.0f};
    input0[9] = (cl_float4){1.0f, 2.0f, 2.0f, 3.0f};
    input1[9] = (cl_float4){1.0f, 0.0f, 0.0f, 0.0f};
    expected[9] = (cl_float4){0.0f, 2.0f, -2.0f, 0.0f};

    std::string kernelSource = loadKernel("geometric_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_cross_float4", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(cl_float4), input0, &err);
    cl_mem inputBuffer1 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(cl_float4), input1, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(cl_float4), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &inputBuffer1);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 3, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(cl_float4), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i].s[0], expected[i].s[0]) &&
                       floatEquals(output[i].s[1], expected[i].s[1]) &&
                       floatEquals(output[i].s[2], expected[i].s[2]) &&
                       floatEquals(output[i].s[3], expected[i].s[3]);
        test_results.push_back({"cross_float4", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(inputBuffer1);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "cross_float4() tests complete" << std::endl << std::endl;
}

void test_distance_float3() {
    std::cout << "Testing distance_float3()..." << std::endl;

    const int NUM_TESTS = 10;
    cl_float3 input0[NUM_TESTS];
    cl_float3 input1[NUM_TESTS];
    float output[NUM_TESTS];
    float expected[NUM_TESTS];

    // Initialize test data
    input0[0] = (cl_float3){1.0f, 0.0f, 0.0f};
    input1[0] = (cl_float3){0.0f, 1.0f, 0.0f};
    expected[0] = 1.4142135623730951f;
    input0[1] = (cl_float3){0.0f, 1.0f, 0.0f};
    input1[1] = (cl_float3){0.0f, 0.0f, 1.0f};
    expected[1] = 1.4142135623730951f;
    input0[2] = (cl_float3){0.0f, 0.0f, 1.0f};
    input1[2] = (cl_float3){1.0f, 1.0f, 1.0f};
    expected[2] = 1.4142135623730951f;
    input0[3] = (cl_float3){1.0f, 1.0f, 1.0f};
    input1[3] = (cl_float3){3.0f, 4.0f, 0.0f};
    expected[3] = 3.7416573867739413f;
    input0[4] = (cl_float3){3.0f, 4.0f, 0.0f};
    input1[4] = (cl_float3){2.0f, 3.0f, 6.0f};
    expected[4] = 6.164414002968976f;
    input0[5] = (cl_float3){2.0f, 3.0f, 6.0f};
    input1[5] = (cl_float3){-1.0f, 2.0f, -3.0f};
    expected[5] = 9.539392014169456f;
    input0[6] = (cl_float3){-1.0f, 2.0f, -3.0f};
    input1[6] = (cl_float3){0.5f, 0.5f, 0.5f};
    expected[6] = 4.092676385936225f;
    input0[7] = (cl_float3){0.5f, 0.5f, 0.5f};
    input1[7] = (cl_float3){1.0f, 2.0f, 2.0f};
    expected[7] = 2.179449471770337f;
    input0[8] = (cl_float3){1.0f, 2.0f, 2.0f};
    input1[8] = (cl_float3){4.0f, 4.0f, 2.0f};
    expected[8] = 3.605551275463989f;
    input0[9] = (cl_float3){4.0f, 4.0f, 2.0f};
    input1[9] = (cl_float3){1.0f, 0.0f, 0.0f};
    expected[9] = 5.385164807134504f;

    std::string kernelSource = loadKernel("geometric_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_distance_float3", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(cl_float3), input0, &err);
    cl_mem inputBuffer1 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(cl_float3), input1, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(float), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &inputBuffer1);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 3, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(float), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i], expected[i]);
        test_results.push_back({"distance_float3", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(inputBuffer1);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "distance_float3() tests complete" << std::endl << std::endl;
}

void test_distance_float4() {
    std::cout << "Testing distance_float4()..." << std::endl;

    const int NUM_TESTS = 10;
    cl_float4 input0[NUM_TESTS];
    cl_float4 input1[NUM_TESTS];
    float output[NUM_TESTS];
    float expected[NUM_TESTS];

    // Initialize test data
    input0[0] = (cl_float4){1.0f, 0.0f, 0.0f, 0.0f};
    input1[0] = (cl_float4){0.0f, 1.0f, 0.0f, 0.0f};
    expected[0] = 1.4142135623730951f;
    input0[1] = (cl_float4){0.0f, 1.0f, 0.0f, 0.0f};
    input1[1] = (cl_float4){0.0f, 0.0f, 1.0f, 0.0f};
    expected[1] = 1.4142135623730951f;
    input0[2] = (cl_float4){0.0f, 0.0f, 1.0f, 0.0f};
    input1[2] = (cl_float4){0.0f, 0.0f, 0.0f, 1.0f};
    expected[2] = 1.4142135623730951f;
    input0[3] = (cl_float4){0.0f, 0.0f, 0.0f, 1.0f};
    input1[3] = (cl_float4){1.0f, 1.0f, 1.0f, 1.0f};
    expected[3] = 1.7320508075688772f;
    input0[4] = (cl_float4){1.0f, 1.0f, 1.0f, 1.0f};
    input1[4] = (cl_float4){2.0f, 3.0f, 4.0f, 5.0f};
    expected[4] = 5.477225575051661f;
    input0[5] = (cl_float4){2.0f, 3.0f, 4.0f, 5.0f};
    input1[5] = (cl_float4){3.0f, 4.0f, 0.0f, 0.0f};
    expected[5] = 6.557438524302f;
    input0[6] = (cl_float4){3.0f, 4.0f, 0.0f, 0.0f};
    input1[6] = (cl_float4){-1.0f, 2.0f, -3.0f, 4.0f};
    expected[6] = 6.708203932499369f;
    input0[7] = (cl_float4){-1.0f, 2.0f, -3.0f, 4.0f};
    input1[7] = (cl_float4){0.5f, 0.5f, 0.5f, 0.5f};
    expected[7] = 5.385164807134504f;
    input0[8] = (cl_float4){0.5f, 0.5f, 0.5f, 0.5f};
    input1[8] = (cl_float4){1.0f, 2.0f, 2.0f, 3.0f};
    expected[8] = 3.3166247903554f;
    input0[9] = (cl_float4){1.0f, 2.0f, 2.0f, 3.0f};
    input1[9] = (cl_float4){1.0f, 0.0f, 0.0f, 0.0f};
    expected[9] = 4.123105625617661f;

    std::string kernelSource = loadKernel("geometric_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_distance_float4", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(cl_float4), input0, &err);
    cl_mem inputBuffer1 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(cl_float4), input1, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(float), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &inputBuffer1);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 3, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(float), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i], expected[i]);
        test_results.push_back({"distance_float4", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(inputBuffer1);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "distance_float4() tests complete" << std::endl << std::endl;
}

void test_length_float4() {
    std::cout << "Testing length_float4()..." << std::endl;

    const int NUM_TESTS = 10;
    cl_float4 input0[NUM_TESTS];
    float output[NUM_TESTS];
    float expected[NUM_TESTS];

    // Initialize test data
    input0[0] = (cl_float4){1.0f, 0.0f, 0.0f, 0.0f};
    expected[0] = 1.0f;
    input0[1] = (cl_float4){0.0f, 1.0f, 0.0f, 0.0f};
    expected[1] = 1.0f;
    input0[2] = (cl_float4){0.0f, 0.0f, 1.0f, 0.0f};
    expected[2] = 1.0f;
    input0[3] = (cl_float4){0.0f, 0.0f, 0.0f, 1.0f};
    expected[3] = 1.0f;
    input0[4] = (cl_float4){1.0f, 1.0f, 1.0f, 1.0f};
    expected[4] = 2.0f;
    input0[5] = (cl_float4){2.0f, 3.0f, 4.0f, 5.0f};
    expected[5] = 7.3484692283495345f;
    input0[6] = (cl_float4){3.0f, 4.0f, 0.0f, 0.0f};
    expected[6] = 5.0f;
    input0[7] = (cl_float4){-1.0f, 2.0f, -3.0f, 4.0f};
    expected[7] = 5.477225575051661f;
    input0[8] = (cl_float4){0.5f, 0.5f, 0.5f, 0.5f};
    expected[8] = 1.0f;
    input0[9] = (cl_float4){1.0f, 2.0f, 2.0f, 3.0f};
    expected[9] = 4.242640687119285f;

    std::string kernelSource = loadKernel("geometric_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_length_float4", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(cl_float4), input0, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(float), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(float), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i], expected[i]);
        test_results.push_back({"length_float4", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "length_float4() tests complete" << std::endl << std::endl;
}

void test_normalize_float2() {
    std::cout << "Testing normalize_float2()..." << std::endl;

    const int NUM_TESTS = 10;
    cl_float2 input0[NUM_TESTS];
    cl_float2 output[NUM_TESTS];
    cl_float2 expected[NUM_TESTS];

    // Initialize test data
    input0[0] = (cl_float2){1.0f, 0.0f};
    expected[0] = (cl_float2){1.0f, 0.0f};
    input0[1] = (cl_float2){0.0f, 1.0f};
    expected[1] = (cl_float2){0.0f, 1.0f};
    input0[2] = (cl_float2){1.0f, 1.0f};
    expected[2] = (cl_float2){0.7071067811865475f, 0.7071067811865475f};
    input0[3] = (cl_float2){3.0f, 4.0f};
    expected[3] = (cl_float2){0.6f, 0.8f};
    input0[4] = (cl_float2){5.0f, 12.0f};
    expected[4] = (cl_float2){0.38461538461538464f, 0.9230769230769231f};
    input0[5] = (cl_float2){-1.0f, 2.0f};
    expected[5] = (cl_float2){-0.4472135954999579f, 0.8944271909999159f};
    input0[6] = (cl_float2){0.5f, 0.5f};
    expected[6] = (cl_float2){0.7071067811865475f, 0.7071067811865475f};
    input0[7] = (cl_float2){2.0f, 3.0f};
    expected[7] = (cl_float2){0.5547001962252291f, 0.8320502943378437f};
    input0[8] = (cl_float2){6.0f, 8.0f};
    expected[8] = (cl_float2){0.6f, 0.8f};
    input0[9] = (cl_float2){10.0f, 20.0f};
    expected[9] = (cl_float2){0.4472135954999579f, 0.8944271909999159f};

    std::string kernelSource = loadKernel("geometric_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_normalize_float2", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(cl_float2), input0, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(cl_float2), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(cl_float2), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i].s[0], expected[i].s[0]) &&
                       floatEquals(output[i].s[1], expected[i].s[1]);
        test_results.push_back({"normalize_float2", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "normalize_float2() tests complete" << std::endl << std::endl;
}

void test_normalize_float3() {
    std::cout << "Testing normalize_float3()..." << std::endl;

    const int NUM_TESTS = 10;
    cl_float3 input0[NUM_TESTS];
    cl_float3 output[NUM_TESTS];
    cl_float3 expected[NUM_TESTS];

    // Initialize test data
    input0[0] = (cl_float3){1.0f, 0.0f, 0.0f};
    expected[0] = (cl_float3){1.0f, 0.0f, 0.0f};
    input0[1] = (cl_float3){0.0f, 1.0f, 0.0f};
    expected[1] = (cl_float3){0.0f, 1.0f, 0.0f};
    input0[2] = (cl_float3){0.0f, 0.0f, 1.0f};
    expected[2] = (cl_float3){0.0f, 0.0f, 1.0f};
    input0[3] = (cl_float3){1.0f, 1.0f, 1.0f};
    expected[3] = (cl_float3){0.5773502691896258f, 0.5773502691896258f, 0.5773502691896258f};
    input0[4] = (cl_float3){3.0f, 4.0f, 0.0f};
    expected[4] = (cl_float3){0.6f, 0.8f, 0.0f};
    input0[5] = (cl_float3){2.0f, 3.0f, 6.0f};
    expected[5] = (cl_float3){0.2857142857142857f, 0.42857142857142855f, 0.8571428571428571f};
    input0[6] = (cl_float3){-1.0f, 2.0f, -3.0f};
    expected[6] = (cl_float3){-0.2672612419124244f, 0.5345224838248488f, -0.8017837257372732f};
    input0[7] = (cl_float3){0.5f, 0.5f, 0.5f};
    expected[7] = (cl_float3){0.5773502691896258f, 0.5773502691896258f, 0.5773502691896258f};
    input0[8] = (cl_float3){1.0f, 2.0f, 2.0f};
    expected[8] = (cl_float3){0.3333333333333333f, 0.6666666666666666f, 0.6666666666666666f};
    input0[9] = (cl_float3){4.0f, 4.0f, 2.0f};
    expected[9] = (cl_float3){0.6666666666666666f, 0.6666666666666666f, 0.3333333333333333f};

    std::string kernelSource = loadKernel("geometric_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_normalize_float3", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(cl_float3), input0, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(cl_float3), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(cl_float3), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i].s[0], expected[i].s[0]) &&
                       floatEquals(output[i].s[1], expected[i].s[1]) &&
                       floatEquals(output[i].s[2], expected[i].s[2]);
        test_results.push_back({"normalize_float3", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "normalize_float3() tests complete" << std::endl << std::endl;
}

void test_normalize_float4() {
    std::cout << "Testing normalize_float4()..." << std::endl;

    const int NUM_TESTS = 10;
    cl_float4 input0[NUM_TESTS];
    cl_float4 output[NUM_TESTS];
    cl_float4 expected[NUM_TESTS];

    // Initialize test data
    input0[0] = (cl_float4){1.0f, 0.0f, 0.0f, 0.0f};
    expected[0] = (cl_float4){1.0f, 0.0f, 0.0f, 0.0f};
    input0[1] = (cl_float4){0.0f, 1.0f, 0.0f, 0.0f};
    expected[1] = (cl_float4){0.0f, 1.0f, 0.0f, 0.0f};
    input0[2] = (cl_float4){0.0f, 0.0f, 1.0f, 0.0f};
    expected[2] = (cl_float4){0.0f, 0.0f, 1.0f, 0.0f};
    input0[3] = (cl_float4){0.0f, 0.0f, 0.0f, 1.0f};
    expected[3] = (cl_float4){0.0f, 0.0f, 0.0f, 1.0f};
    input0[4] = (cl_float4){1.0f, 1.0f, 1.0f, 1.0f};
    expected[4] = (cl_float4){0.5f, 0.5f, 0.5f, 0.5f};
    input0[5] = (cl_float4){2.0f, 3.0f, 4.0f, 5.0f};
    expected[5] = (cl_float4){0.2721655269759087f, 0.408248290463863f, 0.5443310539518174f, 0.6804138174397717f};
    input0[6] = (cl_float4){3.0f, 4.0f, 0.0f, 0.0f};
    expected[6] = (cl_float4){0.6f, 0.8f, 0.0f, 0.0f};
    input0[7] = (cl_float4){-1.0f, 2.0f, -3.0f, 4.0f};
    expected[7] = (cl_float4){-0.18257418583505536f, 0.3651483716701107f, -0.5477225575051661f, 0.7302967433402214f};
    input0[8] = (cl_float4){0.5f, 0.5f, 0.5f, 0.5f};
    expected[8] = (cl_float4){0.5f, 0.5f, 0.5f, 0.5f};
    input0[9] = (cl_float4){1.0f, 2.0f, 2.0f, 3.0f};
    expected[9] = (cl_float4){0.23570226039551587f, 0.47140452079103173f, 0.47140452079103173f, 0.7071067811865476f};

    std::string kernelSource = loadKernel("geometric_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_normalize_float4", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(cl_float4), input0, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(cl_float4), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(cl_float4), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i].s[0], expected[i].s[0]) &&
                       floatEquals(output[i].s[1], expected[i].s[1]) &&
                       floatEquals(output[i].s[2], expected[i].s[2]) &&
                       floatEquals(output[i].s[3], expected[i].s[3]);
        test_results.push_back({"normalize_float4", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "normalize_float4() tests complete" << std::endl << std::endl;
}

void test_fast_distance_float2() {
    std::cout << "Testing fast_distance_float2()..." << std::endl;

    const int NUM_TESTS = 10;
    cl_float2 input0[NUM_TESTS];
    cl_float2 input1[NUM_TESTS];
    float output[NUM_TESTS];
    float expected[NUM_TESTS];

    // Initialize test data
    input0[0] = (cl_float2){1.0f, 0.0f};
    input1[0] = (cl_float2){0.0f, 1.0f};
    expected[0] = 1.4142135623730951f;
    input0[1] = (cl_float2){0.0f, 1.0f};
    input1[1] = (cl_float2){1.0f, 1.0f};
    expected[1] = 1.0f;
    input0[2] = (cl_float2){1.0f, 1.0f};
    input1[2] = (cl_float2){3.0f, 4.0f};
    expected[2] = 3.605551275463989f;
    input0[3] = (cl_float2){3.0f, 4.0f};
    input1[3] = (cl_float2){5.0f, 12.0f};
    expected[3] = 8.246211251235321f;
    input0[4] = (cl_float2){5.0f, 12.0f};
    input1[4] = (cl_float2){-1.0f, 2.0f};
    expected[4] = 11.661903789690601f;
    input0[5] = (cl_float2){-1.0f, 2.0f};
    input1[5] = (cl_float2){0.5f, 0.5f};
    expected[5] = 2.1213203435596424f;
    input0[6] = (cl_float2){0.5f, 0.5f};
    input1[6] = (cl_float2){2.0f, 3.0f};
    expected[6] = 2.9154759474226504f;
    input0[7] = (cl_float2){2.0f, 3.0f};
    input1[7] = (cl_float2){6.0f, 8.0f};
    expected[7] = 6.4031242374328485f;
    input0[8] = (cl_float2){6.0f, 8.0f};
    input1[8] = (cl_float2){10.0f, 20.0f};
    expected[8] = 12.649110640673518f;
    input0[9] = (cl_float2){10.0f, 20.0f};
    input1[9] = (cl_float2){1.0f, 0.0f};
    expected[9] = 21.93171219946131f;

    std::string kernelSource = loadKernel("geometric_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_fast_distance_float2", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(cl_float2), input0, &err);
    cl_mem inputBuffer1 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(cl_float2), input1, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(float), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &inputBuffer1);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 3, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(float), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i], expected[i]);
        test_results.push_back({"fast_distance_float2", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(inputBuffer1);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "fast_distance_float2() tests complete" << std::endl << std::endl;
}

void test_fast_distance_float3() {
    std::cout << "Testing fast_distance_float3()..." << std::endl;

    const int NUM_TESTS = 10;
    cl_float3 input0[NUM_TESTS];
    cl_float3 input1[NUM_TESTS];
    float output[NUM_TESTS];
    float expected[NUM_TESTS];

    // Initialize test data
    input0[0] = (cl_float3){1.0f, 0.0f, 0.0f};
    input1[0] = (cl_float3){0.0f, 1.0f, 0.0f};
    expected[0] = 1.4142135623730951f;
    input0[1] = (cl_float3){0.0f, 1.0f, 0.0f};
    input1[1] = (cl_float3){0.0f, 0.0f, 1.0f};
    expected[1] = 1.4142135623730951f;
    input0[2] = (cl_float3){0.0f, 0.0f, 1.0f};
    input1[2] = (cl_float3){1.0f, 1.0f, 1.0f};
    expected[2] = 1.4142135623730951f;
    input0[3] = (cl_float3){1.0f, 1.0f, 1.0f};
    input1[3] = (cl_float3){3.0f, 4.0f, 0.0f};
    expected[3] = 3.7416573867739413f;
    input0[4] = (cl_float3){3.0f, 4.0f, 0.0f};
    input1[4] = (cl_float3){2.0f, 3.0f, 6.0f};
    expected[4] = 6.164414002968976f;
    input0[5] = (cl_float3){2.0f, 3.0f, 6.0f};
    input1[5] = (cl_float3){-1.0f, 2.0f, -3.0f};
    expected[5] = 9.539392014169456f;
    input0[6] = (cl_float3){-1.0f, 2.0f, -3.0f};
    input1[6] = (cl_float3){0.5f, 0.5f, 0.5f};
    expected[6] = 4.092676385936225f;
    input0[7] = (cl_float3){0.5f, 0.5f, 0.5f};
    input1[7] = (cl_float3){1.0f, 2.0f, 2.0f};
    expected[7] = 2.179449471770337f;
    input0[8] = (cl_float3){1.0f, 2.0f, 2.0f};
    input1[8] = (cl_float3){4.0f, 4.0f, 2.0f};
    expected[8] = 3.605551275463989f;
    input0[9] = (cl_float3){4.0f, 4.0f, 2.0f};
    input1[9] = (cl_float3){1.0f, 0.0f, 0.0f};
    expected[9] = 5.385164807134504f;

    std::string kernelSource = loadKernel("geometric_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_fast_distance_float3", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(cl_float3), input0, &err);
    cl_mem inputBuffer1 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(cl_float3), input1, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(float), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &inputBuffer1);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 3, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(float), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i], expected[i]);
        test_results.push_back({"fast_distance_float3", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(inputBuffer1);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "fast_distance_float3() tests complete" << std::endl << std::endl;
}

void test_fast_distance_float4() {
    std::cout << "Testing fast_distance_float4()..." << std::endl;

    const int NUM_TESTS = 10;
    cl_float4 input0[NUM_TESTS];
    cl_float4 input1[NUM_TESTS];
    float output[NUM_TESTS];
    float expected[NUM_TESTS];

    // Initialize test data
    input0[0] = (cl_float4){1.0f, 0.0f, 0.0f, 0.0f};
    input1[0] = (cl_float4){0.0f, 1.0f, 0.0f, 0.0f};
    expected[0] = 1.4142135623730951f;
    input0[1] = (cl_float4){0.0f, 1.0f, 0.0f, 0.0f};
    input1[1] = (cl_float4){0.0f, 0.0f, 1.0f, 0.0f};
    expected[1] = 1.4142135623730951f;
    input0[2] = (cl_float4){0.0f, 0.0f, 1.0f, 0.0f};
    input1[2] = (cl_float4){0.0f, 0.0f, 0.0f, 1.0f};
    expected[2] = 1.4142135623730951f;
    input0[3] = (cl_float4){0.0f, 0.0f, 0.0f, 1.0f};
    input1[3] = (cl_float4){1.0f, 1.0f, 1.0f, 1.0f};
    expected[3] = 1.7320508075688772f;
    input0[4] = (cl_float4){1.0f, 1.0f, 1.0f, 1.0f};
    input1[4] = (cl_float4){2.0f, 3.0f, 4.0f, 5.0f};
    expected[4] = 5.477225575051661f;
    input0[5] = (cl_float4){2.0f, 3.0f, 4.0f, 5.0f};
    input1[5] = (cl_float4){3.0f, 4.0f, 0.0f, 0.0f};
    expected[5] = 6.557438524302f;
    input0[6] = (cl_float4){3.0f, 4.0f, 0.0f, 0.0f};
    input1[6] = (cl_float4){-1.0f, 2.0f, -3.0f, 4.0f};
    expected[6] = 6.708203932499369f;
    input0[7] = (cl_float4){-1.0f, 2.0f, -3.0f, 4.0f};
    input1[7] = (cl_float4){0.5f, 0.5f, 0.5f, 0.5f};
    expected[7] = 5.385164807134504f;
    input0[8] = (cl_float4){0.5f, 0.5f, 0.5f, 0.5f};
    input1[8] = (cl_float4){1.0f, 2.0f, 2.0f, 3.0f};
    expected[8] = 3.3166247903554f;
    input0[9] = (cl_float4){1.0f, 2.0f, 2.0f, 3.0f};
    input1[9] = (cl_float4){1.0f, 0.0f, 0.0f, 0.0f};
    expected[9] = 4.123105625617661f;

    std::string kernelSource = loadKernel("geometric_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_fast_distance_float4", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(cl_float4), input0, &err);
    cl_mem inputBuffer1 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(cl_float4), input1, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(float), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &inputBuffer1);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 3, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(float), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i], expected[i]);
        test_results.push_back({"fast_distance_float4", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(inputBuffer1);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "fast_distance_float4() tests complete" << std::endl << std::endl;
}

void test_fast_length_float2() {
    std::cout << "Testing fast_length_float2()..." << std::endl;

    const int NUM_TESTS = 10;
    cl_float2 input0[NUM_TESTS];
    float output[NUM_TESTS];
    float expected[NUM_TESTS];

    // Initialize test data
    input0[0] = (cl_float2){1.0f, 0.0f};
    expected[0] = 1.0f;
    input0[1] = (cl_float2){0.0f, 1.0f};
    expected[1] = 1.0f;
    input0[2] = (cl_float2){1.0f, 1.0f};
    expected[2] = 1.4142135623730951f;
    input0[3] = (cl_float2){3.0f, 4.0f};
    expected[3] = 5.0f;
    input0[4] = (cl_float2){5.0f, 12.0f};
    expected[4] = 13.0f;
    input0[5] = (cl_float2){-1.0f, 2.0f};
    expected[5] = 2.23606797749979f;
    input0[6] = (cl_float2){0.5f, 0.5f};
    expected[6] = 0.7071067811865476f;
    input0[7] = (cl_float2){2.0f, 3.0f};
    expected[7] = 3.605551275463989f;
    input0[8] = (cl_float2){6.0f, 8.0f};
    expected[8] = 10.0f;
    input0[9] = (cl_float2){10.0f, 20.0f};
    expected[9] = 22.360679774997898f;

    std::string kernelSource = loadKernel("geometric_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_fast_length_float2", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(cl_float2), input0, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(float), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(float), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i], expected[i]);
        test_results.push_back({"fast_length_float2", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "fast_length_float2() tests complete" << std::endl << std::endl;
}

void test_fast_length_float3() {
    std::cout << "Testing fast_length_float3()..." << std::endl;

    const int NUM_TESTS = 10;
    cl_float3 input0[NUM_TESTS];
    float output[NUM_TESTS];
    float expected[NUM_TESTS];

    // Initialize test data
    input0[0] = (cl_float3){1.0f, 0.0f, 0.0f};
    expected[0] = 1.0f;
    input0[1] = (cl_float3){0.0f, 1.0f, 0.0f};
    expected[1] = 1.0f;
    input0[2] = (cl_float3){0.0f, 0.0f, 1.0f};
    expected[2] = 1.0f;
    input0[3] = (cl_float3){1.0f, 1.0f, 1.0f};
    expected[3] = 1.7320508075688772f;
    input0[4] = (cl_float3){3.0f, 4.0f, 0.0f};
    expected[4] = 5.0f;
    input0[5] = (cl_float3){2.0f, 3.0f, 6.0f};
    expected[5] = 7.0f;
    input0[6] = (cl_float3){-1.0f, 2.0f, -3.0f};
    expected[6] = 3.7416573867739413f;
    input0[7] = (cl_float3){0.5f, 0.5f, 0.5f};
    expected[7] = 0.8660254037844386f;
    input0[8] = (cl_float3){1.0f, 2.0f, 2.0f};
    expected[8] = 3.0f;
    input0[9] = (cl_float3){4.0f, 4.0f, 2.0f};
    expected[9] = 6.0f;

    std::string kernelSource = loadKernel("geometric_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_fast_length_float3", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(cl_float3), input0, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(float), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(float), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i], expected[i]);
        test_results.push_back({"fast_length_float3", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "fast_length_float3() tests complete" << std::endl << std::endl;
}

void test_fast_length_float4() {
    std::cout << "Testing fast_length_float4()..." << std::endl;

    const int NUM_TESTS = 10;
    cl_float4 input0[NUM_TESTS];
    float output[NUM_TESTS];
    float expected[NUM_TESTS];

    // Initialize test data
    input0[0] = (cl_float4){1.0f, 0.0f, 0.0f, 0.0f};
    expected[0] = 1.0f;
    input0[1] = (cl_float4){0.0f, 1.0f, 0.0f, 0.0f};
    expected[1] = 1.0f;
    input0[2] = (cl_float4){0.0f, 0.0f, 1.0f, 0.0f};
    expected[2] = 1.0f;
    input0[3] = (cl_float4){0.0f, 0.0f, 0.0f, 1.0f};
    expected[3] = 1.0f;
    input0[4] = (cl_float4){1.0f, 1.0f, 1.0f, 1.0f};
    expected[4] = 2.0f;
    input0[5] = (cl_float4){2.0f, 3.0f, 4.0f, 5.0f};
    expected[5] = 7.3484692283495345f;
    input0[6] = (cl_float4){3.0f, 4.0f, 0.0f, 0.0f};
    expected[6] = 5.0f;
    input0[7] = (cl_float4){-1.0f, 2.0f, -3.0f, 4.0f};
    expected[7] = 5.477225575051661f;
    input0[8] = (cl_float4){0.5f, 0.5f, 0.5f, 0.5f};
    expected[8] = 1.0f;
    input0[9] = (cl_float4){1.0f, 2.0f, 2.0f, 3.0f};
    expected[9] = 4.242640687119285f;

    std::string kernelSource = loadKernel("geometric_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_fast_length_float4", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(cl_float4), input0, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(float), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(float), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i], expected[i]);
        test_results.push_back({"fast_length_float4", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "fast_length_float4() tests complete" << std::endl << std::endl;
}

void test_fast_normalize_float2() {
    std::cout << "Testing fast_normalize_float2()..." << std::endl;

    const int NUM_TESTS = 10;
    cl_float2 input0[NUM_TESTS];
    cl_float2 output[NUM_TESTS];
    cl_float2 expected[NUM_TESTS];

    // Initialize test data
    input0[0] = (cl_float2){1.0f, 0.0f};
    expected[0] = (cl_float2){1.0f, 0.0f};
    input0[1] = (cl_float2){0.0f, 1.0f};
    expected[1] = (cl_float2){0.0f, 1.0f};
    input0[2] = (cl_float2){1.0f, 1.0f};
    expected[2] = (cl_float2){0.7071067811865475f, 0.7071067811865475f};
    input0[3] = (cl_float2){3.0f, 4.0f};
    expected[3] = (cl_float2){0.6f, 0.8f};
    input0[4] = (cl_float2){5.0f, 12.0f};
    expected[4] = (cl_float2){0.38461538461538464f, 0.9230769230769231f};
    input0[5] = (cl_float2){-1.0f, 2.0f};
    expected[5] = (cl_float2){-0.4472135954999579f, 0.8944271909999159f};
    input0[6] = (cl_float2){0.5f, 0.5f};
    expected[6] = (cl_float2){0.7071067811865475f, 0.7071067811865475f};
    input0[7] = (cl_float2){2.0f, 3.0f};
    expected[7] = (cl_float2){0.5547001962252291f, 0.8320502943378437f};
    input0[8] = (cl_float2){6.0f, 8.0f};
    expected[8] = (cl_float2){0.6f, 0.8f};
    input0[9] = (cl_float2){10.0f, 20.0f};
    expected[9] = (cl_float2){0.4472135954999579f, 0.8944271909999159f};

    std::string kernelSource = loadKernel("geometric_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_fast_normalize_float2", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(cl_float2), input0, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(cl_float2), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(cl_float2), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i].s[0], expected[i].s[0]) &&
                       floatEquals(output[i].s[1], expected[i].s[1]);
        test_results.push_back({"fast_normalize_float2", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "fast_normalize_float2() tests complete" << std::endl << std::endl;
}

void test_fast_normalize_float3() {
    std::cout << "Testing fast_normalize_float3()..." << std::endl;

    const int NUM_TESTS = 10;
    cl_float3 input0[NUM_TESTS];
    cl_float3 output[NUM_TESTS];
    cl_float3 expected[NUM_TESTS];

    // Initialize test data
    input0[0] = (cl_float3){1.0f, 0.0f, 0.0f};
    expected[0] = (cl_float3){1.0f, 0.0f, 0.0f};
    input0[1] = (cl_float3){0.0f, 1.0f, 0.0f};
    expected[1] = (cl_float3){0.0f, 1.0f, 0.0f};
    input0[2] = (cl_float3){0.0f, 0.0f, 1.0f};
    expected[2] = (cl_float3){0.0f, 0.0f, 1.0f};
    input0[3] = (cl_float3){1.0f, 1.0f, 1.0f};
    expected[3] = (cl_float3){0.5773502691896258f, 0.5773502691896258f, 0.5773502691896258f};
    input0[4] = (cl_float3){3.0f, 4.0f, 0.0f};
    expected[4] = (cl_float3){0.6f, 0.8f, 0.0f};
    input0[5] = (cl_float3){2.0f, 3.0f, 6.0f};
    expected[5] = (cl_float3){0.2857142857142857f, 0.42857142857142855f, 0.8571428571428571f};
    input0[6] = (cl_float3){-1.0f, 2.0f, -3.0f};
    expected[6] = (cl_float3){-0.2672612419124244f, 0.5345224838248488f, -0.8017837257372732f};
    input0[7] = (cl_float3){0.5f, 0.5f, 0.5f};
    expected[7] = (cl_float3){0.5773502691896258f, 0.5773502691896258f, 0.5773502691896258f};
    input0[8] = (cl_float3){1.0f, 2.0f, 2.0f};
    expected[8] = (cl_float3){0.3333333333333333f, 0.6666666666666666f, 0.6666666666666666f};
    input0[9] = (cl_float3){4.0f, 4.0f, 2.0f};
    expected[9] = (cl_float3){0.6666666666666666f, 0.6666666666666666f, 0.3333333333333333f};

    std::string kernelSource = loadKernel("geometric_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_fast_normalize_float3", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(cl_float3), input0, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(cl_float3), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(cl_float3), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i].s[0], expected[i].s[0]) &&
                       floatEquals(output[i].s[1], expected[i].s[1]) &&
                       floatEquals(output[i].s[2], expected[i].s[2]);
        test_results.push_back({"fast_normalize_float3", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "fast_normalize_float3() tests complete" << std::endl << std::endl;
}

void test_fast_normalize_float4() {
    std::cout << "Testing fast_normalize_float4()..." << std::endl;

    const int NUM_TESTS = 10;
    cl_float4 input0[NUM_TESTS];
    cl_float4 output[NUM_TESTS];
    cl_float4 expected[NUM_TESTS];

    // Initialize test data
    input0[0] = (cl_float4){1.0f, 0.0f, 0.0f, 0.0f};
    expected[0] = (cl_float4){1.0f, 0.0f, 0.0f, 0.0f};
    input0[1] = (cl_float4){0.0f, 1.0f, 0.0f, 0.0f};
    expected[1] = (cl_float4){0.0f, 1.0f, 0.0f, 0.0f};
    input0[2] = (cl_float4){0.0f, 0.0f, 1.0f, 0.0f};
    expected[2] = (cl_float4){0.0f, 0.0f, 1.0f, 0.0f};
    input0[3] = (cl_float4){0.0f, 0.0f, 0.0f, 1.0f};
    expected[3] = (cl_float4){0.0f, 0.0f, 0.0f, 1.0f};
    input0[4] = (cl_float4){1.0f, 1.0f, 1.0f, 1.0f};
    expected[4] = (cl_float4){0.5f, 0.5f, 0.5f, 0.5f};
    input0[5] = (cl_float4){2.0f, 3.0f, 4.0f, 5.0f};
    expected[5] = (cl_float4){0.2721655269759087f, 0.408248290463863f, 0.5443310539518174f, 0.6804138174397717f};
    input0[6] = (cl_float4){3.0f, 4.0f, 0.0f, 0.0f};
    expected[6] = (cl_float4){0.6f, 0.8f, 0.0f, 0.0f};
    input0[7] = (cl_float4){-1.0f, 2.0f, -3.0f, 4.0f};
    expected[7] = (cl_float4){-0.18257418583505536f, 0.3651483716701107f, -0.5477225575051661f, 0.7302967433402214f};
    input0[8] = (cl_float4){0.5f, 0.5f, 0.5f, 0.5f};
    expected[8] = (cl_float4){0.5f, 0.5f, 0.5f, 0.5f};
    input0[9] = (cl_float4){1.0f, 2.0f, 2.0f, 3.0f};
    expected[9] = (cl_float4){0.23570226039551587f, 0.47140452079103173f, 0.47140452079103173f, 0.7071067811865476f};

    std::string kernelSource = loadKernel("geometric_functions_kernel.cl");
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.size();

    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buildLog[4096];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
        std::cerr << "Build log:\n" << buildLog << std::endl;
        return;
    }

    cl_kernel kernel = clCreateKernel(program, "test_fast_normalize_float4", &err);

    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        NUM_TESTS * sizeof(cl_float4), input0, &err);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         NUM_TESTS * sizeof(cl_float4), NULL, &err);

    unsigned int count = NUM_TESTS;
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer0);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &outputBuffer);
    clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);

    size_t globalSize = NUM_TESTS;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof(cl_float4), output, 0, NULL, NULL);

    // Verify results
    for (int i = 0; i < NUM_TESTS; i++) {
        bool passed = floatEquals(output[i].s[0], expected[i].s[0]) &&
                       floatEquals(output[i].s[1], expected[i].s[1]) &&
                       floatEquals(output[i].s[2], expected[i].s[2]) &&
                       floatEquals(output[i].s[3], expected[i].s[3]);
        test_results.push_back({"fast_normalize_float4", i, passed, ""});
        if (!passed) {
            std::cout << "  Test " << i << " FAILED" << std::endl;
        }
    }

    clReleaseMemObject(inputBuffer0);
    clReleaseMemObject(outputBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);

    std::cout << "fast_normalize_float4() tests complete" << std::endl << std::endl;
}

