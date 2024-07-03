# Use an official Ubuntu base image
FROM ubuntu:22.04

# Set build arguments for HDF5 and Python versions with default values
ARG HDF5_VERSION=1.12.1
ARG PYTHON_VERSION=3.9.7

# Environment variables to avoid prompts during installation
ENV DEBIAN_FRONTEND=noninteractive

# Install dependencies
RUN apt-get update && \
    apt-get install -y \
    build-essential \
    curl \
    git \
    wget \
    zlib1g-dev \
    libssl-dev \
    libreadline-dev \
    libffi-dev \
    libbz2-dev \
    libsqlite3-dev \
    libncurses5-dev \
    libgdbm-dev \
    libnss3-dev \
    liblzma-dev \
    tk-dev \
    uuid-dev

# Install pyenv for managing Python versions
RUN curl https://pyenv.run | bash

# Set environment variables for pyenv
ENV PATH="/root/.pyenv/bin:/root/.pyenv/shims:/root/.pyenv/versions/${PYTHON_VERSION}/bin:$PATH"
ENV PYENV_ROOT="/root/.pyenv"

# Install the specified Python version
RUN /root/.pyenv/bin/pyenv install ${PYTHON_VERSION} && \
    /root/.pyenv/bin/pyenv global ${PYTHON_VERSION}

# Set the working directory
WORKDIR /tmp

# Download and install the specified version of HDF5
RUN wget https://support.hdfgroup.org/ftp/HDF5/releases/hdf5-${HDF5_VERSION}/hdf5-${HDF5_VERSION}/src/hdf5-${HDF5_VERSION}.tar.gz && \
    tar -xzf hdf5-${HDF5_VERSION}.tar.gz && \
    cd hdf5-${HDF5_VERSION} && \
    ./configure --prefix=/usr/local && \
    make -j$(nproc) && \
    make install && \
    cd .. && \
    rm -rf hdf5-${HDF5_VERSION} hdf5-${HDF5_VERSION}.tar.gz

# Update the shared library cache
RUN ldconfig

# Set default command
CMD ["bash"]
