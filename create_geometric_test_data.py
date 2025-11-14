#!/usr/bin/env python3
"""
Automatically generate test data for remaining geometric functions
"""

import json
import math

def generate_test_values_vec2():
    """Generate diverse float2 test values"""
    return [
        (1.0, 0.0), (0.0, 1.0), (1.0, 1.0),
        (3.0, 4.0), (5.0, 12.0), (-1.0, 2.0),
        (0.5, 0.5), (2.0, 3.0), (6.0, 8.0), (10.0, 20.0)
    ]

def generate_test_values_vec3():
    """Generate diverse float3 test values"""
    return [
        (1.0, 0.0, 0.0), (0.0, 1.0, 0.0), (0.0, 0.0, 1.0),
        (1.0, 1.0, 1.0), (3.0, 4.0, 0.0), (2.0, 3.0, 6.0),
        (-1.0, 2.0, -3.0), (0.5, 0.5, 0.5), (1.0, 2.0, 2.0), (4.0, 4.0, 2.0)
    ]

def generate_test_values_vec4():
    """Generate diverse float4 test values"""
    return [
        (1.0, 0.0, 0.0, 0.0), (0.0, 1.0, 0.0, 0.0), (0.0, 0.0, 1.0, 0.0), (0.0, 0.0, 0.0, 1.0),
        (1.0, 1.0, 1.0, 1.0), (2.0, 3.0, 4.0, 5.0), (3.0, 4.0, 0.0, 0.0),
        (-1.0, 2.0, -3.0, 4.0), (0.5, 0.5, 0.5, 0.5), (1.0, 2.0, 2.0, 3.0)
    ]

def vector_dot(a, b):
    """Calculate dot product"""
    return sum(x * y for x, y in zip(a, b))

def vector_length(v):
    """Calculate vector length"""
    return math.sqrt(sum(x * x for x in v))

def vector_distance(a, b):
    """Calculate distance between vectors"""
    diff = tuple(x - y for x, y in zip(a, b))
    return vector_length(diff)

def vector_normalize(v):
    """Normalize vector"""
    length = vector_length(v)
    if length < 0.0001:
        return v
    return tuple(x / length for x in v)

def vector_cross_3d(a, b):
    """Calculate 3D cross product"""
    return (
        a[1] * b[2] - a[2] * b[1],
        a[2] * b[0] - a[0] * b[2],
        a[0] * b[1] - a[1] * b[0]
    )

def vector_cross_4d(a, b):
    """Calculate 4D cross product (using xyz components)"""
    cross = vector_cross_3d(a[:3], b[:3])
    return cross + (0.0,)

