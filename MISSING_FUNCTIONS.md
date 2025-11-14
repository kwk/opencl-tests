# Missing OpenCL Built-in Function Categories

This document tracks OpenCL C built-in functions not yet covered by the test suite.

## Currently Tested Categories (140 functions, 1,397 tests, 100% passing ✅)

✅ **Math Functions** (51 functions)
✅ **Geometric Functions** (23 functions)
✅ **Common Functions** (12 functions)
✅ **Integer Functions** (26 functions - excludes ctz_int, not supported in Mesa Rusticl)
✅ **Relational Functions** (22 functions)
✅ **Vector Miscellaneous Functions** (2 functions)
✅ **Vector Load/Store Functions** (4 functions)

## Missing Categories

### 1. Vector Data Load and Store Functions ✅ PARTIALLY COMPLETED

**Functions implemented:**
- ✅ `vload2, vload4` - Load float2/float4 from scalar pointer (IMPLEMENTED)
- ✅ `vstore2, vstore4` - Store float2/float4 to scalar pointer (IMPLEMENTED)
- ⚠️ `vload3, vload8, vload16` - Not yet implemented
- ⚠️ `vstore3, vstore8, vstore16` - Not yet implemented
- ⚠️ `vload_half*` - Half precision load functions (requires half support)
- ⚠️ `vstore_half*` - Half precision store functions (requires half support)
- ⚠️ `vloada_half*` - Aligned half load (requires half support)
- ⚠️ `vstorea_half*` - Aligned half store (requires half support)

**Status:** ✅ Partially completed - 4 functions with 40 test cases, all passing
- Implemented vload2_float, vload4_float, vstore2_float, vstore4_float
- Tests cover various offsets and value ranges
- Extended test framework to handle scalar array inputs/outputs and size_t offsets
- Half-precision functions and larger vector sizes (8, 16) can be added later

**Priority:** Medium - Core vload2/vload4/vstore2/vstore4 completed

---

### 2. Synchronization Functions ❌ Not Testable in Current Framework

**Functions:**
- `barrier(CLK_LOCAL_MEM_FENCE | CLK_GLOBAL_MEM_FENCE)` - Work-group barrier
- `mem_fence(cl_mem_fence_flags)` - Memory fence
- `read_mem_fence(cl_mem_fence_flags)` - Read memory fence
- `write_mem_fence(cl_mem_fence_flags)` - Write memory fence
- `atomic_*` operations - Atomic operations (deprecated, use C11 atomics)

**Testability:** ❌ Cannot be tested with current approach
- Requires multiple work-items running concurrently
- Needs work-group coordination
- Barrier behavior only observable with >1 work-item
- Current test framework uses single work-item per test

**Priority:** Low - Requires different test architecture

---

### 3. Async Copy and Prefetch Functions ❌ Not Testable in Current Framework

**Functions:**
- `async_work_group_copy(__local T *dst, const __global T *src, size_t num, event_t event)`
- `async_work_group_strided_copy(...)` - Strided async copy
- `wait_group_events(int num_events, event_t *event_list)` - Wait for events
- `prefetch(const __global T *p, size_t num)` - Prefetch data

**Testability:** ❌ Cannot be tested with current approach
- Requires work-group local memory
- Needs event handling
- Async operations need multiple work-items
- Performance-oriented features

**Priority:** Low - Advanced work-group features

---

### 4. Work-Item Functions ⚠️ Implicitly Used

**Functions:**
- `get_work_dim()` - Number of work dimensions
- `get_global_size(uint dimindx)` - Global work size
- `get_global_id(uint dimindx)` - Global work-item ID (already used in kernels)
- `get_local_size(uint dimindx)` - Local work-group size
- `get_local_id(uint dimindx)` - Local work-item ID
- `get_num_groups(uint dimindx)` - Number of work-groups
- `get_group_id(uint dimindx)` - Work-group ID
- `get_global_offset(uint dimindx)` - Global offset

**Testability:** ⚠️ Already implicitly tested
- `get_global_id(0)` is used in every kernel
- Other functions could be tested with multi-dimensional work-groups
- Would require restructuring test framework

**Priority:** Low - Core functionality already exercised

---

### 5. Miscellaneous Vector Functions ✅ COMPLETED

