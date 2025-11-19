#!/usr/bin/env python3
"""
Generate test data for OpenCL half-precision vector load/store functions
- vload_half, vload_half2/3/4/8/16 - Load half values, convert to float
- vstore_half, vstore_half2/3/4/8/16 - Store float values as half
- vloada_half, vloada_halfn - Aligned half loads
- vstorea_half, vstorea_halfn - Aligned half stores
"""

import json


def generate_half_vload_tests():
    """Generate test data for vload_half* functions

    vload_half* loads from __global half* and returns float/floatn
    Signature: floatn vload_halfn(size_t offset, const __global half *p)
    """

    functions = {}

    # Test values - use values that are exactly representable in fp16
    # fp16 has 10-bit mantissa, so use simple fractions
    test_values = [
        1.0,
        2.0,
        3.0,
        4.0,
        5.0,
        6.0,
        7.0,
        8.0,
        0.5,
        0.25,
        0.125,
        0.75,
        1.5,
        2.5,
        3.5,
        4.5,
        -1.0,
        -2.0,
        -0.5,
        -0.25,
        10.0,
        20.0,
        100.0,
        0.0,
    ]

    # vload_half - scalar version
    functions["vload_half"] = {
        "name": "vload_half",
        "kernel_name": "test_vload_half",
        "input_type": "half",  # Stored as half in memory
        "output_type": "float",  # Returned as float
        "num_inputs": 1,  # offset
        "is_half_vload": True,
        "vector_size": 1,
        "description": "Load single half value and convert to float",
        "tests": [],
    }

    # Generate tests: array of halves, load at different offsets
    for test_idx in range(10):
        # Create array of 4 half values
        start_idx = (test_idx * 4) % len(test_values)
        half_array = []
        for i in range(4):
            half_array.append(test_values[(start_idx + i) % len(test_values)])

        offset = test_idx % 4  # Use offset 0-3
        expected = half_array[offset]

        functions["vload_half"]["tests"].append(
            {"inputs": [half_array, offset], "expected": expected}
        )

    # vload_half2/3/4/8/16 - vector versions
    for vec_size in [2, 3, 4, 8, 16]:
        func_name = f"vload_half{vec_size}"
        array_size = vec_size * 2  # Two vectors worth of data

        functions[func_name] = {
            "name": func_name,
            "kernel_name": f"test_{func_name}",
            "input_type": "half",
            "output_type": f"float{vec_size}",
            "num_inputs": 1,  # offset
            "is_half_vload": True,
            "vector_size": vec_size,
            "description": f"Load float{vec_size} from half array",
            "tests": [],
        }

        for test_idx in range(10):
            # Create array of half values
            start = test_idx * array_size
            half_array = test_values[start : start + array_size]
            # Pad if necessary
            while len(half_array) < array_size:
                half_array.extend(test_values[: array_size - len(half_array)])

            offset = test_idx % 2
            expected = half_array[offset * vec_size : (offset + 1) * vec_size]

            functions[func_name]["tests"].append(
                {"inputs": [half_array, offset], "expected": expected}
            )

    return functions


def generate_half_vstore_tests():
    """Generate test data for vstore_half* functions

    vstore_half* takes float/floatn and stores as half
    Signature: void vstore_halfn(floatn data, size_t offset, __global half *p)
    """

    functions = {}

    # Test values - use values exactly representable in fp16
    test_values = [
        1.0,
        2.0,
        3.0,
        4.0,
        5.0,
        6.0,
        7.0,
        8.0,
        0.5,
        0.25,
        0.125,
        0.75,
        1.5,
        2.5,
        3.5,
        4.5,
        -1.0,
        -2.0,
        -0.5,
        -0.25,
        10.0,
        20.0,
        0.0,
        100.0,
    ]

    # vstore_half - scalar version
    functions["vstore_half"] = {
        "name": "vstore_half",
        "kernel_name": "test_vstore_half",
        "input_type": "float",  # Input as float
        "output_type": "half",  # Stored as half
        "num_inputs": 2,  # value and offset
        "is_half_vstore": True,
        "vector_size": 1,
        "description": "Store float value as half",
        "tests": [],
    }

    for test_idx in range(10):
        value = test_values[test_idx]
        offset = test_idx % 4  # Offset within output array
        # Expected output array has 4 slots, value goes at offset position
        expected = [0.0] * 4
        expected[offset] = value

        functions["vstore_half"]["tests"].append({"inputs": [value, offset], "expected": expected})

    # vstore_half2/3/4/8/16 - vector versions
    for vec_size in [2, 3, 4, 8, 16]:
        func_name = f"vstore_half{vec_size}"
        output_size = vec_size * 2  # Two vectors worth of storage

        functions[func_name] = {
            "name": func_name,
            "kernel_name": f"test_{func_name}",
            "input_type": f"float{vec_size}",
            "output_type": "half",
            "num_inputs": 2,  # vector and offset
            "is_half_vstore": True,
            "vector_size": vec_size,
            "description": f"Store float{vec_size} as half array",
            "tests": [],
        }

        for test_idx in range(10):
            # Create vector of floats to store
            start = test_idx * vec_size
            vector = test_values[start : start + vec_size]
            while len(vector) < vec_size:
                vector.extend(test_values[: vec_size - len(vector)])

            offset = test_idx % 2
            # Expected: output array with vector stored at offset
            expected = [0.0] * output_size
            for j in range(vec_size):
                expected[offset * vec_size + j] = vector[j]

            functions[func_name]["tests"].append({"inputs": [vector, offset], "expected": expected})

    return functions


