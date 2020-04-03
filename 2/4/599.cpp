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
#include <bitset>
#include "../../advanced_library_cpp/AdvancedLibraryCpp/union_set.h"

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
  // std::vector<std::pair<char, char>> graph;
  // std::bitset<26>                    nodes[26];
  advanced::union_set_t              union_set{ 26 };
  std::bitset<26>                    nodes_on;
  size_t                             union_size;

  public:

  void add_vertice(const std::string& line) {
    size_t first  = line[1] - 'A';
    size_t second = line[3] - 'A';

    if (first != second && first < 26 && second < 26) {
      union_set.join(first, second);
      // nodes[first].set(second);
    }
  }

  void parse_nodes(const string& line) {
    for (const auto& c : line) {
      if (std::isupper(c)) {
        nodes_on.set(c-'A');
      }
    }
  }

  std::string solve() {
    stringstream ss;
    const size_t invalid_nodes{ 26 - nodes_on.count() };
    size_t trees { union_set.disjoint() - invalid_nodes  },
           acorns{ union_set.acorn()    - invalid_nodes };

    // std::cout << "There are " << 26 - invalid_nodes << " valid nodes\n";

    ss << "There are " << trees - acorns << " tree(s) and "
                       << acorns         << " acorn(s).\n";
    return ss.str();
  };
};

int main() {
  std::string line;
  size_t N;
  std::cin >> N;
  std::cin.ignore();

  for (size_t kk = 1; kk <= N; kk++) {
    Solution solution;

    while ((std::getline(std::cin, line), line[0] != '*')) {
      if (line.size() >= 4) {
        solution.add_vertice(line);
      }
    }

    solution.parse_nodes((std::getline(std::cin, line), line));

    std::cout << solution.solve();
  }

  return(0);
}