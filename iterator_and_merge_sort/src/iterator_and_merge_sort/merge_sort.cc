#include <math.h>
#include <vector>

template <typename T, typename Iter>
void merge_sort(Iter beginElement, Iter endElement) {
  // end element is element after last element in vector
  // if all elements not divised

  if (beginElement + 1 < endElement) {
    // division

    typename std::vector<T>::iterator leftArrayCurrentElement = beginElement;

    typename std::vector<T>::iterator rightArrayCurrentElement = beginElement;

    advance(rightArrayCurrentElement,
            round((endElement - 1 - beginElement) / 2) + 1);

    merge_sort<T>(beginElement,
                  rightArrayCurrentElement); // from begin to (middle+1)=end
    merge_sort<T>(rightArrayCurrentElement,
                  endElement); // from begin=(middle+1) to end

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
    for (typename std::vector<T>::iterator iter = beginElement;
         iter != endElement; iter++) {
    };
  };
}
