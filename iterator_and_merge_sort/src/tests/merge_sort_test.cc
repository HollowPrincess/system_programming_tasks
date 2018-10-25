#include <../iterator_and_merge_sort/merge_sort.cc>
#include <algorithm>
#include <gtest/gtest.h>
#include <vector>

TEST(merge_sort_test, even_number_of_elements_in_vector) {
  std::vector<int> baseVector = {5, 3, 4, 2};
  std::vector<int> sortedVector = baseVector;
  sort(sortedVector.begin(), sortedVector.end());
  merge_sort<int>(baseVector.begin(), baseVector.end());

  EXPECT_EQ(baseVector, sortedVector);
}
TEST(merge_sort_test, noneven_number_of_elements_in_vector) {
  std::vector<int> baseVector = {5, 3, 4};
  std::vector<int> sortedVector = baseVector;
  sort(sortedVector.begin(), sortedVector.end());
  merge_sort<int>(baseVector.begin(), baseVector.end());

  EXPECT_EQ(baseVector, sortedVector);
}
