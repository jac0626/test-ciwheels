# CMakeLists.txt
cmake_minimum_required(VERSION 3.15)
project(vsag_project CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- 1. 定义您的核心C++库 ---
add_library(vsag cpp_src/vsag.cpp)
target_include_directories(vsag PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/cpp_src)


# --- 2. 添加 pybind11 并创建Python绑定 ---
# 将pybind11作为子目录添加
add_subdirectory(extern/pybind11)

# 查找Python解释器和开发库
find_package(Python3 REQUIRED COMPONENTS Interpreter Development.Module)

# 使用pybind11创建一个Python模块
pybind11_add_module(
    _pyvsag # 模块名
    python/pybind_src/bindings.cpp # 绑定代码源文件
)

# 链接您的核心库到Python模块
target_link_libraries(_pyvsag PRIVATE vsag)

# --- 3. 安装构建好的模块 ---
# 这一步至关重要：它告诉CMake在安装时，将编译好的.so/.pyd文件
# 放到Python包的正确位置，以便打包工具可以找到它。
install(
    TARGETS _pyvsag
    LIBRARY DESTINATION pyvsag
)
