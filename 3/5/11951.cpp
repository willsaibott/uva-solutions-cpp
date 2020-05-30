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
  std::vector<std::vector<size_t>> _matrix;
  size_t rows, cols;
  public:

  Solution(size_t rows, size_t cols)
    : _matrix(rows, std::vector<size_t>(cols, 0)), rows{ rows }, cols{ cols }
  { }

  void
  set(size_t ii, size_t jj, size_t price) {
    _matrix[ii][jj] = price;
    if (jj) {
      _matrix[ii][jj] += _matrix[ii][jj-1];
    }
  }

  std::pair<size_t, size_t>
  solve(size_t budget) {
    size_t max_area{ std::numeric_limits<size_t>::min() };
    size_t cost{ 0 };
    for (size_t col_start = 0; col_start < cols; col_start++) {
      for (size_t col_end = col_start; col_end < cols; col_end++) {
        for (size_t row_start = 0; row_start < rows; row_start++) {
          size_t curr_sum{ 0 };
          size_t curr_area{ 0 };
          for (size_t row_end = row_start; row_end < rows; row_end++) {
            curr_sum += _matrix[row_end][col_end];

            if (col_start) {
              curr_sum -= _matrix[row_end][col_start - 1];
            }

            if (curr_sum <= budget) {
              curr_area = (row_end + 1 - row_start) * (col_end + 1 - col_start);
              if (curr_area > max_area) {
                max_area = std::max(max_area, curr_area);
                cost     = curr_sum;
              }
              else if (curr_area == max_area) {
                cost = std::min(curr_sum, cost);
              }
            }
            else {
              break;
            }
          }
        }
      }
    }
    return { max_area, cost };
  };
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::size_t N = getinput();
  size_t rows, cols, budget;

  for (size_t kk = 1; kk <= N; kk++) {
    std::cin >> rows >> cols >> budget;
    Solution solution{ rows, cols };

    for (size_t ii = 0; ii < rows; ii++) {
      for (size_t jj = 0; jj < cols; jj++) {
        solution.set(ii, jj, getinput());
      }
    }

    const auto answer{ solution.solve(budget) };
    std::cout << "Case #" << kk << ": "
              << answer.first << " " << answer.second << "\n";
  }

  return(0);
}