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
  std::priority_queue<int, std::vector<int>, std::greater<int>> min_priority_queue;
  std::priority_queue<int>                                      max_priority_queue;
  std::queue<int>                                               queue;
  std::stack<int>                                               stack;
  std::vector<bool>                                             options{ false, true, true, true };

  enum option_id {
    MIN_PRIORITY_QUEUE = 0,
    MAX_PRIORITY_QUEUE = 1,
    QUEUE,
    STACK
  };

  public:

  enum class command_id {
    PUSH = 1,
    POP  = 2,
  };


  void push(int value) {
    if (options[option_id::MIN_PRIORITY_QUEUE]) {
      min_priority_queue.push(value);
    }
    if (options[option_id::MAX_PRIORITY_QUEUE]) {
      max_priority_queue.push(value);
    }
    if (options[option_id::QUEUE]) {
      queue.push(value);
    }
    if (options[option_id::STACK]) {
      stack.push(value);
    }
  }

  void pop(int value) {
    if (options[option_id::MIN_PRIORITY_QUEUE]) {
      options[option_id::MIN_PRIORITY_QUEUE] = min_priority_queue.size() &&
                                               value == min_priority_queue.top();
      if (options[option_id::MIN_PRIORITY_QUEUE]) {
        min_priority_queue.pop();
      }
    }
    if (options[option_id::MAX_PRIORITY_QUEUE]) {
      options[option_id::MAX_PRIORITY_QUEUE] = max_priority_queue.size() &&
                                    value == max_priority_queue.top();
      if (options[option_id::MAX_PRIORITY_QUEUE]) {
        max_priority_queue.pop();
      }
    }
    if (options[option_id::QUEUE]) {
      options[option_id::QUEUE] = queue.size() && value == queue.front();
      if (options[option_id::QUEUE]) {
        queue.pop();
      }
    }
    if (options[option_id::STACK]) {
      options[option_id::STACK] = stack.size() && value == stack.top();
      if (options[option_id::STACK]) {
        stack.pop();
      }
    }
  }

  void parse(command_id command, int value) {
    if (command_id::POP == command) {
      pop(value);
    }
    else if (command_id::PUSH == command) {
      push(value);
    }
  }

  void solve() {
    std::vector<bool> merged_options{
      options[MIN_PRIORITY_QUEUE] || options[MAX_PRIORITY_QUEUE],
      options[QUEUE],
      options[STACK]
    };
    int count = std::count(merged_options.begin(), merged_options.end(), true);
    switch (count)
    {
    case 0: std::cout << "impossible\n"; break;
    case 2:
    case 3: std::cout << "not sure\n";   break;
    default:
      // 1...
      // std::cout << "It’s definitely a ";
      if      (merged_options[0]) { std::cout << "priority queue\n"; }
      else if (merged_options[1]) { std::cout << "queue\n";          }
      else if (merged_options[2]) { std::cout << "stack\n";          }
      break;
    }
  };
};

int main() {
  size_t commands;
  int value;
  int command;
  while(std::cin >> commands) {
    Solution solution;
    for (size_t ii = 0; ii < commands; ii++) {
      std::cin >> command >> value;
      solution.parse(static_cast<Solution::command_id>(command), value);
    }
    solution.solve();
  }
  return(0);
}