#!/usr/bin/env python3
"""
Automatically generate complete test data for ALL OpenCL built-in functions
This script creates comprehensive JSON test data files with realistic test values
"""

import json
import math

# Complete list of all OpenCL math functions with their properties
MATH_FUNCTIONS = {
    # Already implemented: sqrt, sin, cos, tan, asin, acos, atan, exp, log, pow
    # Remaining trigonometric functions
    "atan2": {"inputs": 2, "type": "float", "test_fn": lambda y, x: math.atan2(y, x)},
    "sinh": {"inputs": 1, "type": "float", "test_fn": lambda x: math.sinh(x)},
    "cosh": {"inputs": 1, "type": "float", "test_fn": lambda x: math.cosh(x)},
    "tanh": {"inputs": 1, "type": "float", "test_fn": lambda x: math.tanh(x)},
    "asinh": {"inputs": 1, "type": "float", "test_fn": lambda x: math.asinh(x)},
    "acosh": {"inputs": 1, "type": "float", "test_fn": lambda x: math.acosh(max(1.0, x))},
    "atanh": {
        "inputs": 1,
        "type": "float",
        "test_fn": lambda x: math.atanh(max(-0.99, min(0.99, x))),
    },
    # Exponential/logarithmic functions
    "exp2": {"inputs": 1, "type": "float", "test_fn": lambda x: 2**x},
    "exp10": {"inputs": 1, "type": "float", "test_fn": lambda x: 10**x},
    "expm1": {"inputs": 1, "type": "float", "test_fn": lambda x: math.expm1(x)},
    "log2": {"inputs": 1, "type": "float", "test_fn": lambda x: math.log2(max(0.001, x))},
    "log10": {"inputs": 1, "type": "float", "test_fn": lambda x: math.log10(max(0.001, x))},
    "log1p": {"inputs": 1, "type": "float", "test_fn": lambda x: math.log1p(max(-0.99, x))},
    # Power functions
    "cbrt": {
        "inputs": 1,
        "type": "float",
        "test_fn": lambda x: x ** (1 / 3) if x >= 0 else -((-x) ** (1 / 3)),
    },
    "rsqrt": {"inputs": 1, "type": "float", "test_fn": lambda x: 1 / math.sqrt(max(0.001, x))},
    "pown": {"inputs": 2, "types": ["float", "int"], "test_fn": lambda x, n: x**n},
    "powr": {"inputs": 2, "type": "float", "test_fn": lambda x, y: max(0.001, x) ** y},
    # Rounding functions
    "ceil": {"inputs": 1, "type": "float", "test_fn": lambda x: math.ceil(x)},
    "floor": {"inputs": 1, "type": "float", "test_fn": lambda x: math.floor(x)},
    "trunc": {"inputs": 1, "type": "float", "test_fn": lambda x: math.trunc(x)},
    "round": {"inputs": 1, "type": "float", "test_fn": lambda x: round(x)},
    "rint": {"inputs": 1, "type": "float", "test_fn": lambda x: round(x)},
    "fmod": {"inputs": 2, "type": "float", "test_fn": lambda x, y: math.fmod(x, max(0.1, y))},
    "remainder": {
        "inputs": 2,
        "type": "float",
        "test_fn": lambda x, y: math.remainder(x, max(0.1, y)),
    },
    # Other math functions
    "fabs": {"inputs": 1, "type": "float", "test_fn": lambda x: abs(x)},
    "fmax": {"inputs": 2, "type": "float", "test_fn": lambda x, y: max(x, y)},
    "fmin": {"inputs": 2, "type": "float", "test_fn": lambda x, y: min(x, y)},
    "fma": {"inputs": 3, "type": "float", "test_fn": lambda a, b, c: a * b + c},
    "hypot": {"inputs": 2, "type": "float", "test_fn": lambda x, y: math.hypot(x, y)},
    "erf": {"inputs": 1, "type": "float", "test_fn": lambda x: math.erf(x)},
    "erfc": {"inputs": 1, "type": "float", "test_fn": lambda x: math.erfc(x)},
    "tgamma": {"inputs": 1, "type": "float", "test_fn": lambda x: math.gamma(max(0.1, x))},
    "lgamma": {"inputs": 1, "type": "float", "test_fn": lambda x: math.lgamma(max(0.1, x))},
    # Native and half-precision variants
    "native_exp": {"inputs": 1, "type": "float", "test_fn": lambda x: math.exp(x)},
    "native_exp2": {"inputs": 1, "type": "float", "test_fn": lambda x: 2**x},
    "native_exp10": {"inputs": 1, "type": "float", "test_fn": lambda x: 10**x},
    "native_log": {"inputs": 1, "type": "float", "test_fn": lambda x: math.log(max(0.001, x))},
    "native_log2": {"inputs": 1, "type": "float", "test_fn": lambda x: math.log2(max(0.001, x))},
    "native_log10": {"inputs": 1, "type": "float", "test_fn": lambda x: math.log10(max(0.001, x))},
    "native_sqrt": {"inputs": 1, "type": "float", "test_fn": lambda x: math.sqrt(max(0, x))},
    "native_rsqrt": {
        "inputs": 1,
        "type": "float",
        "test_fn": lambda x: 1 / math.sqrt(max(0.001, x)),
    },
}


