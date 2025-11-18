#!/usr/bin/env python3
"""
Generate test data for OpenCL native math functions.

These functions use float inputs/outputs with implementation-defined precision
for maximum performance. Like half_* functions, they use standard float type
with reduced accuracy requirements.
"""

import json
import math
from pathlib import Path


def generate_test_values_1input_native():
    """Generate test values for single-input native functions"""
    return [
        0.0,
        1.0,
        -1.0,
        0.5,
        -0.5,
        2.0,
        3.14159,  # pi
        1.5708,  # pi/2
        -3.14159,  # -pi
        6.28318,  # 2*pi
    ]


def generate_test_values_2input_native():
    """Generate test value pairs for native functions"""
    return [
        (1.0, 1.0),
        (10.0, 2.0),
        (100.0, 10.0),
        (5.0, 2.0),
        (8.0, 2.0),
        (16.0, 4.0),
        (3.0, 2.0),
        (7.0, 3.0),
        (20.0, 5.0),
        (50.0, 10.0),
    ]


def create_native_math_json():
    """Create JSON file for native math functions"""

    functions = []

    # Single-input functions
    single_input_funcs = {
        "native_cos": {
            "test_fn": lambda x: math.cos(x),
        },
        "native_sin": {
            "test_fn": lambda x: math.sin(x),
        },
        "native_tan": {
            "test_fn": lambda x: math.tan(x),
            "valid_range": lambda x: abs(x - math.pi / 2) > 0.1
            and abs(x + math.pi / 2) > 0.1,  # Avoid singularities
        },
        "native_recip": {
            "test_fn": lambda x: 1.0 / x,
            "valid_range": lambda x: x != 0,
        },
    }

    for name, spec in single_input_funcs.items():
        test_fn = spec["test_fn"]
        valid_range = spec.get("valid_range")

        tests = []
        for val in generate_test_values_1input_native():
            if valid_range and not valid_range(val):
                continue
            try:
                expected = test_fn(val)
                if math.isfinite(expected):
                    tests.append({"inputs": [val], "expected": float(expected)})
            except:
                pass

        # Ensure we have exactly 10 tests
        if len(tests) < 10:
            # Add more test values if needed
            extra_vals = [0.1, 0.25, 0.75, 1.5, 2.5, 4.0, 5.0, 7.5, 10.0, 15.0]
            for val in extra_vals:
                if len(tests) >= 10:
                    break
                if valid_range and not valid_range(val):
                    continue
                try:
                    expected = test_fn(val)
                    if math.isfinite(expected):
                        tests.append({"inputs": [val], "expected": float(expected)})
                except:
                    pass

        functions.append(
            {
                "name": name,
                "kernel_name": f"test_{name}",
                "input_type": "float",
                "output_type": "float",
                "num_inputs": 1,
                "tests": tests[:10],
            }
        )

    # Two-input functions
    two_input_funcs = {
        "native_divide": {
            "test_fn": lambda x, y: x / y,
            "valid_range": lambda x, y: y != 0,
        },
        "native_powr": {
            "test_fn": lambda x, y: math.pow(x, y),
            "valid_range": lambda x, y: x > 0 and y < 30 and math.pow(x, y) < 1e37,
        },
    }

    for name, spec in two_input_funcs.items():
        test_fn = spec["test_fn"]
        valid_range = spec.get("valid_range")

        tests = []
        for v1, v2 in generate_test_values_2input_native():
            if valid_range and not valid_range(v1, v2):
                continue
            try:
                expected = test_fn(v1, v2)
                if math.isfinite(expected):
                    tests.append({"inputs": [v1, v2], "expected": float(expected)})
            except:
                pass

        functions.append(
            {
                "name": name,
                "kernel_name": f"test_{name}",
                "input_type": "float",
                "output_type": "float",
                "num_inputs": 2,
                "tests": tests[:10],
            }
        )

    data = {
        "category": "native_math",
        "kernel_file": "kernels/native_math_kernel.cl",
        "functions": functions,
    }

    output_path = Path("test_data/native_math.json")
    output_path.parent.mkdir(exist_ok=True)

    with open(output_path, "w") as f:
        json.dump(data, f, indent=2)

    print(f"Created {output_path}")
    print(f"Functions: {len(functions)}")
    print(f"Total tests: {sum(len(f['tests']) for f in functions)}")
    for func in functions:
        print(f"  {func['name']}: {len(func['tests'])} tests")


if __name__ == "__main__":
    create_native_math_json()
    print("Native math function test data generation complete!")
