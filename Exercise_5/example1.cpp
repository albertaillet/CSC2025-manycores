/*
g++ -o example1 -std=c++17 -pthread -g -Wall -Wextra -Wpedantic -Werror
example1.cpp
*/
#include <iostream>
#include <thread>
#include <atomic>

int main() {
  std::atomic<int> counter{0};

  auto inc = [&counter](const unsigned int nTime) mutable {
    for (unsigned int i = 0; i < nTime; ++i) {
      ++counter;
    }
  };
  // launch two threads to increment the counter
  std::thread increment1{inc, 100000};
  std::thread increment2{inc, 100000};
  increment1.join();
  increment2.join();
  std::cout << "Expected value:   200000" << "\n";
  std::cout << "Calculated value: " << counter << "\n";
  return 0;
}
