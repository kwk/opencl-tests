// OpenCL Image Functions
// Test image read, write, and query operations
// Reference: https://registry.khronos.org/OpenCL/specs/3.0-unified/html/OpenCL_C.html#image-functions

// ===== Image Query Functions =====
// These functions query properties of image objects

__kernel void test_get_image_width(__read_only image2d_t image,
                                   __global int *output,
                                   const unsigned int count) {
  int i = get_global_id(0);
  if (i < count)
    output[i] = get_image_width(image);
}

__kernel void test_get_image_height(__read_only image2d_t image,
                                    __global int *output,
                                    const unsigned int count) {
  int i = get_global_id(0);
  if (i < count)
    output[i] = get_image_height(image);
}

__kernel void test_get_image_channel_data_type(__read_only image2d_t image,
                                                __global int *output,
                                                const unsigned int count) {
  int i = get_global_id(0);
  if (i < count)
    output[i] = get_image_channel_data_type(image);
}

__kernel void test_get_image_channel_order(__read_only image2d_t image,
                                            __global int *output,
                                            const unsigned int count) {
  int i = get_global_id(0);
  if (i < count)
    output[i] = get_image_channel_order(image);
}

// ===== Image Read Functions =====
// These functions read pixel data from image objects

__kernel void test_read_imagef_2d(__read_only image2d_t image,
                                  __global const int *x_coords,
                                  __global const int *y_coords,
                                  __global float4 *output,
                                  const unsigned int count) {
  int i = get_global_id(0);
  if (i < count) {
    int2 coord = (int2)(x_coords[i], y_coords[i]);
    output[i] = read_imagef(image, coord);
  }
}

// ===== Image Write Functions =====
// These functions write pixel data to image objects

__kernel void test_write_imagef_2d(__write_only image2d_t image,
                                   __global const int *x_coords,
                                   __global const int *y_coords,
                                   __global const float4 *colors,
                                   const unsigned int count) {
  int i = get_global_id(0);
  if (i < count) {
    int2 coord = (int2)(x_coords[i], y_coords[i]);
    write_imagef(image, coord, colors[i]);
  }
}
