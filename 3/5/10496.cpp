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

struct Point {
  int64_t x;
  int64_t y;
};

class Solution {

  using distance_cache_t = std::vector<int64_t>;
  using cache_t          = std::vector<std::vector<int64_t>>;
  std::vector<Point>                 beepers;
  std::vector<std::vector<int64_t>>  distance;
  size_t                             rows;
  size_t                             cols;

  public:

  Solution(size_t rows, size_t columns, size_t beepers)
    : beepers(beepers+1),
      distance(beepers+1, std::vector<int64_t>(beepers+1, 0)),
      rows{ rows },
      cols{ columns }
  {

  }

  void
  set_start(int64_t x, int64_t y) {
    beepers[0].x = x;
    beepers[0].y = y;
  }

  void
  set_beeper(size_t pos, int64_t x, int64_t y) {
    beepers[pos + 1].x = x;
    beepers[pos + 1].y = y;
  }

  void
  distance_calculate() {
    for (size_t ii = 0; ii < beepers.size(); ii++) {
      for (size_t jj = ii+1; jj < beepers.size(); jj++) {
        distance[ii][jj] = distance[jj][ii] =
          std::abs(beepers[ii].x - beepers[jj].x) +
          std::abs(beepers[ii].y - beepers[jj].y);
      }
    }
  }

  int64_t
  solve() {
    const size_t size    { beepers.size()        };
    const size_t max_mask{ (1ull << size) - 1ull };
    cache_t dp(size, distance_cache_t(max_mask + 1, -1));
    distance_calculate();

    dp[0][0] = 0;

    for (size_t ii = 0; ii < size; ii++) {
      dp[ii][max_mask] = distance[ii][0];
    }

    for (size_t mask = max_mask - 1; mask > 0; mask--) {
      for (size_t ii = 0; ii < size; ii++) {
        const auto bit_from{ (1ull << ii) };
        if (mask & bit_from) {
          for (size_t jj = 0; jj < size; jj++) {
            const auto bit_to{ (1ull << jj) };
            if ((mask & bit_to) == 0) {
              const auto new_mask{ mask | bit_to };
              auto& ref_from { dp[ii][mask]     };
              auto& ref_to   { dp[jj][new_mask] };
              const auto distance_ii_jj{ ref_to + distance[ii][jj] };

              if (ref_from < 0 || ref_from > distance_ii_jj) {
                ref_from = distance_ii_jj;
              }
            }
          }
        }
      }
    }

    return dp[0][1];
  };
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::size_t N = getinput();
  size_t beepers, rows, cols;
  int64_t x, y;

  for (size_t kk = 1; kk <= N; kk++) {
    std::cin >> rows >> cols >> x >> y >> beepers;
    Solution solution{ rows, cols, beepers };
    solution.set_start(x, y);
    for (size_t ii = 0; ii < beepers; ii++) {
      std::cin >> x >> y;
      solution.set_beeper(ii, x, y);
    }
    std::cout << "The shortest path has length " << solution.solve() << "\n";
  }

  return(0);
}