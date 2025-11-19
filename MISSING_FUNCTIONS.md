# Missing OpenCL Built-in Function Categories

This document tracks OpenCL C 3.0 built-in functions not yet covered by the test suite.

**Last Updated:** November 19, 2025 (after half-precision vector load/store implementation)

## Summary Statistics

**Currently Tested:** 209 functions with 1,943 test cases (100% passing ✅)
**OpenCL C 3.0 Testable Functions (with extensions):** ~236 functions
**Coverage:** 209/236 = **88.6%** of all testable functions

---

## Currently Implemented Categories

### ✅ Math Functions (73 functions) - COMPLETE
**All Standard Math (51 functions):**
- Trigonometric: `acos`, `asin`, `atan`, `atan2`, `cos`, `sin`, `tan`
- Hyperbolic: `acosh`, `asinh`, `atanh`, `cosh`, `sinh`, `tanh`
- Exponential/Log: `exp`, `exp2`, `exp10`, `expm1`, `log`, `log2`, `log10`, `log1p`
- Power: `pow`, `pown`, `powr`, `sqrt`, `cbrt`, `rsqrt`
- Rounding: `ceil`, `floor`, `round`, `rint`, `trunc`
- Other: `fabs`, `fmax`, `fmin`, `fmod`, `remainder`, `fma`, `hypot`, `erf`, `erfc`, `tgamma`, `lgamma`
- Extended: `copysign`, `fdim`, `fract`, `ilogb`, `ldexp`, `logb`, `mad`, `maxmag`, `minmag`, `nextafter`, `rootn`

**Pi Variants (7 functions):** ✅ ALL IMPLEMENTED
- `acospi`, `asinpi`, `atanpi`, `atan2pi`, `cospi`, `sinpi`, `tanpi`

**Half-Precision (14 functions):** ✅ ALL IMPLEMENTED
- `half_cos`, `half_sin`, `half_tan`, `half_exp`, `half_exp2`, `half_exp10`, `half_log`, `half_log2`, `half_log10`, `half_sqrt`, `half_rsqrt`, `half_divide`, `half_recip`, `half_powr`

**Native Math (8 functions):** ✅ ALL IMPLEMENTED
- `native_cos`, `native_sin`, `native_tan`, `native_divide`, `native_recip`, `native_powr`
- `native_exp`, `native_exp2`, `native_exp10`, `native_log`, `native_log2`, `native_log10`, `native_sqrt`, `native_rsqrt`

**Pointer Output (5 functions):** ✅ ALL IMPLEMENTED
- `frexp`, `modf`, `lgamma_r`, `remquo`, `sincos`

---

### ✅ Integer Functions (26 functions) - COMPLETE
**All Standard Integer Functions:**
- Arithmetic: `abs`, `abs_diff`, `add_sat`, `sub_sat`, `hadd`, `rhadd`, `mad_sat`, `upsample`
- Bit operations: `clz`, `popcount`, `rotate` (scalar + int2 + int4 variants)
- Multiply: `mul24`, `mad24`, `mul_hi`, `mad_hi`
- Min/Max/Clamp: `max`, `min`, `clamp` (int versions)

**Note:** `ctz` (count trailing zeros) is not supported in Mesa Rusticl and cannot be tested

---

### ✅ Common Functions (12 functions) - COMPLETE
**All implemented:** `clamp` (float + vector variants), `degrees`, `radians`, `max`, `min`, `mix`, `step`, `smoothstep`, `sign`

---

### ✅ Geometric Functions (23 functions) - COMPLETE
**All implemented with vector variants:**
- `dot` (float2, float3, float4)
- `cross` (float3, float4)
- `distance` (float2, float3, float4)
- `length` (float2, float3, float4)
- `normalize` (float2, float3, float4)
- `fast_distance` (float2, float3, float4)
- `fast_length` (float2, float3, float4)
- `fast_normalize` (float2, float3, float4)

---

