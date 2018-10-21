#pragma once
#include <../param_tests/MyArray2D.cc>

template <typename T> class MyArray2D;

template <typename Z> class MyMaskedArray2D {

public:
  MyArray2D<Z> *array2DPtr;
  MyArray2D<bool> *maskPtr;

  // operator=
  MyMaskedArray2D &operator=(const Z num) {
    for (int rowCounter = 0; rowCounter < array2DPtr->getNumOfRows();
         rowCounter++) {
      for (int colCounter = 0; colCounter < array2DPtr->getNumOfCols();
           colCounter++) {
        if ((*maskPtr)(rowCounter, colCounter)) {
          (*array2DPtr)(rowCounter, colCounter) = num;
        };
      };
    };
    return *this;
  }
};
