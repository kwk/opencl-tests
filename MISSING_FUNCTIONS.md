# Missing OpenCL Built-in Function Categories

This document tracks OpenCL C 3.0 built-in functions not yet covered by the test suite.

**Last Updated:** November 19, 2025 (after image functions implementation)

## Summary Statistics

**Currently Tested:** 203 functions with 1,921 test cases (100% passing ✅)
**OpenCL C 3.0 Testable Functions (with extensions):** ~236 functions
**Coverage:** 203/236 = **86.0%** of all testable functions

---

## Currently Implemented Categories

### ✅ Math Functions (51/95 functions) - 53.7%
**Implemented:**
- Trigonometric: `acos`, `asin`, `atan`, `atan2`, `cos`, `sin`, `tan`
- Hyperbolic: `acosh`, `asinh`, `atanh`, `cosh`, `sinh`, `tanh`
- Exponential/Log: `exp`, `exp2`, `exp10`, `expm1`, `log`, `log2`, `log10`, `log1p`
- Power: `pow`, `pown`, `powr`, `sqrt`, `cbrt`, `rsqrt`
- Rounding: `ceil`, `floor`, `round`, `rint`, `trunc`
- Other: `fabs`, `fmax`, `fmin`, `fmod`, `remainder`, `fma`, `hypot`, `erf`, `erfc`, `tgamma`, `lgamma`
- Native: `native_exp`, `native_exp2`, `native_exp10`, `native_log`, `native_log2`, `native_log10`, `native_sqrt`, `native_rsqrt`

**Missing (44 functions):**
- **Pi variants (7):** `acospi`, `asinpi`, `atanpi`, `atan2pi`, `cospi`, `sinpi`, `tanpi`
- **Half-precision (14):** `half_cos`, `half_sin`, `half_tan`, `half_exp`, `half_exp2`, `half_exp10`, `half_log`, `half_log2`, `half_log10`, `half_sqrt`, `half_rsqrt`, `half_divide`, `half_recip`, `half_powr`
- **Native (7):** `native_cos`, `native_sin`, `native_tan`, `native_divide`, `native_recip`, `native_powr`
- **Other (16):** `copysign`, `fdim`, `fract`, `frexp`, `ilogb`, `ldexp`, `lgamma_r`, `logb`, `mad`, `maxmag`, `minmag`, `modf`, `nan`, `nextafter`, `remquo`, `rootn`, `sincos`

**Feasibility:**
- ✅ **High Priority (Pi variants + most Other):** Easy to implement, similar to existing functions (19 functions)
- ⚠️ **Medium Priority (half_*, native_*):** Require precision adjustments (21 functions)
- ⚠️ **Low Priority:** `frexp`, `modf`, `lgamma_r`, `remquo`, `sincos` need pointer outputs (4 functions)

---

### ✅ Integer Functions (14/16 functions) - 87.5%
**Implemented:**
- Arithmetic: `abs`, `abs_diff`, `add_sat`, `sub_sat`, `hadd`, `rhadd`, `mad_sat`
- Bit operations: `clz`, `popcount`, `rotate`
- Multiply: `mul24`, `mad24`, `mul_hi`, `mad_hi`
- Min/Max: `max`, `min` (int versions)

**Missing (2 functions):**
- ❌ `ctz` - Count trailing zeros (not supported in Mesa Rusticl)
- ✅ `upsample` - Combine two ints to create larger type (easy to add)

**Integer Common Functions (2/3 implemented):**
- ✅ Implemented: `max`, `min` (int versions)
- ⚠️ Missing: `clamp` (int version) - easy to add

---

### ✅ Common Functions (9/9 functions) - 100%
**All implemented:** `clamp`, `degrees`, `radians`, `max`, `min`, `mix`, `step`, `smoothstep`, `sign`

---

### ✅ Geometric Functions (8/8 functions) - 100%
**All implemented:** `dot`, `cross`, `distance`, `length`, `normalize`, `fast_distance`, `fast_length`, `fast_normalize`

---

