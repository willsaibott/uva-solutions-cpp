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
  using cache_t = std::vector<std::vector<int64_t>>;
  cache_t dp;
  std::vector<size_t> coin_values{ 1, 5, 10, 25, 50 };

  public:

  Solution() : dp(5, std::vector<int64_t>(30001, -1))
  { }

  int64_t
  memoization(size_t coin_idx, int64_t value) {
    auto it { coin_values.begin() + coin_idx };
    int64_t ways{ 0 };
    if (it != coin_values.end() && *it <= value) {
      const auto& coin{ *it };
      auto& ref{ dp[coin_idx][value] };
      if (ref == -1) {
        ref = std::max(0l, memoization(coin_idx + 1, value));
        while (value >= coin) {
          value -= coin;
          if (dp[coin_idx][value] >= 0) {
            ref += dp[coin_idx][value];
            break;
          }
          ref = std::max(ref, ref + memoization(coin_idx + 1, value));
        }
      }
      ways = ref;
    }
    else {
      ways = value ? std::numeric_limits<int64_t>::min() : 1;
    }
    return ways;
  }

  int64_t solve(int64_t value) {
    return memoization(0, value);
  };
};

int main() {
  std::ios_base::sync_with_stdio(false);
  size_t number;
  Solution solution;

  while (std::cin >> number) {
    int64_t ways{ solution.solve(number) };
    if (ways > 1) {
      std::cout << "There are " << ways << " ways to produce " << number << " cents change.\n";
    }
    else {
      std::cout << "There is only 1 way to produce " << number << " cents change.\n";
    }
  }

  return(0);
}