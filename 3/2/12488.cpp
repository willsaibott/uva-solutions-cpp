/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 * uhunt page: https://uhunt.onlinejudge.org/id/899065
 *
 */

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

template <class T = size_t>
T getInput() {
  static T input;
  return (std::cin >> input, std::cin.ignore(), input);
}

class Solution {
  public:
  std::string
  solve(const std::vector<int>& initial_position, const std::vector<int>& final_position) {
    std::vector<int> position = initial_position;
    std::size_t swaps = 0ul;
    for (auto ii = 0l; ii < (ll)final_position.size(); ii++) {
      int car = final_position[ii];
      auto it = std::find(position.begin(), position.end(), car);
      auto index = std::distance(position.begin(), it);
      while (index != ii) {
        std::swap(position[index-1], position[index]);
        index--;
        swaps++;
      }
    }
    return std::to_string(swaps);
  };
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::size_t N;
  while (std::cin >> N) {
    std::vector<int> initial_position;
    std::vector<int> final_position;

    for (size_t ii = 0; ii < N; ii++) {
      initial_position.push_back(getInput<int>());
    }
    for (size_t ii = 0; ii < N; ii++) {
      final_position.push_back(getInput<int>());
    }

    Solution solution;
    std::cout << solution.solve(initial_position, final_position) + "\n";
  }

  return(0);
}