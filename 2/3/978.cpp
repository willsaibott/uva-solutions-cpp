/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 * uhunt page: https://uhunt.onlinejudge.org/id/899065
 * C++ STL set (Java TreeSet)
 * 978 - Lemmings Battle!
 */

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <bitset>
#include <utility>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <memory>
#include <deque>
#include <stack>
#include <sstream>
#include <cmath>
#include <climits>
#include <cstdlib>
#include <string>
#include <iomanip>
#include <queue>

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

class lemming_t {
  int _health{ 0 };

  public:
  lemming_t() = default;
  lemming_t(int initial_health) : _health{initial_health} {}

  int health() const {
    return _health;
  }

  bool dead() const {
    return _health <= 0;
  }

  bool damage(int damn) {
    return (_health -= damn) <= 0;
  }

  bool operator<(const lemming_t& other) const {
    return _health < other._health;
  }

  bool operator<=(const lemming_t& other) const {
    return _health <= other._health;
  }

  bool operator>(const lemming_t& other) const {
    return _health > other._health;
  }

  bool operator>=(const lemming_t& other) const {
    return _health >= other._health;
  }

  enum class type {
    BLUE = 0,
    GREEN
  };
};


class Solution {
  // using lemmnint_army_t = std::priority_queue<lemming_t, std::vector<lemming_t>, std::greater_equal<lemming_t>>;
  using lemmnint_army_t = std::priority_queue<lemming_t>;
  lemmnint_army_t _greens;
  lemmnint_army_t _blues;

  void print_queue(lemmnint_army_t& queue) {
    while (!queue.empty()) {
      std::cout << queue.top().health() << "\n";
      queue.pop();
    }
  }

  void return_back_survivals(std::queue<lemming_t>& survivals,
                             lemming_t::type type) {
    while (survivals.size()) {
      auto& survival {survivals.front()}; survivals.pop();
      switch (type)
      {
      case lemming_t::type::BLUE:
        _blues.emplace(std::move(survival));
        break;
      case lemming_t::type::GREEN:
        _greens.emplace(std::move(survival));
        break;

      default:
        std::cerr << "Error: Invalid lemming type: " << (int)type << "\n";
        break;
      }
    }
  }

  public:

  void add(lemming_t::type type, int health) {
    switch (type)
    {
    case lemming_t::type::BLUE:
      _blues.push(lemming_t{health});
      break;
    case lemming_t::type::GREEN:
      _greens.push(lemming_t{health});
      break;

    default:
      std::cerr << "Error: Invalid lemming type: " << (int)type << "\n";
      break;
    }
  }

  void solve(size_t battlefields) {
    static const std::string default_output{ "green and blue died\n" };
    std::queue<lemming_t> survived_greens;
    std::queue<lemming_t> survived_blues;

    do {
      for (size_t ii = 0;
                ii < battlefields &&
                !_greens.empty()  &&
                !_blues.empty();
                ii++)
      {
        auto green{ _greens.top() }; _greens.pop();
        auto blue { _blues.top()  }; _blues.pop();
        std::pair<int, int> damages { green.health(), blue.health() };
        if (!blue.damage(damages.first)) {
          survived_blues.emplace(std::move(blue));
        }
        else if (!green.damage(damages.second)) {
          survived_greens.emplace(std::move(green));
        }
      }

      return_back_survivals(survived_greens, lemming_t::type::GREEN);
      return_back_survivals(survived_blues,  lemming_t::type::BLUE);

    } while (_greens.size() && _blues.size());

    if (_greens.size()) {
      std::cout << "green wins\n";
      print_queue(_greens);
    }
    else if (_blues.size()) {
      std::cout << "blue wins\n";
      print_queue(_blues);
    }
    else {
      std::cout << default_output;
    }
  };
};

int main() {
  string line;
  size_t N;
  cin >> N;
  cin.ignore();

  for (size_t kk = 1; kk <= N; kk++) {
    Solution solution;
    size_t battlefield, blues, greens, health;
    if (std::cin >> battlefield >> greens >> blues) {
      for (size_t ii = 0; ii < greens; ii++) {
        solution.add(lemming_t::type::GREEN, (std::cin >> health, health));
      }
      for (size_t ii = 0; ii < blues; ii++) {
        solution.add(lemming_t::type::BLUE,  (std::cin >> health, health));
      }
    }

    solution.solve(battlefield);

    if (kk < N) { std::cout << "\n"; }
  }

  return(0);
}