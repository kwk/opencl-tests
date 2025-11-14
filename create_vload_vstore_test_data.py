#!/usr/bin/env python3
"""
Generate test data for OpenCL vector load/store functions
Tests vload2, vload3, vload4 and vstore2, vstore3, vstore4
"""

import json


def create_vload_vstore_test_data():
    """Create test data for vload and vstore functions"""

    functions = []

    # vload2 - load float2 from scalar array
    functions.append(
        {
            "name": "vload2_float",
            "kernel_name": "test_vload2_float",
            "input_type": "float",  # scalar array input
            "output_type": "float2",  # vector output
            "num_inputs": 2,  # scalar array + offset
            "tests": [
                # offset=0: load from [0,1]
                {"inputs": [[1.0, 2.0, 3.0, 4.0], 0], "expected": [1.0, 2.0]},
                # offset=1: load from [2,3]
                {"inputs": [[1.0, 2.0, 3.0, 4.0], 1], "expected": [3.0, 4.0]},
                # offset=0: different values
                {"inputs": [[10.0, 20.0, 30.0, 40.0], 0], "expected": [10.0, 20.0]},
                # offset=1
                {"inputs": [[10.0, 20.0, 30.0, 40.0], 1], "expected": [30.0, 40.0]},
                # offset=0: negative values
                {"inputs": [[-1.0, -2.0, -3.0, -4.0], 0], "expected": [-1.0, -2.0]},
                # offset=1
                {"inputs": [[-1.0, -2.0, -3.0, -4.0], 1], "expected": [-3.0, -4.0]},
                # offset=0: mixed values
                {"inputs": [[0.5, 1.5, 2.5, 3.5], 0], "expected": [0.5, 1.5]},
                # offset=1
                {"inputs": [[0.5, 1.5, 2.5, 3.5], 1], "expected": [2.5, 3.5]},
                # offset=0: zeros
                {"inputs": [[0.0, 0.0, 1.0, 1.0], 0], "expected": [0.0, 0.0]},
                # offset=1
                {"inputs": [[0.0, 0.0, 1.0, 1.0], 1], "expected": [1.0, 1.0]},
            ],
        }
    )

    # vload4 - load float4 from scalar array
    functions.append(
        {
            "name": "vload4_float",
            "kernel_name": "test_vload4_float",
            "input_type": "float",
            "output_type": "float4",
            "num_inputs": 2,  # scalar array + offset
            "tests": [
                # offset=0: load from [0,1,2,3]
                {
                    "inputs": [[1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0], 0],
                    "expected": [1.0, 2.0, 3.0, 4.0],
                },
                # offset=1: load from [4,5,6,7]
                {
                    "inputs": [[1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0], 1],
                    "expected": [5.0, 6.0, 7.0, 8.0],
                },
                # offset=0: different values
                {
                    "inputs": [[10.0, 20.0, 30.0, 40.0, 50.0, 60.0, 70.0, 80.0], 0],
                    "expected": [10.0, 20.0, 30.0, 40.0],
                },
                # offset=1
                {
                    "inputs": [[10.0, 20.0, 30.0, 40.0, 50.0, 60.0, 70.0, 80.0], 1],
                    "expected": [50.0, 60.0, 70.0, 80.0],
                },
                # offset=0: negative values
                {
                    "inputs": [[-1.0, -2.0, -3.0, -4.0, -5.0, -6.0, -7.0, -8.0], 0],
                    "expected": [-1.0, -2.0, -3.0, -4.0],
                },
                # offset=1
                {
                    "inputs": [[-1.0, -2.0, -3.0, -4.0, -5.0, -6.0, -7.0, -8.0], 1],
                    "expected": [-5.0, -6.0, -7.0, -8.0],
                },
                # offset=0: fractional values
                {
                    "inputs": [[0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8], 0],
                    "expected": [0.1, 0.2, 0.3, 0.4],
                },
                # offset=1
                {
                    "inputs": [[0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8], 1],
                    "expected": [0.5, 0.6, 0.7, 0.8],
                },
                # offset=0: zeros and ones
                {
                    "inputs": [[0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0], 0],
                    "expected": [0.0, 0.0, 0.0, 0.0],
                },
                # offset=1
                {
                    "inputs": [[0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0], 1],
                    "expected": [1.0, 1.0, 1.0, 1.0],
                },
            ],
        }
    )

    # vstore2 - store float2 to scalar array
    # For vstore, we need to verify the stored values
    # Input: vector to store, offset
    # Output: scalar array after store
    functions.append(
        {
            "name": "vstore2_float",
            "kernel_name": "test_vstore2_float",
            "input_type": "float2",  # vector input
            "output_type": "float",  # scalar array output
            "num_inputs": 2,  # vector + offset
            "tests": [
                # offset=0: store to [0,1]
                {"inputs": [[1.0, 2.0], 0], "expected": [1.0, 2.0, 0.0, 0.0]},
                # offset=1: store to [2,3]
                {"inputs": [[3.0, 4.0], 1], "expected": [0.0, 0.0, 3.0, 4.0]},
                # offset=0: negative values
                {"inputs": [[-1.0, -2.0], 0], "expected": [-1.0, -2.0, 0.0, 0.0]},
                # offset=1
                {"inputs": [[-3.0, -4.0], 1], "expected": [0.0, 0.0, -3.0, -4.0]},
                # offset=0: fractional
                {"inputs": [[0.5, 1.5], 0], "expected": [0.5, 1.5, 0.0, 0.0]},
                # offset=1
                {"inputs": [[2.5, 3.5], 1], "expected": [0.0, 0.0, 2.5, 3.5]},
                # offset=0: large values
                {"inputs": [[100.0, 200.0], 0], "expected": [100.0, 200.0, 0.0, 0.0]},
                # offset=1
                {"inputs": [[300.0, 400.0], 1], "expected": [0.0, 0.0, 300.0, 400.0]},
                # offset=0: zeros
                {"inputs": [[0.0, 0.0], 0], "expected": [0.0, 0.0, 0.0, 0.0]},
                # offset=1: ones
                {"inputs": [[1.0, 1.0], 1], "expected": [0.0, 0.0, 1.0, 1.0]},
            ],
        }
    )

    # vstore4 - store float4 to scalar array
    functions.append(
        {
            "name": "vstore4_float",
            "kernel_name": "test_vstore4_float",
            "input_type": "float4",
            "output_type": "float",
            "num_inputs": 2,  # vector + offset
            "tests": [
                # offset=0: store to [0,1,2,3]
                {
                    "inputs": [[1.0, 2.0, 3.0, 4.0], 0],
                    "expected": [1.0, 2.0, 3.0, 4.0, 0.0, 0.0, 0.0, 0.0],
                },
                # offset=1: store to [4,5,6,7]
                {
                    "inputs": [[5.0, 6.0, 7.0, 8.0], 1],
                    "expected": [0.0, 0.0, 0.0, 0.0, 5.0, 6.0, 7.0, 8.0],
                },
                # offset=0: negative values
                {
                    "inputs": [[-1.0, -2.0, -3.0, -4.0], 0],
                    "expected": [-1.0, -2.0, -3.0, -4.0, 0.0, 0.0, 0.0, 0.0],
                },
                # offset=1
                {
                    "inputs": [[-5.0, -6.0, -7.0, -8.0], 1],
                    "expected": [0.0, 0.0, 0.0, 0.0, -5.0, -6.0, -7.0, -8.0],
                },
                # offset=0: fractional
                {
                    "inputs": [[0.1, 0.2, 0.3, 0.4], 0],
                    "expected": [0.1, 0.2, 0.3, 0.4, 0.0, 0.0, 0.0, 0.0],
                },
                # offset=1
                {
                    "inputs": [[0.5, 0.6, 0.7, 0.8], 1],
                    "expected": [0.0, 0.0, 0.0, 0.0, 0.5, 0.6, 0.7, 0.8],
                },
                # offset=0: large values
                {
                    "inputs": [[100.0, 200.0, 300.0, 400.0], 0],
                    "expected": [100.0, 200.0, 300.0, 400.0, 0.0, 0.0, 0.0, 0.0],
                },
                # offset=1
                {
                    "inputs": [[500.0, 600.0, 700.0, 800.0], 1],
                    "expected": [0.0, 0.0, 0.0, 0.0, 500.0, 600.0, 700.0, 800.0],
                },
                # offset=0: zeros
                {
                    "inputs": [[0.0, 0.0, 0.0, 0.0], 0],
                    "expected": [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0],
                },
                # offset=1: ones
                {
                    "inputs": [[1.0, 1.0, 1.0, 1.0], 1],
                    "expected": [0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0],
                },
            ],
        }
    )

    # Create JSON structure
    data = {
        "category": "vector_load_store_functions",
        "kernel_file": "kernels/vector_load_store_kernel.cl",
        "functions": functions,
    }

    # Write to file
    with open("test_data/vector_load_store_functions.json", "w") as f:
        json.dump(data, f, indent=2)

    print(f"Created vector_load_store_functions.json with {len(functions)} functions")
    print("Total test cases:", sum(len(f["tests"]) for f in functions))


if __name__ == "__main__":
    create_vload_vstore_test_data()
    print("Vector load/store functions test data generation complete!")
