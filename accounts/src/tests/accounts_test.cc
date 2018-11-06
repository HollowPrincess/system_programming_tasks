#include <gtest/gtest.h>
#include <../accounts/accounts.cc>

TEST(size_test, account_size) {
  My::account user1("uname1", "unamee1");

  int size = std::Trait<My::account>::size(user1);
  int calculatedSize =
      sizeof(user1.id) + user1.name.size() + user1.surname.size();

  EXPECT_EQ(size, calculatedSize);
}
TEST(size_test, group_size) {
  My::account user1("uname1", "unamee1");
  My::account user2("uname2", "unamee2");

  My::group group1("group1");
  group1.addUser(user1);
  group1.addUser(user2);

  int size = std::Trait<My::group>::size(group1);
  int calculatedSize = sizeof(group1.id) + group1.name.size() +
                       std::Trait<My::account>::size(user1) +
                       std::Trait<My::account>::size(user2);

  EXPECT_EQ(size, calculatedSize);
}
