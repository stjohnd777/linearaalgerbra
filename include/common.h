#pragma once

#include "Vector.h"


namespace dsj {

    template<typename T, size_t N>
    class Vector;

    template<typename T, size_t N>
    Vector<T, N> add(const Vector<T, N> &lhs, const Vector<T, N> &rhs) {
        Vector<T, N> ret; // Initialize to zero
        for (size_t i = 0; i < N; ++i) {
            ret[i] = lhs[i] + rhs[i]; // Multiply element-wise and accumulate
        }
        return ret;
    }

    template<typename T, size_t N>
    Vector<T, N> sub(const Vector<T, N> &lhs, const Vector<T, N> &rhs) {
        Vector<T, N> ret; // Initialize to zero
        for (size_t i = 0; i < N; ++i) {
            ret[i] = lhs[i] - rhs[i]; // Multiply element-wise and accumulate
        }
        return ret;
    }

    template<typename T, size_t N>
    T dot_product(const Vector<T, N> &lhs, const Vector<T, N> &rhs) {
        T result = T(0); // Initialize to zero
        for (size_t i = 0; i < N; ++i) {
            result += lhs[i] * rhs[i]; // Multiply element-wise and accumulate
        }
        return result;
    }

    template<typename T, size_t N>
    Vector<T, N> scale(const Vector<T, N> &vec, const T &scalar) {
        Vector<T, N> result; // Create a new Vector to store the result
        for (size_t i = 0; i < N; ++i) {
            result[i] = vec[i] * scalar; // Scale each component
        }
        return result;
    }

    template<typename T, size_t N>
    Vector<T, N> scale(const T &scalar, const Vector<T, N> &vec) {
        Vector<T, N> result; // Create a new Vector to store the result
        for (size_t i = 0; i < N; ++i) {
            result[i] = vec[i] * scalar; // Scale each component
        }
        return result;
    }

}