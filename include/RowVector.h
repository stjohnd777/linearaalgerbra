//
// Created by Daniel St. John on 11/10/23.
//
#pragma once
#include "Vector.h"
#include "ColVector.h"
using namespace std;
template <typename T , size_t N> class ColVector ;

/**
 * RowVector<double, 3> row = RowVector<double, 3>::from({1.0, 2.0, 3.0});
 * ColVector<double, 3> col{4.0, 5.0, 6.0};
 *
 *
 * @tparam T
 * @tparam N
 */
template <typename T = double , size_t N =3>
class RowVector final: public Vector<T,N> {
public:

    static RowVector<T, N> from(std::initializer_list<T> list) {
        return RowVector(list);
    }

    RowVector() : Vector<T, N>() {}; // Default constructor

    RowVector(std::initializer_list<T> list)
    : Vector<T, N>(list) { } // Use parent constructor

    // dot product
    T dot( const ColVector<T,N> & aCol){
        return this->dot(aCol); // Use shared dot product logic
    }

    T operator *( const ColVector<T,N> & aCol){
        return this->dot(aCol); // Use shared dot product logic
    }

    ColVector<T,N> transpose(){
        ColVector<T, N> colVector;
        for (size_t i = 0; i < N; ++i) {
            colVector[i] = this->operator[](i);  // Copy each element
        }
        return colVector;
    }

    friend ostream &operator<<(ostream &os, const RowVector<T,N> &colVector) {
        os << "RowVector:" ;
        colVector.format(os);
        return os;
    }

};