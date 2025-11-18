#!/usr/bin/env python3
"""
Generate test data for OpenCL half-precision math functions.

These functions use float inputs/outputs but with reduced precision.
Accuracy: ≤ 8192 ULP (vs. ≤ 4 ULP for regular functions)
Range restrictions apply to inputs.
"""

import json
import math
from pathlib import Path


def generate_test_values_1input_half():
    """Generate test values for single-input half functions with range restrictions"""
    # Range: -2^16 to +2^16 for trig functions
    # For other functions, use typical float range
    return [
        0.0,
        1.0,
        -1.0,
        0.5,
        -0.5,
        2.0,
        10.0,
        100.0,
        -10.0,
        3.14159,  # pi
    ]


def generate_test_values_2input_half():
    """Generate test value pairs for half functions"""
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
        (100.0, 25.0),
    ]


def create_half_precision_json():
    """Create JSON file for half-precision math functions"""

    # Define all half_* functions
    functions = []

    # Single-input functions
    single_input_funcs = {
        "half_cos": {
            "test_fn": lambda x: math.cos(x),
            "valid_range": lambda x: abs(x) <= 65536,  # -2^16 to 2^16
        },
        "half_sin": {
            "test_fn": lambda x: math.sin(x),
            "valid_range": lambda x: abs(x) <= 65536,
        },
        "half_tan": {
            "test_fn": lambda x: math.tan(x),
            "valid_range": lambda x: abs(x) <= 65536
            and abs(x - math.pi / 2) > 0.1
            and abs(x + math.pi / 2) > 0.1,
        },
        "half_exp": {
            "test_fn": lambda x: math.exp(x),
            "valid_range": lambda x: x <= 80,  # Avoid overflow
        },
        "half_exp2": {
            "test_fn": lambda x: math.pow(2, x),
            "valid_range": lambda x: x <= 100,
        },
        "half_exp10": {
            "test_fn": lambda x: math.pow(10, x),
            "valid_range": lambda x: x <= 30,
        },
        "half_log": {
            "test_fn": lambda x: math.log(x),
            "valid_range": lambda x: x > 0,
        },
        "half_log2": {
            "test_fn": lambda x: math.log2(x),
            "valid_range": lambda x: x > 0,
        },
        "half_log10": {
            "test_fn": lambda x: math.log10(x),
            "valid_range": lambda x: x > 0,
        },
        "half_sqrt": {
            "test_fn": lambda x: math.sqrt(x),
            "valid_range": lambda x: x >= 0,
        },
        "half_rsqrt": {
            "test_fn": lambda x: 1.0 / math.sqrt(x),
            "valid_range": lambda x: x > 0,
        },
        "half_recip": {
            "test_fn": lambda x: 1.0 / x,
            "valid_range": lambda x: x != 0,
        },
    }

    for name, spec in single_input_funcs.items():
        test_fn = spec["test_fn"]
        valid_range = spec.get("valid_range")

        tests = []
        for val in generate_test_values_1input_half():
            if valid_range and not valid_range(val):
                continue
            try:
                expected = test_fn(val)
                if math.isfinite(expected):
                    tests.append({"inputs": [val], "expected": float(expected)})
            except:
                pass

        # Ensure we have exactly 10 tests
        if len(tests) >= 10:
            tests = tests[:10]
        else:
            # Add more test values if needed
            extra_vals = [0.1, 0.25, 0.75, 1.5, 2.5, 5.0, 7.5, 15.0, 50.0, 200.0]
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
        "half_divide": {
            "test_fn": lambda x, y: x / y,
            "valid_range": lambda x, y: y != 0,
        },
        "half_powr": {
            "test_fn": lambda x, y: math.pow(x, y),
            "valid_range": lambda x, y: x > 0
            and y < 30
            and math.pow(x, y) < 1e37,  # Ensure result fits in float32
        },
    }

    for name, spec in two_input_funcs.items():
        test_fn = spec["test_fn"]
        valid_range = spec.get("valid_range")

        tests = []
        for v1, v2 in generate_test_values_2input_half():
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
        "category": "half_precision_math",
        "kernel_file": "kernels/half_precision_math_kernel.cl",
        "functions": functions,
    }

    output_path = Path("test_data/half_precision_math.json")
    output_path.parent.mkdir(exist_ok=True)

    with open(output_path, "w") as f:
        json.dump(data, f, indent=2)

    print(f"Created {output_path}")
    print(f"Functions: {len(functions)}")
    print(f"Total tests: {sum(len(f['tests']) for f in functions)}")
    for func in functions:
        print(f"  {func['name']}: {len(func['tests'])} tests")


if __name__ == "__main__":
    create_half_precision_json()
    print("Half-precision math function test data generation complete!")
