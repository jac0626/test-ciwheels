# src/pyvsag/__init__.py

# 从 C++ 编译的 _pyvsag 模块中导入 Calculator 类
# 用户可以通过 `from pyvsag import Calculator` 直接使用
from ._pyvsag import Calculator

# 定义 `__all__`，以便 `from pyvsag import *` 时只导出 Calculator
__all__ = ["Calculator"]
