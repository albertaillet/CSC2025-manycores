/*
g++ -o range_looping -std=c++17 -pthread -g -Wall -Wextra -Wpedantic -Werror
range_looping.cpp
*/
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

class Tool {
public:
  Tool() : aMember{0} {
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }
  Tool(const Tool & other) : aMember{ other.aMember } {
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }
  void print() const { std::cout << "tool: " << aMember << "\n"; };

private:
  int aMember;
};

void rangeLoop(std::vector<Tool> tools) {
  for (auto & tool : tools) {
    tool.print();
  }
}

int main() {
  // create a vector of 5 Tools
  std::cout << "Creating tools" << "\n";
  std::vector<Tool> tools(5);

  std::cout << "Start range looping" << "\n";
  rangeLoop(tools);

  return 0;
}
