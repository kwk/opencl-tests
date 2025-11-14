# OpenCL Built-in Functions Test Suite

Comprehensive test suite for OpenCL C built-in functions using Mesa OpenCL (Rusticl).

This project tests **128 OpenCL built-in functions** with **1,280 test cases** across multiple function categories:
- Math Functions (51 functions): trigonometric, exponential, logarithmic, power, rounding, etc.
- Geometric Functions (23 functions): dot, cross, distance, length, normalize, and fast variants
- Common Functions (12 functions): clamp, degrees, radians, max, min, mix, step, smoothstep, sign
- Integer Functions (20 functions): abs, add_sat, clz, mad_hi, mul24, popcount, rotate, etc.
- Relational Functions (22 functions): comparisons, classification, logical operations, select

**Note:** This covers ~60-65% of testable OpenCL built-in functions. Some categories like synchronization functions, async copy, and image functions require multi-work-item execution or special object types that aren't suitable for this single-work-item test framework. See [MISSING_FUNCTIONS.md](MISSING_FUNCTIONS.md) for detailed analysis of untested functions.

## Project Structure

```
opencl-examples/
├── CMakeLists.txt
├── kernels/                        # Test kernels for all built-in functions
│   ├── common_functions_kernel.cl
│   ├── geometric_functions_kernel.cl
│   ├── integer_functions_kernel.cl
│   ├── math_functions_kernel.cl
│   └── relational_functions_kernel.cl
├── test_data/                      # JSON test specifications
│   ├── common_functions.json
│   ├── geometric_functions.json
│   ├── integer_functions.json
│   ├── math_functions.json
│   └── relational_functions.json
├── src/
│   ├── test_all_opencl_functions.cpp       # Comprehensive test runner
│   └── generated_tests.cpp                 # Auto-generated test code (11,000+ lines)
├── generate_tests.py               # Code generator (JSON → C++)
└── create_*_test_data.py          # Test data generators
```

## Features

### Comprehensive Test Suite
- **test_all_opencl_functions**: Tests 129 OpenCL built-in functions with 1,290 test cases
- Data-driven test framework with JSON test specifications
- Automatic C++ code generation from JSON test data
- Organized by function category (math, geometric, common, integer, relational)
- Tolerance-based comparison for floating-point results
- Component-wise comparison for vector types
- Detailed test result reporting

## Prerequisites

- CMake 3.10 or higher
- C++14 compatible compiler
- OpenCL development headers and libraries
- Mesa OpenCL (Rusticl) for GPU support

### Installing OpenCL and Mesa

**Fedora/RHEL:**
```bash
sudo dnf install opencl-headers OpenCL-ICD-Loader-devel mesa-libOpenCL
```

**Ubuntu/Debian:**
```bash
sudo apt-get install opencl-headers ocl-icd-opencl-dev mesa-opencl-icd
```

**Arch Linux:**
```bash
sudo pacman -S opencl-headers ocl-icd opencl-mesa
```

### Enabling Mesa Rusticl

Mesa Rusticl requires enabling your GPU driver via the `RUSTICL_ENABLE` environment variable:

```bash
export RUSTICL_ENABLE=iris      # For Intel GPUs
# or
export RUSTICL_ENABLE=radeonsi  # For AMD GPUs
```

