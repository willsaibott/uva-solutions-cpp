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
  std::string get_merge_part_of(const std::string& merged, const std::string& next) {
    long minor = (long)std::min(merged.size(), next.size());
    long substr_length = 0;
    for (long size = 1l; size <= minor; size++) {
      long left = (long) merged.size() - size;
      long right = (long) 0;
      long sz = size;

      while (sz > 0) {
        if (merged[left] != next[right]) {
          break;
        }
        left++;
        right++;
        sz--;
      }
      if (sz > 0) continue;

      substr_length = size;
    }

    return next.substr(substr_length);
  }

public:

  size_t solve(std::vector<std::string> scenes) {
    size_t min_length = std::numeric_limits<size_t>::max();

    std::sort(scenes.begin(), scenes.end());
    do {
      auto merged = *scenes.begin();
      auto next = std::next(scenes.begin());
      while (next != scenes.end()) {
        merged += get_merge_part_of(merged, *next);
        next++;
      }

      min_length = std::min(min_length, merged.size());
    } while(std::next_permutation(scenes.begin(), scenes.end()));
    return min_length;
  };
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::size_t N = getInput();
  std::size_t number_of_scenes;

  for (size_t kk = 1; kk <= N; kk++) {
    std::cin >> number_of_scenes;
    std::vector<std::string> scenes;
    for (auto ii = 0ul; ii < number_of_scenes; ii++) {
      scenes.emplace_back(getInput<std::string>());
    }

    Solution solution;
    std::cout << "Case " << kk << ": " << solution.solve(scenes) << "\n";
  }

  return EXIT_SUCCESS;
}