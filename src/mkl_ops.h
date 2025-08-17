#ifndef MKL_OPS_H
#define MKL_OPS_H

#include <vector>
#include <mkl.h>

namespace mkl_ops {

class MatrixOperations {
public:
    // Matrix multiplication using MKL
    static std::vector<double> gemm(
        const std::vector<double>& A,
        const std::vector<double>& B,
        int m, int n, int k,
        double alpha = 1.0,
        double beta = 0.0
    );
    
    // Eigenvalue computation
    static std::pair<std::vector<double>, std::vector<double>> eigen(
        const std::vector<double>& matrix,
        int n
    );
    
    // FFT operation
    static std::vector<std::complex<double>> fft(
        const std::vector<double>& input
    );
    
    // Get MKL version
    static std::string get_mkl_version();
};

} // namespace mkl_ops

#endif // MKL_OPS_H