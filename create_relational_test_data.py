#!/usr/bin/env python3
"""
Automatically generate test data for relational functions
"""

import json
import math


def create_relational_functions_json():
    """Create the relational_functions.json file with all relational functions"""

    functions = []

    # Comparison functions
    functions.append(
        {
            "name": "isequal",
            "kernel_name": "test_isequal",
            "input_type": "float",
            "output_type": "int",
            "num_inputs": 2,
            "tests": [
                {"inputs": [1.0, 1.0], "expected": 1},
                {"inputs": [1.0, 2.0], "expected": 0},
                {"inputs": [2.0, 1.0], "expected": 0},
                {"inputs": [0.0, 0.0], "expected": 1},
                {"inputs": [0.0, 1.0], "expected": 0},
                {"inputs": [-1.0, -1.0], "expected": 1},
                {"inputs": [3.14, 3.14], "expected": 1},
                {"inputs": [3.14, 2.71], "expected": 0},
                {"inputs": [100.0, 100.0], "expected": 1},
                {"inputs": [100.0, 99.0], "expected": 0},
            ],
        }
    )

    functions.append(
        {
            "name": "isnotequal",
            "kernel_name": "test_isnotequal",
            "input_type": "float",
            "output_type": "int",
            "num_inputs": 2,
            "tests": [
                {"inputs": [1.0, 1.0], "expected": 0},
                {"inputs": [1.0, 2.0], "expected": 1},
                {"inputs": [2.0, 1.0], "expected": 1},
                {"inputs": [0.0, 0.0], "expected": 0},
                {"inputs": [0.0, 1.0], "expected": 1},
                {"inputs": [-1.0, -1.0], "expected": 0},
                {"inputs": [3.14, 3.14], "expected": 0},
                {"inputs": [3.14, 2.71], "expected": 1},
                {"inputs": [100.0, 100.0], "expected": 0},
                {"inputs": [100.0, 99.0], "expected": 1},
            ],
        }
    )

    functions.append(
        {
            "name": "isgreater",
            "kernel_name": "test_isgreater",
            "input_type": "float",
            "output_type": "int",
            "num_inputs": 2,
            "tests": [
                {"inputs": [2.0, 1.0], "expected": 1},
                {"inputs": [1.0, 2.0], "expected": 0},
                {"inputs": [1.0, 1.0], "expected": 0},
                {"inputs": [0.0, -1.0], "expected": 1},
                {"inputs": [-1.0, 0.0], "expected": 0},
                {"inputs": [10.0, 5.0], "expected": 1},
                {"inputs": [5.0, 10.0], "expected": 0},
                {"inputs": [3.14, 2.71], "expected": 1},
                {"inputs": [2.71, 3.14], "expected": 0},
                {"inputs": [100.0, 100.0], "expected": 0},
            ],
        }
    )

    functions.append(
        {
            "name": "isgreaterequal",
            "kernel_name": "test_isgreaterequal",
            "input_type": "float",
            "output_type": "int",
            "num_inputs": 2,
            "tests": [
                {"inputs": [2.0, 1.0], "expected": 1},
                {"inputs": [1.0, 2.0], "expected": 0},
                {"inputs": [1.0, 1.0], "expected": 1},
                {"inputs": [0.0, -1.0], "expected": 1},
                {"inputs": [-1.0, 0.0], "expected": 0},
                {"inputs": [10.0, 5.0], "expected": 1},
                {"inputs": [5.0, 10.0], "expected": 0},
                {"inputs": [3.14, 2.71], "expected": 1},
                {"inputs": [2.71, 3.14], "expected": 0},
                {"inputs": [100.0, 100.0], "expected": 1},
            ],
        }
    )

    functions.append(
        {
            "name": "isless",
            "kernel_name": "test_isless",
            "input_type": "float",
            "output_type": "int",
            "num_inputs": 2,
            "tests": [
                {"inputs": [1.0, 2.0], "expected": 1},
                {"inputs": [2.0, 1.0], "expected": 0},
                {"inputs": [1.0, 1.0], "expected": 0},
                {"inputs": [-1.0, 0.0], "expected": 1},
                {"inputs": [0.0, -1.0], "expected": 0},
                {"inputs": [5.0, 10.0], "expected": 1},
                {"inputs": [10.0, 5.0], "expected": 0},
                {"inputs": [2.71, 3.14], "expected": 1},
                {"inputs": [3.14, 2.71], "expected": 0},
                {"inputs": [100.0, 100.0], "expected": 0},
            ],
        }
    )

    functions.append(
        {
            "name": "islessequal",
            "kernel_name": "test_islessequal",
            "input_type": "float",
            "output_type": "int",
            "num_inputs": 2,
            "tests": [
                {"inputs": [1.0, 2.0], "expected": 1},
                {"inputs": [2.0, 1.0], "expected": 0},
                {"inputs": [1.0, 1.0], "expected": 1},
                {"inputs": [-1.0, 0.0], "expected": 1},
                {"inputs": [0.0, -1.0], "expected": 0},
                {"inputs": [5.0, 10.0], "expected": 1},
                {"inputs": [10.0, 5.0], "expected": 0},
                {"inputs": [2.71, 3.14], "expected": 1},
                {"inputs": [3.14, 2.71], "expected": 0},
                {"inputs": [100.0, 100.0], "expected": 1},
            ],
        }
    )

    functions.append(
        {
            "name": "islessgreater",
            "kernel_name": "test_islessgreater",
            "input_type": "float",
            "output_type": "int",
            "num_inputs": 2,
            "tests": [
                {"inputs": [1.0, 2.0], "expected": 1},
                {"inputs": [2.0, 1.0], "expected": 1},
                {"inputs": [1.0, 1.0], "expected": 0},
                {"inputs": [-1.0, 0.0], "expected": 1},
                {"inputs": [0.0, -1.0], "expected": 1},
                {"inputs": [5.0, 10.0], "expected": 1},
                {"inputs": [10.0, 5.0], "expected": 1},
                {"inputs": [2.71, 3.14], "expected": 1},
                {"inputs": [3.14, 2.71], "expected": 1},
                {"inputs": [100.0, 100.0], "expected": 0},
            ],
        }
    )

    # Classification functions
    functions.append(
        {
            "name": "isfinite",
            "kernel_name": "test_isfinite",
            "input_type": "float",
            "output_type": "int",
            "num_inputs": 1,
            "tests": [
                {"inputs": [0.0], "expected": 1},
                {"inputs": [1.0], "expected": 1},
                {"inputs": [-1.0], "expected": 1},
                {"inputs": [100.0], "expected": 1},
                {"inputs": [-100.0], "expected": 1},
                {"inputs": [3.14159], "expected": 1},
                {"inputs": [0.00001], "expected": 1},
                {"inputs": [1000000.0], "expected": 1},
                {"inputs": [-1000000.0], "expected": 1},
                {"inputs": [2.71828], "expected": 1},
            ],
        }
    )

    functions.append(
        {
            "name": "isinf",
            "kernel_name": "test_isinf",
            "input_type": "float",
            "output_type": "int",
            "num_inputs": 1,
            "tests": [
                {"inputs": [0.0], "expected": 0},
                {"inputs": [1.0], "expected": 0},
                {"inputs": [-1.0], "expected": 0},
                {"inputs": [100.0], "expected": 0},
                {"inputs": [-100.0], "expected": 0},
                {"inputs": [3.14159], "expected": 0},
                {"inputs": [0.00001], "expected": 0},
                {"inputs": [1000000.0], "expected": 0},
                {"inputs": [-1000000.0], "expected": 0},
                {"inputs": [2.71828], "expected": 0},
            ],
        }
    )

    functions.append(
        {
            "name": "isnan",
            "kernel_name": "test_isnan",
            "input_type": "float",
            "output_type": "int",
            "num_inputs": 1,
            "tests": [
                {"inputs": [0.0], "expected": 0},
                {"inputs": [1.0], "expected": 0},
                {"inputs": [-1.0], "expected": 0},
                {"inputs": [100.0], "expected": 0},
                {"inputs": [-100.0], "expected": 0},
                {"inputs": [3.14159], "expected": 0},
                {"inputs": [0.00001], "expected": 0},
                {"inputs": [1000000.0], "expected": 0},
                {"inputs": [-1000000.0], "expected": 0},
                {"inputs": [2.71828], "expected": 0},
            ],
        }
    )

    functions.append(
        {
            "name": "isnormal",
            "kernel_name": "test_isnormal",
            "input_type": "float",
            "output_type": "int",
            "num_inputs": 1,
            "tests": [
                {"inputs": [1.0], "expected": 1},
                {"inputs": [-1.0], "expected": 1},
                {"inputs": [100.0], "expected": 1},
                {"inputs": [-100.0], "expected": 1},
                {"inputs": [3.14159], "expected": 1},
                {"inputs": [0.00001], "expected": 1},
                {"inputs": [1000000.0], "expected": 1},
                {"inputs": [-1000000.0], "expected": 1},
                {"inputs": [2.71828], "expected": 1},
                {"inputs": [0.5], "expected": 1},
            ],
        }
    )

    functions.append(
        {
            "name": "isordered",
            "kernel_name": "test_isordered",
            "input_type": "float",
            "output_type": "int",
            "num_inputs": 2,
            "tests": [
                {"inputs": [1.0, 2.0], "expected": 1},  # Both ordered (not NaN) -> 1
                {"inputs": [2.0, 1.0], "expected": 1},
                {"inputs": [0.0, 0.0], "expected": 1},
                {"inputs": [-1.0, 1.0], "expected": 1},
                {"inputs": [100.0, 50.0], "expected": 1},
                {"inputs": [3.14, 2.71], "expected": 1},
                {"inputs": [0.0, 1.0], "expected": 1},
                {"inputs": [5.0, 5.0], "expected": 1},
                {"inputs": [-5.0, -10.0], "expected": 1},
                {"inputs": [1000.0, 1.0], "expected": 1},
            ],
        }
    )

    functions.append(
        {
            "name": "isunordered",
            "kernel_name": "test_isunordered",
            "input_type": "float",
            "output_type": "int",
            "num_inputs": 2,
            "tests": [
                {"inputs": [1.0, 2.0], "expected": 0},
                {"inputs": [2.0, 1.0], "expected": 0},
                {"inputs": [0.0, 0.0], "expected": 0},
                {"inputs": [-1.0, 1.0], "expected": 0},
                {"inputs": [100.0, 50.0], "expected": 0},
                {"inputs": [3.14, 2.71], "expected": 0},
                {"inputs": [0.0, 1.0], "expected": 0},
                {"inputs": [5.0, 5.0], "expected": 0},
                {"inputs": [-5.0, -10.0], "expected": 0},
                {"inputs": [1000.0, 1.0], "expected": 0},
            ],
        }
    )

    functions.append(
        {
            "name": "signbit",
            "kernel_name": "test_signbit",
            "input_type": "float",
            "output_type": "int",
            "num_inputs": 1,
            "tests": [
                {"inputs": [0.0], "expected": 0},  # Sign bit not set -> 0
                {"inputs": [1.0], "expected": 0},
                {"inputs": [-1.0], "expected": 1},  # Sign bit set -> 1 (not -1 for scalar)
                {"inputs": [100.0], "expected": 0},
                {"inputs": [-100.0], "expected": 1},
                {"inputs": [3.14159], "expected": 0},
                {"inputs": [-3.14159], "expected": 1},
                {"inputs": [0.00001], "expected": 0},
                {"inputs": [-0.00001], "expected": 1},
                {"inputs": [1000000.0], "expected": 0},
            ],
        }
    )

    # Vector test functions
    functions.append(
        {
            "name": "any_int2",
            "kernel_name": "test_any_int2",
            "input_type": "int2",
            "output_type": "int",
            "num_inputs": 1,
            "tests": [
                {"inputs": [[0, 0]], "expected": 0},
                {"inputs": [[1, 0]], "expected": 1},
                {"inputs": [[0, 1]], "expected": 1},
                {"inputs": [[1, 1]], "expected": 1},
                {"inputs": [[-1, 0]], "expected": 1},
                {"inputs": [[0, -1]], "expected": 1},
                {"inputs": [[-1, -1]], "expected": 1},
                {"inputs": [[5, 0]], "expected": 1},
                {"inputs": [[0, 5]], "expected": 1},
                {"inputs": [[5, 5]], "expected": 1},
            ],
        }
    )

    functions.append(
        {
            "name": "any_int4",
            "kernel_name": "test_any_int4",
            "input_type": "int4",
            "output_type": "int",
            "num_inputs": 1,
            "tests": [
                {"inputs": [[0, 0, 0, 0]], "expected": 0},
                {"inputs": [[1, 0, 0, 0]], "expected": 1},
                {"inputs": [[0, 1, 0, 0]], "expected": 1},
                {"inputs": [[0, 0, 1, 0]], "expected": 1},
                {"inputs": [[0, 0, 0, 1]], "expected": 1},
                {"inputs": [[1, 1, 1, 1]], "expected": 1},
                {"inputs": [[-1, 0, 0, 0]], "expected": 1},
                {"inputs": [[0, -1, 0, 0]], "expected": 1},
                {"inputs": [[5, 5, 0, 0]], "expected": 1},
                {"inputs": [[5, 5, 5, 5]], "expected": 1},
            ],
        }
    )

    functions.append(
        {
            "name": "all_int2",
            "kernel_name": "test_all_int2",
            "input_type": "int2",
            "output_type": "int",
            "num_inputs": 1,
            "tests": [
                {"inputs": [[0, 0]], "expected": 0},
                {"inputs": [[1, 0]], "expected": 0},
                {"inputs": [[0, 1]], "expected": 0},
                {"inputs": [[1, 1]], "expected": 1},
                {"inputs": [[-1, -1]], "expected": 1},
                {"inputs": [[-1, 0]], "expected": 0},
                {"inputs": [[0, -1]], "expected": 0},
                {"inputs": [[5, 5]], "expected": 1},
                {"inputs": [[5, 0]], "expected": 0},
                {"inputs": [[-5, -5]], "expected": 1},
            ],
        }
    )

    functions.append(
        {
            "name": "all_int4",
            "kernel_name": "test_all_int4",
            "input_type": "int4",
            "output_type": "int",
            "num_inputs": 1,
            "tests": [
                {"inputs": [[0, 0, 0, 0]], "expected": 0},
                {"inputs": [[1, 1, 1, 1]], "expected": 1},
                {"inputs": [[1, 1, 1, 0]], "expected": 0},
                {"inputs": [[1, 1, 0, 1]], "expected": 0},
                {"inputs": [[1, 0, 1, 1]], "expected": 0},
                {"inputs": [[0, 1, 1, 1]], "expected": 0},
                {"inputs": [[-1, -1, -1, -1]], "expected": 1},
                {"inputs": [[5, 5, 5, 5]], "expected": 1},
                {"inputs": [[5, 5, 5, 0]], "expected": 0},
                {"inputs": [[-5, -5, -5, -5]], "expected": 1},
            ],
        }
    )

    # Select functions
    functions.append(
        {
            "name": "select_float",
            "kernel_name": "test_select_float",
            "input_type": "float",
            "output_type": "float",
            "num_inputs": 3,
            "tests": [
                {"inputs": [1.0, 2.0, 0], "expected": 1.0},
                {"inputs": [1.0, 2.0, 1], "expected": 2.0},
                {"inputs": [1.0, 2.0, -1], "expected": 2.0},
                {"inputs": [5.0, 10.0, 0], "expected": 5.0},
                {"inputs": [5.0, 10.0, 1], "expected": 10.0},
                {"inputs": [3.14, 2.71, 0], "expected": 3.14},
                {"inputs": [3.14, 2.71, -1], "expected": 2.71},
                {"inputs": [100.0, 200.0, 1], "expected": 200.0},
                {"inputs": [100.0, 200.0, 0], "expected": 100.0},
                {"inputs": [0.5, 1.5, 5], "expected": 1.5},
            ],
        }
    )

    functions.append(
        {
            "name": "select_int",
            "kernel_name": "test_select_int",
            "input_type": "int",
            "output_type": "int",
            "num_inputs": 3,
            "tests": [
                {"inputs": [1, 2, 0], "expected": 1},
                {"inputs": [1, 2, 1], "expected": 2},
                {"inputs": [1, 2, -1], "expected": 2},
                {"inputs": [5, 10, 0], "expected": 5},
                {"inputs": [5, 10, 1], "expected": 10},
                {"inputs": [100, 200, 0], "expected": 100},
                {"inputs": [100, 200, -1], "expected": 200},
                {"inputs": [42, 84, 1], "expected": 84},
                {"inputs": [42, 84, 0], "expected": 42},
                {"inputs": [7, 11, 5], "expected": 11},
            ],
        }
    )

    functions.append(
        {
            "name": "bitselect_float",
            "kernel_name": "test_bitselect_float",
            "input_type": "float",
            "output_type": "float",
            "num_inputs": 3,
            "tests": [
                {"inputs": [1.0, 2.0, 0.0], "expected": 1.0},
                {"inputs": [1.0, 2.0, 1.0], "expected": 1.0},
                {"inputs": [5.0, 10.0, 0.0], "expected": 5.0},
                {"inputs": [5.0, 10.0, 1.0], "expected": 5.0},
                {"inputs": [3.14, 2.71, 0.0], "expected": 3.14},
                {"inputs": [3.14, 2.71, 1.0], "expected": 3.14},
                {"inputs": [100.0, 200.0, 0.0], "expected": 100.0},
                {"inputs": [100.0, 200.0, 1.0], "expected": 100.0},
                {"inputs": [0.5, 1.5, 0.0], "expected": 0.5},
                {"inputs": [0.5, 1.5, 1.0], "expected": 0.5},
            ],
        }
    )

    functions.append(
        {
            "name": "bitselect_int",
            "kernel_name": "test_bitselect_int",
            "input_type": "int",
            "output_type": "int",
            "num_inputs": 3,
            "tests": [
                {"inputs": [0, 255, 0], "expected": 0},
                {"inputs": [0, 255, 255], "expected": 255},
                {"inputs": [255, 0, 0], "expected": 255},
                {"inputs": [255, 0, 255], "expected": 0},
                {"inputs": [15, 240, 15], "expected": 240},
                {"inputs": [15, 240, 240], "expected": 15},
                {"inputs": [170, 85, 255], "expected": 85},
                {"inputs": [170, 85, 0], "expected": 170},
                {"inputs": [12, 3, 15], "expected": 3},
                {"inputs": [12, 3, 0], "expected": 12},
            ],
        }
    )

    # Create the JSON structure
    data = {
        "category": "relational_functions",
        "kernel_file": "kernels/relational_functions.cl",
        "functions": functions,
    }

    # Write to file
    with open("test_data/relational_functions.json", "w") as f:
        json.dump(data, f, indent=2)

    print(f"Created relational_functions.json with {len(functions)} functions")


if __name__ == "__main__":
    create_relational_functions_json()
    print("Relational functions test data generation complete!")
