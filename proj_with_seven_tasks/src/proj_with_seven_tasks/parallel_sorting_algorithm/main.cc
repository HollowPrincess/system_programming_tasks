#include <chrono>
#include <fstream>
#include <parallel_sort.h>
#include <thread>
#include <vector>

// using myTime = std::chrono::seconds;
// using myTime = std::chrono::milliseconds;
using myTime = std::chrono::microseconds;
// using myTime = std::chrono::nanoseconds;

void lineOut(std::ofstream &myLog) {
  for (int counter = 0; counter < 40; counter++) {
    myLog << '=';
  };
  myLog << '\n';
};

int main() {
  unsigned int k = std::thread::hardware_concurrency();
  std::ofstream myLog("myLog.txt", std::ofstream::out);
  myLog << "Number Of Kernels: " << k << "\n";

  std::vector<myTime> vectorOfIntervals;
  std::vector<int> vecForSort;
  for (int counter = 1024; counter > 0; counter--) {
    vecForSort.push_back(counter);
  };
  int maxSizeOfVec = vecForSort.size();
  std::vector<int> vecCopy;
  std::chrono::time_point<std::chrono::system_clock> start;
  std::chrono::system_clock::duration tseStart;
  std::chrono::time_point<std::chrono::system_clock> end;
  std::chrono::system_clock::duration tseEnd;
  myTime s;
  for (int counter = 0; counter < maxSizeOfVec; counter++) {
    vecCopy = vecForSort;
    vecCopy.pop_back();

    start = std::chrono::system_clock::now();
    parallel_sorting<int>(vecForSort.begin(), vecForSort.end());
    end = std::chrono::system_clock::now();

    tseStart = start.time_since_epoch();
    tseEnd = end.time_since_epoch();

    s = std::chrono::duration_cast<myTime>(tseEnd - tseStart);
    vectorOfIntervals.push_back(s);
    vecForSort = vecCopy;
  };

  myLog << "Time Table: \n";
  lineOut(myLog);
  myLog << "| VecSize: | Duration:       \n";
  myTime elem;

  for (int counter = 1; counter <= maxSizeOfVec; counter++) {
    lineOut(myLog);
    elem = vectorOfIntervals.back();
    myLog << "| " << counter << "        | " << elem.count() << "\n ";
    vectorOfIntervals.pop_back();
  };
  lineOut(myLog);

  return 0;
}
