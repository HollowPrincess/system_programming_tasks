#include "../LineNumberBuffer/LineNumberBuffer.cc"
#include <iostream>
#include <string>

int main() {
  std::streambuf *oldbuf = std::cout.rdbuf();
  LineNumberBuffer *mybuf = new LineNumberBuffer(oldbuf);
  std::cout.rdbuf(mybuf);
  std::cout << std::cin.rdbuf();
  std::cout.rdbuf(oldbuf);
  return 0;
}
