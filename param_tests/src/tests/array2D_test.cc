#include <../param_tests/MyArray2D.cc>
#include <gtest/gtest.h>

struct array2D_param_for_arithmetical_operators {
  MyArray2D<double> inputLeft;
  MyArray2D<double> inputRight;
  double *output;
};

struct array2D_param_for_logical_operators {
  MyArray2D<double> inputLeft;
  MyArray2D<double> inputRight;
  bool *output;
};

class array2D_test : public ::testing::TestWithParam<
                         array2D_param_for_arithmetical_operators> {};

double arrayLeft[4] = {0.1, 0, -0.3, -1};
double arrayRight[4] = {0.1, 1, -0.3, 1};

double arraySum[4] = {0.2, 1, -0.6, 0};
double arrayProduct[4] = {0.01, 0, 0.09, -1};
double arraySubtraction[4] = {0, -1, 0, -2};
double arrayDivision[4] = {1, 0, 1, -1};
double arrayMod[4] = {0, 0 % 1, 0, -1 % 1};

double arrayWithAnotherSize[2] = {0.1, 0};

MyArray2D<double> left = MyArray2D<double>(2, 2, arrayLeft);
MyArray2D<double> inputRightTrueSize{2, 2, arrayRight};

MyArray2D<double> inputRightFalseSize{2, 1, arrayWithAnotherSize};

TEST_P(array2D_test, sum_operator_test) {
  const array2D_param_for_arithmetical_operators &param = GetParam();
  MyArray2D<double> result = param.inputLeft + param.inputRight;

  EXPECT_EQ(param.output[0], result(0, 0));
  EXPECT_EQ(param.output[1], result(0, 1));
  EXPECT_EQ(param.output[2], result(1, 0));
  EXPECT_EQ(param.output[3], result(1, 1));
}
INSTANTIATE_TEST_CASE_P(
    sum, array2D_test,
    ::testing::Values(array2D_param_for_arithmetical_operators{
        left, inputRightTrueSize, arraySum}));

TEST_P(array2D_test, prod_operator_test) {
  const array2D_param_for_arithmetical_operators &param = GetParam();
  MyArray2D<double> result = param.inputLeft * param.inputRight;

  EXPECT_EQ(param.output[0], result(0, 0));
  EXPECT_EQ(param.output[1], result(0, 1));
  EXPECT_EQ(param.output[2], result(1, 0));
  EXPECT_EQ(param.output[3], result(1, 1));
}
INSTANTIATE_TEST_CASE_P(
    prod, array2D_test,
    ::testing::Values(array2D_param_for_arithmetical_operators{
        left, inputRightTrueSize, arrayProduct}));
