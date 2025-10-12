from setuptools import setup, Extension
import os

# get the absolute path to the C source file
here = os.path.abspath(os.path.dirname(__file__))
source_file = os.path.join(here, '..', 'src', 'hello.c')

setup(
    ext_modules=[Extension('pyvsag._hello', sources=[source_file])],
    zip_safe=False,
)