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
  std::vector<int64_t> predecessor;
  std::vector<int64_t> lis;
  std::vector<int64_t> lis_idx;
  std::vector<int64_t> values;
  size_t               max_lis_size{ 0 };
  int64_t              root{ 0 };

  public:

  Solution() { }

  void
  add(int64_t value) {
    values.push_back(value);
  }

  std::vector<int64_t> backtrack_lis() {
    std::vector<int64_t> lis_list;
    if (!values.empty()) {
      size_t index = lis.size() - 1;
      lis_list.resize(lis.size());
      while (root >= 0) {
        lis_list[index--] = values[root];
        root = predecessor[root];
      }
    }
    return lis_list;
  }

  std::vector<int64_t> solve() {
    if (values.empty()) { return {}; }

    predecessor.resize(values.size(), 0);
    predecessor[0] = -1;

    for (size_t index = 0; index < values.size(); index++) {
      const auto& value{ values[index] };
      auto it = std::lower_bound(lis.begin(), lis.end(), value);
      if (it == lis.end()) {
        lis.push_back(value);
        lis_idx.push_back(index);
        if (index) {
          predecessor[index] = root;
        }
      }
      else {
        auto last_index    = std::distance(lis.begin(), it);
        auto it_idx        = lis_idx.begin() + last_index;
        predecessor[index] = last_index ? *(it_idx - 1) : -1;
        *it_idx            = index;
        *it                = value;
      }
      root = lis_idx.back();
    }

    return backtrack_lis();
  };
};

int main() {
  std::ios_base::sync_with_stdio(false);
  int64_t value;
  Solution solution;
  while (std::cin >> value) {
    solution.add(value);
  }
  const auto& lis{ solution.solve() };
  std::cout << lis.size() << "\n-\n";
  for (const auto& elem : lis) {
    std::cout << elem << "\n";
  }
  return(0);
}