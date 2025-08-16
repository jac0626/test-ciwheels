import os
import sys
from setuptools import setup, Extension

# pybind11
from pybind11.setup_helpers import Pybind11Extension, build_ext

# Compiler flags for different architectures
extra_compile_args = []

# cibuildwheel sets CIBW_ARCHS variable
# See: https://cibuildwheel.readthedocs.io/en/stable/options/#archs
archs = os.environ.get("CIBW_ARCHS", "").lower()

if "x86_64" in archs:
    # For x86_64, we enable AVX instructions
    extra_compile_args.append("-mavx")
    extra_compile_args.append("-DENABLE_AVX")
elif "aarch64" in archs:
    # For aarch64 (ARM64), we enable NEON instructions
    extra_compile_args.append("-DENABLE_NEON")


ext_modules = [
    Pybind11Extension(
        "ciwheels_example._core", # module name
        ["src/main.cpp"], # source file
        extra_compile_args=extra_compile_args,
        cxx_std=11,
    ),
]

setup(
    name="ciwheels-example",
    version="0.0.1",
    author="Gemini",
    author_email="no-reply@google.com",
    description="A test project for cibuildwheel with C++ extensions",
    long_description="",
    ext_modules=ext_modules,
    cmdclass={"build_ext": build_ext},
    zip_safe=False,
    python_requires=">=3.7",
    packages=["ciwheels_example"],
    package_dir={"": "src"},
)
