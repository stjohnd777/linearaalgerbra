#pragma once
#include "Matrix.h"

namespace utils {
    template< typename T =double, size_t ROWS =3, size_t COLS=3 >
    Matrix<T,ROWS,COLS> CreateIdentity(){
        static_assert(ROWS==COLS);
        Matrix<T,ROWS,COLS> I;
        for( auto rowIndex =0 ; rowIndex < ROWS ; rowIndex++){
            I.setElement(rowIndex,rowIndex,1);
        }
        return I;
    }

    template< typename T, size_t ROWS =3, size_t COLS =3 >
    Matrix<T,ROWS,COLS> CreateOnes(){
        Matrix<T,ROWS, COLS> I;
        for( auto row =0 ; row < ROWS ; row++){
            for ( auto col =0 ; col < COLS ; col++){
                I.setElement(row,col,1);
            }
        }
        return I;
    }

    template< typename T =double, size_t ROWS = 512, size_t COLS = 640, size_t K = 3>
    void Convolution(Matrix<T,ROWS,COLS>& img, Matrix<T,K,K>& ker ) {

    }
}

