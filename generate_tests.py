#!/usr/bin/env python3
"""
Generate C++ test code from JSON test data files
This script reads test specifications from JSON files and generates
comprehensive C++ test functions for all OpenCL built-in functions.
"""

import json
import os
import glob
from pathlib import Path


def get_c_type(opencl_type):
    """Convert OpenCL type name to C type name"""
    type_map = {
        "int2": "cl_int2",
        "int3": "cl_int3",
        "int4": "cl_int4",
        "float2": "cl_float2",
        "float3": "cl_float3",
        "float4": "cl_float4",
        "int": "int",
        "uint": "unsigned int",
        "float": "float",
    }
    return type_map.get(opencl_type, opencl_type)


def is_vector_type(type_name):
    """Check if type is a vector type"""
    return any(type_name.endswith(str(i)) for i in [2, 3, 4])


def is_int_type(type_name):
    """Check if type is an integer type"""
    return "int" in type_name


def format_vector_value(value_list, type_name):
    """Format a vector value with proper type and suffix"""
    c_type = get_c_type(type_name)
    if is_int_type(type_name):
        # Integer vector - no 'f' suffix
        values = ", ".join(str(int(v)) for v in value_list)
    else:
        # Float vector - add 'f' suffix
        values = ", ".join(f"{v}f" for v in value_list)
    return f"({c_type}){{{values}}}"


def format_scalar_value(value, type_name):
    """Format a scalar value with proper type suffix"""
    if is_int_type(type_name):
        return str(int(value))
    else:
        return f"{value}f"


