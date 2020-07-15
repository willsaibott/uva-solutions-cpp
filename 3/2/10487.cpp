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

  std::vector<int64_t>  _numbers;

  public:

  Solution(size_t set_size) {
    _numbers.reserve(set_size);
  }

  void add(int64_t number) {
    _numbers.push_back(number);
  }

  int64_t solve(int64_t target_sum) {
    int64_t best{ 0xcafecafecafell };
    for (size_t ii = 0; ii < _numbers.size() && best != target_sum; ii++) {
      const auto& elem1{ _numbers[ii] };
      for (size_t jj = ii+1; jj < _numbers.size() && best != target_sum; jj++) {
        const auto& elem2{ _numbers[jj] };
        const auto sum{ elem1 + elem2 };
        if (std::abs(target_sum - sum) < std::abs(target_sum - best)) {
          best = sum;
        }
      }
    }
    return best;
  };
};

int main() {
  std::ios_base::sync_with_stdio(false);
  size_t kk{ 1 };
  size_t numbers;
  size_t queries;

  while (std::cin >> numbers && numbers) {
    Solution solution{ numbers };
    for (size_t ii = 0; ii < numbers; ii++) {
      solution.add(getinput<int64_t>());
    }

    std::cin >> queries;
    std::cout << "Case " << kk++ << ":\n";

    for (size_t ii = 0; ii < queries; ii++) {
      int64_t query = getinput<int64_t>();
      std::cout << "Closest sum to " << query
                << " is " << solution.solve(query) << ".\n";
    }
  }


  return(0);
}