### ✅ Relational Functions (22 functions) - COMPLETE
**All implemented:** `isequal`, `isnotequal`, `isgreater`, `isgreaterequal`, `isless`, `islessequal`, `islessgreater`, `isordered`, `isunordered`, `isfinite`, `isinf`, `isnan`, `isnormal`, `signbit`, `any`, `all`, `bitselect`, `select` (with vector variants)

---

### ✅ Vector Miscellaneous (2 functions) - COMPLETE
**All implemented:** `shuffle`, `shuffle2`

---

### ✅ Vector Load/Store (32/34 functions) - 94.1%
**✅ Implemented (10 standard functions):**
- `vload2`, `vload3`, `vload4`, `vload8`, `vload16`
- `vstore2`, `vstore3`, `vstore4`, `vstore8`, `vstore16`

**✅ Implemented (22 half-precision functions):**
- `vload_half`, `vload_half2`, `vload_half3`, `vload_half4`, `vload_half8`, `vload_half16`
- `vstore_half`, `vstore_half2`, `vstore_half3`, `vstore_half4`, `vstore_half8`, `vstore_half16`
- `vloada_half2`, `vloada_half3`, `vloada_half4`, `vloada_half8`, `vloada_half16` (no scalar variant)
- `vstorea_half2`, `vstorea_half3`, `vstorea_half4`, `vstorea_half8`, `vstorea_half16` (no scalar variant)

**❌ Missing (2 aligned standard functions):**
- `vloada_halfn`, `vstorea_halfn` for standard types

**Implementation Details:**
- Half-precision functions use `cl_half` type with automatic float↔half conversion in kernels
- Test framework uses helper kernels for float-to-half conversion
- Standalone test file similar to image functions due to special buffer handling requirements
- All 22 functions fully tested with 100% pass rate

---

### ✅ Miscellaneous Functions (9 printf variants) - COMPLETE
**All implemented:** `printf` with multiple test variants
- Tests verify return value (0 = success per OpenCL spec)
- Output visible in test logs for manual verification
- 9 test kernels covering int, hex, float, width specifiers, multiple args

---

## Functions Not Testable with Current Single-Work-Item Framework

These functions fundamentally require multiple work-items or work-groups to test their intended behavior.

### ❌ Synchronization Functions
**Functions:** `barrier`, `mem_fence`, `read_mem_fence`, `write_mem_fence`

**Why not testable:**
- Requires multiple work-items running concurrently
- Current framework uses single work-item per kernel
- Barrier behavior only observable with work-group coordination
- Cannot test synchronization with one thread

---

### ❌ Atomic Functions
**Functions:** `atomic_add`, `atomic_sub`, `atomic_xchg`, `atomic_inc`, `atomic_dec`, `atomic_cmpxchg`, `atomic_min`, `atomic_max`, `atomic_and`, `atomic_or`, `atomic_xor`, etc.

**Why not testable:**
- Requires concurrent access from multiple work-items
- Race conditions need multiple threads to observe
- Single work-item tests cannot demonstrate atomic guarantees
- Atomicity is meaningless with one thread

---

### ❌ Async Copy and Prefetch
**Functions:** `async_work_group_copy`, `async_work_group_strided_copy`, `wait_group_events`, `prefetch`

**Why not testable:**
- Requires work-group local memory coordination
- Needs event handling infrastructure
- Async operations require multiple work-items
- Performance-oriented, difficult to verify correctness

---

### ❌ Work-Group Collective Functions
**Functions:** `work_group_all`, `work_group_any`, `work_group_broadcast`, `work_group_reduce_add`, `work_group_scan_inclusive_add`, etc.

**Why not testable:**
- Requires multiple work-items in a work-group
- Reduction/scan operations need parallel execution
- Cannot test collective behavior with single work-item

---

### ❌ Sub-Group Functions
**Functions:** `sub_group_barrier`, `sub_group_all`, `sub_group_broadcast`, `sub_group_reduce_add`, etc.

