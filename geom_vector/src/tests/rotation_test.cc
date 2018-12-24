#include <geom_vector/rotation.h>
#include <gtest/gtest.h>

struct param_for_tests {
  int degree;
  geom_vector<int> &output;
};

geom_vector<int> test_vec({1, 1}, {1, 2});

geom_vector<int> vec_rot_90({1, 1}, {2, 1});

geom_vector<int> vec_rot_180({1, 1}, {1, 0});

geom_vector<int> vec_rot_90_left({1, 1}, {0, 1});

class right_rotation : public ::testing::TestWithParam<param_for_tests> {};

TEST(operator_test, _) { EXPECT_FALSE(test_vec == vec_rot_90); }

TEST_P(right_rotation, multiple_90_rotation) {
  param_for_tests param = GetParam();
  geom_vector<int> result_vec = test_vec;
  rotation<int>(result_vec, param.degree);

  EXPECT_EQ(result_vec, param.output);
}
INSTANTIATE_TEST_CASE_P(_, right_rotation,
                        ::testing::Values(param_for_tests{0, test_vec},
                                          param_for_tests{90, vec_rot_90},
                                          param_for_tests{180, vec_rot_180},
                                          param_for_tests{-90,
                                                          vec_rot_90_left}));

TEST(wrong_rotation, not_multiple_90_rotation) {
  EXPECT_EXIT(rotation(test_vec, 1), ::testing::ExitedWithCode(0),
              "Error: this rotation is not multiple 90 degrees");
}
