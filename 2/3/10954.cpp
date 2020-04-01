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
  std::priority_queue<ll, std::vector<ll>, std::greater<ll>> queue;
  ull cost{ 0 };

  public:

  void add(ll value) {
    queue.push(value);
  }

  void solve() {
    ull accumulated = 0;
    while (queue.size() > 1) {
      auto first  { queue.top() }; queue.pop();
      auto second { queue.top() }; queue.pop();
      accumulated = first + second;
      cost += accumulated;
      queue.push(accumulated);
    }
    std::cout << cost << "\n";
  };
};

int main() {
  size_t numbers;
  ll value;
  while(std::cin >> numbers && numbers) {
    Solution solution;
    for (size_t ii = 0; ii < numbers; ii++) {
      solution.add((std::cin >> value, value));
    }
    solution.solve();
  }


  return(0);
}