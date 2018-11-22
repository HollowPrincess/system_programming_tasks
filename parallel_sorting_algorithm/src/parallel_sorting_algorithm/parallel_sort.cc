#include <fstream>
#include <math.h>
#include <thread>
#include <vector>

long unsigned int n = std::thread::hardware_concurrency();
std::vector<std::thread> threads{n};

template <typename T, typename Iter>
void parallel_sorting(Iter beginElement, Iter endElement) {
  // end element is element after last element in vector
  // if all elements not divised

  if (beginElement + 1 < endElement) {
    // division
    typename std::vector<T>::iterator leftArrayCurrentElement = beginElement;
    typename std::vector<T>::iterator rightArrayCurrentElement = beginElement;
    advance(rightArrayCurrentElement,
            round((endElement - 1 - beginElement) / 2) + 1);

    bool isOneThreadBusy = false;
    for (auto &thr : threads) {
      if (!isOneThreadBusy) {
        if (thr.joinable()) {
          thr = std::thread{parallel_sorting<T, Iter>, beginElement,
                            rightArrayCurrentElement};
          isOneThreadBusy = true;
        };
      } else {
        if (thr.joinable()) {
          thr = std::thread{parallel_sorting<T, Iter>, rightArrayCurrentElement,
                            endElement};
          break;
        };
      };
    };
    for (auto &thr : threads) {
      if (thr.joinable()) {
        thr.join();
      };
    };
    parallel_sorting<T>(beginElement, rightArrayCurrentElement);
    parallel_sorting<T>(rightArrayCurrentElement, endElement);

    // merge sorted arrays
    std::vector<T> tmpVector(endElement - beginElement); // empty

    for (typename std::vector<T>::iterator resultVectorCurrentElement =
             tmpVector.begin();
         resultVectorCurrentElement != tmpVector.end();
         resultVectorCurrentElement++) {
      if ((rightArrayCurrentElement == endElement) ||
          (*leftArrayCurrentElement < *rightArrayCurrentElement)) {
        *resultVectorCurrentElement = *leftArrayCurrentElement;
        leftArrayCurrentElement++;
      } else {
        *resultVectorCurrentElement = *rightArrayCurrentElement;
        rightArrayCurrentElement++;
      };
    };

    typename std::vector<T>::iterator resultVectorCurrentElement =
        tmpVector.begin();
    for (typename std::vector<T>::iterator iter = beginElement;
         iter != endElement; iter++, resultVectorCurrentElement++) {
      *iter = *resultVectorCurrentElement;
    };
  };
}

int main() {
  unsigned int k = std::thread::hardware_concurrency();
  std::ofstream myLog("myLog.txt", std::ofstream::out);
  myLog << k;
  std::vector<int> vec{5, 3, 4, 2};
  parallel_sorting<int>(vec.begin(), vec.end());
  return 0;
}
