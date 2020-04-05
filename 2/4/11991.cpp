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
  T input;
  return (std::cin >> input, std::cin.ignore(), input);
}

inline std::string getln() {
  std::string line;
  return (std::getline(std::cin, line), line);
}

class Solution {
  std::unordered_map<size_t, std::vector<size_t>> elements;
  std::vector<std::pair<size_t, size_t>>          queries;

  public:

  Solution(size_t elements, size_t queries) {
    this->elements.reserve(elements);
    this->queries.reserve(queries);
  }

  void add_element(size_t pos, size_t element) {
    elements[element].push_back(pos+1);
  }

  void add_query(size_t kth, size_t element) {
    queries.push_back({ kth-1, element });
  }

  std::string solve() {
    std::stringstream ss;
    for (const auto& query : queries) {
      const auto& element{ elements[query.second] };
      const auto& kth    { query.first };
      auto result = kth < element.size() ? element[kth] : 0;
      ss << result << "\n";
    }
    return ss.str();
  };
};

int main() {
  std::size_t elements, queries, kth, element;
  while(std::cin >> elements >> queries) {
    Solution solution{ elements, queries };
    for (size_t ii = 0; ii < elements; ii++) {
      solution.add_element(ii, getinput());
    }
    for (size_t ii = 0; ii < queries; ii++) {
      kth     = getinput();
      element = getinput();
      solution.add_query(kth, element);
    }
    std::cout << solution.solve();
  }

  return(0);
}