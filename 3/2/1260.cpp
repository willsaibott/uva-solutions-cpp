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

  std::vector<size_t> _sales;

  public:

  Solution(size_t sales) {
    _sales.reserve(sales);
  }

  void add(size_t sale) {
    _sales.push_back(sale);
  }

  size_t
  solve() {
    size_t sum{ 0 };
    for (int64_t ii = 1; static_cast<size_t>(ii) < _sales.size(); ii++) {
      const auto& target{ _sales[ii] };
      size_t sum_it{ 0 };
      for (int64_t jj = ii-1; jj >= 0; jj--) {
        const auto& sale{ _sales[jj] };
        sum_it += sale <= target;
      }
      sum += sum_it;
    }
    return sum;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::string line;
  std::size_t N = getinput();

  for (size_t kk = 1; kk <= N; kk++) {
    size_t size{ getinput() };
    Solution solution{ size };
    for (size_t ii = 0; ii < size; ii++) {
      solution.add(getinput());
    }
    std::cout << solution.solve() << "\n";
  }

  return(0);
}