#include <fstream>
#include <iostream>
#include <string>

int charToNumber(const char c) { return c - '0'; }

int main() {
  std::fstream file("input.txt", std::ios::in);
  std::string line;
  unsigned int sum;
  while (std::getline(file, line)) {
    const int idx_first = line.find_first_of("0123456789", 0);
    const int idx_last = line.find_last_of("0123456789", line.length());
    sum += (line[idx_first] - '0') * 10;
    sum += line[idx_last] - '0';
    std::cout << "line: " << line << "\r\nfirst: " << idx_first
              << "\r\nlast: " << idx_last << std::endl;
  }
  std::cout << sum << std::endl;
  return 0;
}
