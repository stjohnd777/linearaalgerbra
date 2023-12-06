#include <iostream>
#include <gtest/gtest.h>
#include "Matrix.h"

using namespace std;

// Demonstrate some basic assertions.
TEST(Matrix, initializer_list) {

    Matrix<double, 3, 3> m{11, 12, 13, 21, 22, 23, 31, 32, 33};
    cout << m << endl;

    EXPECT_EQ(m.getElement(0,0), 11);
    EXPECT_EQ(m.getElement(0,1), 12);
    EXPECT_EQ(m.getElement(0,2), 13);
    EXPECT_EQ(m.getElement(1,0), 21);
    EXPECT_EQ(m.getElement(1,1), 22);
    EXPECT_EQ(m.getElement(1,2), 23);
    EXPECT_EQ(m.getElement(2,0), 31);
    EXPECT_EQ(m.getElement(2,1), 32);
    EXPECT_EQ(m.getElement(2,2), 33);
}

TEST(Matrix, array_RowVector) {

    std::array<RowVector<double, 3>, 3> rows = {
            RowVector<double, 3>{11, 12, 13},
            RowVector<double, 3>{21, 22, 23},
            RowVector<double, 3>{31, 32, 33} };
    Matrix<double, 3, 3> m(rows);
    cout << m << endl;

    EXPECT_EQ(m.getElement(0,0), 11);
    EXPECT_EQ(m.getElement(0,1), 12);
    EXPECT_EQ(m.getElement(0,2), 13);
    EXPECT_EQ(m.getElement(1,0), 21);
    EXPECT_EQ(m.getElement(1,1), 22);
    EXPECT_EQ(m.getElement(1,2), 23);
    EXPECT_EQ(m.getElement(2,0), 31);
    EXPECT_EQ(m.getElement(2,1), 32);
    EXPECT_EQ(m.getElement(2,2), 33);
}

TEST(Matrix, det3x3) {

    Matrix<double, 3, 3> m{11, 12, 13, 21, 22, 23, 31, 32, 33};
    cout << m << endl;
    //cout << determinate(m) << endl;
    //EXPECT_EQ(determinate(m), 11);

    Matrix<double, 3, 3> i3{1, 0, 0,
                           0, 1, 0,
                           0, 0, 1};
    cout << i3 << endl;
    cout << determinate<double,3> (i3) << endl;
    EXPECT_EQ(determinate(i3), 1);

    Matrix<double, 4, 4> i4 {
           1, 0, 0,0,
           0, 1, 0,0,
           0, 0, 1,0,
           0, 0, 0,1

    };
    cout << i4 << endl;
    cout << determinate(i4) << endl;
    EXPECT_EQ(determinate(i4), 1);
}



/**
 * Test Test row iterator  col iterator
 */
TEST(Matrix, iterator) {

    Matrix<int, 3, 3> aM1{11, 12, 13, 21, 22, 23, 31, 32, 33};
    cout << aM1 << endl;
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
}