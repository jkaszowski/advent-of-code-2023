#include <array>
#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string_view>
#include <tuple>

constexpr const int blue_max = 14;
constexpr const int green_max = 13;
constexpr const int red_max = 12;

std::tuple<int, int, int> parseRound(std::string s);

int main(int argc, char **argv) {
  if (argc < 2)
    return 1;
  std::fstream file(argv[1], std::ios::in);
  if (!file.is_open())
    std::cout << "Failed to open " << argv[1] << std::endl;
  std::cout << "Loaded " << argv[1] << std::endl;

  std::string line;
  int sum = 0;
  long sum_powers = 0;
  while (std::getline(file, line)) {
    bool failed{false};
    int top_red, top_green, top_blue;
    size_t start = line.find(":") + 1;
    size_t end = line.find(";", start);
    int game_id = std::stoi(line.substr(4, start - 4));
    auto [red, green, blue] = parseRound(line.substr(start, end - start));
    top_red = red;
    top_blue = blue;
    top_green = green;

    while (end != line.length()) {
      start = end + 1;
      end = line.find(";", start);
      if (end == std::string::npos)
        end = line.length();
      auto [red, green, blue] = parseRound(line.substr(start, end - start));
      if (red > top_red)
        top_red = red;
      if (green > top_green)
        top_green = green;
      if (blue > top_blue)
        top_blue = blue;
    }
    if (!failed) {
      std::cout << game_id << " OK " << std::endl;
      sum += game_id;
      sum_powers += (top_blue * top_green * top_red);
    }
  }
  std::cout << "Final result: " << sum_powers << std::endl;
  return 0;
}

std::tuple<int, int, int> parseRound(std::string s) {
  int blue = 0, red = 0, green = 0;
  std::stringstream ss(s);
  while (!ss.eof()) {
    int tmp;
    std::string color;
    ss >> tmp >> color;

    if (color[color.length() - 1] == ',')
      color.pop_back();

    if (color == "blue")
      blue = tmp;
    else if (color == "red")
      red = tmp;
    else if (color == "green")
      green = tmp;
  }
  return std::make_tuple(red, green, blue);
}
