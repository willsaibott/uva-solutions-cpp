#include <bits/stdc++.h>

template <class T = size_t>
T getinput() {
  T input;
  return (std::cin >> input, std::cin.ignore(), input);
}

inline std::string getln() {
  std::string line;
  return (std::getline(std::cin, line), line);
}

class Solution {
  using char_map_t = std::vector<std::vector<size_t>>;
  char_map_t positions_map;

  size_t
  char_to_index(char c) {
    size_t position{ 53 };
    if (c >= 'a' &&  c <= 'z') {
      position = c - 'a';
    }
    else if (c >= 'A' && c <= 'Z') {
      position = c - 'A' + 26;
    }
    return position;
  }

public:

  Solution (const std::string& line)
    : positions_map(52)
  {
    for (size_t ii = 0; ii < 52; ii++) {
      positions_map[ii].reserve(line.size() + 10);
    }
    for (size_t ii = 0; ii < line.size(); ii++) {
      positions_map[char_to_index(line[ii])].push_back(ii);
    }
  }

  std::pair<size_t, size_t>
  query(const std::string& line) {
    std::pair<size_t, size_t> result{ static_cast<size_t>(-1), 0u };
    size_t &first{ result.first }, &last{ result.second };
    size_t last_known_index{ 0 };
    bool answer{ true };

    for (size_t ii = 0; ii < line.size() && answer; ii++) {
      const auto& state{ line[ii] };
      const auto& map { positions_map.at(char_to_index(state)) };
      const auto it = std::lower_bound(map.begin(), map.end(), last_known_index);
      if (it != map.end() && *it >= last_known_index) {
        last  = *it;
        first = std::min(first, *it);
        last_known_index = *it + 1;
      }
      else {
        first = static_cast<size_t>(-1);
        last  = 0;
        answer = false;
      }
    }

    return result;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::string line = getln();
  size_t queries   = getinput();
  Solution solution{ line };
  if (std::cin) {
    for (size_t ii = 0; ii < queries; ii++) {
      const std::pair<size_t, size_t> result = solution.query(getln());
      if (result.first != static_cast<size_t>(-1)) {
        std::cout << "Matched " << result.first << " " << result.second << "\n";
      }
      else {
        std::cout << "Not matched\n";
      }
    }
  }
}