#include "proj_with_seven_tasks/iterator_and_merge_sort/merge_sort.cc"
#include <gtest/gtest.h>
#include <proj_with_seven_tasks/parallel_sorting_algorithm/parallel_sort.h>
#include <vector>

TEST(parallel_sort_test, equal_res) {
  std::vector<int> baseVector = {5, 3, 4, 2};
  std::vector<int> sortedVector = baseVector;

  merge_sort<int>(sortedVector.begin(), sortedVector.end());
  parallel_sorting<int>(baseVector.begin(), baseVector.end());

  EXPECT_EQ(baseVector, sortedVector);
}
