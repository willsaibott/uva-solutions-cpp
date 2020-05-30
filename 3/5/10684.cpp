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
  std::vector<int>   _sequence;
  public:

  Solution(size_t size) {
    _sequence.reserve(size + 2);
  }

  void add_value(int value) {
    _sequence.push_back(value);
  }

  int64_t solve() {
    int64_t max_sum      { std::numeric_limits<int64_t>::min() };
    int64_t curr_max_sum { 0 };
    for (size_t ii = 0; ii < _sequence.size(); ii++) {
      curr_max_sum += _sequence[ii];
      max_sum       = std::max(max_sum, curr_max_sum);
      if (curr_max_sum < 0) {
        curr_max_sum = 0;
      }
    }
    return max_sum;
  };
};

int main() {
  std::ios_base::sync_with_stdio(false);
  size_t sequence_size;

  while (std::cin >> sequence_size && sequence_size) {
    Solution solution{ sequence_size };
    for (size_t ii = 0; ii < sequence_size; ii++) {
      solution.add_value(getinput<int>());
    }
    auto max_sum{ solution.solve() };
    if (max_sum > 0) {
      std::cout << "The maximum winning streak is " << max_sum << ".\n";
    }
    else {
      std::cout << "Losing streak.\n";
    }
  }

  return(0);
}