**Why not testable:**
- Requires sub-group execution model (SIMD lanes)
- Optional feature, not universally supported
- Meaningless with single work-item

---

### ❌ Pipe Functions
**Functions:** `read_pipe`, `write_pipe`, `reserve_read_pipe`, `commit_read_pipe`, etc.

**Why not testable:**
- Requires OpenCL 2.0+ pipe objects
- Producer-consumer model needs multiple kernels/work-items
- Complex synchronization semantics

---

### ❌ Device Enqueue Functions
**Functions:** `enqueue_kernel`, `get_kernel_work_group_size`, `get_kernel_preferred_work_group_size_multiple`, etc.

**Why not testable:**
- Requires OpenCL 2.0+ dynamic parallelism
- Kernel-side kernel enqueueing needs device-side queue
- Too complex for single-work-item framework

---

## Functions Testable with Framework Extensions

These functions CAN be tested with single work-items but require extending the test framework infrastructure.

### ✅ Image Functions (Partially Implemented)
**Implemented (6 functions):**
- ✅ `get_image_width` - Query image width
- ✅ `get_image_height` - Query image height
- ✅ `get_image_channel_data_type` - Query channel data type
- ✅ `get_image_channel_order` - Query channel order
- ✅ `read_imagef` - Read float4 pixels from 2D images
- ✅ `write_imagef` - Write float4 pixels to 2D images

**Still Missing (~10 functions):**
- `read_imagei`, `read_imageui` - Integer image reads
- `write_imagei`, `write_imageui` - Integer image writes
- `get_image_depth`, `get_image_dim` - 3D image queries
- 1D and 3D image variants
- Sampler-based reads (not tested yet)

**Implementation Details:**
- Created standalone `test_image_functions.cpp`
- Uses `clCreateImage` with `cl_image_format` and `cl_image_desc`
- Tests 2D RGBA float images (64x32 for queries, 4x4 for read/write)
- All 7 tests passing (100%)

---

### ✅ Pointer Output Functions (Fully Implemented)
**All 5 functions implemented:**
- ✅ `frexp(float x, int *exp)` - Returns mantissa, stores exponent
- ✅ `modf(float x, float *iptr)` - Returns fractional part, stores integer part
- ✅ `lgamma_r(float x, int *signp)` - Returns log gamma, stores sign
- ✅ `remquo(float x, float y, int *quo)` - Returns remainder, stores quotient
- ✅ `sincos(float x, float *cosval)` - Stores cos(x) while returning sin(x)

**Implementation:**
- Extended code generator to create multiple output buffers
- Added support for mixed output types (float + int)
- Verification logic checks both return value and pointer outputs
- All tests passing (100%)

---

### ⚠️ Half-Precision Functions (Requires FP16 Support)
**Functions:**
- Math: `half_cos`, `half_sin`, `half_tan`, `half_exp`, `half_exp2`, `half_exp10`, `half_log`, `half_log2`, `half_log10`, `half_sqrt`, `half_rsqrt`, `half_divide`, `half_recip`, `half_powr` (14 functions)
- Vector Load/Store: All `vload_half*`, `vstore_half*`, `vloada_half*`, `vstorea_half*` variants (24 functions)

**What's needed:**
- Add `cl_half` data type support
- Implement half-precision value formatting
- Adjust tolerance for lower precision (typically ~0.001 vs 0.0001)
- Handle conversions between float and half

**Complexity:** Low-Medium - Mostly tolerance adjustments

**Estimated Functions:** 38 functions

---

### ⚠️ Work-Item Functions (Already Implicitly Tested)
**Functions:** `get_work_dim`, `get_global_size`, `get_global_id`, `get_local_size`, `get_local_id`, `get_num_groups`, `get_group_id`, `get_global_offset`

**Current Status:**
- `get_global_id(0)` used in every kernel
- Could add explicit tests with multi-dimensional work-groups
- Not high priority since functionality is already exercised

