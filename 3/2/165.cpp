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
T getinput() {
  static T input;
  return (std::cin >> input, std::cin.ignore(), input);
}

class Solution {
  int maxTargetSoFar = 0;
  std::vector<int> stamps;
  std::vector<int> maxStamps;

public:

  void checkResult(int targetSum) {
    if (maxTargetSoFar < targetSum) {
      maxTargetSoFar = targetSum;
      maxStamps = stamps;
    }
  }

  template<class T> bool
  checkRecursive(T begin, T end, int targetSum, int numberOfStamps) {
    int rest = targetSum;
    while (begin != end && rest) {
      int numberOfLeftStamps = numberOfStamps;
      rest = targetSum;
      for (auto it = begin; it != end && rest && numberOfLeftStamps; it++) {
        auto stampValue = *it;
        while (rest - stampValue >= 0 && numberOfLeftStamps > 0) {
          rest -= stampValue;
          numberOfLeftStamps--;
          if (checkRecursive(it, end, rest, numberOfLeftStamps)) {
            return true;
          }
        }
      }
      begin++;
    }
    return rest == 0;
  }

  void backtrack(int stamp, int numberOfStamps, int typesOfStamps) {
    if (stamps.size() >= (std::size_t)typesOfStamps) return;

    const auto maxIterations = pow(typesOfStamps, numberOfStamps);
    for (int ii = stamp; ii <= maxIterations; ii++) {
      stamps.push_back(ii);
      int targetSum = 1;
      while (checkRecursive(stamps.rbegin(), stamps.rend(), targetSum, numberOfStamps)) {
        checkResult(targetSum);
        targetSum++;
      }

      bool shouldContinue = ii <= targetSum;
      if (shouldContinue) {
        backtrack(ii+1, numberOfStamps, typesOfStamps);
      }

      stamps.pop_back();

      if (!shouldContinue) { break; }
    }
  }

  std::string solve(int numberOfStamps, int typesOfStamps) {
    backtrack(1, numberOfStamps, typesOfStamps);

    std::stringstream output;
    for (const auto& stamp : maxStamps) {
      output << std::right << std::setw(3) << stamp;
    }
    output << " ->" << std::right << std::setw(3) << maxTargetSoFar;
    return output.str();
  };
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::string line;
  int numberOfStamps, typesOfStamps;

  while ((std::cin >> numberOfStamps >> typesOfStamps) && ((numberOfStamps + typesOfStamps) > 0)) {
    Solution solution;
    std::cout << solution.solve(numberOfStamps, typesOfStamps) + "\n";
  }

  return (0);
}