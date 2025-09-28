#!/bin/bash
set -e

echo "--- 1. 初始化 Git 子模块 (pybind11) ---"
# --init: 仅在第一次运行时需要
# --recursive: 如果子模块还有子模块，也一并处理
git submodule update --init --recursive

echo "--- 2. 清理旧文件 ---"
rm -rf wheelhouse/ build/

echo "--- 3. 使用 build 工具构建 wheel ---"
# 安装构建前端工具
pip install build
# 运行构建，-w表示只构建wheel，-o指定输出目录
python -m build --wheel --outdir wheelhouse ./python

echo "--- 4. 构建完成！Wheel 包位于 'wheelhouse' 目录中 ---"
ls -l wheelhouse/
