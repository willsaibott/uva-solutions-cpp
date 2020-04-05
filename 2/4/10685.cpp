/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 * uhunt page: https://uhunt.onlinejudge.org/id/899065
 *
 */

#include <bits/stdc++.h>
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
  advanced::union_find_t<std::string> chains;
  size_t                              largest{ 1 };

  public:

  Solution(size_t creatures) {
    chains.reserve(creatures);
  }

  void add_creature(const std::string& creature) {
    chains.insert(creature);
  }

  void same_chain(const std::string& A, const std::string& B) {
    if (chains.join_sets(A, B)) {
      largest = std::max(largest, chains.size_of(A));
    }
  }

  size_t solve() {
    return largest;
  };
};

int main() {
  std::string line, creature_A, creature_B;
  std::size_t creatures, pairs;

  while (std::cin >> creatures >> pairs && (creatures || pairs)) {
    Solution solution { creatures };
    std::cin.ignore();
    for (size_t ii = 0; ii < creatures; ii++) {
      solution.add_creature(getinput<std::string>());
    }
    for (size_t ii = 0; ii < pairs; ii++) {
      creature_A = std::move(getinput<std::string>());
      creature_B = std::move(getinput<std::string>());
      solution.same_chain(creature_A, creature_B);
    }
    std::cout << solution.solve() << "\n";
  }

  return(0);
}
