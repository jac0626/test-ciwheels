cmake_minimum_required(VERSION 3.18)
project(my_package_core LANGUAGES CXX)

find_package(pybind11 CONFIG REQUIRED)

pybind11_add_module(${PROJECT_NAME} SHARED add.cpp)
