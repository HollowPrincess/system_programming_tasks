#include <vector>
#include <thread>
#include <mutex>

#include <fstream>
std::ofstream myLog("myLog.txt", std::ofstream::out);

unsigned int n = std::thread::hardware_concurrency();
myLog<<n;
std::vector<std::thread> threads{n};
//std::mutex mutex;

template<typename T, typename Iter>
void parallel_sorting(Iter beginElement, Iter endElement){
        //mutex.lock();
        // end element is element after last element in vector
        // if all elements not divised

        if (beginElement + 1 < endElement) {
                // division
                typename std::vector<T>::iterator leftArrayCurrentElement = beginElement;
                typename std::vector<T>::iterator rightArrayCurrentElement = beginElement;
                advance(rightArrayCurrentElement,
                        round((endElement - 1 - beginElement) / 2) + 1);

                //std::lock_guard<std::mutex> locked(mutex);
                bool isOneThreadBusy=false;
                for(auto& thr : threads) {
                        if(!isOneThreadBusy) {
                                if(thr.joinable()) {
                                        thr=std::thread{parallel_sorting<T>, beginElement, rightArrayCurrentElement};
                                        isOneThreadBusy=true;
                                };
                        }else{
                                if(thr.joinable()) {
                                        thr=std::thread{parallel_sorting<T>, rightArrayCurrentElement, endElement};
                                        thr.join();
                                        break;
                                };
                        };
                };
                parallel_sorting(beginElement, rightArrayCurrentElement);
                parallel_sorting(rightArrayCurrentElement, endElement);

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
                /*
                   for (typename std::vector<T>::iterator iter = beginElement;
                     iter != endElement; iter++) {
                   };*/
        };

        //mutex.unlock();
}
