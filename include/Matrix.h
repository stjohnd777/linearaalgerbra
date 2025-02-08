//
// Created by Daniel St. John on 11/10/23.
//

#pragma once
#include <cassert>
#include <iostream>
#include <array>
#include "RowVector.h"

template< typename T =double, size_t ROWS =3, size_t COLS=3 >
class Matrix {
private:
    std::array< RowVector<T,COLS> ,ROWS> m_RowVectors;
public:
    const size_t  m_cols = ROWS;
    const size_t  m_rows =  COLS;
    Matrix(){
        zero();
    }
    Matrix ( std::initializer_list<T> l)   {
        assert(l.size() == ROWS * COLS  );
        zero();
        size_t index=0;
        size_t r;
        size_t c;
        for_each(l.begin(),l.end(),[&](T aValue){
            r = index / COLS;
            c = index - r*COLS;
            this->setElement(r,c,aValue);
            index++;
        });
    }
    explicit Matrix( std::array< RowVector<T,COLS>, ROWS> rows){
        zero();
        size_t index = 0;
        for ( auto r : rows) {
            this->setRowVector(index++,r);
        }
    }
    explicit Matrix ( std::array<T,ROWS*COLS> dataT ){
        // a11a12..a1na21a22...a2n .... am1am2 .... amn
        zero();
        size_t r;
        size_t c;
        for ( auto index =0 ; index < ROWS*COLS ; index++){
            r = index / COLS;
            c = index - r*COLS;
            this->setElement(r,c,dataT.at(index));
        }
    }

    const RowVector<T,COLS> & operator[](size_t i) const {
        return m_RowVectors[i];
    }
    auto begin() { return m_RowVectors.begin(); }
    auto begin() const { return m_RowVectors.begin(); }
    auto end() { return m_RowVectors.end(); }
    auto end() const { return m_RowVectors.end(); }
    bool isSquare() const { return m_cols == m_cols;}

    T getElement(const size_t row, const size_t col) const {
        return (m_RowVectors)[row][col];
    }
    void setElement(size_t rowIndex, size_t colIndex, T v) {
        m_RowVectors[rowIndex][colIndex] =v;
    }
    RowVector<T,COLS> getRowVector(size_t index){
        return m_RowVectors[index];
    }
    void setRowVector(size_t index, RowVector<T,COLS> r ){
        m_RowVectors.at(index) = r;
    }
    ColVector<T,ROWS> getColVector(size_t colIndex) {
        ColVector<T,ROWS> aColumVector;
        for (size_t rowIndex = 0; rowIndex < ROWS; rowIndex++) {
            aColumVector[rowIndex] = (*this)[rowIndex][colIndex]; // Use operator[]
        }
        return aColumVector;
    }
    void setColVector( size_t index, ColVector<T,ROWS> c ){
        size_t colIndex = 0;
        for ( auto r : this) {
            r[index] = c[colIndex++];
        }
    }

    std::array< ColVector<T,ROWS>, COLS> getColVectors () {
        std::array<ColVector<T,ROWS>,COLS> cols;
        size_t index = 0;
        for ( auto colIndex =0 ; colIndex < COLS; colIndex++){
            cols[index++] = getColVector(colIndex);
        }
        return cols;
    }



    // final dimensions are the outer dimensions
    // these inner dimensions must match
    // (R1 x C1) * ( C1 * C2 ) = ( R1 x C2 )
    template<size_t C2 >
    Matrix<T,ROWS,C2>  operator * ( Matrix<T,COLS,C2>& rhs ){
        Matrix<T,ROWS,C2> m;
        for ( auto rowIndex =0; rowIndex < ROWS ; rowIndex++){
            for ( auto colIndex =0; colIndex < C2; colIndex++){
                auto row = this->getRowVector(rowIndex);
                auto col = rhs.getColVector(colIndex);
                auto aij = row * col;
                m.setElement(rowIndex,colIndex, aij);
            }
        }

        return m;
    }

