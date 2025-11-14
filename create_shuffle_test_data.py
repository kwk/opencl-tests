#!/usr/bin/env python3
"""
Generate test data for OpenCL shuffle functions
"""

import json


def create_shuffle_test_data():
    """Create test data for shuffle and shuffle2 functions"""

    functions = []

    # shuffle(float4, uint4) - rearrange elements from single vector
    functions.append(
        {
            "name": "shuffle_float4",
            "kernel_name": "test_shuffle_float4",
            "input_type": "float4",
            "output_type": "float4",
            "num_inputs": 2,  # float4 data, uint4 mask (mask treated as second input)
            "tests": [
                # Identity shuffle [0,1,2,3]
                {
                    "inputs": [[1.0, 2.0, 3.0, 4.0], [0, 1, 2, 3]],
                    "expected": [1.0, 2.0, 3.0, 4.0],
                },
                # Reverse [3,2,1,0]
                {
                    "inputs": [[1.0, 2.0, 3.0, 4.0], [3, 2, 1, 0]],
                    "expected": [4.0, 3.0, 2.0, 1.0],
                },
                # Duplicate first element [0,0,0,0]
                {
                    "inputs": [[1.0, 2.0, 3.0, 4.0], [0, 0, 0, 0]],
                    "expected": [1.0, 1.0, 1.0, 1.0],
                },
                # Duplicate last element [3,3,3,3]
                {
                    "inputs": [[1.0, 2.0, 3.0, 4.0], [3, 3, 3, 3]],
                    "expected": [4.0, 4.0, 4.0, 4.0],
                },
                # Swap pairs [1,0,3,2]
                {
                    "inputs": [[1.0, 2.0, 3.0, 4.0], [1, 0, 3, 2]],
                    "expected": [2.0, 1.0, 4.0, 3.0],
                },
                # Rotate left [1,2,3,0]
                {
                    "inputs": [[1.0, 2.0, 3.0, 4.0], [1, 2, 3, 0]],
                    "expected": [2.0, 3.0, 4.0, 1.0],
                },
                # Rotate right [3,0,1,2]
                {
                    "inputs": [[1.0, 2.0, 3.0, 4.0], [3, 0, 1, 2]],
                    "expected": [4.0, 1.0, 2.0, 3.0],
                },
                # Pattern [2,0,3,1]
                {
                    "inputs": [[1.0, 2.0, 3.0, 4.0], [2, 0, 3, 1]],
                    "expected": [3.0, 1.0, 4.0, 2.0],
                },
                # Pattern [1,1,2,2]
                {
                    "inputs": [[5.0, 6.0, 7.0, 8.0], [1, 1, 2, 2]],
                    "expected": [6.0, 6.0, 7.0, 7.0],
                },
                # Pattern [0,2,0,2]
                {
                    "inputs": [[10.0, 20.0, 30.0, 40.0], [0, 2, 0, 2]],
                    "expected": [10.0, 30.0, 10.0, 30.0],
                },
            ],
        }
    )

    # shuffle2(float4, float4, uint4) - select elements from two vectors
    functions.append(
        {
            "name": "shuffle2_float4",
            "kernel_name": "test_shuffle2_float4",
            "input_type": "float4",
            "output_type": "float4",
            "num_inputs": 3,  # float4 x, float4 y, uint4 mask
            "tests": [
                # All from first vector [0,1,2,3]
                {
                    "inputs": [[1.0, 2.0, 3.0, 4.0], [5.0, 6.0, 7.0, 8.0], [0, 1, 2, 3]],
                    "expected": [1.0, 2.0, 3.0, 4.0],
                },
                # All from second vector [4,5,6,7]
                {
                    "inputs": [[1.0, 2.0, 3.0, 4.0], [5.0, 6.0, 7.0, 8.0], [4, 5, 6, 7]],
                    "expected": [5.0, 6.0, 7.0, 8.0],
                },
                # Interleave [0,4,1,5]
                {
                    "inputs": [[1.0, 2.0, 3.0, 4.0], [5.0, 6.0, 7.0, 8.0], [0, 4, 1, 5]],
                    "expected": [1.0, 5.0, 2.0, 6.0],
                },
                # Interleave reversed [4,0,5,1]
                {
                    "inputs": [[1.0, 2.0, 3.0, 4.0], [5.0, 6.0, 7.0, 8.0], [4, 0, 5, 1]],
                    "expected": [5.0, 1.0, 6.0, 2.0],
                },
                # Mix pattern [0,5,2,7]
                {
                    "inputs": [[1.0, 2.0, 3.0, 4.0], [5.0, 6.0, 7.0, 8.0], [0, 5, 2, 7]],
                    "expected": [1.0, 6.0, 3.0, 8.0],
                },
                # Reverse both and interleave [7,3,6,2]
                {
                    "inputs": [[1.0, 2.0, 3.0, 4.0], [5.0, 6.0, 7.0, 8.0], [7, 3, 6, 2]],
                    "expected": [8.0, 4.0, 7.0, 3.0],
                },
                # First two from x, last two from y [0,1,6,7]
                {
                    "inputs": [[1.0, 2.0, 3.0, 4.0], [5.0, 6.0, 7.0, 8.0], [0, 1, 6, 7]],
                    "expected": [1.0, 2.0, 7.0, 8.0],
                },
                # Pattern [3,4,3,4]
                {
                    "inputs": [[10.0, 20.0, 30.0, 40.0], [50.0, 60.0, 70.0, 80.0], [3, 4, 3, 4]],
                    "expected": [40.0, 50.0, 40.0, 50.0],
                },
                # Pattern [1,6,1,6]
                {
                    "inputs": [[10.0, 20.0, 30.0, 40.0], [50.0, 60.0, 70.0, 80.0], [1, 6, 1, 6]],
                    "expected": [20.0, 70.0, 20.0, 70.0],
                },
                # All duplicates of y[2] [6,6,6,6]
                {
                    "inputs": [[1.0, 2.0, 3.0, 4.0], [5.0, 6.0, 7.0, 8.0], [6, 6, 6, 6]],
                    "expected": [7.0, 7.0, 7.0, 7.0],
                },
            ],
        }
    )

    # Create JSON structure
    data = {
        "category": "vector_misc_functions",
        "kernel_file": "kernels/vector_misc_kernel.cl",
        "functions": functions,
    }

    # Write to file
    with open("test_data/vector_misc_functions.json", "w") as f:
        json.dump(data, f, indent=2)

    print(f"Created vector_misc_functions.json with {len(functions)} functions")
    print("Total test cases:", sum(len(f["tests"]) for f in functions))


if __name__ == "__main__":
    create_shuffle_test_data()
    print("Shuffle functions test data generation complete!")
