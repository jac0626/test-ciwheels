# src/pyvsag/cpp_src/CMakeLists.txt
cmake_minimum_required(VERSION 3.15)
project(cpp_core CXX)

# --- 1. 定义你的核心 C++ 库 ---
# This is our core library
add_library(core_logic STATIC vsag.cpp)
target_include_directories(core_logic PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(core_logic PRIVATE cxx_std_17)


# --- 2. 配置 Pybind11 ---
# 使用 FetchContent 自动下载和配置 pybind11，使项目自包含
include(FetchContent)
FetchContent_Declare(
  pybind11
  GIT_REPOSITORY https://github.com/pybind/pybind11.git
  GIT_TAG        v2.11.1 # 建议固定到一个稳定的版本
)
FetchContent_MakeAvailable(pybind11)


# --- 3. 创建 Python 扩展模块 ---
# 使用 pybind11_add_module 创建 Python 模块
# The module name must match the one in main.cpp
pybind11_add_module(_pyvsag MODULE main.cpp)

# 链接你的核心 C++ 库
target_link_libraries(_pyvsag PRIVATE core_logic pybind11::module)


# --- 4. 安装规则 (至关重要) ---
# 定义安装规则，告诉 scikit-build-core 如何将编译好的 .so/.pyd 文件打包到 wheel 中
# 目标路径必须是 Python 包的内部路径
install(
  TARGETS _pyvsag
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/pyvsag
)
