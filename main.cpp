#include <iostream>
#include <vector>
#include <set>
#include <array>

using namespace std;

#include "ColVector.h"
#include "RowVector.h"
#include "Matrix.h"


int main() {




//    auto r1 = aM1.getRow(0);
//    if ( r1 == { 11,12,13 } ){
//        cout << "good" << endl;
//    }

    /**
     * Test row iterator
     */
    for (auto row: aM1) {
        cout << row << endl;
    }
    /**
     * Test col iterator
     */
    for (auto col: aM1.getCols()) {
        cout << col << endl;
    }

    // row * col test
    RowVector<double, 3> row = {1, 2, 3};
    cout << "Row Vector:" << row;
    cout << endl;
    ColVector<double, 3> col = {1, 2, 3};
    cout << "Col Vector:\n" << col;
    cout << endl;
    cout << "r dot c " << row * col;
    cout << "c dot r " << col * row;

    // setElement test
    Matrix<double, 3, 3> z;
    cout << z << endl;
    cout << endl;

    z.setElement(0, 0, 11);
    z.setElement(0, 1, 12);
    z.setElement(0, 2, 13);
    z.setElement(1, 0, 21);
    z.setElement(1, 1, 22);
    z.setElement(1, 2, 23);
    z.setElement(2, 0, 32);
    z.setElement(2, 1, 32);
    z.setElement(2, 2, 33);
    cout << z << endl;
    cout << endl;

    cout << z.getRow(0) << endl;
    cout << z.getRow(1) << endl;
    cout << z.getRow(2) << endl;
    cout << z.getCol(0) << endl;
    cout << z.getCol(1) << endl;
    cout << z.getCol(2) << endl;

    // constructor I
    std::array<RowVector<double, 3>, 3> i = {
            RowVector<double, 3>{1, 0, 0},
            RowVector<double, 3>{0, 1, 0},
            RowVector<double, 3>{0, 0, 1}
    };
    Matrix<double, 3, 3> I(i);

    // constructor test
    std::array<RowVector<double, 3>, 3> l = {
            RowVector<double, 3>{1, 0, 0},
            RowVector<double, 3>{0, 2, 0},
            RowVector<double, 3>{0, 0, 3}
    };
    Matrix<double, 3, 3> m(l);
    cout << m << endl;
    cout << endl;


    /**
     * Test matrix multiplication A*B Square
     */
    std::array<double, 3 * 3> data = {
            1, 2, 3,
            4, 5, 6,
            7, 8, 9};
    Matrix<double, 3, 3> A(data);
    Matrix<double, 3, 3> B(
            {RowVector<double, 3>{11, 12, 13},
             RowVector<double, 3>{21, 22, 23},
             RowVector<double, 3>{31, 32, 33}
            }
    );
    Matrix<double, 3, 3> C = A * B;
    cout << C << endl;

    /**
     * Test matrix addition
     */
    Matrix<double, 3, 3> D = A + B;
    cout << D << endl;

    // matrix A times col vector x  A*x= b
    ColVector<double, 3> x = {1, 1, 1};
    auto b = A * x;

    /**
     * Test matrix scalar multiplication
     */
    auto c = CreateIdentity<int, 10, 10>();
    cout << c << endl;
    auto I10 = 10 * c;
    cout << I10 << endl;
    auto cc = CreateOnes<int, 10, 10>();
    cout << cc << endl;
    cout << 10 * cc << endl;
    cout << cc * 10 << endl;


    /**
     * Test Non Square
     */
    Matrix<double, 3, 4> m5{
            11, 12, 13, 14,
            21, 22, 23, 24,
            31, 32, 33, 34};
    cout << m5 << endl;
    cout << endl;

    Matrix<double, 4, 8> m6{
            11, 12, 13, 14, 11, 12, 13, 14,
            21, 22, 23, 24, 11, 12, 13, 14,
            31, 32, 33, 34, 11, 12, 13, 14,
            31, 32, 33, 34, 11, 12, 13, 14,

    };
    cout << m6 << endl;
    cout << endl;

    auto m7 = m5 * m6;
    cout << m7 << endl;

    /**
     * Test Non Square Transpose
     */
    auto m8 = m7.transpose();
    cout << m8 << endl;


    Matrix T = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    cout << T << endl;

    cout << T.getMinor(0, 0) << endl;
    for (auto r = 0; r < T.rows; r++) {
        for (auto c = 0; c < T.cols; c++) {

            cout << "C(" << r +1 << "," << c + 1 << ")" << endl;
            cout << T << endl;
            auto minor = T.getMinor(r, c);
            cout << minor << endl;
//            cout << minor.determinate() << endl;
        }
    }

    return 0;
}


