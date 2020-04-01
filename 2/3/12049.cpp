/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 * uhunt page: https://uhunt.onlinejudge.org/id/899065
 *
 */

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <bitset>
#include <utility>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <memory>
#include <queue>
#include <deque>
#include <stack>
#include <sstream>
#include <cmath>
#include <climits>
#include <cstdlib>
#include <string>
#include <iomanip>

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

class Solution {
  std::unordered_multiset<ll> first;
  std::unordered_multiset<ll> second;

  public:

  Solution(size_t s1, size_t s2) {
    first.reserve(s1);
    second.reserve(s2);
  }

  enum list_enum {
    FIRST,
    SECOND
  };

  void add(list_enum list, ll value) {
    if (list == FIRST) {
      first.insert(value);
    }
    else {
      second.insert(value);
    }
  }

  void solve() {
    size_t removed_elements{ 0 };

    for (auto it = first.begin(); it != first.end();) {
      auto elem = *it;
      auto n1 = first.count(elem);
      auto n2 = second.count(elem);
      removed_elements += (size_t) std::abs((double)n2 - (double)n1);
      std::advance(it, n1);
    }

    for (auto it = second.begin(); it != second.end();) {
      auto elem = *it;
      auto n1 = first.count(elem);
      auto n2 = second.count(elem);

      // just count if exist in 2, but not in 1
      removed_elements += n1 ?  0 : n2 - n1;
      std::advance(it, n2);
    }

    std::cout << removed_elements <<  "\n";
  }
};


int main() {
  std::string line;
  size_t tests, first_size, second_size;
  ll value;

  std::cin >> tests;

  for (size_t ii = 0; ii < tests; ii++) {
    std::cin >> first_size >> second_size;

    Solution solution{ first_size, second_size };
    for (size_t jj = 0; jj < first_size; jj++) {
      solution.add(Solution::FIRST,  (std::cin >> value, value));
    }
    for (size_t jj = 0; jj < second_size; jj++) {
      solution.add(Solution::SECOND, (std::cin >> value, value));
    }
    solution.solve();
  }

  return(0);
}