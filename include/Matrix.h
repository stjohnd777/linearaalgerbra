//
// Created by Daniel St. John on 11/10/23.
//

#pragma once
#include <cassert>
#include <iostream>
#include <array>
#include <algorithm>
#include <random>
#include "RowVector.h"

namespace dsj {

    template<typename T =double, size_t ROWS = 3, size_t COLS = 3>
    class Matrix {
    private:
        std::array<RowVector<T, COLS>, ROWS> m_RowVectors;
    public:
        const size_t m_cols = ROWS;
        const size_t m_rows = COLS;

        Matrix() {
            zero();
        }


        explicit Matrix(std::array<T, ROWS * COLS> l) {
            assert(l.size() == ROWS * COLS);
            zero();
            size_t index = 0;
            size_t r;
            size_t c;
            std::for_each(l.begin(), l.end(), [&](T aValue) {
                r = index / COLS;
                c = index - r * COLS;
                this->setElement(r, c, aValue);
                index++;
            });
        }

        Matrix(std::initializer_list<T> l) {
            assert(l.size() == ROWS * COLS);
            zero();
            size_t index = 0;
            size_t r;
            size_t c;
            std::for_each(l.begin(), l.end(), [&](T aValue) {
                r = index / COLS;
                c = index - r * COLS;
                this->setElement(r, c, aValue);
                index++;
            });
        }

        explicit Matrix(std::array<RowVector<T, COLS>, ROWS> rows) {
            zero();
            size_t index = 0;
            for (auto r: rows) {
                this->setRowVector(index++, r);
            }
        }

        T& operator()(size_t row, size_t col) {
            return m_RowVectors[row][col];
        }

        RowVector<T,COLS>& operator[](size_t row) {
            return m_RowVectors[row];
        }


        Matrix &operator=(const Matrix &other) {
            if (this != &other) {
                // Here, you can do the copying of the `m_RowVectors` member
                // Since `std::array` already has a defined copy assignment operator, we can use it
                m_RowVectors = other.m_RowVectors;
            }
            return *this;
        }

        Matrix(const Matrix &other) : m_RowVectors(other.m_RowVectors), m_cols(other.m_cols), m_rows(other.m_rows) {
            // Since std::array and size_t types take care of their own copying,
            // and we don't have any pointers or dynamically allocated resources in your class,
            // we can use the copy constructor of std::array to do the work.
            // The copy is done in the member initializer list above: m_RowVectors(other.m_RowVectors)
        }

        Matrix &operator=(Matrix &&other) noexcept {
            if (this != &other) {
                // For move assignment, we also need to make sure all resources of `this` are released
                // If your class was managing any dynamically allocated memory, this is where you would `delete` it.
                // However, since your class members (`m_RowVectors`) are automatically managed (they will automatically free their memory when they go out of scope),
                // you do not need to manually release any resources here.

                m_RowVectors = std::move(other.m_RowVectors);
                // Note that `other.m_RowVectors` is in a valid but unspecified state now
                // It is okay, because we know `other` is a temporary object that will be destroyed soon
            }
            return *this;
        }

//    explicit Matrix ( std::array<T,ROWS*COLS> dataT ){
//        // a11a12..a1na21a22...a2n .... am1am2 .... amn
//        zero();
//        size_t r;
//        size_t c;
//        for ( auto index =0 ; index < ROWS*COLS ; index++){
//            r = index / COLS;
//            c = index - r*COLS;
//            this->setElement(r,c,dataT.at(index));
//        }
//    }

        const RowVector<T, COLS> &operator[](size_t i) const {
            return m_RowVectors[i];
        }

        auto begin() { return m_RowVectors.begin(); }

        auto begin() const { return m_RowVectors.begin(); }

        auto end() { return m_RowVectors.end(); }

        auto end() const { return m_RowVectors.end(); }

        bool isSquare() const { return m_cols == m_cols; }

        T getElement(const size_t row, const size_t col) const {
            return (m_RowVectors)[row][col];
        }

        void setElement(size_t rowIndex, size_t colIndex, T v) {
            m_RowVectors[rowIndex][colIndex] = v;
        }

        RowVector<T, COLS> getRowVector(size_t index) {
            return m_RowVectors[index];
        }

        void setRowVector(size_t index, RowVector<T, COLS> r) {
            m_RowVectors.at(index) = r;
        }

        ColVector<T, ROWS> getColVector(size_t colIndex) {
            ColVector<T, ROWS> aColumVector;
            for (size_t rowIndex = 0; rowIndex < ROWS; rowIndex++) {
                aColumVector[rowIndex] = (*this)[rowIndex][colIndex]; // Use operator[]
            }
            return aColumVector;
        }

