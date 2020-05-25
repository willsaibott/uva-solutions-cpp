#include <bits/stdc++.h>

struct comparator {
  inline bool
  operator()(const std::pair<int, int>& p1, const std::pair<int, int> & p2) const {
    return p1.first + p1.second <= p2.first + p2.second;
  }
};

class Solution {
  std::multiset<std::pair<int, int>> containers;
  size_t                             initial_containers;
  size_t                             max_capacity;
  size_t                             sum_capacities;
  std::vector<size_t>                vessels;

public:

  Solution(size_t init) : initial_containers{ init },
                          max_capacity{ 0 },
                          sum_capacities{ 0 }
  {
    vessels.reserve(init + 1);
  }

  void add_vessel(size_t capacity) {
    vessels.push_back(capacity);
    sum_capacities += capacity;
    max_capacity    = std::max(max_capacity, capacity);
  }

  bool
  simulate(size_t greatest_capacity, size_t max_containers) {
    size_t capacity = greatest_capacity;
    size_t containers_used{ 1 };
    bool possible{ true };
    for (size_t ii = 0; ii < vessels.size() && possible; ii++) {
      if (capacity < vessels[ii]) {
        containers_used++;
        capacity = greatest_capacity;
        if (vessels[ii] <= capacity) {
          possible = containers_used <= max_containers;
          capacity -= vessels[ii];
        }
        else {
          possible = false;
        }
      }
      else {
        capacity -= vessels[ii];
      }
    }
    return possible;
  }

  size_t solve(size_t total_containers) {
    if (total_containers > 1) {
      if (total_containers < vessels.size()) {
        size_t min = max_capacity, max = sum_capacities, mid;
        max_capacity = sum_capacities;

        while (min <= max) {
          mid = (min +  (max - min) / 2);
          if (simulate(mid, total_containers)) {
            max_capacity = std::min(max_capacity, mid);
            max = mid - 1;
          }
          else {
            min = mid + 1;
          }
        }
      }
    }
    else {
      max_capacity = sum_capacities;
    }

    return max_capacity;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  size_t vessels, containers, capacity;
  while (std::cin >> vessels >> containers) {
    Solution solution{ vessels };
    for (size_t ii = 0; ii < vessels; ii++) {
      std::cin >> capacity;
      solution.add_vessel(capacity);
    }
    std::cout << solution.solve(containers) << "\n";
  }
}