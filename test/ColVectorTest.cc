#include <gtest/gtest.h>
#include "ColVector.h"
#include "RowVector.h"

using namespace dsj;
class ColVectorTest : public ::testing::Test {

protected:
    ColVector<double, 3> col_vector;
    RowVector<double, 3> row_vector;

    void SetUp() override {
        // Initialize your ColVector and RowVector here if needed
        col_vector = ColVector<double, 3>::from({1, 2, 3});
        row_vector = RowVector<double, 3>::from({4, 5, 6});
    }
};

TEST_F(ColVectorTest, DotProduct) {
    double result = col_vector * row_vector;
    EXPECT_DOUBLE_EQ(32.0, result);
}

TEST_F(ColVectorTest, Transpose) {
    RowVector<double, 3> result = col_vector.transpose();

    // Check that each element of the result is correct
    for(size_t i=0; i<3; ++i) {
        EXPECT_DOUBLE_EQ(col_vector[i], result[i]);
    }
}