        void setColVector(size_t index, ColVector<T, ROWS> c) {
            size_t colIndex = 0;
            for (auto r: this) {
                r[index] = c[colIndex++];
            }
        }

        std::array<ColVector<T, ROWS>, COLS> getColVectors() {
            std::array<ColVector<T, ROWS>, COLS> cols;
            size_t index = 0;
            for (auto colIndex = 0; colIndex < COLS; colIndex++) {
                cols[index++] = getColVector(colIndex);
            }
            return cols;
        }


        // final dimensions are the outer dimensions
        // these inner dimensions must match
        // (R1 x C1) * ( C1 * C2 ) = ( R1 x C2 )
        template<size_t C2>
        Matrix<T, ROWS, C2> operator*(Matrix<T, COLS, C2> &rhs) {
            Matrix<T, ROWS, C2> m;
            for (auto rowIndex = 0; rowIndex < ROWS; rowIndex++) {
                for (auto colIndex = 0; colIndex < C2; colIndex++) {
                    auto row = this->getRowVector(rowIndex);
                    auto col = rhs.getColVector(colIndex);
                    auto aij = row * col;
                    m.setElement(rowIndex, colIndex, aij);
                }
            }

            return m;
        }

        Matrix<T, ROWS, COLS> operator+(const Matrix<T, ROWS, COLS> &lhs) const {
            Matrix<T, ROWS, COLS> sum;
            for (auto r = 0; r < m_rows; r++) {
                for (auto c = 0; c < m_cols; c++) {
                    sum.setElement(r, c, this->getElement(r, c) + lhs.getElement(r, c));
                }
            }
            // std::transform(
            //     m_RowVectors.begin(),
            //     m_RowVectors.end(),
            //     m_RowVectors.begin(),
            //     m_RowVectors.begin(),
            //         [](const auto &a, const auto &b) { return a + b; });
            return sum;
        }


        Vector<T, COLS> operator*(const Vector<T, COLS> v) const {
            Vector<T, COLS> vector;
            size_t index = 0;
            for (auto aRowVector: m_RowVectors) {
                vector[index] = aRowVector * v;
            }
            return vector;
        }

        RowVector<T, COLS> operator*(const ColVector<T> colVector) const {
            RowVector<T, COLS> vector;
            size_t index = 0;
            for (auto aRowVector: m_RowVectors) {
                vector[index] = aRowVector * colVector;
            }
            return vector;
        }

        Matrix<T, ROWS, COLS> operator*(const T s) const {
            Matrix<T, ROWS, COLS> scale;
            for (auto rowIndex = 0; rowIndex < ROWS; rowIndex++) {
                for (auto colIndex = 0; colIndex < COLS; colIndex++) {
                    T aij = this->getElement(rowIndex, colIndex);
                    scale.setElement(
                            rowIndex,
                            colIndex,
                            s * aij);
                }
            }
            return scale;
        }

        friend Matrix<T, ROWS, COLS> operator*(const T s, Matrix<T, ROWS, COLS> m) {
            return m * s;
        }

        RowVector<T, ROWS> operator*(const RowVector<T, COLS> &b) {
            RowVector<T, ROWS> x;
            size_t index = 0;
            for (auto row: *this) {
                T v = row * b;
                x.at(index++) = v;
            }
            return x;
        }

        /*
         * If A is a square matrix, then the minor Mij column is
         * a number formed taking the determinate of  matrix by deleting
         * the i row and j column of A and is denoted Mij
         *
         * The cofactor Cij  is obtained by multiplying the
         * minor Cij =(-1)^(i+j) * Mij
         *
         * The Cofactor Matrix C = [ Cij]
         */
        Matrix<T, ROWS - 1, ROWS - 1> getCofactorMatrix(const size_t r, const size_t c) {
            static_assert(ROWS > 0 && COLS > 0, "Matrix dimensions must be positive.");
            std::array<T, (ROWS - 1) * (ROWS - 1)> aij;
            size_t index = 0;
            for (auto rowIndex = 0; rowIndex < ROWS; rowIndex++) {
                if (rowIndex == r) {
                    continue;
                }

                for (auto colIndex = 0; colIndex < COLS; colIndex++) {
                    if (colIndex == c) continue;
                    auto value = getElement(rowIndex, colIndex);
                    aij[index++] = value;
                }
            }
            Matrix<T, ROWS - 1, ROWS - 1> cRC(aij);
            return cRC;
        }

