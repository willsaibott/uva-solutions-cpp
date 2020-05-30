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
  std::vector<std::vector<int64_t>> _matrix;
  size_t                            N;

  public:

  Solution(size_t N) : _matrix(2 * N, std::vector<int64_t>(2 * N, 0)), N{ N } {

  }

  void
  set(size_t ii, size_t jj, int64_t value) {
    _matrix[ii][jj]     = value;
    _matrix[ii][jj+N]   = value;
    _matrix[ii+N][jj]   = value;
    _matrix[ii+N][jj+N] = value;
  }

  int64_t
  solve() {
    int64_t max_sum{ std::numeric_limits<int64_t>::min() };
    int64_t curr_sum;

    for (size_t ii = 0; ii < 2* N; ii++) {
      for (size_t jj = 0; jj < 2 * N; jj++) {
        if (jj) {
          _matrix[ii][jj] += _matrix[ii][jj - 1];
        }
      }
    }

    for (size_t col_start = 0; col_start < N; col_start++) {
      for (size_t col_end = col_start; col_end < col_start + N; col_end++) {
        for (size_t row_start = 0; row_start < N; row_start++) {
          curr_sum = 0;
          for (size_t row_end = row_start; row_end < row_start + N; row_end++) {
            curr_sum += _matrix[row_end][col_end];
            if (col_start) {
              curr_sum -= _matrix[row_end][col_start-1];
            }
            max_sum  = std::max(max_sum, curr_sum);
            curr_sum = std::max(0l, curr_sum);
          }
        }
      }
    }
    return max_sum;
  };
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::string line;
  std::size_t test_cases = getinput();

  for (size_t kk = 1; kk <= test_cases; kk++) {
    size_t N = getinput();
    Solution solution{ N };

    for (size_t ii = 0; ii < N; ii++) {
      for (size_t jj = 0; jj < N; jj++) {
        solution.set(ii, jj, getinput<int64_t>());
      }
    }

    std::cout << solution.solve() << "\n";
  }

  return(0);
}