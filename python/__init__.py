"""MKL Example Package"""

from ._mkl_example import gemm, eigen, fft, get_mkl_version
import numpy as np

__version__ = "1.0.0"
__all__ = ["gemm", "eigen", "fft", "get_mkl_version", "MatrixOps"]


class MatrixOps:
    """High-level interface for MKL operations"""
    
    @staticmethod
    def matrix_multiply(A, B, alpha=1.0, beta=0.0):
        """
        Compute C = alpha * A @ B + beta * C
        
        Parameters:
        -----------
        A : array-like
            First matrix (m x k)
        B : array-like
            Second matrix (k x n)
        alpha : float
            Scaling factor for A @ B
        beta : float
            Scaling factor for C (initial)
            
        Returns:
        --------
        C : ndarray
            Result matrix (m x n)
        """
        A = np.asarray(A, dtype=np.float64, order='C')
        B = np.asarray(B, dtype=np.float64, order='C')
        return gemm(A, B, alpha, beta)
    
    @staticmethod
    def compute_eigen(matrix):
        """
        Compute eigenvalues and eigenvectors
        
        Parameters:
        -----------
        matrix : array-like
            Square matrix
            
        Returns:
        --------
        eigenvalues : ndarray
            Eigenvalues
        eigenvectors : ndarray
            Eigenvectors (column-wise)
        """
        matrix = np.asarray(matrix, dtype=np.float64, order='C')
        return eigen(matrix)
    
    @staticmethod
    def compute_fft(signal):
        """
        Compute Fast Fourier Transform
        
        Parameters:
        -----------
        signal : array-like
            Input signal
            
        Returns:
        --------
        spectrum : ndarray
            Complex FFT result
        """
        signal = np.asarray(signal, dtype=np.float64)
        return fft(signal)