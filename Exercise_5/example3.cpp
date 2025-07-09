/*
g++ -o example3 -std=c++17 -pthread -g -Wall -Wextra -Wpedantic -Werror
example3.cpp
*/

#include <atomic>
#include <iostream>
#include <thread>
#include <unistd.h>

int main() {
  std::atomic_uint counter{0};
  auto inc = [&counter](unsigned int nTimes){
    for (unsigned int i = 0; i < nTimes; ++i) {
      usleep(100);
      ++counter;
    }
  };
  // launch two threads to increment the counter
  std::thread increment1{inc, 100000};
  std::thread increment2{inc, 1000000000};
  increment1.join();
  increment2.join();
  std::cout << "Expected value:   1000100000" << "\n";
  std::cout << "Calculated value: " << counter << "\n";
  return 0;
}
