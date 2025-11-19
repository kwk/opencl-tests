#!/usr/bin/env python3
"""
Generate test data for OpenCL image functions.

Image functions test queries and read/write operations on image memory objects.
This requires creating OpenCL image objects in the host code.
"""

import json
from pathlib import Path


def create_image_test_data():
    """Create JSON file for image functions"""

    functions = []

    # Image query functions - these return single values about the image
    query_funcs = {
        "get_image_width": {
            "description": "Returns the image width in pixels",
            "input_type": "image2d_t",
            "output_type": "int",
            "num_inputs": 0,  # No scalar inputs, just the image object
            "is_image_query": True,
            "tests": [
                {"image_width": 16, "image_height": 16, "expected": 16},
                {"image_width": 32, "image_height": 16, "expected": 32},
                {"image_width": 64, "image_height": 32, "expected": 64},
                {"image_width": 128, "image_height": 64, "expected": 128},
                {"image_width": 256, "image_height": 128, "expected": 256},
            ],
        },
        "get_image_height": {
            "description": "Returns the image height in pixels",
            "input_type": "image2d_t",
            "output_type": "int",
            "num_inputs": 0,
            "is_image_query": True,
            "tests": [
                {"image_width": 16, "image_height": 16, "expected": 16},
                {"image_width": 32, "image_height": 32, "expected": 32},
                {"image_width": 64, "image_height": 48, "expected": 48},
                {"image_width": 128, "image_height": 96, "expected": 96},
                {"image_width": 256, "image_height": 192, "expected": 192},
            ],
        },
        "get_image_channel_data_type": {
            "description": "Returns the channel data type",
            "input_type": "image2d_t",
            "output_type": "int",
            "num_inputs": 0,
            "is_image_query": True,
            "tests": [
                {
                    "image_width": 16,
                    "image_height": 16,
                    "channel_data_type": "CL_FLOAT",
                    "expected": 0x10DE,  # CL_FLOAT
                },
                {
                    "image_width": 16,
                    "image_height": 16,
                    "channel_data_type": "CL_UNSIGNED_INT8",
                    "expected": 0x10D7,  # CL_UNSIGNED_INT8
                },
            ],
        },
        "get_image_channel_order": {
            "description": "Returns the channel order",
            "input_type": "image2d_t",
            "output_type": "int",
            "num_inputs": 0,
            "is_image_query": True,
            "tests": [
                {
                    "image_width": 16,
                    "image_height": 16,
                    "channel_order": "CL_RGBA",
                    "expected": 0x10B5,  # CL_RGBA
                },
                {
                    "image_width": 16,
                    "image_height": 16,
                    "channel_order": "CL_R",
                    "expected": 0x10B0,  # CL_R
                },
            ],
        },
    }

    for name, spec in query_funcs.items():
        functions.append(
            {
                "name": name,
                "kernel_name": f"test_{name}",
                "input_type": spec["input_type"],
                "output_type": spec["output_type"],
                "num_inputs": spec["num_inputs"],
                "is_image_query": spec["is_image_query"],
                "description": spec["description"],
                "tests": spec["tests"],
            }
        )

    # Image read functions - read pixel data from images
    # For simplicity, we'll test reading a single pixel from known coordinates
    read_funcs = {
        "read_imagef_2d": {
            "description": "Read float4 pixel from 2D image",
            "input_type": "image2d_t",
            "output_type": "float4",
            "num_inputs": 2,  # x and y coordinates
            "is_image_read": True,
            "channel_order": "CL_RGBA",
            "channel_data_type": "CL_FLOAT",
            "tests": [
                {
                    "image_width": 4,
                    "image_height": 4,
                    "inputs": [0, 0],  # x, y coords
                    "image_data": [1.0, 0.0, 0.0, 1.0],  # Red pixel at (0,0)
                    "expected": [1.0, 0.0, 0.0, 1.0],
                },
                {
                    "image_width": 4,
                    "image_height": 4,
                    "inputs": [1, 0],  # x, y coords
                    "image_data": [0.0, 1.0, 0.0, 1.0],  # Green pixel at (1,0)
                    "expected": [0.0, 1.0, 0.0, 1.0],
                },
                {
                    "image_width": 4,
                    "image_height": 4,
                    "inputs": [0, 1],  # x, y coords
                    "image_data": [0.0, 0.0, 1.0, 1.0],  # Blue pixel at (0,1)
                    "expected": [0.0, 0.0, 1.0, 1.0],
                },
            ],
        },
    }

    for name, spec in read_funcs.items():
        functions.append(
            {
                "name": name,
                "kernel_name": f"test_{name}",
                "input_type": spec["input_type"],
                "output_type": spec["output_type"],
                "num_inputs": spec["num_inputs"],
                "is_image_read": spec["is_image_read"],
                "channel_order": spec["channel_order"],
                "channel_data_type": spec["channel_data_type"],
                "description": spec["description"],
                "tests": spec["tests"],
            }
        )

    # Image write functions - write pixel data to images
    write_funcs = {
        "write_imagef_2d": {
            "description": "Write float4 pixel to 2D image",
            "input_type": "image2d_t",
            "output_type": "float4",
            "num_inputs": 2,  # x, y coords, color data passed separately
            "is_image_write": True,
            "channel_order": "CL_RGBA",
            "channel_data_type": "CL_FLOAT",
            "tests": [
                {
                    "image_width": 4,
                    "image_height": 4,
                    "inputs": [0, 0],  # x, y coords
                    "color": [1.0, 0.0, 0.0, 1.0],  # Red to write at (0,0)
                    "expected": [1.0, 0.0, 0.0, 1.0],
                },
                {
                    "image_width": 4,
                    "image_height": 4,
                    "inputs": [1, 0],  # x, y coords
                    "color": [0.0, 1.0, 0.0, 1.0],  # Green to write at (1,0)
                    "expected": [0.0, 1.0, 0.0, 1.0],
                },
            ],
        },
    }

    for name, spec in write_funcs.items():
        functions.append(
            {
                "name": name,
                "kernel_name": f"test_{name}",
                "input_type": spec["input_type"],
                "output_type": spec["output_type"],
                "num_inputs": spec["num_inputs"],
                "is_image_write": spec["is_image_write"],
                "channel_order": spec["channel_order"],
                "channel_data_type": spec["channel_data_type"],
                "description": spec["description"],
                "tests": spec["tests"],
            }
        )

    data = {
        "category": "image_functions",
        "kernel_file": "kernels/image_functions_kernel.cl",
        "functions": functions,
    }

    output_path = Path("test_data/image_functions.json")
    output_path.parent.mkdir(exist_ok=True)

    with open(output_path, "w") as f:
        json.dump(data, f, indent=2)

    print(f"Created {output_path}")
    print(f"Functions: {len(functions)}")
    print(f"Total tests: {sum(len(f['tests']) for f in functions)}")
    for func in functions:
        print(f"  {func['name']}: {len(func['tests'])} tests")


if __name__ == "__main__":
    create_image_test_data()
    print("Image function test data generation complete!")
