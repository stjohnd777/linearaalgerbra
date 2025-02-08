#pragma once
#include "Matrix.h"
#include "Quaternion.h"

template<typename T>
class DCM : public Matrix<T,3,3> {
public:
    DCM (){

    }
    DCM(Quaternion<T>& q) {

    }
    DCM (double roll, double pitch, double yaw){

    }
};
