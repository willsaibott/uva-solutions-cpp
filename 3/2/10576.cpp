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
  T input;
  return (std::cin >> input, std::cin.ignore(), input);
}

inline std::string getln() {
  std::string line;
  return (std::getline(std::cin, line), line);
}

/**
1  2  3  4  5
2  3  4  5  6
3  4  5  6  7
4  5  6  7  8
5  6  7  8  9
6  7  8  9  10
7  8  9  10 11
8  9  10 11 12

best for 1 deficit per report:
R1: 0 0 0 0 1
R2: 0 0 0 1 0
R3: 0 0 1 0 0
R4: 0 1 0 0 0
R5: 1 0 0 0 0
R6: 0 0 0 0 1
R7: 0 0 0 1 0
R8: 0 0 1 0 0   only 2 deficits!!!

best for 2 deficit per report:
R1: 0 0 0 1 1
R2: 0 0 1 1 0
R3: 0 1 1 0 0
R4: 1 1 0 0 0
R5: 1 0 0 0 1
R6: 0 0 0 1 1
R7: 0 0 1 1 0
R8: 0 1 1 0 0   only 4 deficits!!!

best for 3 deficit per report:
R1: 0 0 1 1 1
R2: 0 1 1 1 0
R3: 1 1 1 0 0
R4: 1 1 0 0 0
R5: 1 0 0 1 1
R6: 0 0 1 1 1
R7: 0 1 1 1 0
R8: 1 1 1 0 0   only 6 deficits!!!

best for 4 deficit per report:
R1: 0 1 1 1 1
R2: 1 1 1 1 0
R3: 1 1 1 0 1
R4: 1 1 0 1 1
R5: 1 0 1 1 1
R6: 0 1 1 1 1
R7: 1 1 1 1 1
R8: 1 1 1 1 0   only 9 deficits!!!
*/
static const size_t MASKS[] = {
  0b000000000000,
  0b001000010000,  // 5th and 10th  1 defict per report
  0b001100011000,  // 4th, 5th, 10th and 12th 2 deficts per report
  0b001110011100,  // 3 deficts per report
  0b011111011110,  // 4 defictis per report
  0b111111111111,  // 5 deficits per report
};

class Solution {
  int    surplus;
  int    deficit;
  size_t deficits_per_report;

  public:

  Solution(int surplus, int deficit) : surplus{ surplus }, deficit{ deficit } {
    // Find the minimum deficits per report necessary to keep the rules
    for (size_t ii = 1; ii <= 5; ii++) {
      deficits_per_report = ii;
      if ((5-ii) * surplus < ii * deficit) { break; }
    }
  }

  std::string
  solve() {
    int balance = 0;
    if (deficits_per_report == 5)  {
      balance = -1;
    }
    else {
      for (size_t ii = 0; ii < 12; ii++) {
        balance += (MASKS[deficits_per_report] & (1ul << ii)) ? -deficit : surplus;
      }
    }
    return balance >= 0 ? std::to_string(balance) + "\n" : "Deficit\n";
  };
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::string line;
  int surplus, deficit;

  while( std::cin >> surplus >> deficit) {
    Solution solution{ surplus, deficit };
    std::cout << solution.solve();
  }

  return(0);
}