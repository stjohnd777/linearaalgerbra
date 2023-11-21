//
// Created by Daniel St. John on 11/10/23.
//
#pragma once
#include <iostream>
#include <vector>
#include <array>
#include "RowVector.h"

using namespace std;

template <typename T , size_t N>
class ColVector ;

template <typename T = double , size_t N =3>
class RowVector : public std::array<T,N> {
public:

//    RowVector(){
//        auto index = 0;
//        for_each(this->begin(),this->end(),[&](T aValue){
//            (*this)[index++] = 0;
//        });
//    }

//    RowVector ( std::initializer_list<T> l)   {
//        auto index = 0;
//        for_each(l.begin(),l.end(),[&](T aValue){
//            (*this)[index++] = aValue;
//        });
//    }


    // dot product
    T operator *( const ColVector<T,N> & aCol){
        T ret = 0;
        size_t index = 0;
        for ( auto v : *this){
            auto w =  aCol.at(index++);
            ret += v * w;
        }
        return ret;
    }

    ColVector<T,N> transpose(){
        return ColVector<T,N>(this);
    }

    friend ostream &operator<<(ostream &os, const RowVector &rowVector) {
        os << "|" ;
        for ( auto v : rowVector){
            os << " " << v << " " ;
        }
        os << " " << "|" ;
        return os;
    }

    bool operator==(const RowVector &rhs) const {
        bool ret = false;
        auto index = 0;
        for ( auto aValue : *this){
            if ( aValue != rhs.at(index++)){
                return ret;
            }
        }
        ret = true;
        return ret;
    }

    bool operator!=(const RowVector &rhs) const {
        return !(rhs == *this);
    }
};


