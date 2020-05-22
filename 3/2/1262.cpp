#include <bits/stdc++.h>

template <class T = size_t>
T getinput() {
  T input;
  return (std::cin >> input, std::cin.ignore(), input);
}

class Solution {
  using board_t = std::vector<std::string>;
  board_t first_board{ 5,  std::string(6, ' ') };
  board_t second_board{ 5, std::string(6, ' ') };

  template <class predicate>
  bool
  backtracking(size_t                              index_board,
               std::string&                        anagram1,
               std::string&                        anagram2,
               const std::vector<std::bitset<26>>& grid1,
               const std::vector<std::bitset<26>>& grid2,
               predicate&                          pred)
  {
    bool found{ false };
    if (index_board < first_board.size()) {
      for (size_t jj = 0; jj < first_board[index_board].size() && !found; jj++) {
        char first  { first_board[index_board][jj] };
        char second { second_board[index_board][jj] };
        if (grid2[index_board].test(first - 'A') ||
            grid1[index_board].test(second - 'A'))
        {
          anagram1[index_board] = first;
          anagram2[index_board] = second;
          found = backtracking(index_board + 1,
                               anagram1,
                               anagram2,
                               grid1,
                               grid2,
                               pred);
        }
      }
    }
    else {
      found = pred(anagram1, anagram2);
    }
    return found;
  }

public:

  Solution() {

  }

  void
  set_first_board(const std::string& line, size_t pos) {
    for (size_t ii = 0; ii < first_board.size(); ii++) {
      first_board[ii].at(pos) = line[ii];
    }
  }

  void
  set_second_board(const std::string& line, size_t pos) {
    for (size_t ii = 0; ii < second_board.size(); ii++) {
      second_board[ii].at(pos) = line[ii];
    }
  }

  std::string
  solve(size_t kth) {
    static std::string anagram1(5, ' ');
    static std::string anagram2(5, ' ');
    std::vector<std::string> anagrams;
    std::unordered_set<std::string> first_map, second_map, inserted_anagrams;
    std::string kth_anagram;
    std::function<bool(const std::string&, const std::string&)> pred {
      [&](const std::string& anagram1, const std::string& anagram2) {
        first_map.insert(anagram1);
        second_map.insert(anagram2);

        if (anagram1 < anagram2) {
          if (second_map.count(anagram1) && !inserted_anagrams.count(anagram1)) {
            inserted_anagrams.insert(anagram1);
            if (inserted_anagrams.size() == kth) {
              kth_anagram = anagram1;
            }
          }

          if (first_map.count(anagram2) && !inserted_anagrams.count(anagram2)) {
            inserted_anagrams.insert(anagram2);
            if (inserted_anagrams.size() == kth) {
              kth_anagram = anagram2;
            }
          }
        }
        else {
          if (first_map.count(anagram2) && !inserted_anagrams.count(anagram2)) {
            inserted_anagrams.insert(anagram2);
            if (inserted_anagrams.size() == kth) {
              kth_anagram = anagram2;
            }
          }
          if (second_map.count(anagram1) && !inserted_anagrams.count(anagram1)) {
            inserted_anagrams.insert(anagram1);
            if (inserted_anagrams.size() == kth) {
              kth_anagram = anagram1;
            }
          }
        }
        return inserted_anagrams.size() >= kth;
      }
    };

    std::vector<std::bitset<26>> grid1(5);
    std::vector<std::bitset<26>> grid2(5);
    std::vector<size_t> possible_solutions(5, 0);
    size_t combinations{ 1 };

    for (size_t ii = 0; ii < 5; ii++) {
      for (size_t jj = 0; jj < 6; jj++) {
        const auto index1 { first_board[ii][jj] - 'A' };
        const auto index2 { second_board[ii][jj] - 'A' };
        grid1[ii].set(index1);
        grid2[ii].set(index2);
      }
      for (size_t jj = 0; jj < 26; jj++) {
        possible_solutions[ii] += (grid1[ii].test(jj) && grid2[ii].test(jj));
      }

      combinations *= possible_solutions[ii];
    }

    if (combinations >= kth) {
      bool reverse{ kth >= 7778 / 2 };
      if (reverse) {
        kth = 7778-kth;
      }

      for (auto& board : first_board) {
        if (reverse) {
          std::sort(board.begin(), board.end(), std::greater<char>{});
        }
        else {
          std::sort(board.begin(), board.end());
        }
      }

      for (auto& board : second_board) {
        if (reverse) {
          std::sort(board.begin(), board.end(), std::greater<char>{});
        }
        else {
          std::sort(board.begin(), board.end());
        }
      }

      backtracking(0, anagram1, anagram2, grid1, grid2, pred);
    }
    return kth_anagram;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  size_t test_cases = getinput();
  Solution solution;
  std::string line;

  for (size_t kk = 0; kk < test_cases; kk++) {
    size_t kth{ getinput() };
    for (size_t ii = 0; ii < 12; ii++) {
      std::cin >> line;
      if (ii < 6) {
        solution.set_first_board(line, ii);
      }
      else {
        solution.set_second_board(line, ii - 6);
      }
    }
    const auto anagram{ solution.solve(kth) };
    std::cout << (anagram.empty() ?  "NO" : anagram) << "\n";
  }
}