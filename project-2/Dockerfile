FROM ubuntu:26.10

# Prevent interactive prompts during installation
ENV DEBIAN_FRONTEND=noninteractive

# Install compiler toolchain, Valgrind and GDB
RUN apt-get update && apt-get install -y \
    build-essential \
    valgrind \
    gdb \
    && rm -rf /var/lib/apt/lists/*

# Set the working directory inside the contaienr
WORKDIR /workspace

# Keep the container alive or drop straight into bash
CMD ["/bin/bash"]
