# 构建与测试

## 先决条件

- Python (3.6+)
- C++ 编译器 (GCC, Clang, or MSVC)
- CMake (3.15+)
- Git

## 本地开发

1.  **克隆仓库**
    ```bash
    git clone <your-repo-url>
    cd test-ciwheels
    ```

2.  **创建并激活虚拟环境**
    ```bash
    python -m venv venv
    source venv/bin/activate  # on Linux/macOS
    # venv\Scripts\activate    # on Windows
    ```

3.  **可编辑模式安装**
    此命令会编译 C++ 代码并在当前项目内安装包，便于开发和调试。
    ```bash
    pip install -e .
    ```

4.  **运行测试**
    创建一个 `test.py` 文件：
    ```python
    from pyvsag import Calculator

    calc = Calculator()
    result = calc.add(10, 22)
    print(f"10 + 22 = {result}")
    assert result == 32
    print("测试成功!")
    ```
    然后运行：
    ```bash
    python test.py
    ```

## 构建 Wheel 包用于分发

```bash
pip wheel . --wheel-dir dist
```
