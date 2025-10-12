# Minimal Test Project for Python 3.6 Wheel Building

This is a minimal project to test Python 3.6 wheel building with proper versioning.

## Quick Start

1. Create a new GitHub repository
2. Copy all these files into the repository
3. Push to GitHub
4. Check the Actions tab to see the workflow results

## What This Tests

The workflow tests three different methods for handling version numbers with Python 3.6:

1. **Method 1**: Static version in pyproject.toml
2. **Method 2**: Version in setup.cfg  
3. **Method 3**: Version read from setup.py

Each method will build a wheel and verify that the version is NOT 0.0.0.

## Expected Output

All three methods should produce wheels with proper version numbers like:
- `pyvsag-0.1.dev1+g1234567-cp36-cp36m-linux_x86_64.whl`

NOT:
- `pyvsag-0.0.0-cp36-cp36m-linux_x86_64.whl`
