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
  advanced::union_set_t  religions;
  public:

  Solution(size_t people) : religions{ people } {}

  void same_religion(size_t A, size_t B) {
    religions.join(A, B);
  }

  size_t solve() {
    return religions.disjoint();
  };
};

int main() {
  std::string line;
  std::size_t students, questions;
  std::size_t student_A, student_B;
  std::size_t case_counter = 1;

  while ((std::cin >> students >> questions) && (students || questions)) {
    Solution solution{ students };
    for (size_t ii = 0; ii < questions; ii++) {
      student_A = getinput() - 1; // 1..n
      student_B = getinput() - 1; // 1..n
      solution.same_religion(student_A, student_B);
    }
    std::cout << "Case " << case_counter++ << ": " << solution.solve() << "\n";
  }

  return(0);
}