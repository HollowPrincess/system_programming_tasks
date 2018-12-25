#include <atomic>
#include <chrono>
#include <functional>
#include <iostream>
#include <thread>
#include <thread_class/thread_class.h>
#include <utility>

int f1(void *args) {
  for (int i = 0; i < 5; ++i) {
    std::cout << "Thread 1 executing\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  };
  return 0;
};

int f2(void *args) {
  for (int i = 0; i < 5; ++i) {
    std::cout << "Thread 2 executing\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  };
  return 0;
};

int main() {
  thread_class t1(f1);
  thread_class t2(f2);

  t2.join();

  std::cout << "Thread 2 is joinable: " << t2.joinable() << std::endl;

  std::cout << "Threads ids: " << t1.get_id() << " & " << t2.get_id()
            << std::endl;

  t1.swap(t2);

  std::cout << "Threads ids after swap: " << t1.get_id() << " & " << t2.get_id()
            << std::endl;

  t1 = std::move(t2);

  std::cout << "Threads ids after move: " << t1.get_id() << " & " << t2.get_id()
            << std::endl;

  return 0;
}
