cmake_minimum_required(VERSION 3.10)
project(OpenCLHelloWorld LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define OpenCL target version to suppress cl_version.h warning
add_compile_definitions(CL_TARGET_OPENCL_VERSION=300)

find_package(OpenCL REQUIRED)

if(NOT OpenCL_FOUND)
    message(FATAL_ERROR "OpenCL not found. Please install OpenCL development libraries:\n"
            "Fedora/RHEL: sudo dnf install opencl-headers OpenCL-ICD-Loader-devel pocl\n"
            "Ubuntu/Debian: sudo apt-get install opencl-headers ocl-icd-opencl-dev pocl-opencl-icd\n"
            "Arch: sudo pacman -S opencl-headers ocl-icd pocl")
endif()

include_directories(${OpenCL_INCLUDE_DIRS})

# Copy kernel files to build directory
file(COPY ${CMAKE_SOURCE_DIR}/kernels DESTINATION ${CMAKE_BINARY_DIR})

# Find Python 3 for code generation
find_package(Python3 COMPONENTS Interpreter REQUIRED)

# Generate test code from JSON test data
set(GENERATED_TESTS_FILE ${CMAKE_SOURCE_DIR}/src/generated_tests.cpp)
file(GLOB TEST_DATA_FILES ${CMAKE_SOURCE_DIR}/test_data/*.json)

add_custom_command(
    OUTPUT ${GENERATED_TESTS_FILE}
    COMMAND ${Python3_EXECUTABLE} ${CMAKE_SOURCE_DIR}/generate_tests.py
    DEPENDS
        ${CMAKE_SOURCE_DIR}/generate_tests.py
        ${TEST_DATA_FILES}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Generating C++ test code from JSON test data..."
)

# Create a custom target for the generated file
add_custom_target(generate_tests DEPENDS ${GENERATED_TESTS_FILE})

# Comprehensive OpenCL built-in functions test suite
# Note: generated_tests.cpp is included via #include in test_all_opencl_functions.cpp,
# so we only add it as a dependency, not as a source file to compile separately
add_executable(test_all_opencl_functions
    src/test_all_opencl_functions.cpp
    src/test_image_functions.cpp)
add_dependencies(test_all_opencl_functions generate_tests)
target_link_libraries(test_all_opencl_functions ${OpenCL_LIBRARIES})
