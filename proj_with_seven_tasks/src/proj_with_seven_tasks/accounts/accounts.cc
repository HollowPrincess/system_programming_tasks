/**
 * @brief Classes which mimik work of accounts and groups on social sites
 */
#include <fstream>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>

namespace My {
/**
 * @brief Struct which contains users IDs and checks is the new ID is unique
 */
struct accountsManager {
  std::set<int> accountsBase;
  int maxID;
};
/**
 * @brief Struct which contains groups IDs and checks is the new ID is unique
 */
struct groupsManager {
  std::set<int> groupsBase;
  int maxID;
};
accountsManager amanager;
groupsManager gmanager;

/**
 * @brief Class which contains information about users (id, name, surname) and
 * creates a new account
 */
class account {
public:
  int id;
  std::string name, surname;
  /**
   * @brief Account constructor
   *
   * @param name Name of a new user
   * @param surname Surname of a new user
   */
  account(std::string name, std::string surname) {
    if (amanager.accountsBase.empty()) {
      amanager.accountsBase.insert(1);
      amanager.maxID = 1;
    } else {
      amanager.maxID += 1;
      this->id = amanager.maxID;
      this->name = name;
      this->surname = surname;
      amanager.accountsBase.insert(amanager.maxID);
    };
  }

  bool operator==(const account &user) const { return (this->id == user.id); }
  bool operator!=(const account &user) const { return !(this->id == user.id); }
  bool operator<(const account &user) const { return (this->id < user.id); }

  ~account() {}
};

/**
 * @brief Class which contains information about groups(id, name, users list who
 * are in the group) and creats a new account
 */
class group {
public:
  int id;
  std::string name;
  std::set<My::account> users;
  /**
   * @brief Group constructor
   *
   * @param name Name of a new group
   */
  group(std::string name) {
    if (gmanager.groupsBase.empty()) {
      gmanager.groupsBase.insert(1);
      gmanager.maxID = 1;
    } else {
      gmanager.maxID += 1;
      this->id = gmanager.maxID;
      this->name = name;
      gmanager.groupsBase.insert(gmanager.maxID);
    };
  }
  /**
   * @brief Method which add a new user into group
   *
   * @param user Name of user class object
   *
   * @return Nothing
   */
  void addUser(My::account user) { users.insert(user); }
  /**
   * @brief Method which drop a user from group
   *
   * @param user Name of user class object
   *
   * @return Nothing
   */
  void dropUser(My::account user) { users.erase(user); }

  ~group() {}
};
} // namespace My

namespace std {

template <> struct hash<My::account> {
  typedef size_t result_type;
  typedef My::account argument_type;
  result_type operator()(const argument_type &user) const {
    return static_cast<result_type>(user.id);
  }
};

/**
 * @brief Template of structure for calculating of control sum
 */
template <class T> struct Trait;

/**
 * @brief Template of structure for calculating of control sum in account
 */
template <> struct Trait<My::account> {
  /**
   * @brief Method which calculates a control sum of user class object
   *
   * @param user Object for calculating the control sum
   *
   * @return Size of user class object
   */
  static int size(const My::account &user) {
    return sizeof(user.id) + user.name.size() + user.surname.size();
  }
};

/**
 * @brief Template of structure for calculating of control sum in group
 */
template <> struct Trait<My::group> {
  /**
   * @brief Method which calculates a control sum of group class object
   *
   * @param group Object for calculating the control sum
   *
   * @return Size of group class object
   */
  static int size(const My::group &group) {
    int size = sizeof(group.id) + group.name.size();
    for (auto iter = group.users.begin(); iter != group.users.end(); iter++)
      size = size + std::Trait<My::account>::size(*iter);
    return size;
  }
};
} // namespace std

/**
 * @brief Entry point
 *
 * Execution of the program
 * starts here.
 *
 * @return Program exit status
 */
int main() {
  My::account user1("uname1", "unamee1");
  My::account user2("uname2", "unamee2");
  My::account user3("uname2", "unamee2");

  std::unordered_set<My::account> myAccounts;
  myAccounts.insert(user1);
  myAccounts.insert(user2);
  myAccounts.insert(user3);

  std::unordered_map<My::account, int> myAccountsMap;
  typedef std::unordered_map<My::account, int> Mymap;
  myAccountsMap.insert(Mymap::value_type(user1, 1));
  myAccountsMap.insert(Mymap::value_type(user2, 2));

  My::group group1("group1");
  group1.addUser(user1);
  group1.addUser(user2);
  // group1.dropUser(user1);

  int size = std::Trait<My::account>::size(user1);
  int calculatedSize =
      sizeof(user1.id) + user1.name.size() + user1.surname.size();

  int gsize = std::Trait<My::group>::size(group1);
  int gcalculatedSize = sizeof(group1.id) + group1.name.size() +
                        std::Trait<My::account>::size(user1) +
                        std::Trait<My::account>::size(user2);
  std::ofstream myLog("myLog.txt", std::ofstream::out);
  myLog << size << "==" << calculatedSize << "\n"
        << gsize << "==" << gcalculatedSize;

  return 0;
}