def extend_geometric_functions_json():
    """Extend the geometric_functions.json file with remaining functions"""
    with open("test_data/geometric_functions.json", "r") as f:
        data = json.load(f)

    # Track which functions already exist
    existing = {f["name"] for f in data["functions"]}

    new_functions = []

    # dot_float4
    if "dot_float4" not in existing:
        tests = []
        vec4_pairs = [(generate_test_values_vec4()[i], generate_test_values_vec4()[(i+1) % 10]) for i in range(10)]
        for v1, v2 in vec4_pairs:
            expected = vector_dot(v1, v2)
            tests.append({
                "inputs": [list(v1), list(v2)],
                "expected": float(expected)
            })
        new_functions.append({
            "name": "dot_float4",
            "kernel_name": "test_dot_float4",
            "input_type": "float4",
            "output_type": "float",
            "num_inputs": 2,
            "tests": tests
        })

    # cross (float3)
    if "cross" not in existing:
        tests = []
        vec3_pairs = [(generate_test_values_vec3()[i], generate_test_values_vec3()[(i+1) % 10]) for i in range(10)]
        for v1, v2 in vec3_pairs:
            expected = vector_cross_3d(v1, v2)
            tests.append({
                "inputs": [list(v1), list(v2)],
                "expected": list(expected)
            })
        new_functions.append({
            "name": "cross",
            "kernel_name": "test_cross",
            "input_type": "float3",
            "output_type": "float3",
            "num_inputs": 2,
            "tests": tests
        })

    # cross_float4
    if "cross_float4" not in existing:
        tests = []
        vec4_pairs = [(generate_test_values_vec4()[i], generate_test_values_vec4()[(i+1) % 10]) for i in range(10)]
        for v1, v2 in vec4_pairs:
            expected = vector_cross_4d(v1, v2)
            tests.append({
                "inputs": [list(v1), list(v2)],
                "expected": list(expected)
            })
        new_functions.append({
            "name": "cross_float4",
            "kernel_name": "test_cross_float4",
            "input_type": "float4",
            "output_type": "float4",
            "num_inputs": 2,
            "tests": tests
        })

    # distance_float3
    if "distance_float3" not in existing:
        tests = []
        vec3_pairs = [(generate_test_values_vec3()[i], generate_test_values_vec3()[(i+1) % 10]) for i in range(10)]
        for v1, v2 in vec3_pairs:
            expected = vector_distance(v1, v2)
            tests.append({
                "inputs": [list(v1), list(v2)],
                "expected": float(expected)
            })
        new_functions.append({
            "name": "distance_float3",
            "kernel_name": "test_distance_float3",
            "input_type": "float3",
            "output_type": "float",
            "num_inputs": 2,
            "tests": tests
        })

    # distance_float4
    if "distance_float4" not in existing:
        tests = []
        vec4_pairs = [(generate_test_values_vec4()[i], generate_test_values_vec4()[(i+1) % 10]) for i in range(10)]
        for v1, v2 in vec4_pairs:
            expected = vector_distance(v1, v2)
            tests.append({
                "inputs": [list(v1), list(v2)],
                "expected": float(expected)
            })
        new_functions.append({
            "name": "distance_float4",
            "kernel_name": "test_distance_float4",
            "input_type": "float4",
            "output_type": "float",
            "num_inputs": 2,
            "tests": tests
        })

    # length_float4
    if "length_float4" not in existing:
        tests = []
        for vec in generate_test_values_vec4():
            expected = vector_length(vec)
            tests.append({
                "inputs": [list(vec)],
                "expected": float(expected)
            })
        new_functions.append({
            "name": "length_float4",
            "kernel_name": "test_length_float4",
            "input_type": "float4",
            "output_type": "float",
            "num_inputs": 1,
            "tests": tests
        })

    # normalize_float2
    if "normalize_float2" not in existing:
        tests = []
        for vec in generate_test_values_vec2():
            expected = vector_normalize(vec)
            tests.append({
                "inputs": [list(vec)],
                "expected": list(expected)
            })
        new_functions.append({
            "name": "normalize_float2",
            "kernel_name": "test_normalize_float2",
            "input_type": "float2",
            "output_type": "float2",
            "num_inputs": 1,
            "tests": tests
        })

    # normalize_float3
    if "normalize_float3" not in existing:
        tests = []
        for vec in generate_test_values_vec3():
            expected = vector_normalize(vec)
            tests.append({
                "inputs": [list(vec)],
                "expected": list(expected)
            })
        new_functions.append({
            "name": "normalize_float3",
            "kernel_name": "test_normalize_float3",
            "input_type": "float3",
            "output_type": "float3",
            "num_inputs": 1,
            "tests": tests
        })

    # normalize_float4
    if "normalize_float4" not in existing:
        tests = []
        for vec in generate_test_values_vec4():
            expected = vector_normalize(vec)
            tests.append({
                "inputs": [list(vec)],
                "expected": list(expected)
            })
        new_functions.append({
            "name": "normalize_float4",
            "kernel_name": "test_normalize_float4",
            "input_type": "float4",
            "output_type": "float4",
            "num_inputs": 1,
            "tests": tests
        })

    # Fast variants (same test values as regular versions)
    fast_funcs = [
        ("fast_distance_float2", "test_fast_distance_float2", "float2", "float", 2,
         [(generate_test_values_vec2()[i], generate_test_values_vec2()[(i+1) % 10]) for i in range(10)],
         lambda v1, v2: vector_distance(v1, v2)),
        ("fast_distance_float3", "test_fast_distance_float3", "float3", "float", 2,
         [(generate_test_values_vec3()[i], generate_test_values_vec3()[(i+1) % 10]) for i in range(10)],
         lambda v1, v2: vector_distance(v1, v2)),
        ("fast_distance_float4", "test_fast_distance_float4", "float4", "float", 2,
         [(generate_test_values_vec4()[i], generate_test_values_vec4()[(i+1) % 10]) for i in range(10)],
         lambda v1, v2: vector_distance(v1, v2)),
        ("fast_length_float2", "test_fast_length_float2", "float2", "float", 1,
         [(v,) for v in generate_test_values_vec2()],
         lambda v: vector_length(v)),
        ("fast_length_float3", "test_fast_length_float3", "float3", "float", 1,
         [(v,) for v in generate_test_values_vec3()],
         lambda v: vector_length(v)),
        ("fast_length_float4", "test_fast_length_float4", "float4", "float", 1,
         [(v,) for v in generate_test_values_vec4()],
         lambda v: vector_length(v)),
        ("fast_normalize_float2", "test_fast_normalize_float2", "float2", "float2", 1,
         [(v,) for v in generate_test_values_vec2()],
         lambda v: vector_normalize(v)),
        ("fast_normalize_float3", "test_fast_normalize_float3", "float3", "float3", 1,
         [(v,) for v in generate_test_values_vec3()],
         lambda v: vector_normalize(v)),
        ("fast_normalize_float4", "test_fast_normalize_float4", "float4", "float4", 1,
         [(v,) for v in generate_test_values_vec4()],
         lambda v: vector_normalize(v)),
    ]

    for name, kernel_name, input_type, output_type, num_inputs, test_values, calc_fn in fast_funcs:
        if name not in existing:
            tests = []
            for values in test_values:
                expected = calc_fn(*values)
                inputs = [list(v) if isinstance(v, tuple) else v for v in values]
                expected_val = list(expected) if isinstance(expected, tuple) else float(expected)
                tests.append({
                    "inputs": inputs,
                    "expected": expected_val
                })
            new_functions.append({
                "name": name,
                "kernel_name": kernel_name,
                "input_type": input_type,
                "output_type": output_type,
                "num_inputs": num_inputs,
                "tests": tests
            })

    # Add all new functions
    data["functions"].extend(new_functions)

    # Write back
    with open("test_data/geometric_functions.json", "w") as f:
        json.dump(data, f, indent=2)

    print(f"Extended geometric_functions.json with {len(new_functions)} additional functions")

if __name__ == "__main__":
    extend_geometric_functions_json()
    print("Geometric functions test data generation complete!")
