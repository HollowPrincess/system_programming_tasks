#include <../param_tests/MyArray2D.cc>
#include <../param_tests/MyMaskedArray2D.cc>
#include <../tests/array2D_test.cc>
#include <cstdlib>
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

double arrayMasked[4] = {0.1, 7, -0.3, 7};

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
                            left, inputRightTrueSizeBool, arrayMasked}));

TEST(array2D_test_error, mask_test) {
  // MyMaskedArray2D<double> result = left(inputRightFalseSizeBool);
  ASSERT_DEATH(left(inputRightFalseSizeBool), 0);
}
