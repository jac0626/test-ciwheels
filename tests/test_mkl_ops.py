import pytest
import numpy as np
import mkl_example


def test_matrix_multiply():
    """Test matrix multiplication"""
    A = np.random.rand(3, 4)
    B = np.random.rand(4, 5)
    
    # Using MKL
    C_mkl = mkl_example.gemm(A, B)
    
    # Using NumPy for comparison
    C_numpy = A @ B
    
    np.testing.assert_allclose(C_mkl, C_numpy, rtol=1e-10)


def test_eigenvalues():
    """Test eigenvalue computation"""
    # Create a symmetric matrix for predictable eigenvalues
    A = np.array([[4, -2], [-2, 1]], dtype=np.float64)
    
    eigenvalues, eigenvectors = mkl_example.eigen(A)
    
    # Verify A @ v = λ @ v for each eigenpair
    for i in range(len(eigenvalues)):
        v = eigenvectors[:, i]
        Av = A @ v
        lambda_v = eigenvalues[i] * v
        np.testing.assert_allclose(Av, lambda_v, rtol=1e-10)


def test_fft():
    """Test FFT computation"""
    # Create a simple signal
    t = np.linspace(0, 1, 128)
    signal = np.sin(2 * np.pi * 5 * t) + np.sin(2 * np.pi * 10 * t)
    
    # Compute FFT using MKL
    spectrum_mkl = mkl_example.fft(signal)
    
    # Compare with NumPy FFT
    spectrum_numpy = np.fft.rfft(signal)
    
    # The results might be scaled differently, so compare normalized magnitudes
    np.testing.assert_allclose(
        np.abs(spectrum_mkl[:len(spectrum_numpy)]),
        np.abs(spectrum_numpy),
        rtol=1e-10
    )


def test_mkl_version():
    """Test MKL version retrieval"""
    version = mkl_example.get_mkl_version()
    assert isinstance(version, str)
    assert "MKL" in version


def test_matrix_ops_class():
    """Test high-level MatrixOps interface"""
    ops = mkl_example.MatrixOps()
    
    # Test matrix multiply
    A = np.random.rand(2, 3)
    B = np.random.rand(3, 4)
    C = ops.matrix_multiply(A, B)
    assert C.shape == (2, 4)
    
    # Test eigen
    matrix = np.array([[1, 2], [2, 1]], dtype=np.float64)
    eigenvalues, eigenvectors = ops.compute_eigen(matrix)
    assert len(eigenvalues) == 2
    assert eigenvectors.shape == (2, 2)
    
    # Test FFT
    signal = np.random.rand(64)
    spectrum = ops.compute_fft(signal)
    assert len(spectrum) == 64