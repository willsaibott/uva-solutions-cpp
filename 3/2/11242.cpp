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

  std::vector<long double> rear;
  std::vector<long double> front;

  public:

  Solution(size_t rear_teeth, size_t front_teeth) {
    rear.reserve(rear_teeth);
    front.reserve(front_teeth);
  }

  void
  add_rear(size_t teeth) {
    rear.push_back(teeth);
  }

  void
  add_front(size_t teeth) {
    front.push_back(teeth);
  }

  long double solve() {
    std::vector<long double> ratios;
    long double max_diff{ 0 };

    for (size_t ii = 0; ii < rear.size(); ii++) {
      const auto& r{ rear[ii] };
      for (size_t jj = 0; jj < front.size(); jj++) {
        const auto& f{ front[jj] };
        ratios.push_back( r / f );
      }
    }

    std::sort(ratios.begin(), ratios.end());
    for (size_t ii = 1; ii < ratios.size(); ii++) {
      max_diff = std::max(max_diff, ratios[ii] / ratios[ii-1]);
    }
    return max_diff;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  size_t rear, front;

  while (std::cin >> front >> rear && (rear)) {
    Solution solution(rear, front);

    for (size_t ii = 0; ii < front; ii++) {
      solution.add_front(getinput());
    }
    for (size_t ii = 0; ii < rear; ii++) {
      solution.add_rear(getinput());
    }

    std::cout << std::fixed << std::setprecision(2) << solution.solve() << "\n";
  }

  return(0);
}