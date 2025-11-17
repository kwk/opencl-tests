#!/usr/bin/env python3
"""
Generate test data for OpenCL printf functions

Printf is special because:
1. It returns int: 0 on success, -1 on failure (per OpenCL C spec)
2. It has side effects (prints to stdout)
3. It's variadic (variable arguments)

We test:
- Return value (should be 0 for successful printf)
- Actual output text is visible in test output

Each distinct format pattern gets its own kernel to avoid duplication.

Reference: https://registry.khronos.org/OpenCL/specs/3.0-unified/html/OpenCL_C.html#printf
"""

import json


def create_printf_test_data():
    """Create test data for printf function variants"""

    test_data = []

    # Test: Integer formatting with %d
    test_data.append(
        {
            "name": "printf_int",
            "kernel_name": "test_printf_int",
            "input_type": "int",
            "output_type": "int",
            "num_inputs": 1,
            "tests": [
                {"inputs": [42], "expected": 0, "expected_output": "42"},
                {"inputs": [-123], "expected": 0, "expected_output": "-123"},
                {"inputs": [0], "expected": 0, "expected_output": "0"},
                {"inputs": [999], "expected": 0, "expected_output": "999"},
                {"inputs": [-1], "expected": 0, "expected_output": "-1"},
            ],
        }
    )

    # Test: Hexadecimal formatting with %x
    test_data.append(
        {
            "name": "printf_hex",
            "kernel_name": "test_printf_hex",
            "input_type": "int",
            "output_type": "int",
            "num_inputs": 1,
            "tests": [
                {"inputs": [255], "expected": 0, "expected_output": "ff"},
                {"inputs": [16], "expected": 0, "expected_output": "10"},
                {"inputs": [0], "expected": 0, "expected_output": "0"},
            ],
        }
    )

    # Test: Integer with width specifier %4d
    test_data.append(
        {
            "name": "printf_int_width",
            "kernel_name": "test_printf_int_width",
            "input_type": "int",
            "output_type": "int",
            "num_inputs": 1,
            "tests": [
                {"inputs": [10], "expected": 0, "expected_output": "  10"},
                {"inputs": [1234], "expected": 0, "expected_output": "1234"},
                {"inputs": [5], "expected": 0, "expected_output": "   5"},
            ],
        }
    )

    # Test: Float formatting with %.2f
    test_data.append(
        {
            "name": "printf_float",
            "kernel_name": "test_printf_float",
            "input_type": "float",
            "output_type": "int",
            "num_inputs": 1,
            "tests": [
                {"inputs": [3.14], "expected": 0, "expected_output": "3.14"},
                {"inputs": [-2.5], "expected": 0, "expected_output": "-2.50"},
                {"inputs": [123.456], "expected": 0, "expected_output": "123.46"},
                {"inputs": [0.0], "expected": 0, "expected_output": "0.00"},
            ],
        }
    )

    # Test: String literal "Hello"
    test_data.append(
        {
            "name": "printf_hello",
            "kernel_name": "test_printf_hello",
            "input_type": "int",  # Dummy input
            "output_type": "int",
            "num_inputs": 1,
            "tests": [
                {"inputs": [0], "expected": 0, "expected_output": "Hello"},
            ],
        }
    )

    # Test: String literal "Hello, World!"
    test_data.append(
        {
            "name": "printf_hello_world",
            "kernel_name": "test_printf_hello_world",
            "input_type": "int",  # Dummy input
            "output_type": "int",
            "num_inputs": 1,
            "tests": [
                {"inputs": [0], "expected": 0, "expected_output": "Hello, World!"},
            ],
        }
    )

    # Test: Newline
    test_data.append(
        {
            "name": "printf_newline",
            "kernel_name": "test_printf_newline",
            "input_type": "int",  # Dummy input
            "output_type": "int",
            "num_inputs": 1,
            "tests": [
                {"inputs": [0], "expected": 0, "expected_output": "\n"},
            ],
        }
    )

    # Test: Mixed format "Value is %d"
    test_data.append(
        {
            "name": "printf_value",
            "kernel_name": "test_printf_value",
            "input_type": "int",
            "output_type": "int",
            "num_inputs": 1,
            "tests": [
                {"inputs": [42], "expected": 0, "expected_output": "Value is 42"},
                {"inputs": [0], "expected": 0, "expected_output": "Value is 0"},
            ],
        }
    )

    # Test: Multiple format specifiers "Number: %d (0x%x)"
    test_data.append(
        {
            "name": "printf_multi",
            "kernel_name": "test_printf_multi",
            "input_type": "int",
            "output_type": "int",
            "num_inputs": 1,
            "tests": [
                {"inputs": [100], "expected": 0, "expected_output": "Number: 100 (0x64)"},
                {"inputs": [255], "expected": 0, "expected_output": "Number: 255 (0xff)"},
            ],
        }
    )

    return test_data


def main():
    """Generate and save printf test data to JSON"""

    test_data = create_printf_test_data()

    output = {"category": "misc_functions", "functions": test_data}

    output_file = "test_data/misc_functions.json"

    with open(output_file, "w") as f:
        json.dump(output, f, indent=2)

    print(f"Generated {len(test_data)} printf test functions")
    total_tests = sum(len(func["tests"]) for func in test_data)
    print(f"Total test cases: {total_tests}")
    print(f"Output written to {output_file}")


if __name__ == "__main__":
    main()
