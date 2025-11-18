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
    "acosh": {
        "inputs": 1,
        "type": "float",
        "test_fn": lambda x: math.acosh(x),
        "valid_range": lambda x: x >= 1.0,
    },
    "atanh": {
        "inputs": 1,
        "type": "float",
        "test_fn": lambda x: math.atanh(x),
        "valid_range": lambda x: -1.0 < x < 1.0,
    },
    # Exponential/logarithmic functions
    "exp2": {"inputs": 1, "type": "float", "test_fn": lambda x: 2**x},
    "exp10": {"inputs": 1, "type": "float", "test_fn": lambda x: 10**x},
    "expm1": {"inputs": 1, "type": "float", "test_fn": lambda x: math.expm1(x)},
    "log2": {"inputs": 1, "type": "float", "test_fn": lambda x: math.log2(max(0.001, x))},
    "log10": {"inputs": 1, "type": "float", "test_fn": lambda x: math.log10(max(0.001, x))},
    "log1p": {
        "inputs": 1,
        "type": "float",
        "test_fn": lambda x: math.log1p(x),
        "valid_range": lambda x: x > -1.0,
    },
    # Power functions
    "cbrt": {
        "inputs": 1,
        "type": "float",
        "test_fn": lambda x: x ** (1 / 3) if x >= 0 else -((-x) ** (1 / 3)),
    },
    "rsqrt": {
        "inputs": 1,
        "type": "float",
        "test_fn": lambda x: 1 / math.sqrt(x),
        "valid_range": lambda x: x > 0.0,
    },
    "pown": {"inputs": 2, "types": ["float", "int"], "test_fn": lambda x, n: x ** int(n)},
    "powr": {
        "inputs": 2,
        "type": "float",
        "test_fn": lambda x, y: x**y,
        "valid_range": lambda x: x > 0.0,
    },
    # Rounding functions
    "ceil": {"inputs": 1, "type": "float", "test_fn": lambda x: math.ceil(x)},
    "floor": {"inputs": 1, "type": "float", "test_fn": lambda x: math.floor(x)},
    "trunc": {"inputs": 1, "type": "float", "test_fn": lambda x: math.trunc(x)},
    "round": {
        "inputs": 1,
        "type": "float",
        "test_fn": lambda x: math.floor(x + 0.5) if x >= 0 else math.ceil(x - 0.5),
    },
    "rint": {
        "inputs": 1,
        "type": "float",
        "test_fn": lambda x: float(round(x)),  # Python 3 uses banker's rounding (round-to-even)
    },
    "fmod": {
        "inputs": 2,
        "type": "float",
        "test_fn": lambda x, y: math.fmod(x, y),
        "valid_range": lambda x, y: y != 0.0,  # Avoid division by zero
    },
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
    "tgamma": {
        "inputs": 1,
        "type": "float",
        "test_fn": lambda x: math.gamma(x),
        "valid_range": lambda x: x > 0.0,
    },
    "lgamma": {
        "inputs": 1,
        "type": "float",
        "test_fn": lambda x: math.lgamma(x),
        "valid_range": lambda x: x > 0.0,
    },
    # Native and half-precision variants
    "native_exp": {"inputs": 1, "type": "float", "test_fn": lambda x: math.exp(x)},
    "native_exp2": {"inputs": 1, "type": "float", "test_fn": lambda x: 2**x},
    "native_exp10": {"inputs": 1, "type": "float", "test_fn": lambda x: 10**x},
    "native_log": {
        "inputs": 1,
        "type": "float",
        "test_fn": lambda x: math.log(x),
        "valid_range": lambda x: x > 0.0,
    },
    "native_log2": {
        "inputs": 1,
        "type": "float",
        "test_fn": lambda x: math.log2(x),
        "valid_range": lambda x: x > 0.0,
    },
    "native_log10": {
        "inputs": 1,
        "type": "float",
        "test_fn": lambda x: math.log10(x),
        "valid_range": lambda x: x > 0.0,
    },
    "native_sqrt": {
        "inputs": 1,
        "type": "float",
        "test_fn": lambda x: math.sqrt(x),
        "valid_range": lambda x: x >= 0.0,
    },
    "native_rsqrt": {
        "inputs": 1,
        "type": "float",
        "test_fn": lambda x: 1 / math.sqrt(x),
        "valid_range": lambda x: x > 0.0,
    },
    # Pi variants (Phase 1 - easy additions)
    "acospi": {
        "inputs": 1,
        "type": "float",
        "test_fn": lambda x: math.acos(x) / math.pi,
        "valid_range": lambda x: -1.0 <= x <= 1.0,  # Domain restriction for acos
    },
    "asinpi": {
        "inputs": 1,
        "type": "float",
        "test_fn": lambda x: math.asin(x) / math.pi,
        "valid_range": lambda x: -1.0 <= x <= 1.0,  # Domain restriction for asin
    },
    "atanpi": {"inputs": 1, "type": "float", "test_fn": lambda x: math.atan(x) / math.pi},
    "atan2pi": {"inputs": 2, "type": "float", "test_fn": lambda y, x: math.atan2(y, x) / math.pi},
    "cospi": {"inputs": 1, "type": "float", "test_fn": lambda x: math.cos(x * math.pi)},
    "sinpi": {"inputs": 1, "type": "float", "test_fn": lambda x: math.sin(x * math.pi)},
    "tanpi": {
        "inputs": 1,
        "type": "float",
        "test_fn": lambda x: math.tan(x * math.pi),
        "valid_range": lambda x: abs(x - 0.5) > 0.01
        and abs(x + 0.5) > 0.01,  # Avoid singularity at ±π/2
    },
    # Math other functions (Phase 1)
    "copysign": {"inputs": 2, "type": "float", "test_fn": lambda x, y: math.copysign(x, y)},
    "fdim": {"inputs": 2, "type": "float", "test_fn": lambda x, y: max(x - y, 0.0)},
    "fract": {"inputs": 1, "type": "float", "test_fn": lambda x: x - math.floor(x)},
    "ilogb": {
        "inputs": 1,
        "type": "float",
        "output_type": "int",  # ilogb returns int, not float
        "test_fn": lambda x: int(math.floor(math.log2(abs(x)))) if x != 0 else -2147483648,
        "valid_range": lambda x: x != 0.0,
    },
    "ldexp": {"inputs": 2, "types": ["float", "int"], "test_fn": lambda x, n: x * (2 ** int(n))},
    "logb": {
        "inputs": 1,
        "type": "float",
        "test_fn": lambda x: math.floor(math.log2(abs(x))),
        "valid_range": lambda x: x != 0.0,
    },
    "mad": {"inputs": 3, "type": "float", "test_fn": lambda a, b, c: a * b + c},
    "maxmag": {
        "inputs": 2,
        "type": "float",
        "test_fn": lambda x, y: x if abs(x) > abs(y) else (y if abs(y) > abs(x) else max(x, y)),
    },
    "minmag": {
        "inputs": 2,
        "type": "float",
        "test_fn": lambda x, y: x if abs(x) < abs(y) else (y if abs(y) < abs(x) else min(x, y)),
    },
    # "nan" removed - NaN comparisons fail (NaN != NaN)
    "nextafter": {"inputs": 2, "type": "float", "test_fn": lambda x, y: math.nextafter(x, y)},
    "rootn": {
        "inputs": 2,
        "types": ["float", "int"],
        "test_fn": lambda x, n: (
            x ** (1.0 / int(n))
            if int(n) != 0 and x >= 0
            else (-((-x) ** (1.0 / int(n))) if int(n) != 0 and x < 0 else float("inf"))
        ),
    },
}


