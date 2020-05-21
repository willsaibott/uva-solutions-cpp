#include <bits/stdc++.h>


template <class T = size_t>
T getinput() {
  T input;
  return (std::cin >> input, std::cin.ignore(), input);
}

inline std::string getln() {
  std::string line;
  return (std::getline(std::cin, line), line);
}

static const std::unordered_set<size_t>
primes {
  2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59
};

class Solution {
  std::vector<std::vector<size_t>> _answers;
  size_t                           _n;

  void
  backtracking(std::vector<size_t>& ans, size_t mask, size_t ii) {
    if (ii == _n) {
      auto candidate{ ans[ii-1] + ans[0] };
      if (primes.count(candidate)) {
        _answers.push_back(ans);
      }
    }
    else {
      for (size_t jj = 1; jj < _n; jj++) {
        const auto bit { (1u << jj) };
        auto not_used = (mask & bit) == 0;
        if (not_used) {
          auto candidate{ ans[ii-1] + jj + 1 };
          if (primes.count(candidate)) {
            ans[ii] = jj + 1;
            backtracking(ans, mask | bit, ii + 1);
          }
        }
      }
    }
  }

public:

  Solution(size_t n) : _n{n} { }

  const std::vector<std::vector<size_t>>&
  solve() {
    std::vector<size_t> ans(_n, 0);
    ans[0] = 1;
    backtracking(ans, 1u, 1u);
    return _answers;
  }
};

int main() {
  size_t n;
  size_t kk{ 1 };
  while (std::cin >> n) {
    if (n > 0) {
      Solution solution{ n };

      if (kk > 1) {
        std::cout << "\n";
      }
      std::cout << "Case " << kk++ << ":\n";

      if (n == 1 || (n & 1) == 0) {
        std::string ss;
        const auto& answers{ solution.solve() };
        ss.reserve(50 * answers.size());
        for (const auto& answer : answers) {
          for (const auto& number : answer) {
            ss += std::to_string(number) + " ";
          }
          ss.back() = '\n';
        }
        std::cout << ss;
      }
    }
  }
}
