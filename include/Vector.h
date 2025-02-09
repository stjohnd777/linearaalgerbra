#pragma once
#include <array>
#include <algorithm>
#include <cmath>
#include <ostream>
#include <tuple>
#include <memory>
#include <numeric>
#include <stdexcept>
#include <initializer_list>
#include <stdexcept>
#include <cstring>
#include <string>

#include "RowVector.h"
#include "ColVector.h"

template <typename T , size_t N> class RowVector ;
template <typename T , size_t N> class ColVector ;

class VectorNormalizationException : public std::runtime_error {
public:
    VectorNormalizationException()
            : std::runtime_error("Cannot normalize a Zero-Length Vector") {}
};

class DivideByZeroException : public std::runtime_error {
public:
    DivideByZeroException()
            : std::runtime_error("Division by Zero is not allowed") {}
};

class InvalidDimensionException : public std::runtime_error {
public:
    InvalidDimensionException()
            : std::runtime_error("Invalid dimension for the current operation") {}
};

/**
 * vector independent from viewed as row or column
 * vector. This class models such vectors.
 *
 * This version uses composition, encapsulating on `std::array`
 * as a private member so we retain full control over the
 * interface.
 *
 * Example usage:

    #include <iostream>
    #include "Vector.h"

    int main() {
        Vector<double, 3> v1 = Vector<double, 3>::from({1.0, 2.0, 3.0});
        Vector<double, 3> v2 = Vector<double, 3>::zero();

        v1 += v1;  // In-place addition
        std::cout << "v1: " << v1 << std::endl;

        auto dot = v1 * v1;  // Dot product
        std::cout << "Dot product: " << dot << std::endl;

        v1.normalize();  // Normalize in-place
        std::cout << "Normalized: " << v1 << std::endl;

        auto v_proj = v1.project_onto(Vector<double, 3>::from({0.0, 1.0, 0.0}));
        std::cout << "Projection: " << v_proj << std::endl;

        return 0;
    }
 * ```
 * @tparam T The type of the vector's elements (e.g., double, int).
 * @tparam N The number of dimensions.
 */
template<typename T, size_t N>
class Vector {
protected:
    std::array<T, N> data;  // Composition: Internal storage

public:
    /** Default Constructor: Initializes to zero vector */
    Vector() {
        data.fill(T(0));  // Default: Zero initialization
    }

    /** Constructor with initializer list */
    Vector(const std::initializer_list<T>& list) {
        if (list.size() != N) {
            throw std::invalid_argument("Initializer list must have exactly " + std::to_string(N) + " elements.");
        }
        std::copy(list.begin(), list.end(), data.begin());
    }

    /** Static initializer for constructing from an initializer list */
    static Vector<T, N> from(std::initializer_list<T> list) {
        return Vector(list);
    }

    RowVector<T, N> as_row_vector() const {
        RowVector<T, N> rowVector;
        for (size_t i = 0; i < N; ++i) {
            rowVector[i] = this->operator[](i);
        }
        return rowVector;
    }

    ColVector<T, N> as_col_vector() const {
        ColVector<T, N> colVector;
        for (size_t i = 0; i < N; ++i) {
            colVector[i] = this->operator[](i);
        }
        return colVector;
    }

    /** Static initializer for constructing a zero vector */
    static Vector<T, N> zero() {
        return Vector();
    }

    /** Access operator (read-write) */
    T& operator[](size_t i) {
        return data[i];
    }

    /** Access operator (read-only) */
    const T& operator[](size_t i) const {
        return data[i];
    }

    /** Begin iterator for range-based for loops */
    auto begin() { return data.begin(); }

    /** Const begin iterator */
    auto begin() const { return data.begin(); }

    /** End iterator for range-based for loops */
    auto end() { return data.end(); }

    /** Const end iterator */
    auto end() const { return data.end(); }


    /** Element-wise addition */
    Vector<T, N> operator+(const Vector<T, N>& other) const {
        Vector<T, N> result;
        for (size_t i = 0; i < N; ++i) {
            result[i] = data[i] + other[i];
        }
        return result;
    }

    /** Element-wise subtraction */
    Vector<T, N> operator-(const Vector<T, N>& other) const {
        Vector<T, N> result;
        for (size_t i = 0; i < N; ++i) {
            result[i] = data[i] - other[i];
        }
        return result;
    }