For more information, see the [official Mesa Rusticl documentation](https://docs.mesa3d.org/rusticl.html).

## Building

```bash
mkdir build
cd build
cmake ..
make
```

This builds the test suite executable: `test_all_opencl_functions`

## Running

From the build directory:

```bash
# Run all tests
RUSTICL_ENABLE=iris ./test_all_opencl_functions

# Run a specific function test
RUSTICL_ENABLE=iris ./test_all_opencl_functions sqrt

# Run all tests in a category
RUSTICL_ENABLE=iris ./test_all_opencl_functions --category math

# List all available tests
./test_all_opencl_functions --list

# Show help
./test_all_opencl_functions --help
```

The test runner supports filtering to run specific tests or categories, making it easy to debug individual failing tests. Available categories: `integer`, `common`, `geometric`, `math`, `relational`.

The test runner will:
1. Initialize Mesa OpenCL and detect GPU device
2. Run filtered or all function tests (128 functions, 1,280 test cases total)
3. Display test progress for each function category
4. Show summary with pass/fail statistics
5. List any failed tests with details

Example output:
```
========================================
OpenCL Built-in Functions Test Suite
Testing 129 functions with 1290 test cases
========================================

Found Mesa platform: rusticl (Mesa/X.org)
Using device: Mesa Intel(R) UHD Graphics (TGL GT1)
OpenCL initialized successfully

=== INTEGER FUNCTIONS ===
Testing abs_int()...
abs_int() tests complete

Testing add_sat_int()...
add_sat_int() tests complete

...

=== MATH FUNCTIONS ===
Testing sqrt()...
sqrt() tests complete

Testing sin()...
sin() tests complete

...

========================================
TEST SUMMARY
========================================
Total tests: 1290
Passed: 1285 (99.6%)
Failed: 5 (0.4%)
========================================

Failed tests:
  - exp10 test #9
  - pow test #8
  - tgamma test #9
  - native_exp10 test #9
  - powr test #9
========================================
```

## Test Data Generation

The test suite uses a data-driven approach:

1. **JSON Test Specifications** (`test_data/*.json`):
   - Define function metadata (name, input/output types, number of inputs)
   - Specify 10 test cases per function with inputs and expected outputs
   - Example:
   ```json
   {
     "name": "sqrt",
     "kernel_name": "test_sqrt",
     "input_type": "float",
     "output_type": "float",
     "num_inputs": 1,
     "tests": [
       {"inputs": [4.0], "expected": 2.0},
       ...
     ]
   }
   ```

2. **Automated Test Data Generation** (`create_*_test_data.py`):
   - Python scripts to generate test data for each function category
   - Use Python's math library to compute expected outputs
   - Automatically extend JSON files with new functions

3. **C++ Code Generation** (`generate_tests.py`):
   - Reads all JSON test specifications
   - Generates `src/generated_tests.cpp` (11,000+ lines)
   - Creates test functions with proper OpenCL buffer management
   - Handles scalar and vector types (int2/3/4, float2/3/4)
   - Implements tolerance-based floating-point comparison

To regenerate test code after modifying JSON test data:
```bash
python3 generate_tests.py
```

## OpenCL Built-in Functions and libclc

The functions tested in this suite are defined by the [OpenCL C 3.0 Specification](https://registry.khronos.org/OpenCL/specs/3.0-unified/html/OpenCL_C.html). They are built-in functions that must be available in all conforming OpenCL implementations.

### How Built-in Functions Work

When you call `clBuildProgram()`, the OpenCL implementation compiles your kernel and provides implementations of built-in functions:

1. **Compilation**: The OpenCL driver/compiler compiles your kernel source
2. **Linking**: Built-in function implementations are provided by the runtime
3. **Execution**: Compiled kernels run on the GPU with built-in functions available

### What is libclc?

**libclc** is an open-source library providing reference implementations of OpenCL built-in functions:

- Provides LLVM bitcode implementations
- Used by some OpenCL compilers during kernel compilation
- NOT a runtime library - implementations are compiled into kernels
- Your host application only links against `libOpenCL.so`

Different OpenCL implementations handle built-in functions differently:

- **Mesa Rusticl**: Uses libclc-based implementations
- **NVIDIA**: Proprietary implementations in CUDA drivers
- **AMD ROCm**: Proprietary implementations in ROCm drivers
- **PoCL**: Ships with pre-compiled LLVM bitcode (`/usr/share/pocl/kernel-*.bc`)

You don't need to install libclc separately - the OpenCL runtime you install includes everything needed to compile kernels with built-in functions.

## Function Categories

### Math Functions (51 functions)
- **Trigonometric**: sin, cos, tan, asin, acos, atan, atan2
- **Hyperbolic**: sinh, cosh, tanh, asinh, acosh, atanh
- **Exponential/Log**: exp, exp2, exp10, expm1, log, log2, log10, log1p
- **Power**: pow, pown, powr, sqrt, cbrt, rsqrt
- **Rounding**: ceil, floor, round, rint, trunc
- **Other**: fabs, fmax, fmin, fmod, remainder, fma, hypot, erf, erfc, tgamma, lgamma
- **Native variants**: native_exp, native_exp2, native_exp10, native_log, native_log2, native_log10, native_sqrt, native_rsqrt

### Geometric Functions (23 functions)
- **Dot product**: dot (float2/3/4)
- **Cross product**: cross (float3/4)
- **Distance**: distance (float2/3/4), fast_distance (float2/3/4)
- **Length**: length (float2/3/4), fast_length (float2/3/4)
- **Normalize**: normalize (float2/3/4), fast_normalize (float2/3/4)

### Common Functions (12 functions)
- clamp, degrees, radians, max, min, mix, step, smoothstep, sign
- Vector variants: clamp_float2, max_float2, min_float2

### Integer Functions (21 functions)
- **Arithmetic**: abs, add_sat, sub_sat, mad_sat, hadd, rhadd
- **Bit operations**: clz, ctz, popcount, rotate
- **Multiply**: mul24, mad24, mul_hi, mad_hi
- **Min/Max**: max, min
- **Difference**: abs_diff
- Unsigned variants: add_sat_uint, abs_diff_uint, max_uint, min_uint

### Relational Functions (22 functions)
- **Comparisons**: isequal, isnotequal, isgreater, isgreaterequal, isless, islessequal, islessgreater
- **Classification**: isfinite, isinf, isnan, isnormal, signbit
- **Ordering**: isordered, isunordered
- **Vector tests**: any (int2/4), all (int2/4)
- **Selection**: select (float/int), bitselect (float/int)

## Contributing

### Code Formatting

This project uses pre-commit hooks to maintain consistent code formatting:

```bash
# Install pre-commit
pip install pre-commit

# Set up git hooks
pre-commit install

# Run manually on all files
pre-commit run --all-files
```

**Formatting rules:**
- **Python code**: Formatted with [black](https://github.com/psf/black) (line length: 100)
- **C/C++ code**: Formatted with [clang-format](https://clang.llvm.org/docs/ClangFormat.html) (LLVM style)
- **OpenCL kernels (.cl)**: Formatted with clang-format (LLVM style)

Pre-commit hooks automatically format code before each commit. You can also run formatters manually:
```bash
black generate_tests.py create_*_test_data.py
clang-format -i src/*.cpp kernels/*.cl
```

### Adding New Tests

To add tests for additional OpenCL built-in functions:

1. Create kernel implementations in appropriate `kernels/*_kernel.cl` file
2. Add test data to corresponding `test_data/*.json` file, or create a Python generator script `create_*_test_data.py`
3. Test data is automatically converted to C++ during build (no manual regeneration needed)
4. Add function declarations to the registry in `src/test_all_opencl_functions.cpp`
5. Rebuild and test

## License

This project is provided as educational material for learning OpenCL programming.

## References

- [OpenCL C 3.0 Specification](https://registry.khronos.org/OpenCL/specs/3.0-unified/html/OpenCL_C.html)
- [Mesa Rusticl Documentation](https://docs.mesa3d.org/rusticl.html)
- [libclc Project](https://libclc.llvm.org/)
- [Khronos OpenCL Registry](https://www.khronos.org/registry/OpenCL/)
