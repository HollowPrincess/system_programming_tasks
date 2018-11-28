#include <chrono>
#include <fstream>
#include <parallel_sort.h>
#include <thread>
#include <vector>

// using seconds = std::chrono::duration<long, long>;

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

  std::vector<std::chrono::microseconds> vectorOfIntervals;
  std::vector<int> vecForSort = {5, 3, 4, 2};
  int maxSizeOfVec = vecForSort.size();
  std::vector<int> vecCopy;
  for (int counter = 0; counter < maxSizeOfVec; counter++) {
    vecCopy = vecForSort;
    vecCopy.pop_back();
    auto now = std::chrono::system_clock::now();
    parallel_sorting<int>(vecForSort.begin(), vecForSort.end());
    std::chrono::system_clock::duration tse = now.time_since_epoch();
    std::chrono::microseconds s =
        std::chrono::duration_cast<std::chrono::microseconds>(tse);
    vectorOfIntervals.push_back(s);
    vecForSort = vecCopy;
  };

  myLog << "Time Table: \n";
  lineOut(myLog);
  myLog << "| VecSize: | Duration:       |\n";
  std::chrono::microseconds elem;

  for (int counter = 1; counter <= maxSizeOfVec; counter++) {
    lineOut(myLog);
    elem = vectorOfIntervals.back();
    myLog << "| " << counter << "        | " << elem.count() << "|\n ";
    vectorOfIntervals.pop_back();
  };
  lineOut(myLog);

  return 0;
}
