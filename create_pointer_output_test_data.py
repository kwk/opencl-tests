#!/usr/bin/env python3
"""
Generate test data for OpenCL functions with pointer output parameters
These functions return multiple values - one as return value, one via pointer
"""

import json
import math
from pathlib import Path


def generate_frexp_tests():
    """Generate tests for frexp(float x, int *exp)
    Splits x into mantissa [0.5, 1.0) and exponent such that x = mantissa * 2^exp
    """
    test_values = [
        0.0,  # Special case: 0
        1.0,  # 2^0
        2.0,  # 2^1
        0.5,  # 2^-1
        4.0,  # 2^2
        0.25,  # 2^-2
        3.0,  # Non-power of 2
        100.0,  # Larger value
        0.1,  # Small value
        -2.0,  # Negative value
    ]

    tests = []
    for x in test_values:
        if x == 0:
            mantissa, exp = 0.0, 0
        else:
            mantissa, exp = math.frexp(x)
        tests.append({"inputs": [x], "expected": mantissa, "expected_ptr": exp})

    return {
        "name": "frexp",
        "kernel_name": "test_frexp",
        "input_type": "float",
        "output_type": "float",
        "ptr_output_type": "int",
        "num_inputs": 1,
        "tests": tests,
    }


def generate_modf_tests():
    """Generate tests for modf(float x, float *iptr)
    Splits x into fractional and integer parts
    """
    test_values = [
        0.0,
        1.0,
        -1.0,
        1.5,
        -1.5,
        2.75,
        -2.75,
        10.25,
        -10.25,
        100.123,
    ]

    tests = []
    for x in test_values:
        frac, integer = math.modf(x)
        tests.append({"inputs": [x], "expected": frac, "expected_ptr": integer})

    return {
        "name": "modf",
        "kernel_name": "test_modf",
        "input_type": "float",
        "output_type": "float",
        "ptr_output_type": "float",
        "num_inputs": 1,
        "tests": tests,
    }


def generate_sincos_tests():
    """Generate tests for sincos(float x, float *cosval)
    Computes sin(x) and stores cos(x) in pointer
    """
    test_values = [
        0.0,
        math.pi / 6,  # 30 degrees
        math.pi / 4,  # 45 degrees
        math.pi / 3,  # 60 degrees
        math.pi / 2,  # 90 degrees
        math.pi,  # 180 degrees
        -math.pi / 4,  # -45 degrees
        2 * math.pi,  # 360 degrees
        math.pi / 2 + 0.1,  # Just past 90 degrees
        1.0,
    ]

    tests = []
    for x in test_values:
        sin_val = math.sin(x)
        cos_val = math.cos(x)
        tests.append({"inputs": [x], "expected": sin_val, "expected_ptr": cos_val})

    return {
        "name": "sincos",
        "kernel_name": "test_sincos",
        "input_type": "float",
        "output_type": "float",
        "ptr_output_type": "float",
        "num_inputs": 1,
        "tests": tests,
    }


def generate_remquo_tests():
    """Generate tests for remquo(float x, float y, int *quo)
    Computes remainder and quotient (IEEE remainder)
    """
    test_pairs = [
        (5.0, 2.0),
        (7.0, 3.0),
        (10.0, 3.0),
        (9.0, 4.0),
        (11.5, 2.5),
        (20.0, 6.0),
        (-5.0, 2.0),
        (5.0, -2.0),
        (13.0, 5.0),
        (100.0, 7.0),
    ]

    tests = []
    for x, y in test_pairs:
        remainder = math.remainder(x, y)
        # Quotient is the integer closest to x/y
        quotient = round(x / y)
        tests.append({"inputs": [x, y], "expected": remainder, "expected_ptr": quotient})

    return {
        "name": "remquo",
        "kernel_name": "test_remquo",
        "input_type": "float",
        "output_type": "float",
        "ptr_output_type": "int",
        "num_inputs": 2,
        "tests": tests,
    }


def generate_lgamma_r_tests():
    """Generate tests for lgamma_r(float x, int *signp)
    Returns log(abs(gamma(x))) and sign of gamma(x)
    """
    test_values = [
        0.5,
        1.0,
        1.5,
        2.0,
        3.0,
        4.0,
        5.0,
        10.0,
        15.0,
        20.0,
    ]

    tests = []
    for x in test_values:
        lgamma_val = math.lgamma(x)
        # Sign of gamma function (positive for x > 0)
        gamma_val = math.gamma(x)
        sign = 1 if gamma_val >= 0 else -1
        tests.append({"inputs": [x], "expected": lgamma_val, "expected_ptr": sign})

    return {
        "name": "lgamma_r",
        "kernel_name": "test_lgamma_r",
        "input_type": "float",
        "output_type": "float",
        "ptr_output_type": "int",
        "num_inputs": 1,
        "tests": tests,
    }


def create_pointer_output_json():
    """Create JSON file for pointer output functions"""
    functions = [
        generate_frexp_tests(),
        generate_modf_tests(),
        generate_sincos_tests(),
        generate_remquo_tests(),
        generate_lgamma_r_tests(),
    ]

    data = {
        "category": "pointer_output_functions",
        "kernel_file": "kernels/pointer_output_functions_kernel.cl",
        "functions": functions,
    }

    output_path = Path("test_data/pointer_output_functions.json")
    output_path.parent.mkdir(exist_ok=True)

    with open(output_path, "w") as f:
        json.dump(data, f, indent=2)

    print(f"Created {output_path}")
    print(f"Functions: {len(functions)}")
    print(f"Total tests: {sum(len(f['tests']) for f in functions)}")
    for func in functions:
        print(f"  {func['name']}: {len(func['tests'])} tests")


if __name__ == "__main__":
    create_pointer_output_json()
    print("Pointer output function test data generation complete!")