**Functions:**
- ✅ `shuffle(x, mask)` - Shuffle vector elements (IMPLEMENTED)
- ✅ `shuffle2(x, y, mask)` - Shuffle two vectors (IMPLEMENTED)

**Status:** ✅ Completed - 2 functions with 20 test cases, all passing
- Implemented shuffle_float4 and shuffle2_float4
- Tests cover identity, reverse, rotation, interleaving, and custom patterns

---

### 6. Image Functions ❌ Requires Image Support

**Functions:**
- `read_imagef, read_imagei, read_imageui` - Read from images
- `write_imagef, write_imagei, write_imageui` - Write to images
- `get_image_width, get_image_height, get_image_depth` - Image queries
- `get_image_channel_data_type, get_image_channel_order` - Image metadata

**Testability:** ❌ Requires image objects
- OpenCL images are complex objects
- Require sampler configuration
- Not all devices support images
- Significant additional infrastructure needed

**Priority:** Low - Complex setup required

---

### 7. Extended Bit Operations ✅ COMPLETED

**Functions implemented:**
- ✅ `clz` (count leading zeros) - scalar + int2/int4 vectors
- ✅ `popcount` (population count) - scalar + int2/int4 vectors
- ✅ `rotate` (rotate bits) - scalar + int2/int4 vectors
- ⚠️ `ctz` (count trailing zeros) - not supported in Mesa Rusticl

**Status:** ✅ Completed - Extended with vector variants
- Added clz_int2, clz_int4, popcount_int2, popcount_int4, rotate_int2, rotate_int4
- 60 additional test cases, all passing

---

### 8. Printf (Debug Output) ❌ Not Suitable for Automated Testing

**Functions:**
- `printf(const char *format, ...)` - Formatted output

**Testability:** ❌ Not suitable
- Debug output function
- Output capture is implementation-dependent
- Not designed for verification

**Priority:** Very Low

---

## Recommendations

### High Priority - Should Add

1. ✅ ~~**Shuffle Functions**~~ - COMPLETED
   - ✅ Implemented in `vector_misc_functions` category
   - ✅ Added 20 test cases, all passing

### Medium Priority - Could Add

2. ✅ ~~**Vector Load/Store Functions**~~ - PARTIALLY COMPLETED
   - ✅ Core functions (vload2/4, vstore2/4) implemented
   - ✅ Added to `vector_load_store_functions` category
   - ✅ 40 test cases added, all passing
   - ⚠️ Could extend with vload3/8/16 and half-precision variants

3. ✅ ~~**Extended Bit Operation Variants**~~ - COMPLETED
   - ✅ Added vector variants (int2/int4) for clz, popcount, rotate
   - ✅ 60 test cases added, all passing

### Low Priority - Current Framework Cannot Support

4. **Synchronization Functions** - Requires multi-work-item tests
5. **Async Copy Functions** - Requires work-group architecture
6. **Image Functions** - Requires image object support

---

## Current Test Coverage

**Total Functions Tested:** 140 functions
**Total Test Cases:** 1,397 tests
**Test Pass Rate:** 100% ✅ (1397/1397 passing)
**Estimated Missing (Testable):** ~55-75 functions
**Estimated Missing (Not Testable):** ~30-40 functions

**Overall OpenCL Built-in Function Coverage:** ~65-70% (of testable functions)

## Recent Improvements (Achieved 100% Pass Rate)

The test suite has been extensively validated and improved:
- ✅ **Vector Load/Store** (Jan 2025) - Added vload2/4 and vstore2/4 functions with 40 test cases
- ✅ **Vector Bit Operations** (Jan 2025) - Added int2/int4 variants for clz, popcount, rotate
- ✅ **Shuffle Functions** (Jan 2025) - Added shuffle() and shuffle2() for vector element rearrangement
- Fixed vector relational functions (`any()`, `all()`) to properly check MSB
- Implemented hybrid tolerance for float comparison (absolute + relative)
- Added domain validation to prevent overflow and invalid inputs
- Corrected rounding semantics (`rint()` vs `round()`)
- Fixed all bitwise operation test data
- Custom test value generators for different function characteristics
- Extended test framework to support scalar array inputs/outputs and size_t offset parameters
