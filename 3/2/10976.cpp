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

namespace std{
/**
 * @brief calculate the greatest common divisor
 * @param[in] a first  number
 * @param[in] b second number
 * @return the greatest common divisor
 */
template<typename num>
num gcd(num a, num b) {
  return b == static_cast<num>(0) ? a : gcd(b, (a % b));
}

/**
 * @brief calculate the least common multiple
 * @param[in] a first  number
 * @param[in] b second number
 * @return the least common multiple
 */
template<typename num>
num lcm(num a, num b) {
  return (a * b) / gcd(a, b);
}

}

class Solution {
  public:

  inline static std::vector<std::string>
  solve(int64_t k) {
    std::vector<std::string> response;
    for (int64_t y = k + 1; y <= 2 * k; y++) {
      // int64_t lcm = std::lcm(y, k);
      // int64_t yyy = y * lcm;
      // int64_t kkk = k * lcm;
      // int64_t xxx = yyy - kkk;
      if (y==k) continue;
      int64_t yk  = (k * y);
      int64_t xxx = yk / (y - k);
      int64_t yk2 = xxx * (y-k);

      if (xxx > 0 && yk2 == yk && xxx >= y) {
        std::stringstream ss;
        ss << "1/" << k << " = 1/" << xxx << " + 1/" << y;
        response.push_back(ss.str());
      }
    }
    return response;
  };

  inline static std::vector<std::string>
  solve_by_x(int64_t k) {
    std::vector<std::string> response;
    for (int64_t x = k + 1; x <= k * 2; x++) {
      if (x==k) continue;
      int64_t xk  = (k * x);
      int64_t y   = xk / (x - k);
      int64_t xk2 = y * (x-k);

      if (y > 0 && xk2 == xk && x >= y) {
        std::stringstream ss;
        ss << "1/" << k << " = 1/" << x << " + 1/" << y;
        response.push_back(ss.str());
      }
    }
    return response;
  };
};

int main() {
  std::ios_base::sync_with_stdio(false);
  int64_t k{ 0 };

  while (std::cin >> k) {
    const auto response = Solution::solve(k);
    std::cout << response.size() << "\n";
    for (const auto& fraction : response) {
      std::cout << fraction << "\n";
    }
  }

  return(0);
}