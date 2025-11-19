FROM fedora:rawhide

# Install OpenCL development dependencies and build tools
RUN dnf update -y && \
    dnf install -y \
    cmake \
    gcc \
    gcc-c++ \
    make \
    git \
    opencl-headers \
    ocl-icd \
    ocl-icd-devel \
    mesa-libOpenCL \
    mesa-libOpenCL-devel \
    clinfo \
    rsync \
    python3 \
    && dnf clean all

# Install Mesa Rusticl OpenCL implementation
RUN dnf install -y \
    mesa-dri-drivers \
    mesa-vulkan-drivers \
    && dnf clean all

# Set up environment for Rusticl
# Use iris for Intel GPU hardware acceleration (requires Intel GPU on host)
# Alternative: ENV RUSTICL_ENABLE=llvmpipe (CPU-based software rendering)
ENV RUSTICL_ENABLE=iris

# Create working directory
WORKDIR /workspace

# Default command
CMD ["/bin/bash"]
