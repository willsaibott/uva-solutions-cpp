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

struct maker_t {
  std::string                 name;
  std::pair<int64_t, int64_t> price;

  inline bool operator<(const maker_t& other) const {
    return other.price != price ? price < other.price : name < other.name;
  }
};

class Solution {
  std::vector<maker_t>  _car_makers;

  public:

  Solution(size_t makers) {
    _car_makers.reserve(makers);
  }

  Solution&
  prepare() {
    std::sort(_car_makers.begin(), _car_makers.end());
    return *this;
  }

  void
  add(const std::string& name, int64_t min_price, int64_t max_price) {
    _car_makers.push_back({ name, { min_price, max_price }});
  }

  std::string
  solve(int64_t price) {
    std::string response{ "UNDETERMINED" };
    std::string candidate;
    size_t matches{ 0 };
    for (auto it = _car_makers.begin();
              it != _car_makers.end() && matches <= 1 && it->price.first <= price;
              it++)
    {
      if (price <= it->price.second) {
        candidate = it->name;
        matches++;
      }
    }

    if (matches == 1) {
      response = candidate;
    }

    return response;
  };
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::string name;
  std::size_t N = getinput();
  int64_t min_price, max_price;

  for (size_t kk = 1; kk <= N; kk++) {
    size_t makers{ getinput() }, queries;
    Solution solution{ makers };
    for (size_t ii = 0; ii < makers; ii++) {
      std::cin >> name >> min_price >> max_price;
      solution.add(name, min_price, max_price);
    }

    queries = getinput();
    solution.prepare();

    if (kk > 1) {
      std:: cout << "\n";
    }

    for (size_t ii = 0; ii < queries; ii++) {
      std::cout << solution.solve(getinput<int64_t>()) << "\n";
    }
  }

  return(0);
}