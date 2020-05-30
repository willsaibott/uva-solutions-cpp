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
  std::vector<std::vector<std::vector<int64_t>>>      garbage;
  std::vector<std::vector<std::vector<int64_t>>> dp;
  size_t A, B, C;

  public:

  Solution(size_t A, size_t B, size_t C)
    : garbage(A, std::vector<std::vector<int64_t>>(B, std::vector<int64_t>(C, 0))),
      dp(A, std::vector<std::vector<int64_t>>(B, std::vector<int64_t>(C, 0))),
      A(A),
      B(B),
      C(C)
  { }

  void set(size_t aa, size_t bb, size_t cc, int64_t value) {
    garbage.at(aa).at(bb).at(cc) = value;
    dp.at(aa).at(bb).at(cc)      = value;

    if (aa) {
      dp[aa][bb][cc] += dp[aa-1][bb][cc];
    }
    if (bb) {
      dp[aa][bb][cc] += dp[aa][bb-1][cc];
    }
    if (cc) {
      dp[aa][bb][cc] += dp[aa][bb][cc-1];
    }
    if (aa && bb) {
      dp[aa][bb][cc] -= dp[aa-1][bb-1][cc];
    }
    if (aa && cc) {
      dp[aa][bb][cc] -= dp[aa-1][bb][cc-1];
    }
    if (bb && cc) {
      dp[aa][bb][cc] -= dp[aa][bb-1][cc-1];
    }
    if (aa && bb && cc) {
      dp[aa][bb][cc] += dp[aa-1][bb-1][cc-1];
    }
  }

  int64_t
  solve() {
    int64_t max_sum{ std::numeric_limits<int64_t>::min() };
    int64_t curr_sum;

    for (size_t aa = 0; aa < A; aa++) {
      for (size_t bb = 0; bb < B; bb++) {
        for (size_t cc = 0; cc < C; cc++) {
          for (size_t aaa = aa; aaa < A; aaa++) {
            for (size_t bbb = bb; bbb < B; bbb++) {
              for (size_t ccc = cc; ccc < C; ccc++) {
                curr_sum = dp[aaa][bbb][ccc];
                if (aa) {
                  curr_sum -= dp[aa-1][bbb][ccc];
                }
                if (bb) {
                  curr_sum -= dp[aaa][bb-1][ccc];
                }
                if (cc) {
                  curr_sum -= dp[aaa][bbb][cc-1];
                }
                if (aa && bb) {
                  curr_sum += dp[aa-1][bb-1][ccc];
                }
                if (aa && cc) {
                  curr_sum += dp[aa-1][bbb][cc-1];
                }
                if (bb && cc) {
                  curr_sum += dp[aaa][bb-1][cc-1];
                }
                if (aa && bb && cc) {
                  curr_sum -= dp[aa-1][bb-1][cc-1];
                }
                max_sum = std::max(max_sum, curr_sum);
              }
            }
          }
        }
      }
    }

    return max_sum;
  };
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::size_t N = getinput();
  size_t A, B, C;

  for (size_t kk = 0; kk < N; kk++) {
    std:: cin >> A >> B >> C;
    Solution solution{ A, B, C };
    for (size_t aa = 0; aa < A; aa++) {
      for (size_t bb = 0; bb < B; bb++) {
        for (size_t cc = 0; cc < C; cc++) {
          solution.set(aa, bb, cc, getinput<int64_t>());
        }
      }
    }
    if (kk) {
      std::cout << "\n";
    }
    std::cout << solution.solve() << "\n";
  }

  return(0);
}