#include <../param_tests/MyArray2D.cc>
#include <../param_tests/MyMaskedArray2D.cc>
//#include <cstdlib>
#include <gtest/gtest.h>

struct array2D_param_for_mask {
  MyArray2D<double> inputLeft;
  MyArray2D<bool> inputRight;
  double *output;
};

// mask operator=
class array2D_test_mask
    : public ::testing::TestWithParam<array2D_param_for_mask> {};

/*left is double matrix
 {0.1, 0;
 -0.3, -1}
 right is bool matrix
 {0, 1;
  0, 1};
*/

double arrayLeftMask[4] = {0.1, 0, -0.3, -1};
MyArray2D<double> leftMask = MyArray2D<double>(2, 2, arrayLeftMask);
bool arrayRightBoolMask[4] = {0, 1, 0, 1};
bool arrayWithAnotherSizeBoolMask[2] = {0, 1};
MyArray2D<bool> inputRightTrueSizeBoolMask{2, 2, arrayRightBoolMask};
MyArray2D<bool> inputRightFalseSizeBoolMask{2, 1, arrayWithAnotherSizeBoolMask};

double arrayMasked[4] = {0.1, 7, -0.3, 7};

template <typename T> void equivalence_test(MyArray2D<T> &result, T *answer) {
  ASSERT_EQ(leftMask.getNumOfRows(), result.getNumOfRows());
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

TEST_P(array2D_test_mask, mask_operator_test) {
  array2D_param_for_mask param = GetParam();
  MyMaskedArray2D<double> result = param.inputLeft(param.inputRight);
  result = 7;

  equivalence_test(*result.array2DPtr, param.output); // mask
  EXPECT_EQ(result.array2DPtr, &param.inputLeft);     // address
  EXPECT_EQ(result.maskPtr, &param.inputRight);       // address
}
INSTANTIATE_TEST_CASE_P(_, array2D_test_mask,
                        ::testing::Values(array2D_param_for_mask{
                            leftMask, inputRightTrueSizeBoolMask,
                            arrayMasked}));

TEST(array2D_test_error, mask_test) {
  EXPECT_EXIT(leftMask(inputRightFalseSizeBoolMask),
              ::testing::ExitedWithCode(0),
              "Error: array dimensions don't match");
}