    /** In-place addition */
    void operator+=(const Vector<T, N>& other) {
        for (size_t i = 0; i < N; ++i) {
            data[i] += other[i];
        }
    }

    /** In-place subtraction */
    void operator-=(const Vector<T, N>& other) {
        for (size_t i = 0; i < N; ++i) {
            data[i] -= other[i];
        }
    }

    /** Scale the vector by a scalar (element-wise) */
    void operator*=(const T& scalar) {
        for (auto& val : data) {
            val *= scalar;
        }
    }

    /** Divide the vector by a scalar (element-wise) */
    void operator/=(const T& scalar) {
        if (scalar == 0) {
            throw std::runtime_error("Division by zero");
        }
        for (auto& val : data) {
            val /= scalar;
        }
    }


    friend T dot(const Vector<T, N>& lhs,const Vector<T, N>& rhs) {
        T result = T(0); // Initialize to zero
        for (size_t i = 0; i < N; ++i) {
            result += lhs[i] * rhs[i]; // Multiply element-wise and accumulate
        }
        return result;
    }

    friend Vector<T, N> operator*(const Vector<T, N>& vec, const T& scalar) {
        Vector<T, N> result; // Create a new Vector to store the result
        for (size_t i = 0; i < N; ++i) {
            result[i] = vec[i] * scalar; // Scale each component
        }
        return result;
    }

    /** Compute the dot product of two vectors: Vector * Vector */
    friend T operator*(const Vector<T, N>& lhs, const Vector<T, N>& rhs) {
        T result = T(0); // Initialize to zero
        for (size_t i = 0; i < N; ++i) {
            result += lhs[i] * rhs[i]; // Multiply element-wise and accumulate
        }
        return result;
    }

    // Overload for scaling a vector by a scalar: Scalar * Vector
    friend Vector<T, N> operator*(const T& scalar, const Vector<T, N>& vec) {
        return vec * scalar; // Reuse the existing operator
    }

    /** Compute the Euclidean norm (L2 norm) */
    T norm() const {
        return std::sqrt(std::inner_product(data.begin(), data.end(), data.begin(), T(0)));
    }

    /** Normalize this vector in-place */
    void normalize() {
        T length = norm();
        if (length == 0) {
            throw VectorNormalizationException();
        }
        for (auto& val : data) {
            val /= length;
        }
    }

    /** Return a normalized version of this vector */
    Vector<T, N> normalized() const {
        T length = norm();
        if (length == 0) {
            throw DivideByZeroException();
        }
        Vector<T, N> result;
        for (size_t i = 0; i < N; ++i) {
            result[i] = data[i] / length;
        }
        return result;
    }

    /** Compute the cross product (only for 3D vectors) */
    Vector<T, 3> cross(const Vector<T, 3>& other) const {
        if (N != 3){
            throw InvalidDimensionException();
        }
        Vector<T, 3> result;
        result[0] = data[1] * other[2] - data[2] * other[1];
        result[1] = data[2] * other[0] - data[0] * other[2];
        result[2] = data[0] * other[1] - data[1] * other[0];
        return result;
    }

    /** Returns the projection of this vector onto another vector */
    Vector<T, N> project_onto(const Vector<T, N>& other) const {
        T other_norm = other.norm();
        if (other_norm == 0) {
            throw std::runtime_error("Cannot project onto a zero-length vector");
        }
        T projection_factor = (*this * other) / (other_norm * other_norm); // Dot product
        return other * projection_factor; // Scale the other vector
    }

    /** Equality operator */
    bool operator==(const Vector<T, N>& rhs) const {
        return std::equal(data.begin(), data.end(), rhs.data.begin());
    }

    /** Inequality operator */
    bool operator!=(const Vector<T, N>& rhs) const {
        return !(*this == rhs);
    }

    /** Format the vector for printing */
    void format(std::ostream& os) const {
        os << "[";
        for (size_t i = 0; i < N; ++i) {
            os << data[i];
            if (i < N - 1) {
                os << ", ";
            }
        }
        os << "]";
    }

    /** Overload ostream operator for easy printing */
    friend std::ostream& operator<<(std::ostream& os, const Vector<T, N>& vec) {
        vec.format(os);
        return os;
    }
};