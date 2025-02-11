#pragma once

#include "Matrix.h"

namespace dsj {
    template<typename T, size_t N = 3>
    T _determinate(Matrix<T, N, N> &m) {
        T det = 0;
        if (N == 2) {
            det = m.getElement(0, 0) * m.getElement(1, 1) - m.getElement(0, 1) * m.getElement(1, 0);
        } else if (N == 3) {
            /*
               a b c
               d e f
               g h i
             */
            auto a = m.getElement(0, 0);
            auto b = m.getElement(0, 1);
            auto c = m.getElement(0, 2);

            auto d = m.getElement(1, 0);
            auto e = m.getElement(1, 1);
            auto f = m.getElement(1, 2);

            auto g = m.getElement(2, 0);
            auto h = m.getElement(2, 1);
            auto i = m.getElement(0, 0);
            det = a * e * i + b * f * g + c * d * h - c * e * g - b * d * i - b * d * i;
        } else {

//         for ( auto col =0; col < N; col++){
//             Matrix<T,N-1,N-1> c = m.getCofactorMatrix(0,col);
//             T detc = determinate(c);
//         }
        }
        return det;
    }

}