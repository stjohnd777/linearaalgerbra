//
// Created by Daniel St. John on 11/10/23.
//

#pragma once

#include <iostream>
#include <vector>
#include <array>

using namespace std;
#include "ColVector.h"
#include "RowVector.h"



template< typename T =double, size_t ROWS =3, size_t COLS=3 >
class Matrix : public std::array< RowVector<T,COLS> ,ROWS>{
public:

    static Matrix<T,ROWS,COLS> CreateIdentity(){
        assert(ROWS==COLS);
        Matrix<T,ROWS,COLS> I;
        for( auto rowIndex =0 ; rowIndex < ROWS ; rowIndex++){
           I.setElement(rowIndex,rowIndex,1);
        }
        return I;
    }

    static Matrix<T,ROWS,COLS> CreateRandom(){
        assert(ROWS==COLS);
        Matrix<T,ROWS,COLS> I;
        for( auto rowIndex =0 ; rowIndex < ROWS ; rowIndex++){
            I.setElement(rowIndex,rowIndex,1);
        }
        return I;
    }

    const size_t  cols = ROWS;
    const size_t  rows =  COLS;

    Matrix(){
        zero();
    }


    Matrix ( std::initializer_list<T> l)   {
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

    Matrix ( std::array<T,ROWS*COLS> dataT ){
        // a11a12..a1na21a22...a2n .... am1am2 .... amn
        zero();
        size_t r;
        size_t c;
        for ( auto index =0 ; index < ROWS*COLS ; index++){
            r = index / COLS;
            c = index - r*COLS;
            //cout << "(" << r << "," << c << ")" << endl;
            this->setElement(r,c,dataT.at(index));
        }

    }

    Matrix( std::array< RowVector<T,COLS>, ROWS> rows){
        zero();
        size_t index = 0;
        for ( auto r : rows) {
            this->setRow(index++,r);
        }
    }


    bool isSquare() { return ROWS == COLS;}

    T getElement(size_t row, size_t col) const {
        return this->at(row).at(col);
    }

    void setElement(size_t rowIndex, size_t colIndex, T v) {
        auto r = this->at(rowIndex);
        //cout << r << endl;
        (this->at(rowIndex)).at(colIndex) = v;
    }

    RowVector<T,COLS> getRow(size_t index){
        return this->at(index);
    }

    void setRow(size_t index, RowVector<T,COLS> r ){
        this->at(index) = r;
    }

    ColVector<T,ROWS> getCol(size_t col){
        ColVector<T,ROWS> aColumVector;
        size_t index = 0;
        for ( auto aRow : *this){
            aColumVector.at(index++) = aRow[col];
        }
        return aColumVector;
    }

    std::array< ColVector<T,ROWS>, COLS> getCols () {
        std::array<ColVector<T,ROWS>,COLS> cols;
        size_t index = 0;
        for ( auto col =0 ; col < COLS; col++){
            cols.at(index++) = getCol(col);
        }
        return cols;
    }

    void setCol( size_t index, ColVector<T,ROWS> c ){
        size_t colIndex = 0;
        for ( auto r : this) {
            r[index] = c.at(colIndex++);
        }
    }

    // final dimensions are the outer dimensions
    // these inner dimensions must match
    // (R1 x C1) * ( C1 * C2 ) = ( R1 x C2 )
    template<size_t C2 >
    Matrix<T,ROWS,C2>  operator * ( Matrix<T,COLS,C2>& rhs ){
        Matrix<T,ROWS,C2> m;
        for ( auto rowIndex =0; rowIndex < ROWS ; rowIndex++){
            for ( auto colIndex =0; colIndex < C2; colIndex++){
                auto row = this->getRow(rowIndex);
                auto col = rhs.getCol(colIndex);
                auto aij = row * col;
                m.setElement(rowIndex,colIndex, aij);
            }
        }

        return m;
    }

    Matrix<T,ROWS,COLS> operator + (const Matrix<T,ROWS,COLS>& lhs) const {
        Matrix<T,ROWS,COLS> sum;
        for ( auto rowIndex =0 ; rowIndex < ROWS ; rowIndex++){
            for ( auto colIndex =0 ; colIndex < COLS ;colIndex++){
                T v =  this->getElement(rowIndex,colIndex) + lhs.getElement(rowIndex,colIndex);
                sum.setElement(
                        rowIndex,
                        colIndex,
                        v) ;
            }
        }
        return sum;
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

    ColVector<T,ROWS> operator * (const ColVector<T,COLS>& b ){
        ColVector<T,ROWS> x;
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
    Matrix<T,ROWS-1,ROWS-1> getMinor(size_t r, size_t  c){
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
        assert ( ROWS == COLS);
        Matrix<T,ROWS,COLS> cof;
        for ( auto r =0 ; r < ROWS; r++){
            for ( auto c =0 ; c < ROWS; c++){
                cof.setElement(c,r, determinate(getMinor(r,c)));
            }
        }
        return cof;
    }


    Matrix<T,ROWS,ROWS> inv (){
        assert(ROWS==COLS);
        return ( 1/ determinate(*this) ) * getAdjunct();
    }

    Matrix<T,COLS,ROWS> transpose(){
        Matrix<T,COLS,ROWS> m;
        size_t index = 0;
        for ( auto c : getCols() ){
            m.setRow(index++, c);
        }
        return m;
    }

//    bool isSymmetric (){
//        bool ret =false;
//        return ret;
//    }
//    bool isAntiSymmetric (){
//        bool ret =false;
//        return ret;
//    }
//    bool isDiagnal (){
//        bool ret =false;
//        return ret;
//    }
//    bool isUpperTriangular (){
//        bool ret =false;
//        return ret;
//    }
//    bool isLowerTriangular (){
//        bool ret =false;
//        return ret;
//    }

    friend ostream &operator<<(ostream &os, const Matrix &matrix) {
       for (auto r : matrix){
           os << r << endl;
       }
        return os;
    }

private:

    void zero(){
        for ( auto index = 0; index < ROWS ; index++){
            for ( auto colIndex =0;  colIndex < COLS; colIndex++){
                (this->at(index)).at(colIndex) = 0;
            }
        }
    }

};

class DCM : public Matrix<double,3,3> {
public:
    DCM (){

    }
    DCM (double roll, double pitch, double yaw){

    }
};

class Quaternion {
public:
};

template<typename T, size_t N>
T determinate (  Matrix<T,N,N>& m){
    T det = 0;
    if ( N == 2){
        det = m.getElement(0, 0) * m.getElement(1, 1) - m.getElement(0, 1) * m.getElement(1, 0);
    } else if ( N ==3){
        /*
           a b c
           d e f
           g h i
         */
        auto a = m.getElement(0,0);
        auto b = m.getElement(0,1);
        auto c = m.getElement(0,2);

        auto d = m.getElement(1,0);
        auto e = m.getElement(1,1);
        auto f = m.getElement(1,2);

        auto g = m.getElement(2,0);
        auto h = m.getElement(2,1);
        auto i = m.getElement(0,0);
       det =   a*e*i + b*f*g +c*d*h -  c*e*g -  b*d*i - b*d*i;
    } else {

        for ( auto col =0; col < N; col++){
            Matrix<T,N-1,N-1> c = m.getMinor(0,col);
            cout << c << endl;
            T detc = determinate(c);

//            T v = m.getElement(0,col)*determinate<T,N-1>(c);
//            det += pow(-1,col)* v;
        }
    }
    return det;
}

template< typename T =double, size_t ROWS =3, size_t COLS=3 >
Matrix<T,ROWS,COLS> CreateIdentity(){
    assert(ROWS==COLS);
    Matrix<T,ROWS,COLS> I;
    for( auto rowIndex =0 ; rowIndex < ROWS ; rowIndex++){
        I.setElement(rowIndex,rowIndex,1);
    }
    return I;
}

template< typename T, size_t ROWS , size_t COLS >
Matrix<T,ROWS,COLS> CreateOnes(){
    Matrix<T,ROWS, COLS> I;
    for( auto row =0 ; row < ROWS ; row++){
        for ( auto col =0 ; col < COLS ; col++){
            I.setElement(row,col,1);
        }
    }
    return I;
}

template< typename T =double, size_t ROWS , size_t K>
void Convolution(Matrix<T,ROWS,ROWS>& img, Matrix<T,K,K>& ker ) {

}

