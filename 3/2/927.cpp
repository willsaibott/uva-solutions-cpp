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
  const std::vector<size_t>& _coeficients;
  size_t                     _d;
  size_t                     _kth;

  public:

  Solution(const std::vector<size_t>& coef, size_t d, size_t kth)
    : _coeficients{ coef },
      _d{ d },
      _kth{ kth }
  { }

  size_t
  func(size_t ii) {
    size_t value{ 0 };
    for (size_t jj = 1; jj < _coeficients.size(); jj++) {
      const auto& coef{ _coeficients[jj] };
      value += coef * static_cast<size_t>(std::pow(ii, jj - 1));
    }
    return value;
  }

  size_t
  solve() {
    size_t bth{ 0 }, di{ 1 }, n{ 1 }, ii{ 0 };
    while (ii < _kth) {
      bth = func(n++);
      ii += di++ * _d;
    }
    return bth;
  };
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::string line;
  std::size_t N = getinput();

  for (size_t kk = 1; kk <= N; kk++) {
    std::vector<size_t> coefs;
    std::stringstream ss{ getln() };
    size_t coef, d, kth;
    while (ss >> coef) {
      coefs.push_back(coef);
    }
    d   = getinput();
    kth = getinput();

    Solution solution{ coefs, d, kth };
    std::cout << solution.solve() << "\n";
  }

  return(0);
}