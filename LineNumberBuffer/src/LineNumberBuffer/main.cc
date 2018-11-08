#include <../LineNumberBuffer/LineNumberBuffer.cc>
#include <iostream>
#include <string>

int main() {
  std::streambuf *oldbuf = std::cout.rdbuf();
  LineNumberBuffer mybuf(oldbuf);
  std::cout.rdbuf(&mybuf);

  std::cout.rdbuf(oldbuf); // recovery of old buf
  return 0;
}
