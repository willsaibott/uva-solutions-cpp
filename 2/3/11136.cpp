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
  std::multiset<ll> bills;
  ll                cost{ 0 };

  public:

  void add(ll bill) {
    bills.insert(bill);
  }

  void run() {
    if (bills.size() >= 2) {
      auto highest { (std::prev(bills.end())) };
      auto lowest  { (bills.begin()) };
      cost +=  *highest - *lowest;
      bills.erase(highest);
      bills.erase(lowest);
    }
  };

  void solve() {
    std::cout << cost << "\n";
  }
};


int main() {
  std::string line;
  size_t promotions, number_of_bills;
  ll bill;

  while ((std::cin >> promotions) && promotions) {
    Solution solution;
    std::cin.ignore(); // \n

    for (size_t ii = 0; ii < promotions; ii++) {
      std::cin >> number_of_bills;
      for (size_t jj = 0; jj < number_of_bills; jj++) {
        solution.add((std::cin >> bill, bill));
      }
      solution.run();
    }
    solution.solve();
  }

  return(0);
}