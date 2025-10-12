from setuptools import setup, Extension

setup(
    ext_modules=[Extension('pyvsag._hello', sources=['../src/hello.c'])],
    zip_safe=False,
)