### ✅ Relational Functions (18/18 functions) - 100%
**All implemented:** `isequal`, `isnotequal`, `isgreater`, `isgreaterequal`, `isless`, `islessequal`, `islessgreater`, `isordered`, `isunordered`, `isfinite`, `isinf`, `isnan`, `isnormal`, `signbit`, `any`, `all`, `bitselect`, `select`

---

### ✅ Vector Miscellaneous (2/2 functions) - 100%
**All implemented:** `shuffle`, `shuffle2`

---

### ✅ Vector Load/Store (10/34 functions) - 29.4%
**Implemented (10):**
- `vload2`, `vload3`, `vload4`, `vload8`, `vload16`
- `vstore2`, `vstore3`, `vstore4`, `vstore8`, `vstore16`

**Missing (24 functions - all half-precision):**
- `vload_half`, `vload_half2`, `vload_half3`, `vload_half4`, `vload_half8`, `vload_half16`
- `vstore_half`, `vstore_half2`, `vstore_half3`, `vstore_half4`, `vstore_half8`, `vstore_half16`
- `vloada_half`, `vloada_half2`, `vloada_half3`, `vloada_half4`, `vloada_half8`, `vloada_half16`
- `vstorea_half`, `vstorea_half2`, `vstorea_half3`, `vstorea_half4`, `vstorea_half8`, `vstorea_half16`

**Feasibility:** ⚠️ Requires half-precision (fp16) support in test framework

---

### ✅ Miscellaneous Functions (1 function) - printf
**Implemented:** `printf` (returns 0 on success per OpenCL C spec)
- Tests verify return value (0 = success, -1 = failure)
- Actual output visible in test logs for manual verification
- 9 test kernels, 22 test cases covering int, hex, float formatting

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

## Recommendations

### High Priority - Easy to Add (21 functions)

1. **Math Pi Variants (7 functions)** - Simple wrappers
   - `acospi`, `asinpi`, `atanpi`, `atan2pi`, `cospi`, `sinpi`, `tanpi`
   - Example: `acospi(x) = acos(x) / π`

2. **Math Other Functions (12 functions)** - Straightforward
   - `copysign`, `fdim`, `fract`, `ilogb`, `ldexp`, `logb`, `mad`
   - `maxmag`, `minmag`, `nan`, `nextafter`, `rootn`

3. **Integer Functions (2 functions)**
   - `upsample` - Combine two smaller ints into larger type
   - `clamp` (int version)

---

### Medium Priority - Framework Extensions (48 functions)

1. **Pointer Output Functions (5 functions)** - Extend multi-output support
   - `frexp`, `modf`, `lgamma_r`, `remquo`, `sincos`
   - Low complexity, high value

2. **Half-Precision Math (14 functions)** - Add FP16 support
   - All `half_*` math functions
   - Medium complexity, good coverage boost

3. **Native Math Variants (7 functions)** - Relaxed precision
   - `native_cos`, `native_sin`, `native_tan`, `native_divide`, `native_recip`, `native_powr`
   - May need wider tolerance

4. **Image Functions (~15 functions)** - Add image object support
   - Read/write functions, image queries
   - Medium-high complexity

5. **Half-Precision Vector Load/Store (24 functions)** - Combine with FP16 work
   - All `vload_half*`, `vstore_half*` variants

---

### Low Priority - Not Worth Effort

1. **Work-Item Functions (8 functions)** - Already implicitly tested
2. **Synchronization, Atomics, Collectives** - Cannot test with single work-item
3. **Pipes, Device Enqueue** - Too complex, edge cases

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

**Still Missing (~33 functions):**
- Half-precision vector load/store: 24 functions (vload_half*, vstore_half*, vloada_half*, vstorea_half*)
- Image variants: ~9 functions (read_imagei/ui, write_imagei/ui, 3D variants, samplers)

**Total Testable Functions:** ~236 functions (203 implemented + 33 remaining)
**Overall Coverage:** 203/236 = **86.0%** ✅

