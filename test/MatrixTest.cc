#include <gtest/gtest.h>
#include <array>
#include "Matrix.h"
#include <Eigen/Dense>
#include "Determinate.h"

using namespace dsj;
class MatrixTest : public ::testing::Test {
protected:
    Matrix<double, 3, 3> matrix;
    void SetUp() override {
        std::array<double,9> data { 1, 2, 3, 4, 5, 6,  7, 8, 9} ;
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
    Matrix<double, 3, 3> matrix_to_add({ 1, 1, 1,
                                         1, 1, 1,
                                         1, 1, 1 });
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
    EXPECT_DOUBLE_EQ(0, matrix.determinate());  // Determinant of matrix should be 0

    std::array<double,16> data { 1, 2, 3, 4, 5, 6,  7, 8, 9,10,11,12,13,14,15,16} ;
    auto m4x4 = Matrix<double,4,4>(data);
    EXPECT_DOUBLE_EQ(0, m4x4.determinate());  // Determinant of matrix should be 0
}


TEST_F(MatrixTest,Mult){

    Eigen::MatrixXd m(3,3);
    m(0,0) = 1; m(0,1) = -2; m(0,2) = 3;
    m(1,0) = 4; m(1,1) = 5; m(1,2) =  6;
    m(2,0) = 7; m(2,1) = -8; m(2,2) = 9;
    std::cout << m << std::endl;
    std::cout << m.determinant() << std::endl;

    Eigen::MatrixXd m2(3,3);
    m2(0,0) = 11; m2(0,1) = -12; m2(0,2) = 13;
    m2(1,0) = 21; m2(1,1) = 22; m2(1,2) = 23;
    m2(2,0) = 31; m2(2,1) = -32; m2(2,2) = 33;
    std::cout << m2 << std::endl;
    std::cout << m2.determinant() << std::endl;

    auto m3 = m * m2;
    std::cout << m3<< std::endl;

    std::array<double, 3 * 3> data = { 1, -2, 3,
                                       4, 5, 6,
                                       7, -8, 9};
    dsj::Matrix<double, 3, 3> A(data);
    std::cout << A<< std::endl;
    dsj::Matrix<double, 3, 3> B({ RowVector<double, 3>{11, -12, 13},
                                  RowVector<double, 3>{21, 22, 23},
                                  RowVector<double, 3>{31, -32, 33}});
    std::cout << B << std::endl;
    dsj::Matrix<double, 3, 3> C = A * B;
    std::cout << C << std::endl;

    for ( auto i =0; i < 3 ; i++){
        for ( auto j =0; j < 3 ; j++){
            EXPECT_NEAR(m3(i,j) , C(i,j), 1e-9);  // Rough approximate equality
        }
    }
}

TEST_F(MatrixTest, Inverse) {

    Eigen::MatrixXd m(3,3);
    m(0,0) = 1; m(0,1) = -2; m(0,2) = 3;
    m(1,0) = 4; m(1,1) = 5; m(1,2) =  6;
    m(2,0) = 7; m(2,1) = -8; m(2,2) = 9;
    std::cout << m << std::endl;
    std::cout << m.determinant() << std::endl;
    auto invm = m.inverse();
    std::cout << invm<< std::endl;

    std::array<double, 3 * 3> data = { 1, -2, 3, 4, 5, 6, 7, -8, 9};
    dsj::Matrix<double, 3, 3> A(data);
    auto invA = A.inv();
    std::cout << invA << std::endl;

    for ( auto i =0; i < 3 ; i++){
        for ( auto j =0; j < 3 ; j++){
            EXPECT_NEAR(invm(i, j) , invA(i, j), 1e-9);  // Rough approximate equality
        }
    }


//    Matrix<double, 2, 2> matrix_({ 4, 7, 2, 6 });
//    Matrix<double, 2, 2> expected_inverse({ 0.6, -0.7,-0.2, 0.4 });
//    Matrix<double, 2, 2> actual_inverse = matrix_.inv();
//    for (size_t i = 0; i < 2; i++)
//        for (size_t j = 0; j < 2; j++)
//            EXPECT_NEAR(expected_inverse.getElement(i, j), actual_inverse.getElement(i, j), 1e-9);  // Rough approximate equality

}