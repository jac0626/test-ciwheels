#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>
#include <pybind11/complex.h>
#include "mkl_ops.h"

namespace py = pybind11;

PYBIND11_MODULE(_mkl_example, m) {
    m.doc() = "MKL operations wrapper";
    
    m.def("gemm", [](py::array_t<double> A, py::array_t<double> B,
                     double alpha, double beta) {
        auto buf_A = A.request();
        auto buf_B = B.request();
        
        if (buf_A.ndim != 2 || buf_B.ndim != 2) {
            throw std::runtime_error("Input arrays must be 2D");
        }
        
        int m = buf_A.shape[0];
        int k = buf_A.shape[1];
        int n = buf_B.shape[1];
        
        if (buf_B.shape[0] != k) {
            throw std::runtime_error("Matrix dimensions don't match for multiplication");
        }
        
        std::vector<double> A_vec(static_cast<double*>(buf_A.ptr),
                                  static_cast<double*>(buf_A.ptr) + m * k);
        std::vector<double> B_vec(static_cast<double*>(buf_B.ptr),
                                  static_cast<double*>(buf_B.ptr) + k * n);
        
        auto result = mkl_ops::MatrixOperations::gemm(A_vec, B_vec, m, n, k, alpha, beta);
        
        return py::array_t<double>({m, n}, result.data());
    }, "Matrix multiplication using MKL",
       py::arg("A"), py::arg("B"), py::arg("alpha") = 1.0, py::arg("beta") = 0.0);
    
    m.def("eigen", [](py::array_t<double> matrix) {
        auto buf = matrix.request();
        
        if (buf.ndim != 2) {
            throw std::runtime_error("Input must be a 2D square matrix");
        }
        
        int n = buf.shape[0];
        if (buf.shape[1] != n) {
            throw std::runtime_error("Matrix must be square");
        }
        
        std::vector<double> mat_vec(static_cast<double*>(buf.ptr),
                                    static_cast<double*>(buf.ptr) + n * n);
        
        auto [eigenvalues, eigenvectors] = mkl_ops::MatrixOperations::eigen(mat_vec, n);
        
        return std::make_tuple(
            py::array_t<double>(n, eigenvalues.data()),
            py::array_t<double>({n, n}, eigenvectors.data())
        );
    }, "Compute eigenvalues and eigenvectors");
    
    m.def("fft", [](py::array_t<double> input) {
        auto buf = input.request();
        
        if (buf.ndim != 1) {
            throw std::runtime_error("Input must be 1D array");
        }
        
        std::vector<double> input_vec(static_cast<double*>(buf.ptr),
                                      static_cast<double*>(buf.ptr) + buf.shape[0]);
        
        auto result = mkl_ops::MatrixOperations::fft(input_vec);
        
        return py::array_t<std::complex<double>>(result.size(), result.data());
    }, "Compute FFT using MKL");
    
    m.def("get_mkl_version", &mkl_ops::MatrixOperations::get_mkl_version,
          "Get MKL version string");
}