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

  std::vector<std::pair<int64_t, int64_t>> input;
  size_t                                   N;
  int64_t                                  budget;

  template < class forward_it>
  int64_t memoization(const forward_it& first,
                      const forward_it& last,
                      size_t            index,
                      int64_t           total_spent,
                      cache_t&          dp)
  {
    auto it{ first + index };
    int64_t ans{ 0 };

    if (total_spent > budget) {
      if (!(budget > 1800 && total_spent <= budget + 200)) {
        return std::numeric_limits<int64_t>::min();
      }
    }

    if (it != last) {
      const auto& entry{ *it };
      const auto& price { entry.first  };
      const auto& favour{ entry.second };
      auto& ref{ dp[index][total_spent] };

      if (ref == -1) {
        auto spent = price + total_spent;
        ref = std::max(memoization(first, last, index + 1, total_spent, dp),
                       favour + memoization(first, last, index + 1, spent, dp));
      }

      ans = ref;
    }
    else if (total_spent <= 2000 && total_spent > budget) {
      ans = std::numeric_limits<int64_t>::min();
    }
    return ans;
  }

  public:

  Solution(size_t N, int64_t budget) :
    input(N, {0, 0}), N{ N }, budget{ budget } {

  }

  void set(size_t ii, int64_t price, int64_t favour) {
    input[ii].first  = price;
    input[ii].second = favour;
  }

  int64_t
  solve() {
    cache_t dp(N, std::vector<int64_t>(budget + 201, -1));
    return memoization(input.begin(), input.end(), 0, 0, dp);
  };
};

int main() {
  std::ios_base::sync_with_stdio(false);
  size_t items;
  int64_t budget;
  int64_t favour;
  int64_t price;

  while (std::cin >> budget >> items) {
    Solution solution{ items, budget };
    for (size_t ii = 0; ii < items; ii++) {
      std::cin >> price >> favour;
      solution.set(ii, price, favour);
    }
    std::cout << solution.solve() << "\n";
  }

  return(0);
}