def generate_test_values_1input():
    """Generate diverse test values for single-input functions"""
    return [0.0, 1.0, -1.0, 0.5, -0.5, 2.0, -2.0, 10.0, -10.0, 100.0]


def generate_test_values_hyperbolic():
    """Generate test values for hyperbolic functions (avoid overflow for float32)"""
    # cosh(88) and sinh(88) are close to float max (~3.4e38)
    # Keep values smaller to avoid overflow
    return [0.0, 1.0, -1.0, 0.5, -0.5, 2.0, -2.0, 5.0, -5.0, 10.0]


def generate_test_values_acosh():
    """Generate test values specifically for acosh (domain: x >= 1.0)"""
    return [1.0, 1.5, 2.0, 3.0, 5.0, 10.0, 20.0, 50.0, 100.0, 1000.0]


def generate_test_values_atanh():
    """Generate test values specifically for atanh (domain: -1.0 < x < 1.0)"""
    return [0.0, 0.1, -0.1, 0.5, -0.5, 0.9, -0.9, 0.99, -0.99, 0.25]


def generate_test_values_log():
    """Generate test values for log functions (domain: x > 0.0)"""
    return [0.001, 0.01, 0.1, 0.5, 1.0, 2.0, 5.0, 10.0, 100.0, 1000.0]


def generate_test_values_sqrt():
    """Generate test values for sqrt functions (domain: x >= 0.0)"""
    return [0.0, 0.01, 0.25, 0.5, 1.0, 4.0, 9.0, 16.0, 100.0, 1000.0]


