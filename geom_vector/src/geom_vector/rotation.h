#include <array>
#include <iostream>

template <typename T> class geom_vector {
public:
  std::array<T, 2> beginPoint, endPoint;
  geom_vector(std::array<T, 2> beginPoint, std::array<T, 2> endPoint)
      : beginPoint(beginPoint), endPoint(endPoint){};
};

template <typename T>
bool operator==(const geom_vector<T> &leftVector,
                const geom_vector<T> &rightVector) {
  if ((leftVector.beginPoint != rightVector.beginPoint) ||
      (leftVector.endPoint != rightVector.endPoint)) {
    return false; // I am missing this line in the tests
  };
  return true;
}
template <typename T> void rotation(geom_vector<T> &vec, int degree) {
  degree = degree % 360;
  // transfer to (0,0):
  vec.endPoint[0] = vec.endPoint[0] - vec.beginPoint[0];
  vec.endPoint[1] = vec.endPoint[1] - vec.beginPoint[1];

  if (degree < 0) {
    degree = 360 + degree;
  };

  switch (degree) {
  case 0:
    break;
  case 90:
    std::swap(vec.endPoint[1], vec.endPoint[0]);
    vec.endPoint[1] = -vec.endPoint[1];
    break;
  case 180:
    vec.endPoint[1] = -vec.endPoint[1];
    vec.endPoint[0] = -vec.endPoint[0];
    break;
  case 270:
    std::swap(vec.endPoint[1], vec.endPoint[0]);
    vec.endPoint[0] = -vec.endPoint[0];
    break;
  default:
    std::cerr << "Error: this rotation is not multiple 90 degrees\n";
    exit(0);
  };

  // transfer to beginPoint:
  vec.endPoint[0] = vec.endPoint[0] + vec.beginPoint[0];
  vec.endPoint[1] = vec.endPoint[1] + vec.beginPoint[1];
};
