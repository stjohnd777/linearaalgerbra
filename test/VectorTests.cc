#include <gtest/gtest.h>
#include "Vector.h"

// Test fixture for Vector tests
class VectorTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Common setup for all tests (if needed)
    }

    void TearDown() override {
        // Cleanup after tests (if needed)
    }
};

// Test default initialization
TEST_F(VectorTest, DefaultInitialization) {
    Vector<double, 3> v;
    EXPECT_EQ(v[0], 0.0);
    EXPECT_EQ(v[1], 0.0);
    EXPECT_EQ(v[2], 0.0);
}

// Test static initializer: from()
TEST_F(VectorTest, StaticInitializerFrom) {
    Vector<double, 3> v = Vector<double, 3>::from({1.0, 2.0, 3.0});
    EXPECT_EQ(v[0], 1.0);
    EXPECT_EQ(v[1], 2.0);
    EXPECT_EQ(v[2], 3.0);
}

// Test static initializer: zero()
TEST_F(VectorTest, StaticInitializerZero) {
    auto v = Vector<double, 3>::zero();
    EXPECT_EQ(v[0], 0.0);
    EXPECT_EQ(v[1], 0.0);
    EXPECT_EQ(v[2], 0.0);
}

// Test addition and operator+
TEST_F(VectorTest, VectorAddition) {
    Vector<double, 3> v1 = Vector<double, 3>::from({1.0, 2.0, 3.0});
    Vector<double, 3> v2 = Vector<double, 3>::from({4.0, 5.0, 6.0});

    auto result = v1 + v2;

    EXPECT_EQ(result[0], 5.0);
    EXPECT_EQ(result[1], 7.0);
    EXPECT_EQ(result[2], 9.0);
}

// Test in-place addition (operator+=)
TEST_F(VectorTest, VectorInPlaceAddition) {
    Vector<double, 3> v1 = Vector<double, 3>::from({1.0, 2.0, 3.0});
    Vector<double, 3> v2 = Vector<double, 3>::from({4.0, 5.0, 6.0});

    v1 += v2;

    EXPECT_EQ(v1[0], 5.0);
    EXPECT_EQ(v1[1], 7.0);
    EXPECT_EQ(v1[2], 9.0);
}

// Test subtraction and operator-
TEST_F(VectorTest, VectorSubtraction) {
    Vector<double, 3> v1 = Vector<double, 3>::from({7.0, 8.0, 9.0});
    Vector<double, 3> v2 = Vector<double, 3>::from({4.0, 2.0, 1.0});

    auto result = v1 - v2;

    EXPECT_EQ(result[0], 3.0);
    EXPECT_EQ(result[1], 6.0);
    EXPECT_EQ(result[2], 8.0);
}

// Test in-place subtraction (operator-=)
TEST_F(VectorTest, VectorInPlaceSubtraction) {
    Vector<double, 3> v1 = Vector<double, 3>::from({7.0, 8.0, 9.0});
    Vector<double, 3> v2 = Vector<double, 3>::from({4.0, 2.0, 1.0});

    v1 -= v2;

    EXPECT_EQ(v1[0], 3.0);
    EXPECT_EQ(v1[1], 6.0);
    EXPECT_EQ(v1[2], 8.0);
}

// Test scalar multiplication
TEST_F(VectorTest, ScalarMultiplication) {
    Vector<double, 3> v = Vector<double, 3>::from({1.0, 2.0, 3.0});

    v *= 2.0;

    EXPECT_EQ(v[0], 2.0);
    EXPECT_EQ(v[1], 4.0);
    EXPECT_EQ(v[2], 6.0);
}

// Test scalar division
TEST_F(VectorTest, ScalarDivision) {
    Vector<double, 3> v = Vector<double, 3>::from({2.0, 4.0, 6.0});

    v /= 2.0;

    EXPECT_EQ(v[0], 1.0);
    EXPECT_EQ(v[1], 2.0);
    EXPECT_EQ(v[2], 3.0);
}

// Test dot product
TEST_F(VectorTest, DotProduct) {
    Vector<double, 3> v1 = Vector<double, 3>::from({1.0, 2.0, 3.0});
    Vector<double, 3> v2 = Vector<double, 3>::from({4.0, 5.0, 6.0});

    double dot = v1 * v2;

    EXPECT_DOUBLE_EQ(dot, 32.0);  // 1*4 + 2*5 + 3*6 = 32
}

// Test norm (magnitude)
TEST_F(VectorTest, NormCalculation) {
    Vector<double, 3> v = Vector<double, 3>::from({3.0, 4.0, 0.0});

    double norm = v.norm();

    EXPECT_DOUBLE_EQ(norm, 5.0);  // sqrt(3^2 + 4^2) = 5
}

// Test normalization
TEST_F(VectorTest, Normalization) {
    Vector<double, 3> v = Vector<double, 3>::from({3.0, 4.0, 0.0});

    v.normalize();

    EXPECT_DOUBLE_EQ(v[0], 3.0 / 5.0);
    EXPECT_DOUBLE_EQ(v[1], 4.0 / 5.0);
    EXPECT_DOUBLE_EQ(v[2], 0.0);
}

// Test projection
TEST_F(VectorTest, Projection) {
    Vector<double, 3> v1 = Vector<double, 3>::from({2.0, 3.0, 4.0});
    Vector<double, 3> v2 = Vector<double, 3>::from({1.0, 0.0, 0.0});

    auto projection = v1.project_onto(v2);

    EXPECT_DOUBLE_EQ(projection[0], 2.0);
    EXPECT_DOUBLE_EQ(projection[1], 0.0);
    EXPECT_DOUBLE_EQ(projection[2], 0.0);
}

// Test cross product
TEST_F(VectorTest, CrossProduct) {
    Vector<double, 3> v1 = Vector<double, 3>::from({1.0, 0.0, 0.0});
    Vector<double, 3> v2 = Vector<double, 3>::from({0.0, 1.0, 0.0});

    auto cross = v1.cross(v2);

    EXPECT_DOUBLE_EQ(cross[0], 0.0);
    EXPECT_DOUBLE_EQ(cross[1], 0.0);
    EXPECT_DOUBLE_EQ(cross[2], 1.0);
}

// Test equality operator
TEST_F(VectorTest, EqualityOperator) {
    Vector<double, 3> v1 = Vector<double, 3>::from({1.0, 2.0, 3.0});
    Vector<double, 3> v2 = Vector<double, 3>::from({1.0, 2.0, 3.0});

    EXPECT_TRUE(v1 == v2);
}

// Test inequality operator
TEST_F(VectorTest, InequalityOperator) {
    Vector<double, 3> v1 = Vector<double, 3>::from({1.0, 2.0, 3.0});
    Vector<double, 3> v2 = Vector<double, 3>::from({3.0, 2.0, 1.0});

    EXPECT_TRUE(v1 != v2);
}

// Test ostream
TEST_F(VectorTest, OstreamOutput) {
    Vector<double, 3> v = Vector<double, 3>::from({1.0, 2.0, 3.0});

    std::ostringstream oss;
    oss << v;

    EXPECT_EQ(oss.str(), "[1, 2, 3]");
}