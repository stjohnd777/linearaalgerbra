#include <iostream>
#include <gtest/gtest.h>
#include "Matrix.h"

using namespace std;

// Demonstrate some basic assertions.
TEST(Matrix, BasicAssertions) {
    // Expect two strings not to be equal.
    EXPECT_STRNE("hello", "world");
    // Expect equality.
    EXPECT_EQ(7 * 6, 42);
}


/**
 * Test initializer_list
 */
TEST(Matrix, initializer_list) {
    /**
     * Test initializer_list
     */
    Matrix<int, 3, 3> a{11, 12, 13, 21, 22, 23, 31, 32, 33};
    cout << a << endl;
    EXPECT_EQ(11, a.getElement(0,0));
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