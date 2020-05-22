#include <bits/stdc++.h>

static size_t seven_segments[] = {
  0b0111111,
  0b0000110,
  0b1011011,
  0b1001111,
  0b1100110,
  0b1101101,
  0b1111101,
  0b0000111,
  0b1111111,
  0b1101111,
};

class Solution {
  std::vector<size_t> led_sequence;

  bool
  backtracking(std::vector<size_t>::iterator led, int value, size_t burned_out) {
    bool possible{ led == led_sequence.end() };
    if (!possible && value < 10 && value >= 0) {
      auto discarded = ((*led) | seven_segments[value]) != seven_segments[value];
      auto rest      = (*led) ^ seven_segments[value];
      discarded     |= (burned_out & *led) != 0u;
      if (!discarded) {
        burned_out = burned_out | rest;
        possible  |= backtracking(std::next(led), value - 1, burned_out);
      }
    }
    return possible;
  }

public:

  void
  add_led(const std::string& line) {
    size_t led_pattern{ 0u };
    for (size_t ii = 0; ii < line.size(); ii++) {
      auto bit{ 1u << ii };
      if (line[ii] == 'Y') {
        led_pattern = led_pattern | bit;
      }
    }
    led_sequence.push_back(led_pattern);
  }

  bool
  solve() {
    bool possible{ false };
    auto begin{ led_sequence.begin() };
    for (int ii = led_sequence.size() - 1; ii < 10 && !possible; ii++) {
      const auto discarded = ((*begin) | seven_segments[ii]) != seven_segments[ii];
      const auto rest      = (*begin) ^ seven_segments[ii];
      size_t burned_out    = rest;
      if (!discarded) {
        possible |= backtracking(std::next(begin), ii - 1, burned_out);
      }
    }
    return possible;
  }
};


int main() {
  size_t seq_size;
  std::string line;

  while (std::cin >> seq_size && seq_size) {
    Solution solution;
    for (size_t ii = 0; ii < seq_size; ii++) {
      std::cin >> line;
      solution.add_led(line);
    }
    std::cout << (solution.solve() ? "MATCH\n" : "MISMATCH\n");
  }

}
