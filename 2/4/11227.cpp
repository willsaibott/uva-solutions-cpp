/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 * uhunt page: https://uhunt.onlinejudge.org/id/899065
 *
 */

#include <bits/stdc++.h>
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
  advanced::union_set_t          persons;
  std::vector<std::vector<bool>> opinions;

  public:
  Solution(size_t people, size_t trees) :
     persons{ people },
     opinions(people, std::vector<bool>( trees, false ) )
  { }

  void heard(size_t person, size_t tree) {
    if (person <= opinions.size()) {
      opinions[person-1][tree-1] = true;
    }
  }

  std::string solve() {
    for (size_t ii = 0; ii < opinions.size(); ii++) {
      const auto& first{ opinions[ii] };
      for (size_t jj = ii+1; jj < opinions.size(); jj++) {
        const auto& second{ opinions[jj] };
        if (std::equal(first.begin(), first.end(), second.begin())) {
          persons.join(ii, jj);
        }
      }
    }
    return std::to_string(persons.disjoint()) + "\n";
  };
};

int main() {
  std::string line;
  std::size_t N, trees, people, tree_id, person_id;
  std::cin >> N;
  std::cin.ignore();

  for (size_t kk = 1; kk <= N; kk++) {
    people = getinput();
    trees  = getinput();
    Solution solution{ people, trees };
    while ((line = getln()).size()) {
      std::stringstream ss{ line };
      ss >> person_id >> tree_id;
      solution.heard(person_id, tree_id);
    }

    std::cout << solution.solve();
    if (kk < N) {
      std::cout << "\n";
    }
  }

  return(0);
}