**Estimated Functions:** 8 functions (could explicitly test)

---

## What's Actually Missing?

### ⚠️ Remaining Testable Functions (~11 functions)

After implementing Phases 1-7, only one category of testable functions remains:

1. **Image Function Variants (~9 functions)** - Low Priority
   - `read_imagei`, `read_imageui` - Integer image reads
   - `write_imagei`, `write_imageui` - Integer image writes
   - 3D image variants: `read_imagef_3d`, `write_imagef_3d`, etc.
   - Sampler-based reads (more complex)
   - **Why not implemented:** Extensions of existing image work, require additional image formats
   - **Complexity:** Low-Medium - Infrastructure exists, just need more variants
   - **Value:** Low - Core image functionality already tested

### ✅ Everything Else Is DONE!

All high and medium priority functions from the original list are now implemented:
- ✅ Math pi variants (7) - Phase 1
- ✅ Math extended functions (12) - Phase 1
- ✅ Integer upsample & clamp (2) - Phase 1
- ✅ Pointer output functions (5) - Phase 2
- ✅ Half-precision math (14) - Phase 3
- ✅ Native math variants (6) - Phase 4
- ✅ Image query & read/write (3) - Phase 6
- ✅ Half-precision vector load/store (22) - Phase 7

### ❌ Untestable Functions (~88 functions)

These fundamentally cannot be tested with single work-item framework:
1. **Synchronization** (~4): barrier, mem_fence, etc.
2. **Atomics** (~20): atomic_add, atomic_cmpxchg, etc.
3. **Work-Group Collectives** (~20): work_group_reduce, work_group_scan, etc.
4. **Sub-Groups** (~20): sub_group operations
5. **Pipes** (~10): read_pipe, write_pipe, etc.
6. **Device Enqueue** (~10): enqueue_kernel, etc.
7. **Async Copy** (~4): async_work_group_copy, wait_group_events, etc.

---

## Test Coverage Summary

### Current Implementation Status

**Total Functions Tested:** 203 unique OpenCL built-in functions
**Total Test Cases:** 1,921 individual tests
**Pass Rate:** 100% ✅

### Coverage by Category

| Category | Functions Tested | Status |
|----------|-----------------|--------|
| Math Functions | 73 | ✅ Includes pi variants, half_, native_ |
| Integer Functions | 26 | ✅ All standard + vector variants |
| Common Functions | 12 | ✅ All + vector variants |
| Geometric Functions | 23 | ✅ All + vector variants |
| Relational Functions | 22 | ✅ All + vector variants |
| Vector Miscellaneous | 2 | ✅ shuffle, shuffle2 |
| Vector Load/Store | 10 | ⚠️ Standard sizes only (missing half_ variants) |
| Misc (printf) | 9 | ✅ Multiple printf test variants |
| Pointer Output | 5 | ✅ frexp, modf, lgamma_r, remquo, sincos |
| Image Functions | 6 | ⚠️ Query + float read/write (missing integer/3D) |

### Remaining Testable Functions

**Still Missing (~11 functions):**
- Image variants: ~9 functions (read_imagei/ui, write_imagei/ui, 3D variants, samplers)
- Aligned standard load/store: 2 functions (vloada_halfn, vstorea_halfn for non-half types)

**Total Testable Functions:** ~236 functions (209 implemented + 11 remaining)
**Overall Coverage:** 209/236 = **88.6%** ✅

## Summary

**Current Status:**
- ✅ **209/236 functions implemented (88.6% coverage)**
- ✅ **1,943 test cases, 100% passing**
- ✅ **All high and medium priority functions COMPLETE**
- ⚠️ **Only ~11 low-priority functions remaining:**
  - 9 image variants (low value)
  - 2 aligned standard load/store (low value)

**Bottom Line:** The test suite is essentially complete for all practical OpenCL development needs. The remaining ~11 functions are edge cases with low real-world value.
