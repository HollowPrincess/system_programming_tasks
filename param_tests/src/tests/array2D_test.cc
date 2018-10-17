#include <../param_tests/MyArray2D.cc>
#include <gtest/gtest.h>

//подход AAA (arrange, act, assert)
struct array2D_param_for_arithmetical_operators {
  MyArray2D<double> inputLeft;
  MyArray2D<double> inputRight;
  MyArray2D<double> output;
};

class array2D_test : public ::testing::TestWithParam<
                         array2D_param_for_arithmetical_operators> {};

double Array1[4] = {0.1, 0, -0.3, -1};
double Array2[4] = {0.1, 0, -0.3, 1};
double Array3[4] = {0.2, 0, -0.6, 0};
double Array4[2] = {0.1, 0};
MyArray2D<double> Left = MyArray2D<double>(2, 2, Array1);
MyArray2D<double> inputRightTrueSize{2, 2, Array2};
MyArray2D<double> outputSum{2, 2, Array3};

MyArray2D<double> inputRightFalseSize{2, 1, Array4};

INSTANTIATE_TEST_CASE_P(
    arithmetical_operators_test, array2D_test,
    ::testing::Values(array2D_param_for_arithmetical_operators{
        Left, inputRightTrueSize, outputSum}));

TEST_P(array2D_test, sum_operator_test) {
  const array2D_param_for_arithmetical_operators &param = GetParam();
  MyArray2D<double> result = param.inputLeft + param.inputRight;

  EXPECT_EQ(param.output(0, 0), result(0, 0));
  EXPECT_EQ(param.output(0, 1), result(0, 1));
  EXPECT_EQ(param.output(1, 0), result(1, 0));
  EXPECT_EQ(param.output(1, 1), result(1, 1));
}
