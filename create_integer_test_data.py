#!/usr/bin/env python3
"""
Automatically generate test data for remaining integer functions
"""

import json


def extend_integer_functions_json():
    """Extend the integer_functions.json file with remaining functions"""
    with open("test_data/integer_functions.json", "r") as f:
        data = json.load(f)

    # Track which functions already exist
    existing = {f["name"] for f in data["functions"]}

    new_functions = []

    # abs_diff_int
    if "abs_diff_int" not in existing:
        tests = [
            {"inputs": [5, 3], "expected": 2},
            {"inputs": [3, 5], "expected": 2},
            {"inputs": [0, 0], "expected": 0},
            {"inputs": [10, -5], "expected": 15},
            {"inputs": [-5, 10], "expected": 15},
            {"inputs": [-10, -5], "expected": 5},
            {"inputs": [100, 50], "expected": 50},
            {"inputs": [2147483647, 0], "expected": 2147483647},
            {"inputs": [0, -2147483648], "expected": 2147483648},
            {"inputs": [1000, 999], "expected": 1},
        ]
        new_functions.append(
            {
                "name": "abs_diff_int",
                "kernel_name": "test_abs_diff_int",
                "input_type": "int",
                "output_type": "uint",
                "num_inputs": 2,
                "tests": tests,
            }
        )

    # abs_diff_uint
    if "abs_diff_uint" not in existing:
        tests = [
            {"inputs": [5, 3], "expected": 2},
            {"inputs": [3, 5], "expected": 2},
            {"inputs": [0, 0], "expected": 0},
            {"inputs": [10, 5], "expected": 5},
            {"inputs": [100, 50], "expected": 50},
            {"inputs": [4294967295, 0], "expected": 4294967295},
            {"inputs": [1000, 999], "expected": 1},
            {"inputs": [50, 100], "expected": 50},
            {"inputs": [255, 128], "expected": 127},
            {"inputs": [1024, 512], "expected": 512},
        ]
        new_functions.append(
            {
                "name": "abs_diff_uint",
                "kernel_name": "test_abs_diff_uint",
                "input_type": "uint",
                "output_type": "uint",
                "num_inputs": 2,
                "tests": tests,
            }
        )

    # add_sat_uint
    if "add_sat_uint" not in existing:
        tests = [
            {"inputs": [0, 0], "expected": 0},
            {"inputs": [5, 10], "expected": 15},
            {"inputs": [100, 200], "expected": 300},
            {"inputs": [4294967295, 1], "expected": 4294967295},
            {"inputs": [4294967294, 1], "expected": 4294967295},
            {"inputs": [4294967295, 4294967295], "expected": 4294967295},
            {"inputs": [1000000, 2000000], "expected": 3000000},
            {"inputs": [2147483647, 2147483647], "expected": 4294967294},
            {"inputs": [1000, 2000], "expected": 3000},
            {"inputs": [500, 500], "expected": 1000},
        ]
        new_functions.append(
            {
                "name": "add_sat_uint",
                "kernel_name": "test_add_sat_uint",
                "input_type": "uint",
                "output_type": "uint",
                "num_inputs": 2,
                "tests": tests,
            }
        )

    # hadd_int (half add: (x+y) >> 1)
    if "hadd_int" not in existing:
        tests = [
            {"inputs": [0, 0], "expected": 0},
            {"inputs": [2, 4], "expected": 3},
            {"inputs": [4, 2], "expected": 3},
            {"inputs": [1, 1], "expected": 1},
            {"inputs": [10, 20], "expected": 15},
            {"inputs": [-10, 10], "expected": 0},
            {"inputs": [5, 7], "expected": 6},
            {"inputs": [100, 200], "expected": 150},
            {"inputs": [-5, -15], "expected": -10},
            {"inputs": [3, 5], "expected": 4},
        ]
        new_functions.append(
            {
                "name": "hadd_int",
                "kernel_name": "test_hadd_int",
                "input_type": "int",
                "output_type": "int",
                "num_inputs": 2,
                "tests": tests,
            }
        )

    # rhadd_int (rounded half add: (x+y+1) >> 1)
    if "rhadd_int" not in existing:
        tests = [
            {"inputs": [0, 0], "expected": 0},
            {"inputs": [2, 4], "expected": 3},
            {"inputs": [4, 2], "expected": 3},
            {"inputs": [1, 1], "expected": 1},
            {"inputs": [10, 20], "expected": 15},
            {"inputs": [-10, 10], "expected": 0},
            {"inputs": [5, 7], "expected": 6},
            {"inputs": [100, 200], "expected": 150},
            {"inputs": [-5, -15], "expected": -10},
            {"inputs": [3, 5], "expected": 4},
        ]
        new_functions.append(
            {
                "name": "rhadd_int",
                "kernel_name": "test_rhadd_int",
                "input_type": "int",
                "output_type": "int",
                "num_inputs": 2,
                "tests": tests,
            }
        )

    # ctz_int (count trailing zeros)
    if "ctz_int" not in existing:
        tests = [
            {"inputs": [1], "expected": 0},
            {"inputs": [2], "expected": 1},
            {"inputs": [4], "expected": 2},
            {"inputs": [8], "expected": 3},
            {"inputs": [16], "expected": 4},
            {"inputs": [32], "expected": 5},
            {"inputs": [64], "expected": 6},
            {"inputs": [128], "expected": 7},
            {"inputs": [256], "expected": 8},
            {"inputs": [3], "expected": 0},
        ]
        new_functions.append(
            {
                "name": "ctz_int",
                "kernel_name": "test_ctz_int",
                "input_type": "int",
                "output_type": "int",
                "num_inputs": 1,
                "tests": tests,
            }
        )

    # mad_hi_int (multiply and add high: mul_hi(a, b) + c)
    if "mad_hi_int" not in existing:
        tests = [
            {"inputs": [0, 0, 0], "expected": 0},
            {"inputs": [1, 1, 0], "expected": 0},
            {"inputs": [2, 2, 1], "expected": 1},
            {"inputs": [65536, 65536, 0], "expected": 1},
            {"inputs": [100, 200, 5], "expected": 5},
            {"inputs": [1000, 1000, 10], "expected": 10},
            {"inputs": [10000, 10000, 100], "expected": 100},
            {"inputs": [32768, 65536, 0], "expected": 0},
            {"inputs": [50000, 50000, 50], "expected": 50},
            {"inputs": [100000, 100000, 1000], "expected": 1000},
        ]
        new_functions.append(
            {
                "name": "mad_hi_int",
                "kernel_name": "test_mad_hi_int",
                "input_type": "int",
                "output_type": "int",
                "num_inputs": 3,
                "tests": tests,
            }
        )

    # mad_sat_int (saturating multiply and add: sat(a * b + c))
    if "mad_sat_int" not in existing:
        tests = [
            {"inputs": [0, 0, 0], "expected": 0},
            {"inputs": [1, 1, 1], "expected": 2},
            {"inputs": [2, 3, 4], "expected": 10},
            {"inputs": [10, 20, 30], "expected": 230},
            {"inputs": [100, 200, 300], "expected": 20300},
            {"inputs": [5, 5, 5], "expected": 30},
            {"inputs": [1000, 1000, 1000], "expected": 1001000},
            {"inputs": [50, 100, 50], "expected": 5050},
            {"inputs": [3, 4, 5], "expected": 17},
            {"inputs": [7, 8, 9], "expected": 65},
        ]
        new_functions.append(
            {
                "name": "mad_sat_int",
                "kernel_name": "test_mad_sat_int",
                "input_type": "int",
                "output_type": "int",
                "num_inputs": 3,
                "tests": tests,
            }
        )

    # max_uint
    if "max_uint" not in existing:
        tests = [
            {"inputs": [1, 2], "expected": 2},
            {"inputs": [2, 1], "expected": 2},
            {"inputs": [5, 5], "expected": 5},
            {"inputs": [0, 1], "expected": 1},
            {"inputs": [0, 0], "expected": 0},
            {"inputs": [10, 100], "expected": 100},
            {"inputs": [100, 10], "expected": 100},
            {"inputs": [999, 1000], "expected": 1000},
            {"inputs": [4294967295, 0], "expected": 4294967295},
            {"inputs": [1000000, 2000000], "expected": 2000000},
        ]
        new_functions.append(
            {
                "name": "max_uint",
                "kernel_name": "test_max_uint",
                "input_type": "uint",
                "output_type": "uint",
                "num_inputs": 2,
                "tests": tests,
            }
        )

    # min_uint
    if "min_uint" not in existing:
        tests = [
            {"inputs": [1, 2], "expected": 1},
            {"inputs": [2, 1], "expected": 1},
            {"inputs": [5, 5], "expected": 5},
            {"inputs": [0, 1], "expected": 0},
            {"inputs": [0, 0], "expected": 0},
            {"inputs": [10, 100], "expected": 10},
            {"inputs": [100, 10], "expected": 10},
            {"inputs": [999, 1000], "expected": 999},
            {"inputs": [4294967295, 0], "expected": 0},
            {"inputs": [1000000, 2000000], "expected": 1000000},
        ]
        new_functions.append(
            {
                "name": "min_uint",
                "kernel_name": "test_min_uint",
                "input_type": "uint",
                "output_type": "uint",
                "num_inputs": 2,
                "tests": tests,
            }
        )

    # mul_hi_int (high part of multiplication)
    if "mul_hi_int" not in existing:
        tests = [
            {"inputs": [0, 0], "expected": 0},
            {"inputs": [1, 1], "expected": 0},
            {"inputs": [65536, 65536], "expected": 1},
            {"inputs": [32768, 65536], "expected": 0},
            {"inputs": [100000, 100000], "expected": 2},
            {"inputs": [50000, 50000], "expected": 0},
            {"inputs": [200000, 200000], "expected": 9},
            {"inputs": [1000000, 1000], "expected": 0},
            {"inputs": [65535, 65536], "expected": 0},
            {"inputs": [131072, 65536], "expected": 2},
        ]
        new_functions.append(
            {
                "name": "mul_hi_int",
                "kernel_name": "test_mul_hi_int",
                "input_type": "int",
                "output_type": "int",
                "num_inputs": 2,
                "tests": tests,
            }
        )

    # rotate_int (rotate bits left)
    if "rotate_int" not in existing:
        tests = [
            {"inputs": [1, 0], "expected": 1},
            {"inputs": [1, 1], "expected": 2},
            {"inputs": [1, 2], "expected": 4},
            {"inputs": [1, 31], "expected": -2147483648},
            {"inputs": [15, 4], "expected": 240},
            {"inputs": [255, 8], "expected": 65280},
            {"inputs": [1, 32], "expected": 1},
            {"inputs": [7, 1], "expected": 14},
            {"inputs": [128, 1], "expected": 256},
            {"inputs": [3, 2], "expected": 12},
        ]
        new_functions.append(
            {
                "name": "rotate_int",
                "kernel_name": "test_rotate_int",
                "input_type": "int",
                "output_type": "int",
                "num_inputs": 2,
                "tests": tests,
            }
        )

    # sub_sat_int (saturating subtraction)
    if "sub_sat_int" not in existing:
        tests = [
            {"inputs": [0, 0], "expected": 0},
            {"inputs": [10, 5], "expected": 5},
            {"inputs": [5, 10], "expected": -5},
            {"inputs": [100, 50], "expected": 50},
            {"inputs": [-10, 5], "expected": -15},
            {"inputs": [10, -5], "expected": 15},
            {"inputs": [-2147483648, 1], "expected": -2147483648},
            {"inputs": [2147483647, -1], "expected": 2147483647},
            {"inputs": [1000, 500], "expected": 500},
            {"inputs": [0, 100], "expected": -100},
        ]
        new_functions.append(
            {
                "name": "sub_sat_int",
                "kernel_name": "test_sub_sat_int",
                "input_type": "int",
                "output_type": "int",
                "num_inputs": 2,
                "tests": tests,
            }
        )

    # mad24_int (24-bit multiply and add)
    if "mad24_int" not in existing:
        tests = [
            {"inputs": [0, 0, 0], "expected": 0},
            {"inputs": [1, 1, 1], "expected": 2},
            {"inputs": [2, 3, 4], "expected": 10},
            {"inputs": [5, 10, 15], "expected": 65},
            {"inputs": [10, 20, 30], "expected": 230},
            {"inputs": [100, 200, 300], "expected": 20300},
            {"inputs": [7, 8, 9], "expected": 65},
            {"inputs": [3, 4, 5], "expected": 17},
            {"inputs": [50, 100, 50], "expected": 5050},
            {"inputs": [123, 456, 789], "expected": 56877},
        ]
        new_functions.append(
            {
                "name": "mad24_int",
                "kernel_name": "test_mad24_int",
                "input_type": "int",
                "output_type": "int",
                "num_inputs": 3,
                "tests": tests,
            }
        )

    # Add all new functions
    data["functions"].extend(new_functions)

    # Write back
    with open("test_data/integer_functions.json", "w") as f:
        json.dump(data, f, indent=2)

    print(f"Extended integer_functions.json with {len(new_functions)} additional functions")


if __name__ == "__main__":
    extend_integer_functions_json()
    print("Integer functions test data generation complete!")
