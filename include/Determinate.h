#pragma once

#include "Matrix.h"

namespace dsj {

    template<typename T>
    T Det2 (Matrix<T,2,2>& m){
        auto a = m.getElement(0, 0);
        auto b = m.getElement(0, 1);
        auto c = m.getElement(1, 0);
        auto d = m.getElement(1, 1);
        T det = a*d - b*c;
        return det;
    };

    template<typename T>
    auto Det3 (Matrix<T,3,3>& m){
        auto a = m.getElement(0, 0);
        auto b = m.getElement(0, 1);
        auto c = m.getElement(0, 2);
        auto d = m.getElement(1, 0);
        auto e = m.getElement(1, 1);
        auto f = m.getElement(1, 2);
        auto g = m.getElement(2, 0);
        auto h = m.getElement(2, 1);
        auto i = m.getElement(2, 2);
        T det = a*(e*i-f*h)- b*(d*i-f*g)+c*(d*h-e*g);
        return det;
    };

 
    template<typename T, size_t N = 3>
    T Determinate(Matrix<T, N, N> &m) {

        T det = 0;
        if constexpr (N == 2) {
            det = Det2(m);

        } else if constexpr (N == 3) {
            det = Det3(m);
            std::cout << det ;
        }else {
            for(auto col = 0; col < N; col++){
                T a = m.getElement(0, col);
                Matrix<T, N-1, N-1> minor = m.getCofactorMatrix(0, col);
                det += pow(-1, col) * a * Determinate(minor);
            }
        }
        return det;
    }

}