/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 * uhunt page: https://uhunt.onlinejudge.org/id/899065
 *
 */

#include <bits/stdc++.h>

using namespace std;

template <class T = size_t>
T getinput() {
  static T input;
  return (std::cin >> input, std::cin.ignore(), input);
}

static bool checkIfSumIsPerfectSquare(std::int64_t ball1, std::int64_t ball2) {
  std::int64_t sum = ball1 + ball2;
  std::int64_t sroot = std::sqrt(sum);
  return sroot * sroot == sum;
}


class Solution {
public:

  static std::vector<int> memo;

  std::int64_t placeBalls(int numberOfPegs) {
    std::vector<int> pegs = std::vector<int>(numberOfPegs, 0);
    std::int64_t ball = 1;
    std::int64_t lastBall = 1;

    do {
      lastBall = ball;
      for (auto ii = 0; ii < numberOfPegs; ii++) {
        if (!pegs[ii] || checkIfSumIsPerfectSquare(pegs[ii], ball)) {
          pegs[ii] = ball;
          ball++;
          break;
        }
      }
    } while (lastBall != ball);
    return lastBall-1;
  }

  std::int64_t solve(int pegs) {
    if (memo[pegs]) return memo[pegs];
    return memo[pegs] = placeBalls(pegs);
  };
};

std::vector<int> Solution::memo = std::vector<int>(51, 0);

int main() {
  std::ios_base::sync_with_stdio(false);
  std::string line;
  std::size_t N = getinput();
  int pegs;

  for (size_t kk = 1; kk <= N; kk++) {
    Solution solution;
    std::cin >> pegs;
    std::cout << solution.solve(pegs) << "\n";
  }

  return(0);
}