#!/usr/bin/env python3
"""
Automatically generate test data for remaining common functions
"""

import json


def extend_common_functions_json():
    """Extend the common_functions.json file with remaining functions"""
    with open("test_data/common_functions.json", "r") as f:
        data = json.load(f)

    # Track which functions already exist
    existing = {f["name"] for f in data["functions"]}

    new_functions = []

    # clamp_float2
    if "clamp_float2" not in existing:
        tests = [
            {"inputs": [[0.5, 0.5], [0.0, 0.0], [1.0, 1.0]], "expected": [0.5, 0.5]},
            {"inputs": [[-0.5, -0.5], [0.0, 0.0], [1.0, 1.0]], "expected": [0.0, 0.0]},
            {"inputs": [[1.5, 1.5], [0.0, 0.0], [1.0, 1.0]], "expected": [1.0, 1.0]},
            {"inputs": [[0.2, 0.8], [0.0, 0.0], [1.0, 1.0]], "expected": [0.2, 0.8]},
            {"inputs": [[5.0, 15.0], [0.0, 10.0], [10.0, 20.0]], "expected": [5.0, 15.0]},
            {"inputs": [[-5.0, 5.0], [0.0, 10.0], [10.0, 20.0]], "expected": [0.0, 10.0]},
            {"inputs": [[15.0, 25.0], [0.0, 10.0], [10.0, 20.0]], "expected": [10.0, 20.0]},
            {"inputs": [[3.0, 7.0], [5.0, 5.0], [10.0, 10.0]], "expected": [5.0, 7.0]},
            {"inputs": [[12.0, 12.0], [5.0, 5.0], [10.0, 10.0]], "expected": [10.0, 10.0]},
            {"inputs": [[0.0, 0.5], [-1.0, 0.0], [1.0, 1.0]], "expected": [0.0, 0.5]},
        ]
        new_functions.append(
            {
                "name": "clamp_float2",
                "kernel_name": "test_clamp_float2",
                "input_type": "float2",
                "output_type": "float2",
                "num_inputs": 3,
                "tests": tests,
            }
        )

    # max_float2
    if "max_float2" not in existing:
        tests = [
            {"inputs": [[1.0, 2.0], [2.0, 1.0]], "expected": [2.0, 2.0]},
            {"inputs": [[2.0, 1.0], [1.0, 2.0]], "expected": [2.0, 2.0]},
            {"inputs": [[5.0, 5.0], [5.0, 5.0]], "expected": [5.0, 5.0]},
            {"inputs": [[-1.0, 1.0], [1.0, -1.0]], "expected": [1.0, 1.0]},
            {"inputs": [[0.0, 0.0], [0.0, 0.0]], "expected": [0.0, 0.0]},
            {"inputs": [[-5.0, -3.0], [-3.0, -5.0]], "expected": [-3.0, -3.0]},
            {"inputs": [[10.0, 100.0], [100.0, 10.0]], "expected": [100.0, 100.0]},
            {"inputs": [[3.14, 2.71], [2.71, 3.14]], "expected": [3.14, 3.14]},
            {"inputs": [[-10.0, 10.0], [10.0, -10.0]], "expected": [10.0, 10.0]},
            {"inputs": [[0.5, 0.25], [0.25, 0.5]], "expected": [0.5, 0.5]},
        ]
        new_functions.append(
            {
                "name": "max_float2",
                "kernel_name": "test_max_float2",
                "input_type": "float2",
                "output_type": "float2",
                "num_inputs": 2,
                "tests": tests,
            }
        )

    # min_float2
    if "min_float2" not in existing:
        tests = [
            {"inputs": [[1.0, 2.0], [2.0, 1.0]], "expected": [1.0, 1.0]},
            {"inputs": [[2.0, 1.0], [1.0, 2.0]], "expected": [1.0, 1.0]},
            {"inputs": [[5.0, 5.0], [5.0, 5.0]], "expected": [5.0, 5.0]},
            {"inputs": [[-1.0, 1.0], [1.0, -1.0]], "expected": [-1.0, -1.0]},
            {"inputs": [[0.0, 0.0], [0.0, 0.0]], "expected": [0.0, 0.0]},
            {"inputs": [[-5.0, -3.0], [-3.0, -5.0]], "expected": [-5.0, -5.0]},
            {"inputs": [[10.0, 100.0], [100.0, 10.0]], "expected": [10.0, 10.0]},
            {"inputs": [[3.14, 2.71], [2.71, 3.14]], "expected": [2.71, 2.71]},
            {"inputs": [[-10.0, 10.0], [10.0, -10.0]], "expected": [-10.0, -10.0]},
            {"inputs": [[0.5, 0.25], [0.25, 0.5]], "expected": [0.25, 0.25]},
        ]
        new_functions.append(
            {
                "name": "min_float2",
                "kernel_name": "test_min_float2",
                "input_type": "float2",
                "output_type": "float2",
                "num_inputs": 2,
                "tests": tests,
            }
        )

    # Add all new functions
    data["functions"].extend(new_functions)

    # Write back
    with open("test_data/common_functions.json", "w") as f:
        json.dump(data, f, indent=2)

    print(f"Extended common_functions.json with {len(new_functions)} additional functions")


if __name__ == "__main__":
    extend_common_functions_json()
    print("Common functions test data generation complete!")
