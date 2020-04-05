/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 * uhunt page: https://uhunt.onlinejudge.org/id/899065
 *
 */

#include <bits/stdc++.h>
#include "../../advanced_library_cpp/AdvancedLibraryCpp/union_set.h"
#include "../../advanced_library_cpp/AdvancedLibraryCpp/union_find.h"

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
  advanced::union_set_t suspects;

  public:

  Solution(size_t persons) : suspects{ persons } { }

  void add_group(const std::vector<size_t>& group) {
    for (size_t ii = 1; ii < group.size(); ii++) {
      suspects.join(group[ii-1], group[ii]);
    }
  }

  std::string solve() {
    return std::to_string(suspects.size_of(0)) + "\n";
  };
};

int main() {
  std::string line;
  std::size_t groups, persons, group_size;

  while ((std::cin >> persons >> groups) && (groups || persons)) {
    Solution solution{ persons };
    for (size_t ii = 0; ii < groups; ii++) {
      std::vector<size_t> group(group_size = getinput());
      for (size_t jj = 0; jj < group_size; jj++) {
        group[jj] = getinput();
      }
      solution.add_group(group);
    }
    std::cout << solution.solve();
  }

  return(0);
}