        Matrix<T, ROWS, COLS> getAdjunct() {
            static_assert(ROWS == COLS);
            Matrix<T, ROWS, COLS> cof;
            for (auto r = 0; r < ROWS; r++) {
                for (auto c = 0; c < ROWS; c++) {
                    //cof.setElement(c,r, determinate(getCofactorMatrix(r, c)));
                    cof.setElement(c, r, getCofactorMatrix(r, c).determinate());
                }
            }
            return cof;
        }


        Matrix<T, ROWS, ROWS> inv() {
            static_assert(ROWS == COLS);
            return (1 / determinate()) * getAdjunct();
        }

        Matrix<T, COLS, ROWS> transpose() {
            Matrix<T, COLS, ROWS> m;
            size_t index = 0;
            for (auto c: getColVectors()) {
                m.setRowVector(index++, c.transpose());
            }
            return m;
        }

        T determinate() {

            auto det2 = [&](){
                auto a = getElement(0, 0);
                auto b = getElement(0, 1);
                auto c = getElement(1, 0);
                auto d = getElement(1, 1);
                T det = a*d - b*c;
                return det;
            };
            auto det3 = [&](){
                auto a = getElement(0, 0);
                auto b = getElement(0, 1);
                auto c = getElement(0, 2);

                auto d = getElement(1, 0);
                auto e = getElement(1, 1);
                auto f = getElement(1, 2);

                auto g = getElement(2, 0);
                auto h = getElement(2, 1);
                auto i = getElement(2, 2);

                T det = a*(e*i-f*h)
                      - b*(d*i-f*g)
                      +c*(d*h-e*g);

                return det;

            };

            T det = 0;
            if constexpr (ROWS == 2) {
                det = det2();

            } else if constexpr (ROWS == 3) {
                det = det3();
                std::cout << det ;
            }else {
                for(auto col = 0; col < COLS; col++){
                    T a = getElement(0, col);
                    Matrix<T, ROWS-1, COLS-1> minor = getCofactorMatrix(0, col);
                    det += pow(-1, col) * a * minor.determinate();
                }
            }
            return det;
        }

        friend std::ostream &operator<<(std::ostream &os, const Matrix &matrix) {
            for (auto r: matrix) {
                os << r << std::endl;
            }
            return os;
        }

        void randomize(T min = 0, T max = 1) {
            static_assert(std::is_floating_point<T>::value || std::is_integral<T>::value,
                          "Matrix type must be numeric");

            std::random_device dev;
            std::mt19937 rng(dev());

            if constexpr (std::is_integral<T>::value) {
                std::uniform_int_distribution<T> dist(min, max);

                for (size_t rowIndex = 0; rowIndex < ROWS; rowIndex++) {
                    for (size_t colIndex = 0; colIndex < COLS; colIndex++) {
                        T randomValue = dist(rng);
                        this->setElement(rowIndex, colIndex, randomValue);
                    }
                }

            } else {
                std::uniform_real_distribution<T> dist(min, max);

                for (size_t rowIndex = 0; rowIndex < ROWS; rowIndex++) {
                    for (size_t colIndex = 0; colIndex < COLS; colIndex++) {
                        T randomValue = dist(rng);
                        this->setElement(rowIndex, colIndex, randomValue);
                    }
                }
            }
        }

        void randomizeNonSingular(T min = 0, T max = 1) {

            Matrix<T, ROWS, COLS> ensure_non_zero_determinant(T min = 0, T max = 1) {
                Matrix<T, ROWS, COLS> matrix;
                do {
                    matrix.randomize(min, max);
                } while (matrix.determinate() == 0);
                return matrix;
            }
        }

        T norm() const {
            T sum = 0;
            for (size_t i = 0; i < ROWS; i++) {
                for (size_t j = 0; j < COLS; j++) {
                    sum += std::pow(m_RowVectors[i][j], 2);
                }
            }
            return std::sqrt(sum);
        }

        T conditionNumber() const {
            Matrix<T, ROWS, COLS> inv = this->inverse();
            T normA = this->norm();
            T normInvA = inv.norm();
            return normA * normInvA;
        }

    private:

        [[nodiscard]] static inline constexpr size_t asIndex(const size_t row, const size_t col) {
            return row * COLS + col;
        }

        void zero() {
            for (auto index = 0; index < ROWS; index++) {
                for (auto colIndex = 0; colIndex < COLS; colIndex++) {
                    (m_RowVectors)[index][colIndex] = 0;
                }
            }
        }

    };

}



