#!/usr/bin/env python3
"""
Add vector variants for existing bit operation functions
Extends clz, popcount, and rotate with int2 and int4 variants
"""

import json


def to_signed_int32(n):
    """Convert unsigned 32-bit value to signed int32"""
    n = n & 0xFFFFFFFF
    if n >= 0x80000000:
        return int(n - 0x100000000)
    return int(n)


def count_leading_zeros(n):
    """Count leading zeros in a 32-bit integer"""
    n = n & 0xFFFFFFFF
    if n == 0:
        return 32
    count = 0
    for i in range(31, -1, -1):
        if n & (1 << i):
            break
        count += 1
    return count


def popcount(n):
    """Count number of set bits"""
    return bin(n & 0xFFFFFFFF).count("1")


def rotate_left_32(n, shift):
    """Rotate 32-bit integer left by shift bits, return as signed int32"""
    n = n & 0xFFFFFFFF
    shift = shift & 31
    result = ((n << shift) | (n >> (32 - shift))) & 0xFFFFFFFF
    return to_signed_int32(result)


def add_vector_bit_functions():
    """Add vector variants to integer_functions.json"""

    # Read existing data
    with open("test_data/integer_functions.json", "r") as f:
        data = json.load(f)

    # Remove any existing vector bit operation variants to avoid duplicates
    vector_names = {
        "clz_int2",
        "clz_int4",
        "popcount_int2",
        "popcount_int4",
        "rotate_int2",
        "rotate_int4",
    }
    data["functions"] = [f for f in data["functions"] if f["name"] not in vector_names]

    new_functions = []

    # clz variants - use values < 0x80000000 to avoid sign issues
    clz_test_values_2 = [
        ([0, 0], [32, 32]),
        ([1, 255], [31, 24]),
        ([256, 65536], [23, 15]),
        ([16777216, 251658240], [7, 4]),
        ([1073741824, 1], [1, 31]),
        ([42, 1337], [26, 21]),
        ([305419896, 587202560], [3, 2]),
        ([1023, 4095], [22, 20]),
        ([16777216, 33554432], [7, 6]),
        ([7, 15], [29, 28]),
    ]

    clz_test_values_4 = [
        ([0, 0, 0, 0], [32, 32, 32, 32]),
        ([1, 2, 4, 8], [31, 30, 29, 28]),
        ([16, 32, 64, 128], [27, 26, 25, 24]),
        ([255, 256, 512, 1024], [24, 23, 22, 21]),
        ([1073741824, 1073741824, 536870912, 268435456], [1, 1, 2, 3]),
        ([100, 200, 300, 400], [25, 24, 23, 23]),
        ([2013265920, 251658240, 15728640, 983040], [1, 4, 8, 12]),
        ([7, 15, 31, 63], [29, 28, 27, 26]),
        ([1000000, 2000000, 3000000, 4000000], [12, 11, 10, 10]),
        ([305419896, 587202560, 872415232, 1157627904], [3, 2, 2, 1]),
    ]

    new_functions.append(
        {
            "name": "clz_int2",
            "kernel_name": "test_clz_int2",
            "input_type": "int2",
            "output_type": "int2",
            "num_inputs": 1,
            "tests": [{"inputs": [inp], "expected": exp} for inp, exp in clz_test_values_2],
        }
    )

    new_functions.append(
        {
            "name": "clz_int4",
            "kernel_name": "test_clz_int4",
            "input_type": "int4",
            "output_type": "int4",
            "num_inputs": 1,
            "tests": [{"inputs": [inp], "expected": exp} for inp, exp in clz_test_values_4],
        }
    )

    # popcount variants - verify expected values programmatically
    popcount_test_inputs_2 = [
        [0, 0],
        [1, 3],
        [7, 15],
        [255, 511],
        [2147483647, 1073741824],
        [1431655765, 1431655765],
        [305419896, 1644167168],
        [127, 1023],
        [2021161080, 252645135],
        [42, 1337],
    ]
    popcount_test_values_2 = [
        (inp, [popcount(inp[0]), popcount(inp[1])]) for inp in popcount_test_inputs_2
    ]

    popcount_test_inputs_4 = [
        [0, 0, 0, 0],
        [1, 3, 7, 15],
        [31, 63, 127, 255],
        [2147483647, 0, 1, 2147483647],
        [1431655765, 1431655765, 2021161080, 252645135],
        [100, 200, 300, 400],
        [1073741824, 1073741824, 536870912, 268435456],
        [511, 1023, 2047, 4095],
        [305419896, 587202560, 872415232, 1157627904],
        [7, 14, 28, 56],
    ]
    popcount_test_values_4 = [
        (inp, [popcount(inp[i]) for i in range(4)]) for inp in popcount_test_inputs_4
    ]

    new_functions.append(
        {
            "name": "popcount_int2",
            "kernel_name": "test_popcount_int2",
            "input_type": "int2",
            "output_type": "int2",
            "num_inputs": 1,
            "tests": [{"inputs": [inp], "expected": exp} for inp, exp in popcount_test_values_2],
        }
    )

    new_functions.append(
        {
            "name": "popcount_int4",
            "kernel_name": "test_popcount_int4",
            "input_type": "int4",
            "output_type": "int4",
            "num_inputs": 1,
            "tests": [{"inputs": [inp], "expected": exp} for inp, exp in popcount_test_values_4],
        }
    )

    # rotate variants (2-input function) - calculate expected values programmatically
    rotate_test_inputs_2 = [
        ([305419896, 1644167168], [0, 0]),
        ([305419896, 1644167168], [4, 4]),
        ([305419896, 1644167168], [8, 8]),
        ([305419896, 1644167168], [16, 16]),
        ([2147483647, 1], [1, 1]),
        ([1073741824, 1], [1, 31]),
        ([255, 65535], [4, 8]),
        ([1431655765, 1431655765], [1, 1]),
        ([305419896, 1157627904], [12, 20]),
        ([1, 1], [0, 32]),  # rotate by 32 = no change
    ]

    rotate_tests_2 = []
    for inp, shifts in rotate_test_inputs_2:
        expected = [rotate_left_32(inp[i], shifts[i]) for i in range(2)]
        rotate_tests_2.append({"inputs": [inp, shifts], "expected": expected})

    new_functions.append(
        {
            "name": "rotate_int2",
            "kernel_name": "test_rotate_int2",
            "input_type": "int2",
            "output_type": "int2",
            "num_inputs": 2,
            "tests": rotate_tests_2,
        }
    )

    rotate_test_inputs_4 = [
        ([1, 2, 4, 8], [0, 0, 0, 0]),
        ([1, 2, 4, 8], [1, 1, 1, 1]),
        ([1, 2, 4, 8], [4, 4, 4, 4]),
        ([305419896, 587202560, 872415232, 1157627904], [0, 4, 8, 12]),
        ([2147483647, 2147483647, 2147483647, 2147483647], [1, 8, 16, 24]),
        ([1073741824, 1073741824, 536870912, 268435456], [1, 2, 3, 4]),
        ([255, 255, 255, 255], [4, 8, 12, 16]),
        ([1431655765, 1431655765, 2021161080, 252645135], [1, 1, 4, 4]),
        ([100, 200, 300, 400], [3, 6, 9, 12]),
        ([1, 1, 1, 1], [0, 8, 16, 32]),
    ]

    rotate_tests_4 = []
    for inp, shifts in rotate_test_inputs_4:
        expected = [rotate_left_32(inp[i], shifts[i]) for i in range(4)]
        rotate_tests_4.append({"inputs": [inp, shifts], "expected": expected})

    new_functions.append(
        {
            "name": "rotate_int4",
            "kernel_name": "test_rotate_int4",
            "input_type": "int4",
            "output_type": "int4",
            "num_inputs": 2,
            "tests": rotate_tests_4,
        }
    )

    # Add new functions to the data
    data["functions"].extend(new_functions)

    # Write updated data back
    with open("test_data/integer_functions.json", "w") as f:
        json.dump(data, f, indent=2)

    print(f"Added {len(new_functions)} vector bit operation variants")
    print("Functions added:")
    for func in new_functions:
        print(f"  - {func['name']}: {len(func['tests'])} tests")
    print(f"\nTotal functions in integer_functions.json: {len(data['functions'])}")


if __name__ == "__main__":
    add_vector_bit_functions()
    print("Vector bit operation variants generation complete!")
