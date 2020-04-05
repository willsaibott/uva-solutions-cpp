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
  advanced::union_set_t people;
  size_t                largest{ 1 };

  public:

  Solution(size_t population) : people{ population } { }

  void same_chain(size_t A, size_t B) {
    if (people.join(A, B)) {
      largest = std::max(largest, people.size_of(A));
    }
  }

  size_t solve() {
    return largest;
  };
};

int main() {
  std::string line;
  std::size_t N = getinput(), population, pairs, person_A, person_B;

  for (size_t kk = 1; kk <= N; kk++) {
    Solution solution { population = getinput() };
    pairs = getinput();
    for (size_t ii = 0; ii < pairs; ii++) {
      person_A = getinput() - 1; //1..n
      person_B = getinput() - 1; //1..n
      solution.same_chain(person_A, person_B);
    }
    std::cout << solution.solve() << "\n";
  }

  return(0);
}