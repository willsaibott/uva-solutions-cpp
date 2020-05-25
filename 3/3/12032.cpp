#include <bits/stdc++.h>

class Solution {
  std::vector<int> bamboos;
  int              max_diff{ 0 };

public:

  Solution(size_t number_of_bamboos) {
    bamboos.reserve(number_of_bamboos + 1);
  }

  void
  add_bamboo(size_t height) {
    int diff = bamboos.empty() ?  height : (int)height - (int)bamboos.back();
    bamboos.push_back(height);
    max_diff = std::max(max_diff, diff);
  }

  bool
  simulate(int strength) {
    int current_stregth = strength - (int)(bamboos[0] == strength);
    bool possible { bamboos[0] <= strength };
    for (size_t ii = 1; ii < bamboos.size() && possible; ii++) {
      int diff = (int)bamboos[ii] - (int)bamboos[ii-1];
      possible = diff <= current_stregth;
      if (diff == current_stregth) {
        current_stregth--;
      }
    }
    return possible;
  }

  int
  solve() {
    int min = max_diff, max = max_diff + bamboos.size(), mid;
    int max_possible{ max };
    while (min <= max) {
      mid = min + (max - min) / 2;
      if (simulate(mid)) {
        max_possible = std::min(max_possible, mid);
        max = mid - 1;
      }
      else {
        min = mid + 1;
      }
    }
    return max_possible;
  }
};

template <class T = size_t>
T getinput() {
  static T input;
  return (std::cin >> input, std::cin.ignore(), input);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  size_t test_cases = getinput();
  size_t bamboos;

  for (size_t kk = 0; kk < test_cases; kk++) {
    Solution solution{ bamboos = getinput() };
    for (size_t ii = 0; ii < bamboos; ii++) {
      solution.add_bamboo(getinput());
    }
    std::cout << "Case " << kk + 1 << ": " << solution.solve() << "\n";
  }
}