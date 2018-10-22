#include <../param_tests/MyArray2D.cc>
#include <gtest/gtest.h>
#include <typeinfo>

struct array2D_param_for_arithmetical_operators {
  MyArray2D<double> inputLeft;
  MyArray2D<double> inputRight;
  double *output;
};

struct array2D_param_for_logical_operators {
  MyArray2D<bool> inputLeftBool;
  MyArray2D<bool> inputRightBool;
  bool *outputBool;
};

struct array2D_param_for_NOT_operator {
  MyArray2D<bool> inputRightNot;
  bool *outputNot;
};

double arrayLeft[4] = {0.1, 0, -0.3, -1};
double arrayRight[4] = {0.1, 1, -0.3, 1};
double arrayWithAnotherSize[2] = {0.1, 0};
MyArray2D<double> left = MyArray2D<double>(2, 2, arrayLeft);
MyArray2D<double> inputRightTrueSize{2, 2, arrayRight};
MyArray2D<double> inputRightFalseSize{2, 1, arrayWithAnotherSize};

bool arrayLeftBool[4] = {0, 0, 1, 1};
bool arrayRightBool[4] = {0, 1, 0, 1};
bool arrayWithAnotherSizeBool[2] = {0, 1};
MyArray2D<bool> leftBool = MyArray2D<bool>(2, 2, arrayLeftBool);
MyArray2D<bool> inputRightTrueSizeBool{2, 2, arrayRightBool};
MyArray2D<bool> inputRightFalseSizeBool{2, 1, arrayWithAnotherSizeBool};

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
  int arrayLeftLocal[4] = {1, 0, 3, -6};
  int arrayRightLocal[4] = {1, 1, 2, 4};
  int arrayAnswerLocal[4] = {1 % 1, 0 % 1, 3 % 2, -6 % 4};

  MyArray2D<int> leftLocal{2, 2, arrayLeftLocal};
  MyArray2D<int> rightLocal{2, 2, arrayRightLocal};

  MyArray2D<int> result = leftLocal % rightLocal;

  equivalence_test(result, arrayAnswerLocal);
}
INSTANTIATE_TEST_CASE_P(
    _, array2D_test_mod,
    ::testing::Values(array2D_param_for_arithmetical_operators{
        left, inputRightTrueSize, arrayMod}));

TEST(array2D_test_error, mod_operator_test) {
  int arrayLeftLocal[4] = {1, 0, 3, -6};
  int arrayRightLocal[4] = {1, 1};

  MyArray2D<int> leftLocal{2, 2, arrayLeftLocal};
  MyArray2D<int> rightLocal{2, 1, arrayRightLocal};

  MyArray2D<int> result = leftLocal % rightLocal;
  EXPECT_EQ(result.getNumOfCols() + result.getNumOfRows(), 0);
}

class array2D_test_AND
    : public ::testing::TestWithParam<array2D_param_for_logical_operators> {};
class array2D_test_OR
    : public ::testing::TestWithParam<array2D_param_for_logical_operators> {};
class array2D_test_NOT
    : public ::testing::TestWithParam<array2D_param_for_NOT_operator> {};

bool arrayAND[4] = {0, 0, 0, 1};
bool arrayOR[4] = {0, 1, 1, 1};
bool arrayNOT[4] = {1, 0, 1, 0};

// operator &&
TEST_P(array2D_test_AND, AND_operator_test) {
  const array2D_param_for_logical_operators &param = GetParam();
  MyArray2D<bool> result = param.inputLeftBool && param.inputRightBool;

  equivalence_test(result, param.outputBool);
}
INSTANTIATE_TEST_CASE_P(_, array2D_test_AND,
                        ::testing::Values(array2D_param_for_logical_operators{
                            leftBool, inputRightTrueSizeBool, arrayAND}));

TEST(array2D_test_error, AND_operator_test) {
  MyArray2D<bool> result = leftBool && inputRightFalseSizeBool;
  EXPECT_EQ(result.getNumOfCols() + result.getNumOfRows(), 0);
}

// operator ||
TEST_P(array2D_test_OR, OR_operator_test) {
  const array2D_param_for_logical_operators &param = GetParam();
  MyArray2D<bool> result = param.inputLeftBool || param.inputRightBool;

  equivalence_test(result, param.outputBool);
}
INSTANTIATE_TEST_CASE_P(_, array2D_test_OR,
                        ::testing::Values(array2D_param_for_logical_operators{
                            leftBool, inputRightTrueSizeBool, arrayOR}));

TEST(array2D_test_error, OR_operator_test) {
  MyArray2D<bool> result = leftBool || inputRightFalseSizeBool;
  EXPECT_EQ(result.getNumOfCols() + result.getNumOfRows(), 0);
}

// operator !
TEST_P(array2D_test_NOT, NOT_operator_test) {
  const array2D_param_for_NOT_operator &param = GetParam();
  MyArray2D<bool> result = !param.inputRightNot;

  equivalence_test(result, param.outputNot);
}
INSTANTIATE_TEST_CASE_P(_, array2D_test_NOT,
                        ::testing::Values(array2D_param_for_NOT_operator{
                            inputRightTrueSizeBool, arrayNOT}));
