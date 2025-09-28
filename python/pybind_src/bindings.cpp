#include <pybind11/pybind11.h>
#include "vsag.h" // 包含您的核心库头文件

namespace py = pybind11;

PYBIND11_MODULE(_pyvsag, m) {
    m.doc() = "A simple C++ calculator binding for Python";

    py::class_<Calculator>(m, "Calculator")
        .def(py::init<>()) // 暴露构造函数
        .def("add", &Calculator::add, "A function that adds two integers"); // 暴露add方法
}