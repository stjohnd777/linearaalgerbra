//
// Created by Daniel St. John on 11/10/23.
//
#pragma once
#include "Vector.h"
#include "RowVector.h"

template<typename T, size_t N> class Vector;
template <typename T , size_t N> class RowVector ;


/**
 *
 * @tparam T
 * @tparam N
 */
template <typename T = double , size_t N =3>
class ColVector final: public Vector<T,N> {
public:

    static ColVector<T, N> from(std::initializer_list<T> list) {
        return ColVector(list);
    }

    ColVector() : Vector<T, N>() {};

    ColVector(std::initializer_list<T> list)
        : Vector<T, N>(list) { }

    // dot product
    T operator *( const ColVector<T,N> & aRow){
        return this->dot(aRow); // Use shared dot product logic
    }

    RowVector<T,N> transpose(){
        RowVector<T, N> rowVector;
        for (size_t i = 0; i < N; ++i) {
            rowVector[i] = this->operator[](i);  // Copy each element
        }
        return rowVector;
    }

    friend std::ostream &operator<<(std::ostream &os, const ColVector<T,N> &rowVector) {
        os << "ColVector:" ;
        rowVector.format(os);
        return os;
    }

};

