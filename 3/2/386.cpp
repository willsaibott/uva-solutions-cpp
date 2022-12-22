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
T getInput() {
  static T input;
  return (std::cin >> input, std::cin.ignore(), input);
}

inline const std::string& getln() {
  static std::string line;
  return (std::getline(std::cin, line), line);
}

class Solution {
public:

  inline ull cubeOf(ull number) {
    return number * number * number;
  }

  std::string solve(ull a) {
    std::stringstream ss;
    ull cube = cubeOf(a);
    for (ull b = 2ull; b < a; b++) {
      for (ull c = b + 1; c < a; c++) {
        for (ull d = c + 1; d < a; d++) {
          if (cube == cubeOf(b) + cubeOf(c) + cubeOf(d)) {
            ss << "Cube = " << a << ", Triple = (" << b << "," << c << "," << d << ")\n";
          }
        }
      }
    }
    return ss.str();
  };
};

int main() {
  std::ios_base::sync_with_stdio(false);

  for (ull a = 1ull; a <= 200ull; a++) {
    Solution solution;
    std::cout << solution.solve(a);
  }

  return(0);
}