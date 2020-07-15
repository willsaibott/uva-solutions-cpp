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
  using value_cache_t = std::vector<int64_t>;
  using cache_t       = std::vector<value_cache_t>;

  std::vector<int64_t> coins;
  size_t               N;
  int64_t              price;
  int64_t              max_value;

  public:

  Solution(size_t coins, int64_t expense)
  : coins(coins, 0), N{ coins }, price{ expense }, max_value{ expense } {

  }

  void
  set(size_t ii, int64_t coin_value) {
    coins[ii] = coin_value;
    max_value = std::max(max_value, price + coin_value);
  }

  std::pair<int64_t, int64_t>
  tabulation() {
    std::pair<int64_t, int64_t> ans{ std::numeric_limits<int32_t>::max(),
                                     std::numeric_limits<int32_t>::max() };
    int64_t& min_ammount{ ans.first };
    int64_t& number_of_coins{ ans.second };
    value_cache_t dp(max_value + 1, 0);

    dp[0] = 0;

    for (size_t ii = 0; ii < N; ii++) {
      const auto& coin{ coins[ii % N] };

      for (int64_t value = max_value; value >= 0; value--) {
        if (dp[value] && value + coin <= max_value) {
          auto& ref { dp[value + coin] };
          auto& prev{ dp[value] };
          if (ref) {
            ref = std::min(ref, prev + 1);
          }
          else {
            ref = prev + 1;
          }
        }
      }

      dp[coin] = 1;
    }

    auto it = std::find_if(dp.begin() + price,
                           dp.end(),
                           std::bind2nd(std::greater<int>(), 0));

    min_ammount     = it - dp.begin();
    number_of_coins = *it;
    return ans;
  }

  std::pair<int64_t, int64_t>
  solve() {
    return tabulation();
  };
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::size_t N = getinput();
  size_t coins;
  int64_t price;

  for (size_t kk = 1; kk <= N; kk++) {
    std::cin >> price >> coins;
    Solution solution(coins, price);
    for (size_t ii = 0; ii < coins; ii++) {
      solution.set(ii, getinput<int64_t>());
    }
    const auto& pair{ solution.solve() };
    std::cout << pair.first << " " << pair.second  << "\n";
  }

  return(0);
}