    Matrix<T,ROWS,COLS> operator + (const Matrix<T,ROWS,COLS>& lhs) const {
        Matrix<T,ROWS,COLS> sum;
        for (auto r =0 ; r< m_rows; r ++) {
            for (auto c =0 ; c< m_cols; c ++) {
                sum.setElement(r,c ,this->getElement(r,c)+ lhs.getElement(r,c));
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


    Vector<T,COLS> operator * (const Vector<T,COLS> v) const {
        Vector<T,COLS> vector;
        size_t index = 0;
        for ( auto aRowVector: m_RowVectors) {
            vector[index] = aRowVector * v;
        }
        return vector;
    }

    RowVector<T,COLS> operator * (const ColVector<T> colVector) const {
        RowVector<T,COLS> vector;
        size_t index = 0;
        for ( auto aRowVector: m_RowVectors) {
            vector[index] = aRowVector * colVector;
        }
        return vector;
    }

    Matrix<T,ROWS,COLS> operator * (const T s) const {
        Matrix<T,ROWS,COLS> scale;
        for ( auto rowIndex =0 ; rowIndex < ROWS ; rowIndex++) {
            for (auto colIndex = 0; colIndex < COLS; colIndex++) {
                T aij = this->getElement(rowIndex,colIndex);
                scale.setElement(
                        rowIndex,
                        colIndex,
                        s * aij);
            }
        }
        return scale;
    }

    friend Matrix<T,ROWS,COLS> operator * (const T s, Matrix<T,ROWS,COLS> m)  {
        return m * s;
    }

    RowVector<T,ROWS> operator * (const RowVector<T,COLS>& b ){
        RowVector<T,ROWS> x;
        size_t index = 0;
        for (auto row: *this){
            T v = row * b ;
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
    Matrix<T,ROWS-1,ROWS-1> getMinor(const size_t r, const size_t  c){
        static_assert(ROWS > 0 && COLS > 0, "Matrix dimensions must be positive.");
        std::array<T,(ROWS-1)*(ROWS-1)> aij;
        size_t index = 0;
        for ( auto rowIndex = 0 ; rowIndex < ROWS ; rowIndex++ ){
            if ( rowIndex == r) {
                continue;
            }

            for ( auto colIndex = 0 ; colIndex < COLS ; colIndex++) {
                if ( colIndex == c) continue;
                auto value = getElement(rowIndex,colIndex);
                aij[index++] = value;
            }
        }
        Matrix<T,ROWS-1,ROWS-1> cRC(aij);
        return cRC;
    }

    Matrix<T,ROWS,COLS> getAdjunct(){
        static_assert ( ROWS == COLS);
        Matrix<T,ROWS,COLS> cof;
        for ( auto r =0 ; r < ROWS; r++){
            for ( auto c =0 ; c < ROWS; c++){
                cof.setElement(c,r, determinate(getMinor(r,c)));
            }
        }
        return cof;
    }


    Matrix<T,ROWS,ROWS> inv (){
        static_assert(ROWS==COLS);
        return ( 1/ determinate(*this) ) * getAdjunct();
    }

    Matrix<T,COLS,ROWS> transpose(){
        Matrix<T,COLS,ROWS> m;
        size_t index = 0;
        for ( auto c : getColVectors() ){
            m.setRowVector(index++, c.transpose());
        }
        return m;
    }

    friend ostream &operator<<(ostream &os, const Matrix &matrix) {
       for (auto r : matrix){
           os << r << endl;
       }
        return os;
    }
private:

    [[nodiscard]] static inline constexpr size_t asIndex(const size_t row, const size_t col) {
        return row * COLS + col;
    }
    void zero(){
        for ( auto index = 0; index < ROWS ; index++){
            for ( auto colIndex =0;  colIndex < COLS; colIndex++){
                (m_RowVectors)[index][colIndex] = 0;
            }
        }
    }

};




