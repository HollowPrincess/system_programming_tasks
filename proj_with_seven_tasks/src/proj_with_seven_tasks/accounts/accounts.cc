#include <fstream>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>

namespace My {
struct accountsManager {
  std::set<int> accountsBase;
  int maxID;
};
struct groupsManager {
  std::set<int> groupsBase;
  int maxID;
};
accountsManager amanager;
groupsManager gmanager;

class account {
public:
  int id;
  std::string name, surname;
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

class group {
public:
  int id;
  std::string name;
  std::set<My::account> users;

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

  void addUser(My::account user) { users.insert(user); }
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

template <class T> struct Trait;

template <> struct Trait<My::account> {
  static int size(const My::account &user) {
    return sizeof(user.id) + user.name.size() + user.surname.size();
  }
};

template <> struct Trait<My::group> {
  static int size(const My::group &group) {
    int size = sizeof(group.id) + group.name.size();
    for (auto iter = group.users.begin(); iter != group.users.end(); iter++)
      size = size + std::Trait<My::account>::size(*iter);
    return size;
  }
};
} // namespace std

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
