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
ENV RUSTICL_ENABLE=llvmpipe

# Create working directory
WORKDIR /workspace

# Default command
CMD ["/bin/bash"]