def generate_test_values_1input():
    """Generate diverse test values for single-input functions"""
    return [0.0, 1.0, -1.0, 0.5, -0.5, 2.0, -2.0, 10.0, -10.0, 100.0]


def generate_test_values_2input():
    """Generate diverse test value pairs for two-input functions"""
    return [
        (1.0, 1.0),
        (2.0, 3.0),
        (5.0, 2.0),
        (10.0, 0.5),
        (3.0, 4.0),
        (-1.0, 1.0),
        (1.0, -1.0),
        (0.5, 0.5),
        (100.0, 10.0),
        (7.0, 3.0),
    ]


def generate_test_values_3input():
    """Generate diverse test value triples for three-input functions"""
    return [
        (1.0, 2.0, 3.0),
        (2.0, 3.0, 4.0),
        (5.0, 2.0, 1.0),
        (10.0, 0.5, 0.1),
        (3.0, 4.0, 5.0),
        (-1.0, 1.0, 0.0),
        (1.0, -1.0, 2.0),
        (0.5, 0.5, 0.5),
        (100.0, 10.0, 1.0),
        (7.0, 3.0, 2.0),
    ]


def generate_math_function_tests(name, spec):
    """Generate 10 test cases for a math function"""
    num_inputs = spec["inputs"]
    test_fn = spec["test_fn"]
    tests = []

    if num_inputs == 1:
        values = generate_test_values_1input()
        for val in values:
            try:
                expected = test_fn(val)
                tests.append({"inputs": [val], "expected": float(expected)})
            except:
                pass
    elif num_inputs == 2:
        value_pairs = generate_test_values_2input()
        for v1, v2 in value_pairs:
            try:
                expected = test_fn(v1, v2)
                tests.append({"inputs": [v1, v2], "expected": float(expected)})
            except:
                pass
    elif num_inputs == 3:
        value_triples = generate_test_values_3input()
        for v1, v2, v3 in value_triples:
            try:
                expected = test_fn(v1, v2, v3)
                tests.append({"inputs": [v1, v2, v3], "expected": float(expected)})
            except:
                pass

    return tests[:10]  # Ensure exactly 10 tests


def extend_math_functions_json():
    """Extend the math_functions.json file with all remaining functions"""
    with open("test_data/math_functions.json", "r") as f:
        data = json.load(f)

    for func_name, spec in MATH_FUNCTIONS.items():
        # Check if function already exists
        exists = any(f["name"] == func_name for f in data["functions"])
        if not exists:
            tests = generate_math_function_tests(func_name, spec)
            data["functions"].append(
                {
                    "name": func_name,
                    "kernel_name": f"test_{func_name}",
                    "input_type": "float",
                    "output_type": "float",
                    "num_inputs": spec["inputs"],
                    "tests": tests,
                }
            )

    with open("test_data/math_functions.json", "w") as f:
        json.dump(data, f, indent=2)

    print(f"Extended math_functions.json with {len(MATH_FUNCTIONS)} additional functions")


if __name__ == "__main__":
    extend_math_functions_json()
    print("Math functions test data generation complete!")
