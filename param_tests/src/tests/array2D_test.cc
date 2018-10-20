#include <../param_tests/MyArray2D.cc>
#include <gtest/gtest.h>
#include <typeinfo>

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

double arrayLeft[4] = {0.1, 0, -0.3, -1};
double arrayRight[4] = {0.1, 1, -0.3, 1};
double arrayWithAnotherSize[2] = {0.1, 0};
MyArray2D<double> left = MyArray2D<double>(2, 2, arrayLeft);
MyArray2D<double> inputRightTrueSize{2, 2, arrayRight};
MyArray2D<double> inputRightFalseSize{2, 1, arrayWithAnotherSize};

template <typename T> void equivalence_test(MyArray2D<T> &result, T *answer) {
  ASSERT_EQ(left.getNumOfRows(), result.getNumOfRows());
  for (int rowCounter = 0; rowCounter < result.getNumOfRows(); rowCounter++) {
    for (int colCounter = 0; colCounter < result.getNumOfCols(); colCounter++) {
      if (typeid(answer).name() == typeid(int).name()) {
        EXPECT_EQ(answer[rowCounter * result.getNumOfCols() + colCounter],
                  result(rowCounter, colCounter));
      } else {
        EXPECT_DOUBLE_EQ(
            answer[rowCounter * result.getNumOfCols() + colCounter],
            result(rowCounter, colCounter));
      };
    };
  };
};

/*class array2D_test_error : public ::testing::TestWithParam<
                               array2D_param_for_arithmetical_operators> {};*/

class array2D_test_sum : public ::testing::TestWithParam<
                             array2D_param_for_arithmetical_operators> {};
class array2D_test_product : public ::testing::TestWithParam<
                                 array2D_param_for_arithmetical_operators> {};
class array2D_test_substraction
    : public ::testing::TestWithParam<
          array2D_param_for_arithmetical_operators> {};
class array2D_test_division : public ::testing::TestWithParam<
                                  array2D_param_for_arithmetical_operators> {};
class array2D_test_mod : public ::testing::TestWithParam<
                             array2D_param_for_arithmetical_operators> {};

double arraySum[4] = {0.2, 1, -0.6, 0};
double arrayProduct[4] = {0.01, 0, 0.09, -1};
double arraySubtraction[4] = {0, -1, 0, -2};
double arrayDivision[4] = {1, 0, 1, -1};
double arrayMod[4] = {0, 0 % 1, 0, -1 % 1};

// operator +
TEST_P(array2D_test_sum, sum_operator_test) {
  const array2D_param_for_arithmetical_operators &param = GetParam();
  MyArray2D<double> result = param.inputLeft + param.inputRight;

  equivalence_test(result, param.output);
}
INSTANTIATE_TEST_CASE_P(
    _, array2D_test_sum,
    ::testing::Values(array2D_param_for_arithmetical_operators{
        left, inputRightTrueSize, arraySum}));

TEST(array2D_test_error, sum_operator_test) {
  MyArray2D<double> result = left + inputRightFalseSize;
  EXPECT_EQ(result.getNumOfCols() + result.getNumOfRows(), 0);
}

// operator *
TEST_P(array2D_test_product, prod_operator_test) {
  const array2D_param_for_arithmetical_operators &param = GetParam();
  MyArray2D<double> result = param.inputLeft * param.inputRight;

  equivalence_test(result, param.output);
}
INSTANTIATE_TEST_CASE_P(
    _, array2D_test_product,
    ::testing::Values(array2D_param_for_arithmetical_operators{
        left, inputRightTrueSize, arrayProduct}));

TEST(array2D_test_error, prod_operator_test) {
  MyArray2D<double> result = left * inputRightFalseSize;
  EXPECT_EQ(result.getNumOfCols() + result.getNumOfRows(), 0);
}

// operator -
TEST_P(array2D_test_substraction, minus_operator_test) {
  const array2D_param_for_arithmetical_operators &param = GetParam();
  MyArray2D<double> result = param.inputLeft - param.inputRight;

  equivalence_test(result, param.output);
}
INSTANTIATE_TEST_CASE_P(
    _, array2D_test_substraction,
    ::testing::Values(array2D_param_for_arithmetical_operators{
        left, inputRightTrueSize, arraySubtraction}));

TEST(array2D_test_error, substraction_operator_test) {
  MyArray2D<double> result = left - inputRightFalseSize;
  EXPECT_EQ(result.getNumOfCols() + result.getNumOfRows(), 0);
}

// operator /
TEST_P(array2D_test_division, division_operator_test) {
  const array2D_param_for_arithmetical_operators &param = GetParam();
  MyArray2D<double> result = param.inputLeft / param.inputRight;

  equivalence_test(result, param.output);
}
INSTANTIATE_TEST_CASE_P(
    _, array2D_test_division,
    ::testing::Values(array2D_param_for_arithmetical_operators{
        left, inputRightTrueSize, arrayDivision}));

TEST(array2D_test_error, division_operator_test) {
  MyArray2D<double> result = left / inputRightFalseSize;
  EXPECT_EQ(result.getNumOfCols() + result.getNumOfRows(), 0);
}

// operator %
TEST_P(array2D_test_mod, mod_operator_test) {
  int arrayLeft[4] = {1, 0, 3, -6};
  int arrayRight[4] = {1, 1, 2, 4};
  int arrayAnswer[4] = {1 % 1, 0 % 1, 3 % 2, -6 % 4};

  MyArray2D<int> left{2, 2, arrayLeft};
  MyArray2D<int> right{2, 2, arrayRight};

  MyArray2D<int> result = left % right;

  equivalence_test(result, arrayAnswer);
}
INSTANTIATE_TEST_CASE_P(
    _, array2D_test_mod,
    ::testing::Values(array2D_param_for_arithmetical_operators{
        left, inputRightTrueSize, arrayMod}));

TEST(array2D_test_error, mod_operator_test) {
  int arrayLeft[4] = {1, 0, 3, -6};
  int arrayRight[4] = {1, 1};

  MyArray2D<int> left{2, 2, arrayLeft};
  MyArray2D<int> right{2, 1, arrayRight};

  MyArray2D<int> result = left % right;
  EXPECT_EQ(result.getNumOfCols() + result.getNumOfRows(), 0);
}
