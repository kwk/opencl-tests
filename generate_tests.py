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
        "uint2": "cl_uint2",
        "uint3": "cl_uint3",
        "uint4": "cl_uint4",
        "float2": "cl_float2",
        "float3": "cl_float3",
        "float4": "cl_float4",
        "float8": "cl_float8",
        "float16": "cl_float16",
        "int": "int",
        "uint": "unsigned int",
        "long": "long",
        "ulong": "unsigned long",
        "float": "float",
    }
    return type_map.get(opencl_type, opencl_type)


def is_vector_type(type_name):
    """Check if type is a vector type"""
    return any(type_name.endswith(str(i)) for i in [2, 3, 4, 8, 16])


def is_int_type(type_name):
    """Check if type is an integer type (not float/double)"""
    # Floating point base types
    float_bases = ["float", "double", "half"]
    # Integer base types
    int_bases = ["char", "uchar", "short", "ushort", "int", "uint", "long", "ulong", "bool"]

    # Check if type matches any integer base (with or without vector suffix)
    for int_base in int_bases:
        if type_name == int_base or type_name.startswith(int_base):
            # Make sure it's not a substring match (e.g., "long" in "long double")
            if len(type_name) == len(int_base) or type_name[len(int_base) :].isdigit():
                return True
    return False


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

    # Check for pointer output functions
    has_ptr_output = "ptr_output_type" in func_data
    ptr_output_type = func_data.get("ptr_output_type", None)

    # Check if this is a half-precision or native function (needs relaxed tolerance)
    is_relaxed_precision = name.startswith("half_") or name.startswith("native_")

    num_tests = len(tests)

    code = []
    code.append(f"void test_{name}() {{")
    code.append(f'    std::cout << "Testing {name}()..." << std::endl;')
    code.append(f"")
    code.append(f"    const int NUM_TESTS = {num_tests};")

    # Declare input and output arrays
    input_c_type = get_c_type(input_type)
    output_c_type = get_c_type(output_type)

    # Special handling for vload/vstore functions
    is_vload = name.startswith("vload")
    is_vstore = name.startswith("vstore")

    if is_vload:
        # vload: first input is scalar array, second is size_t offset
        # Determine array size based on vector width
        if "vload2" in name:
            array_size = 4  # 2 floats per offset * 2 offsets
        elif "vload3" in name:
            array_size = 6  # 3 floats per offset * 2 offsets
        elif "vload4" in name:
            array_size = 8  # 4 floats per offset * 2 offsets
        elif "vload8" in name:
            array_size = 16  # 8 floats per offset * 2 offsets
        elif "vload16" in name:
            array_size = 32  # 16 floats per offset * 2 offsets
        else:
            array_size = 4  # default
        code.append(f"    {input_c_type} input0[NUM_TESTS * {array_size}];")
        code.append(f"    size_t input1[NUM_TESTS];")
    elif is_vstore:
        # vstore: first input is vector, second is size_t offset
        code.append(f"    {input_c_type} input0[NUM_TESTS];")
        code.append(f"    size_t input1[NUM_TESTS];")
    else:
        # Standard handling
        for i in range(num_inputs):
            # Special case: select, pown, ldexp, rootn functions have int as last parameter
            if ("select" in name or name in ["pown", "ldexp", "rootn"]) and i == num_inputs - 1:
                code.append(f"    int input{i}[NUM_TESTS];")
            # Special case: shuffle functions have uint4 mask as last parameter(s)
            elif "shuffle" in name and i >= num_inputs - 1:
                code.append(f"    cl_uint4 input{i}[NUM_TESTS];")
            else:
                code.append(f"    {input_c_type} input{i}[NUM_TESTS];")

    # Output arrays
    if is_vstore:
        # vstore outputs to scalar array
        if "vstore2" in name:
            output_array_size = 4
        elif "vstore3" in name:
            output_array_size = 6
        elif "vstore4" in name:
            output_array_size = 8
        elif "vstore8" in name:
            output_array_size = 16
        elif "vstore16" in name:
            output_array_size = 32
        else:
            output_array_size = 4
        code.append(f"    {output_c_type} output[NUM_TESTS * {output_array_size}];")
        code.append(f"    {output_c_type} expected[NUM_TESTS * {output_array_size}];")
    else:
        code.append(f"    {output_c_type} output[NUM_TESTS];")
        code.append(f"    {output_c_type} expected[NUM_TESTS];")

    # Pointer output arrays (if applicable)
    if has_ptr_output:
        ptr_output_c_type = get_c_type(ptr_output_type)
        code.append(f"    {ptr_output_c_type} ptr_output[NUM_TESTS];")
        code.append(f"    {ptr_output_c_type} expected_ptr[NUM_TESTS];")

    code.append("")
    code.append("    // Initialize test data")

    # Generate test data initialization
    for test_idx, test in enumerate(tests):
        inputs = test["inputs"]
        expected = test["expected"]

        # Handle inputs - special cases for vload/vstore
        if is_vload:
            # vload: inputs[0] is scalar array, inputs[1] is offset
            scalar_array = inputs[0]
            offset = inputs[1]
            # Initialize scalar array for this test
            for i, val in enumerate(scalar_array):
                code.append(
                    f"    input0[{test_idx} * {array_size} + {i}] = {format_scalar_value(val, input_type)};"
                )
            code.append(f"    input1[{test_idx}] = {offset};")
        elif is_vstore:
            # vstore: inputs[0] is vector, inputs[1] is offset
            vector_data = inputs[0]
            offset = inputs[1]
            code.append(f"    input0[{test_idx}] = {format_vector_value(vector_data, input_type)};")
            code.append(f"    input1[{test_idx}] = {offset};")
        elif isinstance(inputs[0], list):
            # Vector inputs
            for input_idx in range(num_inputs):
                vector_data = inputs[input_idx]
                # Special case: shuffle functions have uint4 mask as last parameter(s)
                if "shuffle" in name and input_idx >= num_inputs - 1:
                    formatted = format_vector_value(vector_data, "uint4")
                else:
                    formatted = format_vector_value(vector_data, input_type)
                code.append(f"    input{input_idx}[{test_idx}] = {formatted};")
        else:
            # Scalar inputs
            for input_idx in range(num_inputs):
                value = inputs[input_idx] if num_inputs > 1 else inputs[0]
                # Special case: select, pown, ldexp, rootn functions have int as last parameter
                if (
                    "select" in name or name in ["pown", "ldexp", "rootn"]
                ) and input_idx == num_inputs - 1:
                    formatted = str(int(value))
                else:
                    formatted = format_scalar_value(value, input_type)
                code.append(f"    input{input_idx}[{test_idx}] = {formatted};")

        # Handle expected output
        if is_vstore:
            # vstore: expected is scalar array
            for i, val in enumerate(expected):
                code.append(
                    f"    expected[{test_idx} * {output_array_size} + {i}] = {format_scalar_value(val, output_type)};"
                )
        elif isinstance(expected, list):
            # Vector expected
            formatted = format_vector_value(expected, output_type)
            code.append(f"    expected[{test_idx}] = {formatted};")
        else:
            formatted = format_scalar_value(expected, output_type)
            code.append(f"    expected[{test_idx}] = {formatted};")

        # Handle pointer output expected value (if applicable)
        if has_ptr_output:
            expected_ptr = test["expected_ptr"]
            formatted_ptr = format_scalar_value(expected_ptr, ptr_output_type)
            code.append(f"    expected_ptr[{test_idx}] = {formatted_ptr};")

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
    if is_vload:
        # vload: first buffer is scalar array, second is size_t offset
        code.append(
            f"    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,"
        )
        code.append(
            f"                                        NUM_TESTS * {array_size} * sizeof({input_c_type}), input0, &err);"
        )
        code.append(
            f"    cl_mem inputBuffer1 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,"
        )
        code.append(
            f"                                        NUM_TESTS * sizeof(size_t), input1, &err);"
        )
    elif is_vstore:
        # vstore: first buffer is vector, second is size_t offset
        code.append(
            f"    cl_mem inputBuffer0 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,"
        )
        code.append(
            f"                                        NUM_TESTS * sizeof({input_c_type}), input0, &err);"
        )
        code.append(
            f"    cl_mem inputBuffer1 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,"
        )
        code.append(
            f"                                        NUM_TESTS * sizeof(size_t), input1, &err);"
        )
    else:
        # Standard buffer creation
        for i in range(num_inputs):
            # Special case: select, pown, ldexp, rootn functions have int as last parameter
            if ("select" in name or name in ["pown", "ldexp", "rootn"]) and i == num_inputs - 1:
                buffer_type = "int"
            # Special case: shuffle functions have uint4 mask as last parameter(s)
            elif "shuffle" in name and i >= num_inputs - 1:
                buffer_type = "cl_uint4"
            else:
                buffer_type = input_c_type
            code.append(
                f"    cl_mem inputBuffer{i} = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,"
            )
            code.append(
                f"                                        NUM_TESTS * sizeof({buffer_type}), input{i}, &err);"
            )

    # Output buffer
    if is_vstore:
        code.append(f"    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,")
        code.append(
            f"                                         NUM_TESTS * {output_array_size} * sizeof({output_c_type}), NULL, &err);"
        )
    else:
        code.append(f"    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,")
        code.append(
            f"                                         NUM_TESTS * sizeof({output_c_type}), NULL, &err);"
        )

    # Pointer output buffer (if applicable)
    if has_ptr_output:
        code.append(f"    cl_mem ptrOutputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,")
        code.append(
            f"                                          NUM_TESTS * sizeof({ptr_output_c_type}), NULL, &err);"
        )

    code.append("")

    # Set kernel arguments
    code.append("    unsigned int count = NUM_TESTS;")
    for i in range(num_inputs):
        code.append(f"    clSetKernelArg(kernel, {i}, sizeof(cl_mem), &inputBuffer{i});")
    code.append(f"    clSetKernelArg(kernel, {num_inputs}, sizeof(cl_mem), &outputBuffer);")

    # For pointer output functions, add ptr_output buffer argument
    if has_ptr_output:
        code.append(
            f"    clSetKernelArg(kernel, {num_inputs + 1}, sizeof(cl_mem), &ptrOutputBuffer);"
        )
        code.append(f"    clSetKernelArg(kernel, {num_inputs + 2}, sizeof(unsigned int), &count);")
    else:
        code.append(f"    clSetKernelArg(kernel, {num_inputs + 1}, sizeof(unsigned int), &count);")
    code.append("")

    # Execute kernel
    code.append("    size_t globalSize = NUM_TESTS;")
    code.append(
        "    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);"
    )

    # Read buffer - special handling for vstore
    if is_vstore:
        code.append(
            f"    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * {output_array_size} * sizeof({output_c_type}), output, 0, NULL, NULL);"
        )
    else:
        code.append(
            f"    clEnqueueReadBuffer(queue, outputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof({output_c_type}), output, 0, NULL, NULL);"
        )

    # Read pointer output buffer (if applicable)
    if has_ptr_output:
        code.append(
            f"    clEnqueueReadBuffer(queue, ptrOutputBuffer, CL_TRUE, 0, NUM_TESTS * sizeof({ptr_output_c_type}), ptr_output, 0, NULL, NULL);"
        )

    code.append("")

    # Verify results
    code.append("    // Verify results")

    # Choose comparison function based on precision requirements
    float_cmp_fn = "halfFloatEquals" if is_relaxed_precision else "floatEquals"

    if is_vstore:
        # For vstore, we need to verify the entire scalar array for each test
        code.append("    for (int i = 0; i < NUM_TESTS; i++) {")
        code.append(f"        bool passed = true;")
        code.append(f"        for (int j = 0; j < {output_array_size}; j++) {{")
        code.append(
            f"            if (!{float_cmp_fn}(output[i * {output_array_size} + j], expected[i * {output_array_size} + j])) {{"
        )
        code.append(f"                passed = false;")
        code.append(f"                break;")
        code.append(f"            }}")
        code.append(f"        }}")
    else:
        code.append("    for (int i = 0; i < NUM_TESTS; i++) {")

    # Generate comparison code based on output type (skip for vstore, already handled)

    if not is_vstore and is_vector_type(output_type):
        # For vector outputs, compare component-wise
        if "float" in output_type:
            # Float vector - use tolerance-based comparison
            if output_type.endswith("2"):
                code.append(
                    f"        bool passed = {float_cmp_fn}(output[i].s[0], expected[i].s[0]) &&"
                )
                code.append(
                    f"                       {float_cmp_fn}(output[i].s[1], expected[i].s[1]);"
                )
            elif output_type.endswith("3"):
                code.append(
                    f"        bool passed = {float_cmp_fn}(output[i].s[0], expected[i].s[0]) &&"
                )
                code.append(
                    f"                       {float_cmp_fn}(output[i].s[1], expected[i].s[1]) &&"
                )
                code.append(
                    f"                       {float_cmp_fn}(output[i].s[2], expected[i].s[2]);"
                )
            elif output_type.endswith("4"):
                code.append(
                    f"        bool passed = {float_cmp_fn}(output[i].s[0], expected[i].s[0]) &&"
                )
                code.append(
                    f"                       {float_cmp_fn}(output[i].s[1], expected[i].s[1]) &&"
                )
                code.append(
                    f"                       {float_cmp_fn}(output[i].s[2], expected[i].s[2]) &&"
                )
                code.append(
                    f"                       {float_cmp_fn}(output[i].s[3], expected[i].s[3]);"
                )
            elif output_type.endswith("8"):
                comparisons = [
                    f"{float_cmp_fn}(output[i].s[{j}], expected[i].s[{j}])" for j in range(8)
                ]
                code.append(f"        bool passed = {comparisons[0]} &&")
                for j in range(1, 7):
                    code.append(f"                       {comparisons[j]} &&")
                code.append(f"                       {comparisons[7]};")
            elif output_type.endswith("16"):
                comparisons = [
                    f"{float_cmp_fn}(output[i].s[{j}], expected[i].s[{j}])" for j in range(16)
                ]
                code.append(f"        bool passed = {comparisons[0]} &&")
                for j in range(1, 15):
                    code.append(f"                       {comparisons[j]} &&")
                code.append(f"                       {comparisons[15]};")
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
    elif not is_vstore and is_int_type(output_type):
        code.append("        bool passed = (output[i] == expected[i]);")
    elif not is_vstore:
        # Use relaxed tolerance for half-precision and native functions
        if is_relaxed_precision:
            code.append("        bool passed = halfFloatEquals(output[i], expected[i]);")
        else:
            code.append("        bool passed = floatEquals(output[i], expected[i]);")

    # Add pointer output verification if applicable
    if has_ptr_output:
        # Check if pointer output type is int or float to use appropriate comparison
        if is_int_type(ptr_output_type):
            code.append("        passed = passed && (ptr_output[i] == expected_ptr[i]);")
        else:
            code.append("        passed = passed && floatEquals(ptr_output[i], expected_ptr[i]);")

    code.append(f'        test_results.push_back({{"{name}", i, passed, ""}});')
    code.append("        if (passed) {")
    code.append(f'            std::cout << "  Test " << i << " PASS" << std::endl;')
    code.append("        } else {")
    code.append(f'            std::cout << "  Test " << i << " FAILED" << std::endl;')
    code.append("        }")
    code.append("    }")
    code.append("")

    # Cleanup
    for i in range(num_inputs):
        code.append(f"    clReleaseMemObject(inputBuffer{i});")
    code.append("    clReleaseMemObject(outputBuffer);")
    if has_ptr_output:
        code.append("    clReleaseMemObject(ptrOutputBuffer);")
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

            # Skip image functions - they're handled separately in test_image_functions.cpp
            if category == "image_functions":
                continue

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
