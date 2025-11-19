# Container-Based Testing

This document explains how to build and run the OpenCL test suite in a Fedora Rawhide container using Podman.

## Prerequisites

- Podman installed on your system
- Access to `/dev/dri` devices (for GPU access)

## Quick Start

Run the complete test suite in a container:

```bash
make -f Makefile.container all
```

This will:
1. Build the Fedora Rawhide container image
2. Install all OpenCL dependencies
3. Mount the project source code
4. Build the test suite
5. Run all 1,943 tests

## Available Commands

### Build Container Image

```bash
make -f Makefile.container container-build
```

Builds the container image with all dependencies installed.

### Run Tests (One-Shot)

```bash
make -f Makefile.container container-run
```

Runs a fresh container, builds the project, runs tests, and exits.

### Interactive Development

```bash
# Start container and open shell
make -f Makefile.container container-shell

# Inside container:
cd /workspace
cmake -B build
make -C build -j$(nproc)
RUSTICL_ENABLE=llvmpipe ./build/test_all_opencl_functions
```

### Run Tests in Running Container

```bash
# Start container in background
make -f Makefile.container container-sync

# Run tests
make -f Makefile.container container-test

# Open shell when needed
make -f Makefile.container container-shell
```

### Clean Up

```bash
make -f Makefile.container container-clean
```

Stops and removes the container and image.

## Container Details

### Base Image
- **Image**: `fedora:rawhide`
- **OpenCL Implementation**: Mesa Rusticl
- **Device**: `RUSTICL_ENABLE=iris` (Intel GPU hardware acceleration)
- **Fallback**: Can use `RUSTICL_ENABLE=llvmpipe` for CPU-based software rendering

### Installed Packages
- Build tools: `cmake`, `gcc`, `gcc-c++`, `make`, `git`
- OpenCL headers: `opencl-headers`, `ocl-icd`, `ocl-icd-devel`
- Mesa OpenCL: `mesa-libOpenCL`, `mesa-libOpenCL-devel`
- Mesa drivers: `mesa-dri-drivers`, `mesa-vulkan-drivers`
- Utilities: `clinfo`, `rsync`, `python3`

### Volume Mounting
The project directory is mounted at `/workspace` inside the container using:
- Volume mount with `:Z` flag for SELinux compatibility
- `/dev/dri` device access for GPU support

## Why Container?

### Benefits
1. **Reproducible environment**: Same Fedora Rawhide base across all systems
2. **Isolated dependencies**: No conflicts with host system packages
3. **Easy cleanup**: Remove container when done, no system pollution
4. **CI/CD ready**: Can be used in automated testing pipelines
5. **Latest packages**: Rawhide provides cutting-edge Mesa/Rusticl versions
6. **Hardware acceleration**: Uses Intel GPU (iris driver) for better performance

### Limitations
1. **Intel GPU required**: Default configuration requires Intel GPU on host
   - Use `RUSTICL_ENABLE=llvmpipe` for CPU-based software rendering on any system
2. **Device access**: Requires `/dev/dri` passthrough
3. **GPU sharing**: Container uses host GPU resources

## Troubleshooting

### Container fails to start
```bash
# Check if image exists
podman images | grep opencl-test-suite

# Rebuild if needed
make -f Makefile.container container-build
```

### No OpenCL devices found
```bash
# Inside container, check OpenCL availability
clinfo -l

# Should show (with Intel GPU):
# Platform #0: rusticl
#   Device #0: Mesa Intel(R) UHD Graphics (TGL GT1)

# If no Intel GPU, fallback to software rendering:
RUSTICL_ENABLE=llvmpipe clinfo -l
# Should show:
# Platform #0: rusticl
#   Device #0: llvmpipe
```

### Permission denied on /dev/dri
```bash
# Check host permissions
ls -la /dev/dri

# May need to add user to video/render groups on host
sudo usermod -a -G video,render $USER
```

### Tests fail in container but pass on host
The container uses the same GPU as the host (iris driver), so behavior should be identical. If tests fail in container but pass on host:
1. Check that `/dev/dri` is properly mounted: `ls -la /dev/dri` inside container
2. Verify GPU permissions on host
3. Try rebuilding with `make -f Makefile.container container-clean && make -f Makefile.container container-build`

### No Intel GPU available
If you don't have an Intel GPU, use software rendering instead:
```bash
# Override at runtime
podman run --rm --device=/dev/dri -v $(pwd):/workspace:Z \
  opencl-test-suite:latest \
  /bin/bash -c "RUSTICL_ENABLE=llvmpipe ./build/test_all_opencl_functions"

# Or modify Containerfile to change default from iris to llvmpipe
```

## Advanced Usage

### Custom RUSTICL_ENABLE
```bash
# Run with software rendering (CPU-based, works on any system)
podman run --rm \
  --device=/dev/dri \
  -v $(pwd):/workspace:Z \
  opencl-test-suite:latest \
  /bin/bash -c "cd /workspace && RUSTICL_ENABLE=llvmpipe ./build/test_all_opencl_functions"

# Run with specific GPU (e.g., AMD)
podman run --rm \
  --device=/dev/dri \
  -v $(pwd):/workspace:Z \
  opencl-test-suite:latest \
  /bin/bash -c "cd /workspace && RUSTICL_ENABLE=radeonsi ./build/test_all_opencl_functions"
```

### Debug Build
```bash
make -f Makefile.container container-shell

# Inside container:
cmake -B build -DCMAKE_BUILD_TYPE=Debug
make -C build -j$(nproc)
gdb ./build/test_all_opencl_functions
```

### Run Specific Tests
```bash
podman exec -it opencl-test-suite \
  /bin/bash -c "cd /workspace && \
                RUSTICL_ENABLE=llvmpipe ./build/test_all_opencl_functions --category math"
```

## Integration with CI/CD

Example GitHub Actions workflow:

```yaml
name: Container Tests

on: [push, pull_request]

jobs:
  test:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v3
      - name: Build and Test
        run: |
          make -f Makefile.container container-run
```

Example GitLab CI:

```yaml
test:
  image: quay.io/podman/stable
  script:
    - make -f Makefile.container container-run
```
