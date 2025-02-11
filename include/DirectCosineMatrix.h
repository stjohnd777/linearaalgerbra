#pragma once
#include "Matrix.h"
#include "Quaternion.h"

namespace dsj {

    template<typename T>
    class IRotation  : public Matrix<T, 3, 3>{
    public:
        bool IsValid(){
            return (this->determinate()) == 1 && (this->Inv() == this->transpose());
        }
    };

    template<typename T>
    class Rx : public IRotation<T> {
    public:
        explicit Rx(T angle) {
            *this(0,0) = 1;*this(0,1) = 0;*this(0,2) = 0;
            *this(1,0) = 0;*this(1,2) = std::cos(angle);*this(1,2) =  std::sin(angle);
            *this(2,0) = 0;*this(2,1) =  -std::sin(angle);*this(2,2) =  std::cos(angle);
        }

    };
    template<typename T> using R1 = Rx<T>;

    template<typename T>
    class Ry : public IRotation<T> {
    public:
        explicit Ry(T angle) {
            *this(0,0) = std::cos(angle);*this(0,1) = 0;*this(0,2) = -std::sin(angle);
            *this(1,0) = 0;*this(1,1) = 1; *this(1,2) =  0;
            *this(2,0) = std::sin(angle);*this(2,1) = 0;*this(2,2) =  std::cos(angle);
        }
    };
    template<typename T> using R2 = Ry<T>;

    template<typename T>
    class Rz :public IRotation<T> {
    public:
        explicit Rz(T angle) {
            *this(0,0) = std::cos(angle);*this(0,1) = std::sin(angle);*this(0,2) = 0;
            *this(1,0) = std::sin(angle);*this(1,1) = std::cos(angle); *this(1,2) =  0;
            *this(2,0)  = 0; *this(2,1) = 0 ;*this(2,2) =  1;
        }

    };
    template<typename T> using R3 = Rz<T>;


    template<typename T>
    class DCM : public IRotation<T> {
    public:
        DCM() {

        }

        explicit DCM(Quaternion<T> &q) {
            *this = q.toRotationMatrix();
        }

        DCM(double roll, double pitch, double yaw) {

        }

        bool IsValid(){
            return (this->determinate()) == 1 && (this->Inv() == this->transpose());
        }


    };
}