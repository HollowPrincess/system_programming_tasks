#include <fstream>

template <class T, class ostream_type> class my_ostream_iterator {
  ostream_type *stream;
  int N, currentState;

public:
  my_ostream_iterator(ostream_type &stream, int N) : stream(&stream), N(N) {
    currentState = 0;
  }

  my_ostream_iterator &operator=(T element) {
    currentState++;
    if (currentState == N) {
      *stream << element;
      currentState = 0;
    };
    return *this;
  }

  my_ostream_iterator &operator*() { return *this; }
  my_ostream_iterator &operator++() { return *this; }
  my_ostream_iterator &operator++(int num) { return *this; }

  ~my_ostream_iterator() { stream = nullptr; }
};

int main() {
  std::ofstream myLog("myLog.txt", std::ofstream::out);
  my_ostream_iterator<char, std::ofstream> iter(myLog, 2);
  iter = '1';
  iter = 'h';
  iter = '2';
  iter = 'e';
  iter = '3';
  iter = 'l';
  iter = '4';
  iter = 'l';
  iter = '5';
  iter = 'o';

  return 0;
}
