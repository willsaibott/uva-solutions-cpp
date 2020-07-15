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

  using favour_cache_t = std::vector<int64_t>;
  using dim_cache_t    = std::vector<favour_cache_t>;
  using cache_t        = std::vector<dim_cache_t>;
  std::vector<int64_t>              favour_by_friend;
  std::vector<int64_t>              prices;
  size_t                            friends;
  size_t                            dims;
  int64_t                           tax;
  int64_t                           individual_budget;
  int64_t                           total_budget;



  int64_t calculate_price(int64_t dim_sum_prices, size_t served_dims) {
    return std::ceil((dim_sum_prices + tax) * 1.1l);
  }

  int64_t memoization(size_t dim_idx, size_t served_dims, int64_t dim_sum, cache_t& dp) {
    const int64_t spent{ calculate_price(dim_sum, served_dims) };
    int64_t ans{ 0 };
    if (spent > total_budget || served_dims > 2 * (friends + 1)) {
      ans = std::numeric_limits<int64_t>::lowest();
    }
    else if (dim_idx < dims && spent < total_budget && served_dims < 2 * (friends + 1)) {
      const auto& dim_price { prices[dim_idx]           };
      const auto& dim_favour{ favour_by_friend[dim_idx] };
      auto& ref{ dp[dim_idx][served_dims][spent] };
      if (ref == -1) {
        for (int64_t ii = 0; ii <= 2; ii++) {
          auto new_value{ dim_favour * ii +
                          memoization(dim_idx + 1,
                                      served_dims + ii,
                                      dim_sum + dim_price * ii,
                                      dp) };
          ref = std::max(ref, new_value);
        }
      }
      ans = ref;
    }
    return ans;
  }

  public:

  Solution(size_t N, int64_t budget, int64_t tea_charge, size_t dims)
    : favour_by_friend(dims, 0.0),
      prices(dims, 0.0),
      friends(N),
      dims(dims),
      tax(tea_charge * (N + 1)),
      individual_budget(budget),
      total_budget(budget * ( N + 1))
  { }

  long double mean(long double sum_favour) {
    return sum_favour / (friends + 1);
  }

  void add(size_t dim, int64_t favour) {
    favour_by_friend[dim] += favour;
  }

  void set_price(size_t dim, int64_t price) {
    prices[dim] = price;
  }

  long double solve() {
    cache_t dp(dims, dim_cache_t(2*(dims + 1), favour_cache_t(total_budget + 1, -1)));
    return mean(static_cast<long double>(memoization(0, 0, 0, dp)));
  };
};

int main() {
  std::ios_base::sync_with_stdio(false);
  size_t friends, dims;
  int64_t tea_charge, budget;

  while (std::cin >> friends >> budget >> tea_charge >> dims &&
         (friends || budget || tea_charge || dims))
  {
    Solution solution(friends, budget, tea_charge, dims);

    for (size_t ii = 0; ii < dims; ii++) {
      solution.set_price(ii, getinput<int64_t>());
      for (size_t jj = 0; jj <= friends; jj++) {
        solution.add(ii, getinput<int64_t>());
      }
    }

    std::cout << std::fixed << std::setprecision(2) << solution.solve() << "\n";
  }

  return(0);
}