#include <fstream>
#include <iostream>

#include <string>
#include <tuple>
#include <vector>

enum class ObjectType { NUMBER, SYMBOL, GEAR };

struct Object {
  int position;
  int value;
  int length;
  ObjectType type;
  const char *str();
};

const char *Object::str() {
  switch (type) {
  case ObjectType::NUMBER:
    return "Number";
  case ObjectType::SYMBOL:
    return "Symbol";
  default:
    return "Unrecognized type";
  }
}

std::vector<std::tuple<int, int, int>> gear_map;

int check_relation(const std::vector<Object> &l1,
                   const std::vector<Object> &l2) {
  int sum = 0;
  // l1 against l2
  for (const auto &number : l1) {
    if (number.type != ObjectType::NUMBER)
      continue;
    for (const auto &symbol : l2) {
      if (symbol.type == ObjectType::NUMBER)
        continue;
      int number_position =
          number.position > 0 ? number.position - 1 : number.position;

      if (symbol.position >= number_position &&
          symbol.position <= (number_position + number.length + 1)) {
        sum += number.value;
        bool doesGearExist = false;
        if (symbol.type == ObjectType::GEAR) {
          for (auto &el : gear_map) {
            auto &[no, first, second] = el;
            if (no == symbol.value) {
              second = number.value;
              doesGearExist = true;
            }
          }
          if (!doesGearExist)
            gear_map.push_back(std::make_tuple(symbol.value, number.value, 0));
        }
        break;
      }
    }
  }
  return sum;
}

int check_relation(const std::vector<Object> &l1) {
  int sum = 0;
  // l1 against l2
  for (const auto &number : l1) {
    if (number.type != ObjectType::NUMBER)
      continue;
    for (const auto &symbol : l1) {
      if (symbol.type == ObjectType::NUMBER)
        continue;
      int number_position =
          number.position > 0 ? number.position - 1 : number.position;
      if (symbol.position >= number_position &&
          symbol.position <= (number_position + number.length + 1)) {
        sum += number.value;
        bool doesGearExist = false;
        if (symbol.type == ObjectType::GEAR) {
          for (auto &el : gear_map) {
            auto &[no, first, second] = el;
            if (no == symbol.value) {
              second = number.value;
              doesGearExist = true;
            }
          }
          if (!doesGearExist)
            gear_map.push_back(std::make_tuple(symbol.value, number.value, 0));
        }
        break;
      }
    }
  }
  return sum;
}

std::vector<std::vector<Object>> v;
std::vector<Object> parseLine(std::string_view s);

int main(int argc, char **argv) {
  if (argc < 2)
    return 1;
  std::fstream file(argv[1], std::ios::in);
  if (!file.is_open()) {
    std::cout << "Failed to open " << argv[1] << std::endl;
    return 1;
  }
  std::cout << "Loaded " << argv[1] << std::endl;

  std::string line;
  int line_number = 0;

  while (std::getline(file, line)) {
    v.emplace_back(std::move(parseLine(line)));
    line_number++;
  }

  int sum = 0;
  for (int i = 0; i < line_number; i++) {
    if (i > 0)
      sum += check_relation(v[i], v[i - 1]);
    sum += check_relation(v[i]);
    if (i < (line_number - 1))
      sum += check_relation(v[i], v[i + 1]);
  }
  std::cout << "Result for the first part: " << sum << std::endl;
  int sum_ratios = 0;
  for (auto &gear : gear_map) {
    auto [no, first, second] = gear;
    sum_ratios += (first * second);
  }
  std::cout << "Result for second part: " << sum_ratios << std::endl;
}

std::vector<Object> parseLine(std::string_view s) {
  std::vector<Object> line;
  int pos = 0, length = 0;
  Object found;

  while (s.data() < s.cend()) {

    char tmp[6]{};
    int idx = 0;
    char c = *s.begin();

    if (c == '.') {
      s.remove_prefix(1);
      pos++;
      continue;
    }
    found.position = pos;
    while (c >= '0' && c <= '9') {
      tmp[idx++] = c;
      s.remove_prefix(1);
      c = s[0];
      pos++;
      length++;
    }
    if (tmp[0]) {
      int number = std::stoi(tmp);
      found.value = number;
      found.type = ObjectType::NUMBER;
      found.length = length;
      length = 0;
    }
    if (c != '.' && c != '*' && !tmp[0]) {
      found.type = ObjectType::SYMBOL;
      s.remove_prefix(1);
      pos++;
    }
    if (c != '.' && c == '*' && !tmp[0]) {
      static int gear_number = 0;
      found.type = ObjectType::GEAR;
      found.value = gear_number++;
      s.remove_prefix(1);
      pos++;
    }
    line.push_back(std::move(found));
  }
  return line;
}
