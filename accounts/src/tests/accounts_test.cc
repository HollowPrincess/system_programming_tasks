#include <../accounts/accounts.cc>
#include <gtest/gtest.h>

TEST(size_test, account_size) {
  My::account user("uname1", "unamee1");

  int size = std::Trait<My::account>::size(user);
  int calculatedSize = sizeof(user.id) + user.name.size() + user.surname.size();

  EXPECT_EQ(size, calculatedSize);
}
TEST(size_test, group_size) {
  My::account user21("uname1", "unamee1");
  My::account user22("uname2", "unamee2");

  My::group group21("group1");
  group21.addUser(user21);
  group21.addUser(user22);

  int size = std::Trait<My::group>::size(group21);
  int calculatedSize = sizeof(group21.id) + group21.name.size() +
                       std::Trait<My::account>::size(user21) +
                       std::Trait<My::account>::size(user22);

  EXPECT_EQ(size, calculatedSize);
}
