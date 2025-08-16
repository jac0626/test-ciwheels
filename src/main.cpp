#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <vector>
#include <stdexcept>

// Platform-specific headers
#if defined(ENABLE_NEON)
#include <arm_neon.h>
#elif defined(ENABLE_AVX)
#include <immintrin.h>
#endif

namespace py = pybind11;

// Function to get the compiled implementation type
const char* get_implementation() {
#if defined(ENABLE_NEON)
    return "NEON";
#elif defined(ENABLE_AVX)
    return "AVX";
#else
    return "Scalar";
#endif
}

// Main vector addition function
std::vector<float> vector_add(const std::vector<float>& a, const std::vector<float>& b) {
    if (a.size() != b.size()) {
        throw std::runtime_error("Input vectors must be of the same size");
    }

    std::vector<float> result(a.size());
    size_t size = a.size();

#if defined(ENABLE_AVX)
    // AVX implementation (processes 8 floats at a time)
    size_t i = 0;
    for (; i + 7 < size; i += 8) {
        __m256 va = _mm256_loadu_ps(&a[i]);
        __m256 vb = _mm256_loadu_ps(&b[i]);
        __m256 vr = _mm256_add_ps(va, vb);
        _mm256_storeu_ps(&result[i], vr);
    }
    // Process remaining elements
    for (; i < size; ++i) {
        result[i] = a[i] + b[i];
    }
#elif defined(ENABLE_NEON)
    // NEON implementation (processes 4 floats at a time)
    size_t i = 0;
    for (; i + 3 < size; i += 4) {
        float32x4_t va = vld1q_f32(&a[i]);
        float32x4_t vb = vld1q_f32(&b[i]);
        float32x4_t vr = vaddq_f32(va, vb);
        vst1q_f32(&result[i], vr);
    }
    // Process remaining elements
    for (; i < size; ++i) {
        result[i] = a[i] + b[i];
    }
#else
    // Scalar implementation (fallback)
    for (size_t i = 0; i < size; ++i) {
        result[i] = a[i] + b[i];
    }
#endif

    return result;
}

PYBIND11_MODULE(_core, m) {
    m.doc() = "pybind11 example plugin with NEON/AVX support";

    m.def("vector_add", &vector_add, "Adds two vectors of floats",
          py::arg("a"), py::arg("b"));

    m.def("get_implementation", &get_implementation, "Returns the compiled implementation type (Scalar, NEON, or AVX)");
}
