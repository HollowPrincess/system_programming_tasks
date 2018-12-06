#pragma once
#include <math.h>
#include <mutex>
#include <thread>
#include <vector>

unsigned int n = std::thread::hardware_concurrency();
std::vector<std::thread> threads{n};
std::mutex mutex;

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

    bool isFirstBusy = false;
    bool isSecondBusy = false;
    unsigned int thr1iter = n;
    unsigned int thr2iter = n;

    mutex.lock();
    for (unsigned int iter = 0; iter < n; iter++) {
      if (!threads[iter].joinable()) {
        threads[iter] = std::thread{parallel_sorting<T, Iter>, beginElement,
                                    rightArrayCurrentElement};
        thr1iter = iter;
        isFirstBusy = true;
        break;
      };
    };

    for (unsigned int iter = 0; iter < n; iter++) {
      if (!threads[iter].joinable()) {
        threads[iter] = std::thread{parallel_sorting<T, Iter>,
                                    rightArrayCurrentElement, endElement};
        thr2iter = iter;
        isSecondBusy = true;
        break;
      };
    };
    mutex.unlock();

    if (thr1iter < n) {
      threads[thr1iter].join();
    };
    if (thr2iter < n) {
      threads[thr2iter].join();
    };

    if (!isFirstBusy) {
      parallel_sorting<T>(beginElement, rightArrayCurrentElement);
    };

    if (!isSecondBusy) {
      parallel_sorting<T>(rightArrayCurrentElement, endElement);
    };

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
