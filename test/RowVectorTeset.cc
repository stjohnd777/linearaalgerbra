#include <gtest/gtest.h>
#include "RowVector.h"
#include "ColVector.h"

class RowVectorTest : public ::testing::Test {

protected:

    RowVector<double, 3> row_vector;
    ColVector<double, 3> col_vector;

    void SetUp() override {
        // Initialize your RowVector and ColVector here if needed
        row_vector = RowVector<double, 3>::from({1, 2, 3});
        col_vector = ColVector<double, 3>::from({4, 5, 6});
    }
};

TEST_F(RowVectorTest, DotProduct) {
    double result = row_vector.dot(col_vector);
    EXPECT_DOUBLE_EQ(32, result);
}

TEST_F(RowVectorTest, OperatorMultiplication) {
    double result = row_vector * col_vector;
    EXPECT_DOUBLE_EQ(32, result);
}

TEST_F(RowVectorTest, Transpose) {

    ColVector<double, 3> result = row_vector.transpose();

    // Check that each element of the result is correct
    for(size_t i=0; i<3; ++i) {
        EXPECT_DOUBLE_EQ(row_vector[i], result[i]);
    }
}