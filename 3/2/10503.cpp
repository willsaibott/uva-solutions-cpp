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

class Solution{

  const std::pair<int, int>&        _begin;
  const std::pair<int, int>&        _end;
  std::vector<std::pair<int, int>>  _input;
  size_t                            _total_spaces;


  bool
  backtracking(size_t index, size_t spaces, size_t mask, int left) {
    bool possible{ false };
    if (spaces == 0) {
      possible = left == _end.first;
    }
    else {
      const auto& piece  { _input[index] };
      const auto bit     { 1u << index };
      const auto new_mask{ mask | bit };
      if (piece.first == left) {
        if (spaces > 1) {
          for (size_t ii = 0; ii < _input.size() && !possible; ii++) {
            bool included{ (new_mask & (1u << ii)) != 0u };
            if (!included) {
              possible |= backtracking(ii, spaces - 1, new_mask, piece.second);
            }
          }
        }
        else {
          possible |= piece.second == _end.first;
        }
      }
      else if (piece.second == left) {
        if (spaces > 1) {
          for (size_t ii = 0; ii < _input.size() && !possible; ii++) {
            bool included{ (new_mask & (1u << ii)) != 0u };
            if (!included) {
              possible |= backtracking(ii, spaces - 1, new_mask, piece.first);
            }
          }
        }
        else {
          possible |= piece.first == _end.first;
        }
      }
    }
    return possible;
  }

public:
  Solution(const std::pair<int, int>& begin,
           const std::pair<int, int>& end,
           size_t                     spaces)
    : _begin{ begin }, _end{ end }, _total_spaces{ spaces }
  { }

  void
  add_piece(int first, int second) {
    _input.push_back({ first, second });
  }

  bool
  possible() {
    bool ok{ false };
    for (size_t ii = 0; ii < _input.size() && !ok; ii++) {
      ok |= backtracking(ii, _total_spaces, 0, _begin.second);
    }
    return ok;
  }
};

int main() {
  size_t spaces;
  size_t pieces;
  std::pair<int, int> begin, end;

  while ((std::cin >> spaces >> pieces) && spaces) {
    std::cin >> begin.first >> begin.second
             >> end.first >> end.second;

    Solution solution{ begin, end, spaces };
    for (size_t ii = 0; ii < pieces; ii++) {
      const auto piece_first  = getinput<int>();
      const auto piece_second = getinput<int>();
      solution.add_piece(piece_first, piece_second);
    }
    std::cout << (solution.possible() ? "YES\n" : "NO\n");
  }

}