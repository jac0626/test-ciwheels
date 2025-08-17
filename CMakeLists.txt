cmake_minimum_required(VERSION 3.15)
project(mkl_example VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# 明确要求 Python 3，不接受 Python 2
find_package(Python3 3.8 REQUIRED COMPONENTS Interpreter Development)
find_package(pybind11 REQUIRED)

# 处理 MKL
# 如果 find_package(MKL CONFIG) 失败，使用手动配置
if(DEFINED ENV{MKLROOT})
    set(MKL_ROOT $ENV{MKLROOT})
endif()

# 尝试使用 MKL 的 CMake 配置
find_package(MKL CONFIG QUIET)

if(NOT MKL_FOUND)
    # 手动配置 MKL
    if(MKL_ROOT)
        set(MKL_INCLUDE_DIR ${MKL_ROOT}/include)
        set(MKL_LIB_DIR ${MKL_ROOT}/lib/intel64)
        
        # 创建 MKL 目标
        add_library(MKL::MKL INTERFACE IMPORTED)
        set_target_properties(MKL::MKL PROPERTIES
            INTERFACE_INCLUDE_DIRECTORIES "${MKL_INCLUDE_DIR}"
            INTERFACE_LINK_DIRECTORIES "${MKL_LIB_DIR}"
            INTERFACE_LINK_LIBRARIES "mkl_intel_lp64;mkl_sequential;mkl_core;pthread;m;dl"
        )
    else()
        message(FATAL_ERROR "MKL not found. Please set MKLROOT environment variable.")
    endif()
endif()

# Create the C++ library
add_library(mkl_ops SHARED
    src/mkl_ops.cpp
)

# Link MKL to the C++ library
target_link_libraries(mkl_ops
    PUBLIC
    MKL::MKL
)

target_include_directories(mkl_ops
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Create Python module - 使用 Python3 变量
pybind11_add_module(_mkl_example 
    python/mkl_wrapper.cpp
)

# 确保使用正确的 Python 包含目录
target_include_directories(_mkl_example
    PRIVATE
    ${Python3_INCLUDE_DIRS}
)

target_link_libraries(_mkl_example
    PRIVATE
    mkl_ops
    MKL::MKL
)

# 设置 RPATH
if(UNIX AND NOT APPLE)
    set_target_properties(_mkl_example PROPERTIES
        INSTALL_RPATH "$ORIGIN"
        BUILD_RPATH "$ORIGIN"
    )
    set_target_properties(mkl_ops PROPERTIES
        INSTALL_RPATH "$ORIGIN:${MKL_LIB_DIR}"
        BUILD_RPATH "${MKL_LIB_DIR}"
    )
elseif(APPLE)
    set_target_properties(_mkl_example PROPERTIES
        INSTALL_RPATH "@loader_path"
        BUILD_RPATH "@loader_path"
    )
    set_target_properties(mkl_ops PROPERTIES
        INSTALL_RPATH "@loader_path:${MKL_LIB_DIR}"
        BUILD_RPATH "${MKL_LIB_DIR}"
    )
endif()

# Install targets
install(TARGETS _mkl_example mkl_ops
    LIBRARY DESTINATION .
    RUNTIME DESTINATION .
)