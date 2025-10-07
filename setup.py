from setuptools import setup
import pybind11
from cmake_build_extension import BuildExtension, CMakeExtension

setup(
    ext_modules=[
        CMakeExtension(
            name="my_package_core",
            install_prefix="my_package",
            source_dir="src/my_package",
            # Pass pybind11's cmake dir to cmake
            cmake_configure_options=[f"-Dpybind11_DIR={pybind11.get_cmake_dir()}"],
        )
    ],
    cmdclass={"build_ext": BuildExtension},
    packages=["my_package"],
    package_dir={"my_package": "src/my_package"},
)