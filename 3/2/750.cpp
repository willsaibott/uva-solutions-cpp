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
  static T input;
  return (std::cin >> input, std::cin.ignore(), input);
}

inline const std::string& getln() {
  static std::string line;
  return (std::getline(std::cin, line), line);
}

class Solution {

  std::array<bool, 9> occupied_rows;
  std::array<bool, 9> occupied_cols;
  std::array<bool, 15> occupied_desc_diag;
  std::array<bool, 15> occupied_asc_diag;

  int addedQueens = 0;
  std::vector<int> queenRows = std::vector<int>(8, 0);
  std::vector<std::vector<int>> solutions;

  int getDescDiagIndex(int row, int col) {
    return 8-row + col-1;
  }

  int getAscDiagIndex(int row, int col) {
    return 8-row + 8-col;
  }

public:

  bool putQueenAt(int row, int col) {
    if (!occupied_rows[row] &&
        !occupied_cols[col] &&
        !occupied_desc_diag[getDescDiagIndex(row, col)] &&
        !occupied_asc_diag[getAscDiagIndex(row, col)])
    {
      occupied_rows[row] = true;
      occupied_cols[col] = true;
      occupied_desc_diag[getDescDiagIndex(row, col)] = true;
      occupied_asc_diag[getAscDiagIndex(row, col)] = true;
      addedQueens++;
      queenRows[col - 1] = row;
      return true;
    }
    return false;
  }

  void removeQueenAt(int row, int col) {
    occupied_rows[row] = false;
    occupied_cols[col] = false;
    occupied_desc_diag[getDescDiagIndex(row, col)] = false;
    occupied_asc_diag[getAscDiagIndex(row, col)] = false;
    addedQueens--;
    queenRows[col - 1] = 0;
  }

  void backtrack(int row, int col) {
    if (addedQueens == 8) {
      solutions.push_back(queenRows);
      return;
    }

    for (int col_ii = col; col_ii <= 8; col_ii++) {
      if (occupied_cols[col_ii]) continue;
      for (int row_ii = 1; row_ii <= 8; row_ii++) {
        if (putQueenAt(row_ii, col_ii)) {
          backtrack(row_ii, col_ii);
          removeQueenAt(row_ii, col_ii);
        }
      }
    }
  }

  void clear() {
    for (auto& col : occupied_cols) {
      col = false;
    }
    for (auto& row : occupied_rows) {
      row = false;
    }
    for (auto& diag : occupied_asc_diag) {
      diag = false;
    }
    for (auto& diag : occupied_desc_diag) {
      diag = false;
    }
  }

  std::string solve(int row, int col) {
    clear();
    putQueenAt(row, col);
    backtrack(1, 1);

    std::stringstream ss;
    ss << "SOLN       COLUMN\n" <<
          " #      1 2 3 4 5 6 7 8\n\n";

    for (std::size_t ii = 1ull; ii <= solutions.size(); ii++) {
      ss << std::right << std::setw(2) << ii << "      ";
      for (int col = 1; col <= 8; col++) {
        auto& sol_row = solutions[ii - 1][col-1];
        ss << sol_row << (col == 8 ? "": " ");
      }
      ss << "\n";
    }
    return ss.str();
  };


};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::string line;
  std::size_t N = getinput();

  int row, col;
  for (size_t kk = 0; kk < N; kk++) {
    if (kk) std::cout << "\n";
    Solution solution;
    std::cin >> row >> col;
    std::cout << solution.solve(row, col);
  }

  return(0);
}