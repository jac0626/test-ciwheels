# MKL Example Package

A Python package demonstrating C++ integration with Intel MKL using dynamic linking.

## Features

- Matrix multiplication (GEMM)
- Eigenvalue/eigenvector computation
- Fast Fourier Transform (FFT)
- Dynamic linking to MKL (not bundled in wheel)

## Installation

### Prerequisites

Install Intel MKL on your system:

**Linux:**
```bash
# Using apt (Ubuntu/Debian)
wget -O- https://apt.repos.intel.com/intel-gpg-keys/GPG-PUB-KEY-INTEL-SW-PRODUCTS.PUB | gpg --dearmor | sudo tee /usr/share/keyrings/oneapi-archive-keyring.gpg > /dev/null
echo "deb [signed-by=/usr/share/keyrings/oneapi-archive-keyring.gpg] https://apt.repos.intel.com/oneapi all main" | sudo tee /etc/apt/sources.list.d/oneAPI.list
sudo apt update
sudo apt install intel-oneapi-mkl-devel

# Or using yum (RHEL/CentOS)
sudo yum-config-manager --add-repo https://yum.repos.intel.com/mkl/setup/intel-mkl.repo
sudo yum install intel-mkl