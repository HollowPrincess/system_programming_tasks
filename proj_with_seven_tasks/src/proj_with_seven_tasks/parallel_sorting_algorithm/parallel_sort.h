#pragma once
#include <math.h>
#include <thread>
#include <vector>

unsigned int n = std::thread::hardware_concurrency();
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

    bool isBusy = false;
    for (auto &thr : threads) {
      if (!thr.joinable()) {
        thr = std::thread{parallel_sorting<T, Iter>, beginElement,
                          rightArrayCurrentElement};
        thr.join();
        isBusy = true;
        break;
      };
    };

    if (!isBusy) {
      parallel_sorting<T>(beginElement, rightArrayCurrentElement);
    };

    isBusy = false;
    for (auto &thr : threads) {
      if (!thr.joinable()) {
        thr = std::thread{parallel_sorting<T, Iter>, rightArrayCurrentElement,
                          endElement};
        thr.join();
        isBusy = true;
        break;
      };
    };

    if (!isBusy) {
      parallel_sorting<T>(rightArrayCurrentElement, endElement);
    };
    /*for (auto &thr : threads) {
      if (thr.joinable()) {
        thr.join();
      };
    };*/

    // parallel_sorting<T>(beginElement, rightArrayCurrentElement);

    // parallel_sorting<T>(rightArrayCurrentElement, endElement);

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
