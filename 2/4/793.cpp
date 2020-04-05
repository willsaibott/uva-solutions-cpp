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

  advanced::union_set_t network;
  size_t                successfully{ 0 };
  size_t                unsuccessfully{ 0 };

  public:

  Solution(size_t computers) : network{ computers } {}

  void add_connection(size_t pc1, size_t pc2) {
    network.join(pc1, pc2);
  }

  void query(size_t pc1, size_t pc2) {
    if (network.same(pc1, pc2)) {
      successfully++;
    }
    else {
      unsuccessfully++;
    }
  }

  std::string solve() {
    return std::to_string(successfully)   + "," +
           std::to_string(unsuccessfully) + "\n";
  };
};

int main() {
  std::string line;
  std::size_t N = getinput(), pc1, pc2;
  char command;

  for (size_t kk = 1; kk <= N; kk++) {
    Solution solution{ getinput() };
    while ((line = getln()).size()) {
      stringstream ss{ line };
      ss >> command >> pc1 >> pc2;
      switch (command)
      {
      case 'c':
        solution.add_connection(pc1-1, pc2-1);
        break;
      case 'q':
        solution.query(pc1-1, pc2-1);
        break;
      default:
        break;
      }
    }

    std::cout << solution.solve();
    if (kk < N) {
      std::cout << "\n";
    }
  }

  return(0);
}