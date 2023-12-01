#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <utility>

void printMap(const std::map<unsigned int, unsigned int> &map) {
  for (auto it = map.begin(); it != map.end(); it++) {
    std::cout << "key: " << it->first << ", value: " << it->second << std::endl;
  }
}

std::map<unsigned int, unsigned int> container;
const std::string numbers[] = {"one", "two",   "three", "four", "five",
                               "six", "seven", "eight", "nine"};

int main() {
  std::fstream file("input.txt", std::ios::in);
  std::string line;
  unsigned int sum = 0;
  while (std::getline(file, line)) {
    std::cout << "line: " << line << std::endl;
    container.clear();
    int number = 1;
    size_t idx;
    for (const auto &word : numbers) {
      if ((idx = line.find(word)) != std::string::npos) {
        auto pair1 = std::make_pair(idx, number);
        std::cout << "Found " << word << "(" << number << ") at " << idx
                  << std::endl;
        container.insert(pair1);
      }
      if ((idx = line.rfind(word)) != std::string::npos) {
        auto pair = std::make_pair(idx, number);
        std::cout << "Found " << word << "(" << number << ") at " << idx
                  << std::endl;
        container.insert(pair);
      }
      number++;
    }
    if ((idx = line.find_first_of("0123456789")) != std::string::npos) {
      auto pair = std::make_pair(idx, line[idx] - '0');
      container.insert(pair);
    }
    if ((idx = line.find_last_of("0123456789")) != std::string::npos) {
      auto pair = std::make_pair(idx, line[idx] - '0');
      container.insert(pair);
    }
    const int first = container.begin()->second;
    const int last = container.rbegin()->second;
    std::cout << "first: " << first << std::endl;
    std::cout << "last: " << last << std::endl;
    sum += (first * 10);
    sum += last;
    printMap(container);
    std::cout << "-------------------------------------" << std::endl;
  }
  std::cout << sum << std::endl;
  return 0;
}
