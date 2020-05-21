/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 * uhunt page: https://uhunt.onlinejudge.org/id/899065
 *
 */

#include <bits/stdc++.h>

using namespace std;
typedef unsigned char byte;
typedef unsigned long long ull;
typedef long long ll;

namespace std {
template<typename T, typename... Args>
  unique_ptr<T> make_unique(Args&&... args) {
    return unique_ptr<T>(new T(forward<Args>(args)...));
  }
}

template <class T = size_t>
T getinput() {
  T input;
  return (std::cin >> input, std::cin.ignore(), input);
}

inline std::string
getln() {
  std::string line;
  return (std::getline(std::cin, line), line);
}

class Solution {
  using queen_t = std::vector<std::pair<size_t, size_t>>;
  queen_t queens;
  size_t  min_moves{ std::numeric_limits<size_t>::max() };

  inline size_t
  position_to_first_diag(size_t row, size_t col) {
    // switch(col) {
    //   case 0: return row + 7;
    //   case 1: return row + 6;
    //   case 2: return row + 5;
    //   case 3: return row + 4;
    //   case 4: return row + 3;
    //   case 5: return row + 2;
    //   case 6: return row + 1;
    //   case 7: return row + 0;
    // }
    return row + (7 - col);
  }

  inline size_t
  position_to_second_diag(size_t row, size_t col) {
    // switch(col) {
    //   case 0: return row + 0;
    //   case 1: return row + 1;
    //   case 2: return row + 2;
    //   case 3: return row + 3;
    //   case 4: return row + 4;
    //   case 5: return row + 5;
    //   case 6: return row + 6;
    //   case 7: return row + 7;
    // }
    return row + col;
  }

  public:

  Solution(const std::string& line) {
    for (size_t ii = 0; ii < line.size(); ii+=2) {
      auto row        = (line[ii] - '0') - 1;
      auto col        = ii >> 1;
      queens.push_back({ row, col });
    }
  }

  bool
  is_under_attack(queen_t::iterator last_queen) {
    size_t row_map{ 0 }, col_map{ 0 }, first_diag_map{ 0 }, second_diag_map{ 0 };
    const auto&row { last_queen->first };
    const auto&col { last_queen->second };
    bool attacked{ false };
    for (auto queen = queens.begin(); queen != last_queen && !attacked; queen++) {
      const auto&row2 { queen->first };
      const auto&col2 { queen->second };
      row_map         |= (1 << row2);
      col_map         |= (1 << col2);
      first_diag_map  |= (1 << position_to_first_diag(row2, col2));
      second_diag_map |= (1 << position_to_second_diag(row2, col2));

      attacked |= row_map & (1 << row);
      attacked |= col_map & (1 << col);
      attacked |= first_diag_map  & (1 << position_to_first_diag(row, col));
      attacked |= second_diag_map & (1 << position_to_second_diag(row, col));
    }
    return attacked;
  }

  size_t
  backtrack(size_t moves, queen_t::iterator queen) {
    size_t moves_to_return { std::numeric_limits<size_t>::max() };
    if (queen != queens.end()) {
      auto& row { queen->first  };
      auto next_queen { std::next(queen) };
      auto original_row{ row };

      for (size_t ii = 0; ii < 8; ii++) {
        auto moves_curr = moves + (original_row != row);
        if (moves_curr < this->min_moves && !is_under_attack(queen)) {
          auto tmp         = backtrack(moves_curr, next_queen);
          moves_to_return  = std::min(moves_to_return, tmp);
        }
        // make a move:
        row = (row + 1) & 7;
      }
    }
    else {
      moves_to_return = moves;
      this->min_moves = std::min(min_moves, moves);
    }

    return moves_to_return;
  }

  size_t
  solve() {
    return backtrack(0, queens.begin());
  };
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::string line;
  std::size_t kk{ 1 };

  while ((line = getln()).size()) {
    Solution solution{ line };
    std::cout << "Case " << kk++ << ": " << solution.solve() << "\n";
  }

  return(0);
}