#pragma once

#include <array>
#include <cmath>
#include <iostream>

namespace dsj {
/*
    A quaternion is typically represented as:
    q = [w, x, y, z],
    w is the scalar part,
    x, y, z are the vector/imaginary components.

    The corresponding 3x3 rotation matrix R is given by:
    ⎡ 1 - 2(y² + z²),     2(xy - wz),     2(xz + wy) ⎤
    ⎢ 2(xy + wz),     1 - 2(x² + z²),     2(yz - wx) ⎥
    ⎣ 2(xz - wy),         2(yz + wx), 1 - 2(x² + y²) ⎦


    Below is a templated C++ implementation to build the rotation
    matrix given a quaternion:
 */
    template<typename T>
    class Quaternion {
    public:
        T w, x, y, z; // Quaternion components

        // Default Constructor
        explicit Quaternion(T w = 1, T x = 0, T y = 0, T z = 0)
                : w(w), x(x), y(y), z(z) {}

        // Normalize the quaternion
        void normalize() {
            T norm = std::sqrt(w * w + x * x + y * y + z * z);
            if (norm > 0) {
                w /= norm;
                x /= norm;
                y /= norm;
                z /= norm;
            }
        }

        // Convert Quaternion to a 3x3 Rotation Matrix
        std::array<std::array<T, 3>, 3> toRotationMatrix() const {
            std::array<std::array<T, 3>, 3> R;

            T xx = x * x, yy = y * y, zz = z * z;
            T xy = x * y, xz = x * z, yz = y * z;
            T wx = w * x, wy = w * y, wz = w * z;

            // Rotation matrix elements
            R[0][0] = 1 - 2 * (yy + zz);
            R[0][1] = 2 * (xy - wz);
            R[0][2] = 2 * (xz + wy);

            R[1][0] = 2 * (xy + wz);
            R[1][1] = 1 - 2 * (xx + zz);
            R[1][2] = 2 * (yz - wx);

            R[2][0] = 2 * (xz - wy);
            R[2][1] = 2 * (yz + wx);
            R[2][2] = 1 - 2 * (xx + yy);

            return R;
        }


    };

// Function to convert a DCM (3x3 matrix) to a Quaternion
    template<typename T>
    Quaternion<T> DCMToQuaternion(const std::array<std::array<T, 3>, 3> &R) {
        // Ensure the matrix is orthogonal and its determinant is 1
        assert(std::abs(R[0][0] * R[1][1] * R[2][2] - R[0][1] * R[1][2] * R[2][0]) - 1 < 1e-5);

        Quaternion<T> q;

        // Compute trace of the matrix
        T trace = R[0][0] + R[1][1] + R[2][2];

        if (trace > 0) {
            // Case where the trace is positive
            T S = std::sqrt(trace + 1.0) * 2; // Scale factor
            q.w = 0.25 * S;
            q.x = (R[2][1] - R[1][2]) / S;
            q.y = (R[0][2] - R[2][0]) / S;
            q.z = (R[1][0] - R[0][1]) / S;
        } else if ((R[0][0] > R[1][1]) && (R[0][0] > R[2][2])) {
            // Case where the largest diagonal element is R[0][0]
            T S = std::sqrt(1.0 + R[0][0] - R[1][1] - R[2][2]) * 2;
            q.w = (R[2][1] - R[1][2]) / S;
            q.x = 0.25 * S;
            q.y = (R[0][1] + R[1][0]) / S;
            q.z = (R[0][2] + R[2][0]) / S;
        } else if (R[1][1] > R[2][2]) {
            // Case where the largest diagonal element is R[1][1]
            T S = std::sqrt(1.0 + R[1][1] - R[0][0] - R[2][2]) * 2;
            q.w = (R[0][2] - R[2][0]) / S;
            q.x = (R[0][1] + R[1][0]) / S;
            q.y = 0.25 * S;
            q.z = (R[1][2] + R[2][1]) / S;
        } else {
            // Case where the largest diagonal element is R[2][2]
            T S = std::sqrt(1.0 + R[2][2] - R[0][0] - R[1][1]) * 2;
            q.w = (R[1][0] - R[0][1]) / S;
            q.x = (R[0][2] + R[2][0]) / S;
            q.y = (R[1][2] + R[2][1]) / S;
            q.z = 0.25 * S;
        }

        q.normalize(); // Ensure the quaternion is normalized
        return q;
    }
}