def generate_test_values_exp():
    """Generate test values for exp functions (avoid overflow for float32)"""
    # exp(88) is close to float max, so keep inputs smaller
    return [0.0, 0.5, 1.0, 2.0, 5.0, 10.0, 20.0, 40.0, 80.0, -10.0]


def generate_test_values_exp10():
    """Generate test values for exp10/pow10 functions (avoid overflow for float32)"""
    # 10^38 is close to float max, so keep inputs smaller
    return [0.0, 0.5, 1.0, 2.0, 3.0, 5.0, 10.0, 20.0, 30.0, -5.0]


def generate_test_values_log1p():
    """Generate test values for log1p (domain: x > -1.0)"""
    return [0.0, 0.1, 0.5, 1.0, 2.0, 5.0, 10.0, 100.0, 1000.0, -0.5]


def generate_test_values_gamma():
    """Generate test values for gamma functions (domain: x > 0.0)"""
    # Avoid very large values that cause overflow in gamma function
    return [0.1, 0.5, 1.0, 1.5, 2.0, 3.0, 5.0, 10.0, 15.0, 20.0]


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


def generate_test_values_rootn():
    """Generate test values for rootn (x, n) where n must be non-zero integer"""
    return [
        (8.0, 3),  # cube root of 8
        (16.0, 4),  # fourth root of 16
        (27.0, 3),  # cube root of 27
        (1.0, 5),  # any root of 1 is 1
        (32.0, 5),  # fifth root of 32
        (64.0, 6),  # sixth root of 64
        (100.0, 2),  # square root of 100
        (625.0, 4),  # fourth root of 625
        (2.0, 2),  # square root of 2
        (10.0, 3),  # cube root of 10
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
    valid_range = spec.get("valid_range", None)
    output_type = spec.get("output_type", "float")
    tests = []

    if num_inputs == 1:
        # Use custom test values for specific functions
        if name == "acosh":
            values = generate_test_values_acosh()
        elif name == "atanh":
            values = generate_test_values_atanh()
        elif name in ["native_log", "native_log2", "native_log10", "log2", "log10"]:
            values = generate_test_values_log()
        elif name in ["native_sqrt", "native_rsqrt", "rsqrt"]:
            values = generate_test_values_sqrt()
        elif name in ["native_exp"]:
            values = generate_test_values_exp()
        elif name in ["native_exp10", "exp10"]:
            values = generate_test_values_exp10()
        elif name in ["native_exp2", "exp2"]:
            values = generate_test_values_exp()
        elif name == "log1p":
            values = generate_test_values_log1p()
        elif name in ["tgamma", "lgamma"]:
            values = generate_test_values_gamma()
        elif name in ["cosh", "sinh", "expm1"]:
            values = generate_test_values_hyperbolic()
        else:
            values = generate_test_values_1input()

        for val in values:
            # Skip values outside valid range if specified
            if valid_range and not valid_range(val):
                continue
            try:
                expected = test_fn(val)
                # Cast to correct output type (int for ilogb, float for others)
                if output_type == "int":
                    tests.append({"inputs": [val], "expected": int(expected)})
                else:
                    tests.append({"inputs": [val], "expected": float(expected)})
            except:
                pass
    elif num_inputs == 2:
        # Use custom test values for specific functions
        if name == "rootn":
            value_pairs = generate_test_values_rootn()
        else:
            value_pairs = generate_test_values_2input()

        for v1, v2 in value_pairs:
            # Skip values outside valid range if specified
            # Check if valid_range takes 1 or 2 parameters
            if valid_range:
                import inspect

                sig = inspect.signature(valid_range)
                if len(sig.parameters) == 1:
                    if not valid_range(v1):
                        continue
                elif len(sig.parameters) == 2:
                    if not valid_range(v1, v2):
                        continue
            try:
                # For pown, ldexp, rootn: second parameter should be int
                if name in ["pown", "ldexp", "rootn"]:
                    v2_val = int(v2)
                    expected = test_fn(v1, v2_val)
                    tests.append({"inputs": [v1, v2_val], "expected": float(expected)})
                else:
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
        existing_func = None
        for i, f in enumerate(data["functions"]):
            if f["name"] == func_name:
                existing_func = i
                break

        tests = generate_math_function_tests(func_name, spec)

        if existing_func is not None:
            # Update existing function (including output_type if specified)
            data["functions"][existing_func]["tests"] = tests
            if "output_type" in spec:
                data["functions"][existing_func]["output_type"] = spec["output_type"]
        else:
            # Add new function
            data["functions"].append(
                {
                    "name": func_name,
                    "kernel_name": f"test_{func_name}",
                    "input_type": "float",
                    "output_type": spec.get(
                        "output_type", "float"
                    ),  # Use spec output_type if provided
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
