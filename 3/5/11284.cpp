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

using cost_t = int64_t;
static const auto infinity{ std::numeric_limits<cost_t>::max() };

class Solution {
  using cost_cache_t = std::vector<cost_t>;
  using cache_t      = std::vector<cost_cache_t>;

  // using cache_t;

  std::vector<std::vector<cost_t>> costs;
  std::vector<cost_t>              dvds;
  std::vector<cost_t>              dvd_mask;
  std::vector<int>                 store_map;

  size_t places;
  size_t total_stores;

  public:

  Solution(size_t stores)
    : costs( stores + 1, cost_cache_t(stores + 1, infinity )),
      dvds(stores + 1, 0),
      store_map(stores + 1, -1),
      places{ stores + 1 },
      total_stores{ 0 }
  {
    for (size_t ii = 0; ii < places; ii++) {
      costs[ii][ii] = 0;
    }
    store_map[0] = 0;
    total_stores++;
  }

  void
  set_cost(size_t from, size_t to, cost_t cost) {
    if (from < places && to < places) {
      costs[from][to] = costs[to][from] = std::min(costs[to][from], cost);
    }
  }

  void
  set_dvd(size_t store, cost_t value) {
    // dvds.push_back({ store, value });
    if (!dvds[store]) {
      store_map[total_stores++] = store;
    }
    dvds[store] += value;
  }

  Solution&
  create_node_mask() {
    const size_t max_mask{ (1ull << total_stores) - 1ull };
    dvd_mask.resize(max_mask + 1, 0);
    for (size_t mask = max_mask; mask > 0; mask--) {
      for (size_t ii = 0; ii < total_stores; ii++) {
        const auto bit{ (1ull << ii) };
        if (mask & bit) {
          dvd_mask[mask] += dvds[store_map[ii]];
        }
      }
    }
    return *this;
  }


  Solution&
  apply_floyd_warshall() {
    for (size_t mid = 0; mid < places; mid++) {
      for (size_t start = 0; start < places; start++) {
        for (size_t end = 0; end < places; end++) {
          const auto start_mid_end{ costs[start][mid] + costs[mid][end] };
          auto& start_end{ costs[start][end] };
          if (start_mid_end >= 0 && start_mid_end < start_end) {
            start_end = start_mid_end;
          }
        }
      }
    }
    return *this;
  }

  cost_t
  go_home(size_t index, size_t mask, cache_t& dp) {
    return costs[store_map[index]][store_map[0]] - dvd_mask[mask];
  }

  cost_t
  memoization(size_t index, size_t mask, cache_t& dp) {
    auto& ref{ dp[index][mask] };
    cost_t cost{ infinity };

    if (ref == -1) {
      for (size_t ii = 1; ii < total_stores; ii++) {
        const auto& visit_cost{ costs[store_map[index]][store_map[ii]] };
        const auto bit{ (1ull << ii ) };

        if ((bit & mask)==0) {
          if (visit_cost < infinity) {
            size_t new_mask{ mask | bit };

            const auto dfs{ memoization(ii, new_mask, dp) };
            if (dfs < infinity) {
              cost = std::min(cost, visit_cost + dfs);
            }
          }
        }
      }

      const auto go_home_cost{ go_home(index, mask, dp) };
      if (go_home_cost < infinity) {
        cost = std::min(cost, go_home_cost);
      }

      ref = cost;
    }
    else {
      cost = ref;
    }

    return cost;
  }

  cost_t
  solve() {
    const size_t max_mask{ (1ull << total_stores) - 1ull };
    cache_t dp(places, cost_cache_t(max_mask + 1, -1));
    return create_node_mask().apply_floyd_warshall().memoization(0, 1, dp);
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::size_t N = getinput();
  size_t stores, dvds, roads, from, to, store_index;
  int64_t cost_hundred, cost_cents;
  char decimal_point;

  for (size_t kk = 1; kk <= N; kk++) {
    std::cin >> stores >> roads;
    Solution solution{ stores };

    for (size_t ii = 0; ii < roads; ii++) {
      std::cin >> from >> to >> cost_hundred >> decimal_point >> cost_cents;
      solution.set_cost(from, to, cost_hundred * 100ll + cost_cents);
    }

    std::cin >> dvds;

    for (size_t ii = 0; ii < dvds; ii++) {
      std::cin >> store_index >> cost_hundred >> decimal_point >> cost_cents;
      solution.set_dvd(store_index, cost_hundred * 100ll + cost_cents);
    }

    auto savings{ -solution.solve() };
    if (savings >= 1) {
      std::cout << "Daniel can save $"
                << (savings / 100ll) << "."
                << std:: setw(2) << std::setfill('0') << (savings % 100ll) << "\n";
    }
    else {
      std::cout << "Don't leave the house\n";
    }
  }

  return(0);
}