### Truly Untestable (Multi-Work-Item Required)
- Synchronization: ~4 functions
- Atomics: ~20 functions
- Async Copy: ~4 functions
- Work-Group Collective: ~20 functions
- Sub-Groups: ~20 functions
- Pipes: ~10 functions
- Device Enqueue: ~10 functions
- **Total untestable:** ~88 functions

**Complete OpenCL Built-in Estimate:** ~330 functions
- **Testable with current framework:** 186 functions (56%)
- **Testable with extensions:** 244 functions (74%)
- **Truly untestable (require multi-work-item):** 86 functions (26%)

**Current implementation:** 115/244 = **47% of all testable functions**

---

## Recent Additions

### ✅ Printf Implementation (November 17, 2025)
- Added 9 printf test functions with 22 test cases
- Tests integer (`%d`), hex (`%x`), float (`%.2f`) formatting
- Width specifiers (`%4d`), string literals, multiple format args
- Verifies return value (0 = success per OpenCL spec)
- Output visible in test logs for manual verification
- All tests passing on Mesa Rusticl

### ✅ Vector Load/Store (November 14-15, 2025)
- Added all standard vload/vstore variants (2, 3, 4, 8, 16)
- 100 test cases covering various offsets and value ranges
- Extended code generator for float8/float16 support
- Fixed `is_vector_type()` to recognize 8 and 16-element vectors
- Added component-wise comparison for 8 and 16-element float vectors

### ✅ Vector Bit Operations (November 14, 2025)
- Added int2/int4 variants for clz, popcount, rotate
- 60 test cases with programmatic verification
- Proper signed int32 handling to avoid narrowing conversion errors

### ✅ Shuffle Functions (November 14, 2025)
- Implemented shuffle() and shuffle2() for vector rearrangement
- 20 test cases covering identity, reverse, rotation, interleaving
- Special handling for mixed-type parameters (float4 data with uint4 mask)

### ✅ Math Function Fixes (November 14, 2025)
- Fixed vector relational functions (`any()`, `all()`) to properly check MSB
- Implemented hybrid tolerance for float comparison (absolute + relative)
- Added domain validation to prevent overflow and invalid inputs
- Corrected rounding semantics (`rint()` vs `round()`)
- Custom test value generators for different function characteristics

---

## Next Steps to Reach 80% Coverage

To reach **80% of all testable functions** (195/244 functions):

### Phase 1: Easy Additions (21 functions) - ~2-3 days
1. Math pi variants (7): `acospi`, `asinpi`, `atanpi`, `atan2pi`, `cospi`, `sinpi`, `tanpi`
2. Math other (12): `copysign`, `fdim`, `fract`, `ilogb`, `ldexp`, `logb`, `mad`, `maxmag`, `minmag`, `nan`, `nextafter`, `rootn`
3. Integer (2): `upsample`, `clamp(int)`

**Coverage after Phase 1:** 136/244 = 55.7%

### Phase 2: Multi-Output Support (5 functions) - ~1-2 days
1. Extend framework for pointer outputs
2. Add: `frexp`, `modf`, `lgamma_r`, `remquo`, `sincos`

**Coverage after Phase 2:** 141/244 = 57.8%

### Phase 3: FP16 Math (14 functions) - ~2-3 days
1. Add `cl_half` support
2. Implement: All `half_*` math functions
3. Adjust tolerances for lower precision

**Coverage after Phase 3:** 155/244 = 63.5%

### Phase 4: Native Math (7 functions) - ~1 day
1. Add: `native_cos`, `native_sin`, `native_tan`, `native_divide`, `native_recip`, `native_powr`

**Coverage after Phase 4:** 162/244 = 66.4%

### Phase 5: FP16 Vector Load/Store (24 functions) - ~2 days
1. Leverage FP16 support from Phase 3
2. Add all `vload_half*`, `vstore_half*` variants

**Coverage after Phase 5:** 186/244 = 76.2%

### Phase 6: Image Functions (15 functions) - ~3-4 days
1. Add image object creation
2. Implement samplers
3. Test read/write/query functions

**Coverage after Phase 6:** 201/244 = **82.4%** ✅

**Total Effort:** ~11-15 days of development to reach 80%+ coverage
