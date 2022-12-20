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

template <class T = size_t>
T getInput() {
  static T input;
  return (std::cin >> input, std::cin.ignore(), input);
}

class Solution {

public:

  std::string solve(const std::vector<int>& weights) {

    for (int p0 = 1; p0 <= 200; p0++) {
      for (int p1 = p0; p1 <= 200; p1++) {
        if ((p1 + p0) > weights[0]) break;
        if ((p1 + p0) != weights[0]) continue;

        for (int p2 = p1; p2 <= 200; p2++) {
          if ((p2 + p0) > weights[1]) break;
          if ((p2 + p0) != weights[1]) continue;

          for (int p3 = p2; p3 <= 200; p3++) {
            if ((p0 + p3) != weights[2] && (p1 + p2) != weights[2]) continue;

            for (int p4 = p3; p4 <= 200; p4++) {
              if (p3 + p4 > weights[9]) break;
              if (p2 + p4 > weights[8]) break;

              if ((p0 + p3) != weights[3] && (p1 + p2) != weights[3] && (p0 + p4) != weights[3] && (p1 + p3) != weights[3]) continue;
              if ((p0 + p4) != weights[4] && (p1 + p2) != weights[4] && (p1 + p3) != weights[4] && (p2 + p3) != weights[4] && (p1 + p4) != weights[4]) continue;
              if ((p0 + p4) != weights[5] && (p1 + p3) != weights[5] && (p2 + p3) != weights[5] && (p1 + p4) != weights[5]) continue;
              if ((p0 + p4) != weights[6] && (p1 + p4) != weights[6] && (p2 + p3) != weights[6] && (p1 + p3) != weights[6]) continue;
              if ((p1 + p4) != weights[7] && (p2 + p3) != weights[7] && (p2 + p4) != weights[7] && (p1 + p3) != weights[7]) continue;

              if ((p2 + p4) == weights[8] && (p3 + p4) == weights[9]) {
                std::stringstream ss;
                ss << p0 << " " << p1 << " " << p2 << " " << p3 << " " << p4;
                return ss.str();
              }
            }
          }
        }
      }
    }
    return "error";
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::string line;
  std::size_t N = getInput();
  std::vector<int> weights = std::vector<int>(10, 0);

  for (size_t kk = 1; kk <= N; kk++) {
    Solution solution;
    for (auto ii = 0; ii < 10; ii++) {
      std::cin >> weights[ii];
    }
    std::cout << "Case " << kk << ": " << solution.solve(weights) << "\n";
  }

  return(0);
}