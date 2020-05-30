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
  std::vector<int64_t>    input;
  size_t                  max_lis_size{ 0 };
  size_t                  lis_index{ 0 };
  size_t                  N;

  public:

  Solution (size_t N) : input(N, 0), N{ N }
  { }

  void
  set(size_t index, int64_t value) {
    input[index] = value;
  }

  size_t
  solve() {
    std::vector<int64_t> lis;
    auto calculate_lis = [&](int64_t index) {
      const auto& value{ input[index] };
      auto iit = std::lower_bound(lis.begin(), lis.end(), value);
      if (iit == lis.end()) {
        lis.push_back(value);
      }
      else {
        *iit = value;
      }
    };

    for (int64_t index = input.size() - 1; index >= 0; index--) {
      calculate_lis(index);
    }

    for (size_t index = 0; index < input.size(); index++) {
      calculate_lis(index);
    }

    return lis.size();
  };
};

int main() {
  std::ios_base::sync_with_stdio(false);
  size_t test_cases{ getinput() };

  for (size_t kk = 1; kk <= test_cases; kk++) {
    size_t size{ getinput() };
    if (size) {
      Solution solution{ size };
      for (size_t ii = 0; ii < size; ii++) {
        solution.set(ii, getinput<int64_t>());
      }

      std::cout << solution.solve() << "\n";
    }
    else {
      std::cout << "0\n";
    }
  }

  return(0);
}