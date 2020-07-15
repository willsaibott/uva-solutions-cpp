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
  using cache2_t = std::vector<int64_t>;
  using cache1_t = std::vector<std::vector<int64_t>>;
  using cache_t  = std::vector<std::vector<std::vector<int64_t>>>;
  std::vector<int64_t>                             input;
  size_t                                           N;

  public:

  Solution(size_t N, size_t size_subset)
    : input(N, 0), N{ N }
  { }

  void set(size_t ii, int64_t value) {
    input[ii] = value;
  }

  template<class forward_it>
  int64_t
  memoization(forward_it first,
              forward_it last,
              size_t     index,
              size_t     items_taken,
              size_t     max_items_taken,
              int64_t    sum,
              int64_t    target_sum,
              cache_t&   dp)
  {
    auto it { first + index };
    int64_t ways{ 0 };
    if (items_taken >= max_items_taken) {
      ways = sum == 0;
    }
    else if (it != last) {
      int64_t& ref{ dp[index][items_taken][sum] };
      if (ref >= 0) {
        ways = ref;
      }
      else {
        const auto& value { *it };
        int64_t rest{ (sum + value) % target_sum };
        if (rest < 0) {
          rest += target_sum;
        }
        ref = memoization(first, last, index + 1, items_taken + 1, max_items_taken, rest,             target_sum, dp) +
              memoization(first, last, index + 1, items_taken,     max_items_taken, sum % target_sum, target_sum, dp);
      }
      ways = ref;
    }
    return ways;
  }

  size_t solve(int64_t target_sum, size_t size_subset) {
    cache_t dp(N + 1, cache1_t(size_subset + 1, cache2_t(target_sum, -1)));
    return memoization(input.begin(),
                       input.end(),
                       0,
                       0,
                       size_subset,
                       0,
                       target_sum,
                       dp);
  };
};

int main() {
  std::ios_base::sync_with_stdio(false);
  size_t kk{ 1 };
  size_t size;
  size_t queries;
  size_t items;
  int64_t sum;

  while ( std::cin >> size >> queries && (size || queries)) {
    Solution solution{ size, 2 };
    std::cout << "SET " << kk++ << ":\n";

    for (size_t ii = 0; ii < size; ii++) {
      solution.set(ii, getinput<int64_t>());
    }

    for (size_t ii = 0; ii < queries; ii++) {
      std::cin >> sum >> items;
      std::cout << "QUERY " << (ii + 1) << ": "
                << solution.solve(sum, items) << "\n";
    }
  }

  return(0);
}