template <typename T>
class MyArray2D{
public:
  T** array2DPtr;
	int rows;
	int cols;

  //empty constructor
	MyArray2D() {
    rows=0;
    cols=0;
  };

  //constructor
	MyArray2D(int row, int col, double* arrayOfNums) :rows(row), cols(col) {
		double **array2D = new double *[row];
		int counter = 0;
		for (int i = 0; i < row; i++) {
			array2D[i] = new double[col];
		};
		for (int countRow = 0; countRow < row; countRow++) {
			for (int countCol = 0; countCol < col; countCol++) {
				array2D[countRow][countCol] = arrayOfNums[counter];
				counter++;
			}
		};
		array2DPtr = array2D;
	}

  MyArray2D(int row, int col) :rows(row), cols(col) {
		double **array2D = new double *[row];
		array2DPtr = array2D;
	}

  //copy constructor
	MyArray2D(const MyArray2D &existedArray2D) :rows(existedArray2D.rows), cols(existedArray2D.cols) {
		double **array2D = new double *[existedArray2D.rows];
		int counter = 0;
		for (int i = 0; i < existedArray2D.rows; i++) {
			array2D[i] = new double[existedArray2D.cols];
		};
		for (int countRow = 0; countRow < existedArray2D.rows; countRow++) {
			for (int countCol = 0; countCol < existedArray2D.cols; countCol++) {
				array2D[countRow][countCol] = existedArray2D.array2DPtr[countRow][countCol];
			}
		};
		array2DPtr = array2D;
	}

  //operator=
  MyArray2D& operator=(const MyArray2D &rightArray2D) {
		if (this == rightArray2D) {
			return this;
		}
		else {
			this->cols = rightArray2D.cols;
			this->rows = rightArray2D.rows;
			for (int i = 0; i < cols; i++) {
				for (int j = 0; j < rows; j++) {
					this->array2DPtr[j][i] = std::forward(rightArray2D.array2DPtr[j][i]);
				};
			};
			return *this;
		}
	}

  //element-by-element arithmetic operations
	MyArray2D& operator*(const MyArray2D &rightArray2D) const {
		MyArray2D* result = new MyArray2D(rows, cols);
		for (int countRow = 0; countRow < this->rows; countRow++) {
			for (int countCol = 0; countCol < this->cols; countCol++) {
					result->array2DPtr[countRow][countCol] = std::forward(this->array2DPtr[countRow][countCol]*rightArray2D.array2DPtr[countRow][countCol]);
			};
		};
		return *result;
	};

	MyArray2D& operator+(const MyArray2D &rightArray2D) const {
    MyArray2D* result = new MyArray2D(rows, cols);
		for (int countRow = 0; countRow < this->rows; countRow++) {
			for (int countCol = 0; countCol < this->cols; countCol++) {
					result->array2DPtr[countRow][countCol] = std::forward(this->array2DPtr[countRow][countCol]+rightArray2D.array2DPtr[countRow][countCol]);
			};
		};
		return *result;
	};

	MyArray2D& operator-(const MyArray2D &rightArray2D) const {
    MyArray2D* result = new MyArray2D(rows, cols);
		for (int countRow = 0; countRow < this->rows; countRow++) {
			for (int countCol = 0; countCol < this->cols; countCol++) {
					result->array2DPtr[countRow][countCol] = std::forward(this->array2DPtr[countRow][countCol]-rightArray2D.array2DPtr[countRow][countCol]);
			};
		};
		return *result;
	};

	MyArray2D& operator/(const MyArray2D &rightArray2D) const {
    MyArray2D* result = new MyArray2D(rows, cols);
		for (int countRow = 0; countRow < this->rows; countRow++) {
			for (int countCol = 0; countCol < this->cols; countCol++) {
					result->array2DPtr[countRow][countCol] = std::forward(this->array2DPtr[countRow][countCol]/rightArray2D.array2DPtr[countRow][countCol]);
			};
		};
		return *result;
	};

  MyArray2D& operator%(const MyArray2D &rightArray2D) const {
    MyArray2D* result = new MyArray2D(rows, cols);
		for (int countRow = 0; countRow < this->rows; countRow++) {
			for (int countCol = 0; countCol < this->cols; countCol++) {
					result->array2DPtr[countRow][countCol] = std::forward(this->array2DPtr[countRow][countCol]%rightArray2D.array2DPtr[countRow][countCol]);
			};
		};
		return *result;
	};
/*
	double* operator[] (int num) const {
		return this->array2DPtr[num];
	}

	friend std::ostream &operator<<(std::ostream &out, const matrix& left);
	matrix* operator=(const matrix *left) {
		if (this == left) {
			return this;
		}
		else {

			this->cols = left->cols;
			this->rows = left->rows;
			for (int i = 0; i < cols; i++) {
				for (int j = 0; j < rows; j++) {
					this->someMatrixPtr[j][i] = left->someMatrixPtr[j][i];
				};
			};
			return this;
		}
	};*/

  //element-by-element logical operations
  MyArray2D& operator&&(const MyArray2D &rightArray2D) const {
    MyArray2D* result = new MyArray2D(rows, cols);
		for (int countRow = 0; countRow < this->rows; countRow++) {
			for (int countCol = 0; countCol < this->cols; countCol++) {
					result->array2DPtr[countRow][countCol] = std::forward(this->array2DPtr[countRow][countCol]&&rightArray2D.array2DPtr[countRow][countCol]);
			};
		};
		return *result;
	};

  MyArray2D& operator||(const MyArray2D &rightArray2D) const {
    MyArray2D* result = new MyArray2D(rows, cols);
		for (int countRow = 0; countRow < this->rows; countRow++) {
			for (int countCol = 0; countCol < this->cols; countCol++) {
					result->array2DPtr[countRow][countCol] = std::forward(this->array2DPtr[countRow][countCol]||rightArray2D.array2DPtr[countRow][countCol]);
			};
		};
		return *result;
	};

  MyArray2D& operator!(const MyArray2D &rightArray2D) const {
    MyArray2D* result = new MyArray2D(rows, cols);
		for (int countRow = 0; countRow < this->rows; countRow++) {
			for (int countCol = 0; countCol < this->cols; countCol++) {
					result->array2DPtr[countRow][countCol] = std::forward(!rightArray2D.array2DPtr[countRow][countCol]);
			};
		};
		return *result;
	};

  MyArray2D& operator^(const MyArray2D &rightArray2D) const {
    MyArray2D* result = new MyArray2D(rows, cols);
		for (int countRow = 0; countRow < this->rows; countRow++) {
			for (int countCol = 0; countCol < this->cols; countCol++) {
					result->array2DPtr[countRow][countCol] = std::forward(this->array2DPtr[countRow][countCol]^rightArray2D.array2DPtr[countRow][countCol]);
			};
		};
		return *result;
	};

	~MyArray2D() {
		for (int count = 0; count < rows; count++)
			delete[] array2DPtr[count];
	}
};
/*
std::ostream &operator<<(std::ostream &out, const matrix& left) {
	for (int countRow = 0; countRow < left.rows; countRow++) {
		for (int countCol = 0; countCol < left.cols; countCol++) {
			out << left.someMatrixPtr[countRow][countCol] << " ";
		}
		out << std::endl;
	};
	return out;
}*/




int main(){
  return 0;
}
