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
  using y_cache_t = std::vector<int64_t>;
  using x_cache_t = std::vector<y_cache_t>;
  using cache_t = std::vector<x_cache_t>;

  std::vector<std::pair<int64_t, int64_t>> coins;
  size_t               size;
  int64_t              target;
  int64_t              min_coins{ std::numeric_limits<int64_t>::max() };

  public:

  Solution(size_t size, int64_t s) : coins(size, {0,0}), size{ size }, target{ s * s }
  { }

  void set(size_t ii, int64_t conventional, int64_t infotech) {
    coins[ii].first  = conventional;
    coins[ii].second = infotech;
  }

  int64_t
  memoization(size_t coin_idx, int64_t x, int64_t y, cache_t& dp) {
    int64_t minimum_number_coins{ 0 };
    int64_t emod = x*x + y*y;
    auto it { coins.begin() + coin_idx };

    if (emod != target) {
      if (emod > target || it == coins.end()) {
        minimum_number_coins = std::numeric_limits<int64_t>::min();
      }
      else {
        const auto& coin{ *it };
        auto& ref { dp[coin_idx][x][y] };

        if (ref == -1) {
          ref = std::numeric_limits<int64_t>::max();

          for (int64_t ii = 0; x*x + y*y <= target; ii++) {
            int64_t coins = memoization(coin_idx + 1, x, y, dp);
            if (coins >= 0) {
              ref = std::min(ref, ii + coins);
            }
            x += coin.first;
            y += coin.second;
          }
          if (ref == std::numeric_limits<int64_t>::max()) {
            ref = std::numeric_limits<int64_t>::min();
          }
        }

        minimum_number_coins = ref;
      }
    }
    return minimum_number_coins;
  }

  int64_t
  tabulation() {
    int64_t minimum_number_coins{ std::numeric_limits<int64_t>::max() };
    int64_t sqroot = std::sqrt(target);
    cache_t dp(1, x_cache_t(sqroot + 1, y_cache_t(sqroot + 1, std::numeric_limits<int64_t>::max() / 1000)));

    dp[0][0][0] = 0;

    for (size_t ii = 1; ii <= coins.size(); ii++) {
      int64_t x_coin{ coins[ii-1].first  };
      int64_t y_coin{ coins[ii-1].second };

      for (int64_t x = x_coin; x*x + y_coin*y_coin <= target; x++) {
        for (int64_t y = y_coin; x*x + y*y <= target; y++) {
          dp[0][x][y] = std::min(dp[0][x-x_coin][y-y_coin] + 1, dp[0][x][y]);
        }
      }
    }

    for (int64_t xx = 0; xx <= sqroot; xx++) {
      for (int64_t yy = 0; yy <= sqroot; yy++) {
        if (xx*xx + yy*yy == target) {
          minimum_number_coins = std::min(minimum_number_coins, dp[0][xx][yy]);
        }
      }
    }

    return minimum_number_coins < std::numeric_limits<int64_t>::max() / 1000 ?
           minimum_number_coins :
           0;
  }

  int64_t solve() {
    return tabulation();
    // cache_t dp(coins.size(), x_cache_t(301, y_cache_t(301, -1)));
    // return memoization(0, 0, 0, dp);
  };
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::string line;
  std::size_t N = getinput();
  int64_t conventional;
  int64_t infotech;

  for (size_t kk = 1; kk <= N; kk++) {
    size_t size    = getinput();
    int64_t target = getinput<int64_t>();
    Solution solution{ size, target };

    for (size_t ii = 0; ii < size; ii++) {
      std::cin >> conventional >> infotech;
      solution.set(ii, conventional, infotech);
    }

    const auto ways = solution.solve();

    if (ways > 0) {
      std::cout << ways << "\n";
    }
    else {
      std::cout << "not possible\n";
    }
  }

  return(0);
}