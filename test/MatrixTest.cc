#include <gtest/gtest.h>
#include <array>
#include "Matrix.h"
#include "Determinate.h"

class MatrixTest : public ::testing::Test {

protected:

    Matrix<double, 3, 3> matrix;




    void SetUp() override {

        std::array<double,9> data { 1, 2, 3, 4, 5, 6,  7, 8, 10} ;
        matrix = Matrix<double,3,3>(data);
    }
};

TEST_F(MatrixTest, ElementAccess) {
    double element = matrix.getElement(0, 1);
    EXPECT_DOUBLE_EQ(2.0, element);
}

TEST_F(MatrixTest, SetElement) {
    matrix.setElement(0, 0, 100.0);
    EXPECT_DOUBLE_EQ(100.0, matrix.getElement(0, 0));
}

TEST_F(MatrixTest, MatrixAddition) {
    Matrix<double, 3, 3> matrix_to_add({
                                               1, 1, 1,
                                               1, 1, 1,
                                               1, 1, 1
                                       });
    Matrix<double, 3, 3> result = matrix + matrix_to_add;
    EXPECT_DOUBLE_EQ(2.0, result.getElement(0, 0));
    EXPECT_DOUBLE_EQ(3.0, result.getElement(0, 1));
}

TEST_F(MatrixTest, Transpose) {
    Matrix<double, 3, 3> result = matrix.transpose();
    EXPECT_DOUBLE_EQ(1.0, result.getElement(0, 0));
    EXPECT_DOUBLE_EQ(4.0, result.getElement(0, 1));
}

TEST_F(MatrixTest, Determinant) {
    Matrix<double, 3, 3> matrix_({
                                         1, 2, 3,
                                         4, 5, 6,
                                         7, 8, 9
                                 });
    EXPECT_DOUBLE_EQ(0, matrix.determinate());  // Determinant of matrix should be 0
}

TEST_F(MatrixTest, Inverse) {
    Matrix<double, 2, 2> matrix_({
                                         4, 7,
                                         2, 6
                                 });
    Matrix<double, 2, 2> expected_inverse({
                                                  0.6, -0.7,
                                                  -0.2, 0.4
                                          });
    Matrix<double, 2, 2> actual_inverse = matrix_.inv();
    for (size_t i = 0; i < 2; i++)
        for (size_t j = 0; j < 2; j++)
            EXPECT_NEAR(expected_inverse.getElement(i, j), actual_inverse.getElement(i, j), 1e-9);  // Rough approximate equality

}