/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 * uhunt page: https://uhunt.onlinejudge.org/id/899065
 * 11239 - Open Source
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
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <list>
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
  std::multiset<ll>                 _black_box;
  std::queue<ll>                    _add_instructions;
  std::queue<size_t>                _get_instructions;

  public:

  void
  get(size_t black_box_size) {
    _get_instructions.push(black_box_size);
  }

  void
  add(ll number) {
    _add_instructions.push(number);
  }

  std::string
  solve() {
    multiset<ll>::iterator it;
    std::string output;
    bool first{ true };
    output.reserve(4*_add_instructions.size());

    while (!_get_instructions.empty()) {
      size_t size_at = _get_instructions.front(); _get_instructions.pop();

      while (_black_box.size() < size_at) {
        ll value = _add_instructions.front(); _add_instructions.pop();

        if (_black_box.size()) {
          ll current_value = *it;
          _black_box.insert(value);

          if (value < current_value) {
            std::advance(it, -1);
          }
        }
        else {
          it = _black_box.insert(value);
        }
      }
      std::advance(it, (int)(!first));
      first = false;

      output += std::to_string(*it) + "\n";

    }
    return output;
  }
};


int main() {
  string output = "";
  std::string line;
  size_t datasets;
  cin >> datasets;
  cin.ignore();

  for (size_t ii = 0; ii < datasets; ii++) {
    Solution solution;
    size_t adds, gets, size;
    ll value;

    std::getline(std::cin, line); // blank line
    std::cin >> adds >> gets;
    std::cin.ignore(); // /n

    for (size_t jj = 0; jj < adds; jj++) {
      solution.add((cin >> value, value));
    }
    for (size_t jj = 0; jj < gets; jj++) {
      solution.get((cin >> size, size));
    }

    std::cout << solution.solve() << ((ii != datasets-1) ? "\n" : "");
  }

  return(0);
}