def generate_function_test(func_data, category):
    """Generate C++ test function for a single OpenCL function"""

    name = func_data["name"]
    kernel_name = func_data["kernel_name"]
    num_inputs = func_data["num_inputs"]
    input_type = func_data["input_type"]
    output_type = func_data["output_type"]
    tests = func_data["tests"]

    num_tests = len(tests)

    code = []
    code.append(f"void test_{name}() {{")
    code.append(f'    std::cout << "Testing {name}()..." << std::endl;')
    code.append(f"")
    code.append(f"    const int NUM_TESTS = {num_tests};")

    # Declare input and output arrays
    input_c_type = get_c_type(input_type)
    output_c_type = get_c_type(output_type)

    for i in range(num_inputs):
        # Special case: select functions have int as last parameter
        if "select" in name and i == num_inputs - 1:
            code.append(f"    int input{i}[NUM_TESTS];")
        else:
            code.append(f"    {input_c_type} input{i}[NUM_TESTS];")

    code.append(f"    {output_c_type} output[NUM_TESTS];")
    code.append(f"    {output_c_type} expected[NUM_TESTS];")

    code.append("")
    code.append("    // Initialize test data")

    # Generate test data initialization
    for test_idx, test in enumerate(tests):
        inputs = test["inputs"]
        expected = test["expected"]

        # Handle inputs
        if isinstance(inputs[0], list):
            # Vector inputs
            for input_idx in range(num_inputs):
                vector_data = inputs[input_idx]
                formatted = format_vector_value(vector_data, input_type)
                code.append(f"    input{input_idx}[{test_idx}] = {formatted};")
        else:
            # Scalar inputs
            for input_idx in range(num_inputs):
                value = inputs[input_idx] if num_inputs > 1 else inputs[0]
                # Special case: select functions have int as last parameter
                if "select" in name and input_idx == num_inputs - 1:
                    formatted = str(int(value))
                else:
                    formatted = format_scalar_value(value, input_type)
                code.append(f"    input{input_idx}[{test_idx}] = {formatted};")

        # Handle expected output
        if isinstance(expected, list):
            # Vector expected
            formatted = format_vector_value(expected, output_type)
            code.append(f"    expected[{test_idx}] = {formatted};")
        else:
            formatted = format_scalar_value(expected, output_type)
            code.append(f"    expected[{test_idx}] = {formatted};")

    code.append("")
    code.append(f'    std::string kernelSource = loadKernel("{category}_kernel.cl");')
    code.append("    const char* kernelSourcePtr = kernelSource.c_str();")
    code.append("    size_t kernelSize = kernelSource.size();")
    code.append("")
    code.append("    cl_int err;")
    code.append(
        "    cl_program program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);"
    )
    code.append("    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);")
    code.append("    if (err != CL_SUCCESS) {")
    code.append("        char buildLog[4096];")
    code.append(
        "        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);"
    )
    code.append('        std::cerr << "Build log:\\n" << buildLog << std::endl;')
    code.append("        return;")
    code.append("    }")
    code.append("")
    code.append(f'    cl_kernel kernel = clCreateKernel(program, "{kernel_name}", &err);')
    code.append("")

    # Create buffers with correct types
    for i in range(num_inputs):
        # Special case: select functions have int as last parameter
        if "select" in name and i == num_inputs - 1:
            buffer_type = "int"
        else:
            buffer_type = input_c_type
        code.append(
            f"    cl_mem inputBuffer{i} = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,"
        )
        code.append(
            f"                                        NUM_TESTS * sizeof({buffer_type}), input{i}, &err);"
        )

    code.append(f"    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,")
    code.append(
        f"                                         NUM_TESTS * sizeof({output_c_type}), NULL, &err);"
    )
    code.append("")

    # Set kernel arguments
    code.append("    unsigned int count = NUM_TESTS;")
    for i in range(num_inputs):
        code.append(f"    clSetKernelArg(kernel, {i}, sizeof(cl_mem), &inputBuffer{i});")
    code.append(f"    clSetKernelArg(kernel, {num_inputs}, sizeof(cl_mem), &outputBuffer);")
    code.append(f"    clSetKernelArg(kernel, {num_inputs + 1}, sizeof(unsigned int), &count);")
    code.append("")

    # Execute kernel
    code.append("    size_t globalSize = NUM_TESTS;")
    code.append(
        "    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);"
    )
    code.append(
        f"    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof({output_c_type}), output, 0, NULL, NULL);"
    )
    code.append("")

    # Verify results
    code.append("    // Verify results")
    code.append("    for (int i = 0; i < NUM_TESTS; i++) {")

    # Generate comparison code based on output type
    if is_vector_type(output_type):
        # For vector outputs, compare component-wise
        if "float" in output_type:
            # Float vector - use tolerance-based comparison
            if output_type.endswith("2"):
                code.append(
                    "        bool passed = floatEquals(output[i].s[0], expected[i].s[0]) &&"
                )
                code.append("                       floatEquals(output[i].s[1], expected[i].s[1]);")
            elif output_type.endswith("3"):
                code.append(
                    "        bool passed = floatEquals(output[i].s[0], expected[i].s[0]) &&"
                )
                code.append(
                    "                       floatEquals(output[i].s[1], expected[i].s[1]) &&"
                )
                code.append("                       floatEquals(output[i].s[2], expected[i].s[2]);")
            elif output_type.endswith("4"):
                code.append(
                    "        bool passed = floatEquals(output[i].s[0], expected[i].s[0]) &&"
                )
                code.append(
                    "                       floatEquals(output[i].s[1], expected[i].s[1]) &&"
                )
                code.append(
                    "                       floatEquals(output[i].s[2], expected[i].s[2]) &&"
                )
                code.append("                       floatEquals(output[i].s[3], expected[i].s[3]);")
        else:
            # Int vector - exact comparison
            if output_type.endswith("2"):
                code.append("        bool passed = (output[i].s[0] == expected[i].s[0]) &&")
                code.append("                       (output[i].s[1] == expected[i].s[1]);")
            elif output_type.endswith("3"):
                code.append("        bool passed = (output[i].s[0] == expected[i].s[0]) &&")
                code.append("                       (output[i].s[1] == expected[i].s[1]) &&")
                code.append("                       (output[i].s[2] == expected[i].s[2]);")
            elif output_type.endswith("4"):
                code.append("        bool passed = (output[i].s[0] == expected[i].s[0]) &&")
                code.append("                       (output[i].s[1] == expected[i].s[1]) &&")
                code.append("                       (output[i].s[2] == expected[i].s[2]) &&")
                code.append("                       (output[i].s[3] == expected[i].s[3]);")
    elif is_int_type(output_type):
        code.append("        bool passed = (output[i] == expected[i]);")
    else:
        code.append("        bool passed = floatEquals(output[i], expected[i]);")

    code.append(f'        test_results.push_back({{"{name}", i, passed, ""}});')
    code.append("        if (!passed) {")
    code.append(f'            std::cout << "  Test " << i << " FAILED" << std::endl;')
    code.append("        }")
    code.append("    }")
    code.append("")

    # Cleanup
    for i in range(num_inputs):
        code.append(f"    clReleaseMemObject(inputBuffer{i});")
    code.append("    clReleaseMemObject(outputBuffer);")
    code.append("    clReleaseKernel(kernel);")
    code.append("    clReleaseProgram(program);")
    code.append("")
    code.append(f'    std::cout << "{name}() tests complete" << std::endl << std::endl;')
    code.append("}")
    code.append("")

    return "\n".join(code)


def generate_all_tests():
    """Generate C++ test code from all JSON test data files"""

    test_data_dir = Path("test_data")
    json_files = list(test_data_dir.glob("*.json"))

    all_functions = []

    for json_file in json_files:
        with open(json_file, "r") as f:
            data = json.load(f)
            category = data["category"]

            for func in data["functions"]:
                test_code = generate_function_test(func, category)
                all_functions.append({"name": func["name"], "code": test_code})

    # Generate the complete test file
    print(f"Generated test functions for {len(all_functions)} OpenCL built-in functions")
    print(f"Total test cases: {len(all_functions) * 10}")

    # Write to file
    with open("src/generated_tests.cpp", "w") as f:
        f.write("// AUTO-GENERATED TEST CODE\n")
        f.write("// Generated from JSON test data files\n\n")

        for func in all_functions:
            f.write(func["code"])
            f.write("\n")

    print(f"Test code generated in src/generated_tests.cpp")


if __name__ == "__main__":
    generate_all_tests()
