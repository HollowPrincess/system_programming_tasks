#include <iostream>
#include <string>

class LineNumberBuffer : public std::streambuf {
  std::streambuf *old;
  bool flagOfNewLine;
  int numOfLine;

public:
  explicit LineNumberBuffer(std::streambuf *b) : old(b) {
    numOfLine = 1;
    flagOfNewLine = true;
  }

protected:
  int_type overflow(int_type c) override {
    if (flagOfNewLine) {
      std::string str = std::to_string(numOfLine) + " ";
      numOfLine++;
      old->sputn(str.data(), str.size());
      flagOfNewLine = false;
    };
    if (c == '\n') {
      flagOfNewLine = true;
    };
    old->sputc(c);
    return c;
  }
};
