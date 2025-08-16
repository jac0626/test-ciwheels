# C++ Wheels with NEON/AVX Example

This project demonstrates how to build Python wheels for a C++ extension that has platform-specific optimizations (AVX for x86_64, NEON for aarch64) using `cibuildwheel`.

## How it Works

The `setup.py` script checks for the `CIBW_ARCHS` environment variable, which is set by `cibuildwheel` during the build process. Based on the target architecture, it passes specific compiler flags (`-mavx` or `-DENABLE_NEON`) to the C++ compiler.

The C++ code (`src/main.cpp`) uses preprocessor directives (`#ifdef`) to include the correct headers and compile the optimized code for the target platform. A scalar implementation is used as a fallback.

## GitHub Actions

The included GitHub Actions workflow in `.github/workflows/build_wheels.yml` will automatically build the wheels for Linux (`x86_64` and `aarch64`) using the `manylinux2014` image every time code is pushed to the `main` branch or a pull request is created.

## Usage

Once the wheel is installed, you can use it in Python like this:

```python
import numpy as np
from ciwheels_example import vector_add, get_implementation

# Check which version was compiled
print(f"Using implementation: {get_implementation()}")

a = np.arange(10, dtype=np.float32)
b = np.arange(10, dtype=np.float32) * 2

result = vector_add(a.tolist(), b.tolist())
print(f"{a.tolist()} + {b.tolist()} = {result}")
```
