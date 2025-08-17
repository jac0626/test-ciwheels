#include "mkl_ops.h"
#include <mkl.h>
#include <mkl_dfti.h>
#include <complex>
#include <stdexcept>
#include <sstream>

namespace mkl_ops {

std::vector<double> MatrixOperations::gemm(
    const std::vector<double>& A,
    const std::vector<double>& B,
    int m, int n, int k,
    double alpha, double beta) {
    
    std::vector<double> C(m * n, 0.0);
    
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
                m, n, k, alpha,
                A.data(), k,
                B.data(), n,
                beta, C.data(), n);
    
    return C;
}

std::pair<std::vector<double>, std::vector<double>> MatrixOperations::eigen(
    const std::vector<double>& matrix, int n) {
    
    std::vector<double> eigenvalues_real(n);
    std::vector<double> eigenvalues_imag(n);
    std::vector<double> eigenvectors(n * n);
    std::vector<double> work_matrix = matrix;
    
    int lwork = -1;
    double work_query;
    int info;
    
    // Query optimal workspace
    LAPACKE_dgeev_work(LAPACK_ROW_MAJOR, 'N', 'V',
                       n, work_matrix.data(), n,
                       eigenvalues_real.data(), eigenvalues_imag.data(),
                       nullptr, n, eigenvectors.data(), n,
                       &work_query, lwork);
    
    lwork = static_cast<int>(work_query);
    std::vector<double> work(lwork);
    
    // Compute eigenvalues and eigenvectors
    info = LAPACKE_dgeev_work(LAPACK_ROW_MAJOR, 'N', 'V',
                              n, work_matrix.data(), n,
                              eigenvalues_real.data(), eigenvalues_imag.data(),
                              nullptr, n, eigenvectors.data(), n,
                              work.data(), lwork);
    
    if (info != 0) {
        throw std::runtime_error("Eigenvalue computation failed");
    }
    
    return {eigenvalues_real, eigenvectors};
}

std::vector<std::complex<double>> MatrixOperations::fft(
    const std::vector<double>& input) {
    
    MKL_LONG n = input.size();
    std::vector<std::complex<double>> output(n);
    
    DFTI_DESCRIPTOR_HANDLE descriptor;
    MKL_LONG status;
    
    status = DftiCreateDescriptor(&descriptor, DFTI_DOUBLE, DFTI_REAL, 1, n);
    if (status != DFTI_NO_ERROR) {
        throw std::runtime_error("FFT descriptor creation failed");
    }
    
    status = DftiSetValue(descriptor, DFTI_PLACEMENT, DFTI_NOT_INPLACE);
    status = DftiCommitDescriptor(descriptor);
    
    std::vector<double> input_copy = input;
    status = DftiComputeForward(descriptor, input_copy.data(), output.data());
    
    DftiFreeDescriptor(&descriptor);
    
    if (status != DFTI_NO_ERROR) {
        throw std::runtime_error("FFT computation failed");
    }
    
    return output;
}

std::string MatrixOperations::get_mkl_version() {
    MKLVersion version;
    mkl_get_version(&version);
    
    std::stringstream ss;
    ss << "MKL " << version.MajorVersion << "."
       << version.MinorVersion << "."
       << version.UpdateVersion;
    return ss.str();
}

} // namespace mkl_ops