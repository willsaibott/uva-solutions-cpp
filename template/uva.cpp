/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 * uhunt page: https://uhunt.onlinejudge.org/id/899065
 *
 */

#include <bits/stdc++.h>

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
  static T input;
  return (std::cin >> input, std::cin.ignore(), input);
}

inline const std::string& getln() {
  static std::string line;
  return (std::getline(std::cin, line), line);
}

class Solution {
  public:
  std::string solve() { return ""; };
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::string line;
  std::size_t N = getinput();

  for (size_t kk = 1; kk <= N; kk++) {
    Solution solution;
    std::cout << solution.solve() + "\n";
  }

  return(0);
}