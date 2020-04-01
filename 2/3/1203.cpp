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


struct query_t {
  int id;
  int time;

  bool operator<(const query_t& other) const {
    int diff = time - other.time;
    return diff ? diff > 0 : id > other.id;
  }
};

class Solution {
  std::map<int, int>           periods;
  std::priority_queue<query_t> queries;

  public:

  void add(int id, int period) {
    periods[id] = period;
    queries.push(query_t{ id, period });
  }

  std::string solve(size_t kth) {
    std::string output;
    output.reserve(12 * kth);
    for (size_t ii = 0; ii < kth; ii++) {
      auto query{ queries.top() }; queries.pop();
      output += std::to_string(query.id) + "\n";
      query.time += periods[query.id];
      queries.emplace(std::move(query));
    }
    return output;
  };
};

int main() {
  Solution solution;
  string command;
  int period, id;
  size_t kth;

  while (std::cin >> command && command!= "#") {
    std::cin >> id >> period;
    solution.add(id, period);
  }

  std::cout << solution.solve((std::cin >> kth, kth));

  return(0);
}