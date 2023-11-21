//
// Created by Daniel St. John on 11/10/23.
//
#pragma once
#include <iostream>
#include <vector>
#include <array>
#include "ColVector.h"

using namespace std;

template <typename T , size_t N>
class RowVector ;

template <typename T = double , size_t N =3>
class ColVector : public RowVector<T,N> {
public:
    // dot product
    T operator *( const RowVector<T,N>& aCol){
        T ret = 0;
        size_t index = 0;
        for ( auto v : *this){
            ret += v * aCol.at(index++);
        }
        return ret;
    }

    RowVector<T,N> transpose(){
        return RowVector<T,N>(this);
    }



    friend ostream &operator<<(ostream &os, const ColVector &colVector) {
        os << "-\n" ;
        for ( auto v : colVector){
            os << " " << v << " "  << endl;
        }
        os  << "-" ;
        return os;
    }
};







