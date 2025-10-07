from setuptools import setup
from cmake_build_extension import BuildExtension, CMakeExtension

setup(
    ext_modules=[
        CMakeExtension(
            name="my_package_core",
            install_prefix="my_package",
            source_dir="src/my_package",
        )
    ],
    cmdclass={"build_ext": BuildExtension},
    packages=["my_package"],
    package_dir={"my_package": "src/my_package"},
)