def generate_half_vloada_tests():
    """Generate test data for vloada_half* functions (aligned loads)

    vloada_halfn is same as vload_halfn but requires aligned addresses
    For testing purposes, we treat it the same as vload_halfn
    """

    functions = {}
    test_values = [
        1.0,
        2.0,
        3.0,
        4.0,
        5.0,
        6.0,
        7.0,
        8.0,
        0.5,
        0.25,
        0.125,
        0.75,
        1.5,
        2.5,
        3.5,
        4.5,
        -1.0,
        -2.0,
        -0.5,
        -0.25,
        10.0,
        20.0,
        100.0,
        0.0,
    ]

    # vloada_half doesn't exist (only vloada_halfn for n >= 2)
    # vloada_half2/3/4/8/16
    for vec_size in [2, 3, 4, 8, 16]:
        func_name = f"vloada_half{vec_size}"
        array_size = vec_size * 2

        functions[func_name] = {
            "name": func_name,
            "kernel_name": f"test_{func_name}",
            "input_type": "half",
            "output_type": f"float{vec_size}",
            "num_inputs": 1,  # offset
            "is_half_vloada": True,
            "vector_size": vec_size,
            "description": f"Aligned load of float{vec_size} from half array",
            "tests": [],
        }

        for test_idx in range(10):
            start = test_idx * array_size
            half_array = test_values[start : start + array_size]
            while len(half_array) < array_size:
                half_array.extend(test_values[: array_size - len(half_array)])

            offset = test_idx % 2
            expected = half_array[offset * vec_size : (offset + 1) * vec_size]

            functions[func_name]["tests"].append(
                {"inputs": [half_array, offset], "expected": expected}
            )

    return functions


def generate_half_vstorea_tests():
    """Generate test data for vstorea_half* functions (aligned stores)

    vstorea_halfn is same as vstore_halfn but requires aligned addresses
    """

    functions = {}
    test_values = [
        1.0,
        2.0,
        3.0,
        4.0,
        5.0,
        6.0,
        7.0,
        8.0,
        0.5,
        0.25,
        0.125,
        0.75,
        1.5,
        2.5,
        3.5,
        4.5,
        -1.0,
        -2.0,
        -0.5,
        -0.25,
        10.0,
        20.0,
        0.0,
        100.0,
    ]

    # vstorea_half doesn't exist (only vstorea_halfn for n >= 2)
    for vec_size in [2, 3, 4, 8, 16]:
        func_name = f"vstorea_half{vec_size}"
        output_size = vec_size * 2

        functions[func_name] = {
            "name": func_name,
            "kernel_name": f"test_{func_name}",
            "input_type": f"float{vec_size}",
            "output_type": "half",
            "num_inputs": 2,  # vector and offset
            "is_half_vstorea": True,
            "vector_size": vec_size,
            "description": f"Aligned store of float{vec_size} as half array",
            "tests": [],
        }

        for test_idx in range(10):
            start = test_idx * vec_size
            vector = test_values[start : start + vec_size]
            while len(vector) < vec_size:
                vector.extend(test_values[: vec_size - len(vector)])

            offset = test_idx % 2
            expected = [0.0] * output_size
            for j in range(vec_size):
                expected[offset * vec_size + j] = vector[j]

            functions[func_name]["tests"].append({"inputs": [vector, offset], "expected": expected})

    return functions


def main():
    # Generate all test data
    all_functions = {}

    # vload_half variants
    all_functions.update(generate_half_vload_tests())

    # vstore_half variants
    all_functions.update(generate_half_vstore_tests())

    # vloada_half variants
    all_functions.update(generate_half_vloada_tests())

    # vstorea_half variants
    all_functions.update(generate_half_vstorea_tests())

    # Create JSON structure
    test_data = {
        "category": "half_vector_load_store_functions",
        "kernel_file": "kernels/half_vector_load_store_functions_kernel.cl",
        "functions": list(all_functions.values()),
    }

    # Write to file
    with open("test_data/half_vector_load_store_functions.json", "w") as f:
        json.dump(test_data, f, indent=2)

    print(f"Generated test data for {len(all_functions)} half-precision functions:")
    print(f"  - vload_half variants: 6 functions")
    print(f"  - vstore_half variants: 6 functions")
    print(f"  - vloada_half variants: 5 functions")
    print(f"  - vstorea_half variants: 5 functions")
    print(
        f"Total: {len(all_functions)} functions with {sum(len(f['tests']) for f in all_functions.values())} tests"
    )
    print(f"Saved to test_data/half_vector_load_store_functions.json")


if __name__ == "__main__":
    main()
