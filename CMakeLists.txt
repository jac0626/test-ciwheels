cmake_minimum_required(VERSION 3.15)
project(mkl_example VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Find Python and pybind11
find_package(Python COMPONENTS Interpreter Development REQUIRED)
find_package(pybind11 REQUIRED)

# Find MKL
set(MKL_LINK dynamic)
set(MKL_THREADING sequential)
find_package(MKL CONFIG REQUIRED)

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

# Create Python module
pybind11_add_module(_mkl_example 
    python/mkl_wrapper.cpp
)

target_link_libraries(_mkl_example
    PRIVATE
    mkl_ops
    MKL::MKL
)

# Set RPATH for Linux/macOS
if(UNIX AND NOT APPLE)
    set_target_properties(_mkl_example PROPERTIES
        INSTALL_RPATH "$ORIGIN"
        BUILD_RPATH "$ORIGIN"
    )
elseif(APPLE)
    set_target_properties(_mkl_example PROPERTIES
        INSTALL_RPATH "@loader_path"
        BUILD_RPATH "@loader_path"
    )
endif()

# Install targets
install(TARGETS _mkl_example mkl_ops
    LIBRARY DESTINATION .
    RUNTIME DESTINATION .
)