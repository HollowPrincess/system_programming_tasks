#pragma once
#include <../param_tests/MyMaskedArray2D.cc>
#include <cstdlib>
#include <iostream>

template <typename Z> class MyMaskedArray2D;

template <typename T> class MyArray2D {
  T **array2DPtr;
  int rows;
  int cols;

public:
  // empty constructor
  MyArray2D() {
    rows = 0;
    cols = 0;
    array2DPtr = nullptr;
  };

  // constructor
  MyArray2D(int row, int col, T *arrayOfNums) : rows(row), cols(col) {
    array2DPtr = new T *[row];
    int counter = 0;
    for (int i = 0; i < row; i++) {
      array2DPtr[i] = new T[col];
    };
    for (int countRow = 0; countRow < row; countRow++) {
      for (int countCol = 0; countCol < col; countCol++) {
        array2DPtr[countRow][countCol] = arrayOfNums[counter];
        counter++;
      }
    };
  }

  MyArray2D(int row, int col) : rows(row), cols(col) {
    array2DPtr = new T *[row];
    for (int i = 0; i < row; i++) {
      array2DPtr[i] = new T[col];
    };
  }

  // copy constructor
  MyArray2D(const MyArray2D &existedArray2D)
      : rows(existedArray2D.rows), cols(existedArray2D.cols) {
    array2DPtr = new T *[existedArray2D.rows];
    for (int i = 0; i < existedArray2D.rows; i++) {
      array2DPtr[i] = new T[existedArray2D.cols];
    };
    for (int countRow = 0; countRow < existedArray2D.rows; countRow++) {
      for (int countCol = 0; countCol < existedArray2D.cols; countCol++) {
        array2DPtr[countRow][countCol] =
            existedArray2D.array2DPtr[countRow][countCol];
      }
    };
  }

  // swap
  void swap(MyArray2D &rightArray2D) {
    T **tmpArray2DPtr = array2DPtr;
    int tmpRows = rows;
    int tmpCols = cols;

    array2DPtr = rightArray2D.array2DPtr;
    rows = rightArray2D.rows;
    cols = rightArray2D.cols;

    rightArray2D.array2DPtr = tmpArray2DPtr;
    rightArray2D.rows = tmpRows;
    rightArray2D.cols = tmpCols;
  }

  // operator=
  MyArray2D &operator=(const MyArray2D &rightArray2D) {
    if (this == &rightArray2D) {
      return *this;
    } else {
      for (int count = 0; count < rows; count++)
        delete[] array2DPtr[count];
      delete[] array2DPtr;

      this->cols = rightArray2D.cols;
      this->rows = rightArray2D.rows;
      MyArray2D<T> tmp(rightArray2D);
      this->swap(tmp);
      return *this;
    };
  }

  MyArray2D operator=(const MyArray2D rightArray2D) {
    for (int count = 0; count < rows; count++)
      delete[] array2DPtr[count];
    delete[] array2DPtr;

    this->cols = rightArray2D.cols;
    this->rows = rightArray2D.rows;
    MyArray2D<T> tmp(rightArray2D);
    this->swap(tmp);
    return *this;
  }

  int getNumOfRows() { return this->rows; };
  int getNumOfCols() { return this->cols; };

  // element-by-element arithmetic operations
  MyArray2D<T> operator*(const MyArray2D &rightArray2D) const {
    if ((rows == rightArray2D.rows) && (cols == rightArray2D.cols)) {
      MyArray2D<T> result(rows, cols);
      for (int countRow = 0; countRow < this->rows; countRow++) {
        for (int countCol = 0; countCol < this->cols; countCol++) {
          result.array2DPtr[countRow][countCol] =
              this->array2DPtr[countRow][countCol] *
              rightArray2D.array2DPtr[countRow][countCol];
        };
      };
      return result;
    } else {
      MyArray2D<T> error;
      return error;
    };
  };

  MyArray2D<T> operator+(const MyArray2D &rightArray2D) const {
    if ((rows == rightArray2D.rows) && (cols == rightArray2D.cols)) {
      MyArray2D<T> result(rows, cols);
      for (int countRow = 0; countRow < this->rows; countRow++) {
        for (int countCol = 0; countCol < this->cols; countCol++) {
          result.array2DPtr[countRow][countCol] =
              this->array2DPtr[countRow][countCol] +
              rightArray2D.array2DPtr[countRow][countCol];
        };
      };
      return result;
    } else {
      MyArray2D<T> error;
      return error;
    };
  };

  MyArray2D<T> operator-(const MyArray2D &rightArray2D) const {
    if ((rows == rightArray2D.rows) && (cols == rightArray2D.cols)) {
      MyArray2D<T> result(rows, cols);
      for (int countRow = 0; countRow < this->rows; countRow++) {
        for (int countCol = 0; countCol < this->cols; countCol++) {
          result.array2DPtr[countRow][countCol] =
              this->array2DPtr[countRow][countCol] -
              rightArray2D.array2DPtr[countRow][countCol];
        };
      };
      return result;
    } else {
      MyArray2D<T> error;
      return error;
    };
  };

  MyArray2D<T> operator/(const MyArray2D &rightArray2D) const {
    if ((rows == rightArray2D.rows) && (cols == rightArray2D.cols)) {
      MyArray2D<T> result(rows, cols);
      for (int countRow = 0; countRow < this->rows; countRow++) {
        for (int countCol = 0; countCol < this->cols; countCol++) {
          result.array2DPtr[countRow][countCol] =
              this->array2DPtr[countRow][countCol] /
              rightArray2D.array2DPtr[countRow][countCol];
        };
      };
      return result;
    } else {
      MyArray2D<T> error;
      return error;
    };
  };

  MyArray2D<T> operator%(const MyArray2D &rightArray2D) const {
    if ((rows == rightArray2D.rows) && (cols == rightArray2D.cols)) {
      MyArray2D<T> result(rows, cols);
      for (int countRow = 0; countRow < this->rows; countRow++) {
        for (int countCol = 0; countCol < this->cols; countCol++) {
          result.array2DPtr[countRow][countCol] =
              this->array2DPtr[countRow][countCol] %
              rightArray2D.array2DPtr[countRow][countCol];
        };
      };
      return result;
    } else {
      MyArray2D<T> error;
      return error;
    };
  };

  // element-by-element logical operations
  MyArray2D<bool> operator&&(const MyArray2D<bool> &rightArray2D) const {
    if ((rows == rightArray2D.rows) && (cols == rightArray2D.cols)) {
      MyArray2D<bool> result(rows, cols);
      for (int countRow = 0; countRow < this->rows; countRow++) {
        for (int countCol = 0; countCol < this->cols; countCol++) {
          result.array2DPtr[countRow][countCol] =
              this->array2DPtr[countRow][countCol] &&
              rightArray2D.array2DPtr[countRow][countCol];
        };
      };
      return result;
    } else {
      MyArray2D<bool> error;
      return error;
    };
  };

  MyArray2D<bool> operator||(const MyArray2D<bool> &rightArray2D) const {
    if ((rows == rightArray2D.rows) && (cols == rightArray2D.cols)) {
      MyArray2D<bool> result(rows, cols);
      for (int countRow = 0; countRow < this->rows; countRow++) {
        for (int countCol = 0; countCol < this->cols; countCol++) {
          result.array2DPtr[countRow][countCol] =
              this->array2DPtr[countRow][countCol] ||
              rightArray2D.array2DPtr[countRow][countCol];
        };
      };
      return result;
    } else {
      MyArray2D<bool> error;
      return error;
    };
  };

  MyArray2D<bool> operator!() const {
    if (this->cols + this->rows > 0) {
      MyArray2D<bool> result(rows, cols);
      for (int countRow = 0; countRow < this->rows; countRow++) {
        for (int countCol = 0; countCol < this->cols; countCol++) {
          result.array2DPtr[countRow][countCol] =
              !this->array2DPtr[countRow][countCol];
        };
      };
      return result;
    } else {
      MyArray2D<bool> error;
      return error;
    };
  };

  // operator[]
  // T &operator[](int &num) const { return this->array2DPtr[num]; };

  // operator() for [][]
  T &operator()(int &rowNum, int &colNum) {
    if ((this->rows > rowNum) && (this->cols > colNum)) {
      return this->array2DPtr[rowNum][colNum];
    } else {
      T *error = new T;
      return *error;
    };
  };

  MyMaskedArray2D<T> operator()(MyArray2D<bool> &mask) {
    if ((this->rows == mask.getNumOfRows()) &&
        (this->cols == mask.getNumOfCols())) {
      MyMaskedArray2D<T> maskedArray(this, &mask);
      // maskedArray->array2DPtr = this;
      // maskedArray->maskPtr = &mask;
      return maskedArray;
    } else {
      std::cerr << "Error: array dimensions don't match\n";
      exit(0);
    };
  };

  ~MyArray2D<T>() {
    if (array2DPtr != nullptr) {
      for (int count = 0; count < rows; count++)
        delete[] array2DPtr[count];
      delete[] array2DPtr;
    };
  };
};
