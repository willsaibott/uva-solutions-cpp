/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 * uhunt page: https://uhunt.onlinejudge.org/id/899065
 *
 */

#include <bits/stdc++.h>
#include "../../advanced_library_cpp/AdvancedLibraryCpp/union_set.h"
#include "../../advanced_library_cpp/AdvancedLibraryCpp/union_find.h"

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

enum command_t {
  SET_FRIENDS = 1,
  SET_ENEMIES = 2,
  ARE_FRIENDS = 3,
  ARE_ENEMIES = 4,
};

class Solution {
  advanced::union_set_t countries_friendship;
  size_t                countries;

  size_t enemy_of(size_t x) {
    return x + countries;
  }

  public:

  Solution(size_t total_countries)
  : countries_friendship{ 2 * total_countries },
    countries{ total_countries }
  { }

  bool set_enemies(size_t x, size_t y) {
    bool result { !are_friends(x, y) };
    if (result) {
      countries_friendship.join(x, enemy_of(y));
      countries_friendship.join(y, enemy_of(x));
    }
    return result;
  }

  bool set_friends(size_t x, size_t y) {
    bool result { !are_enemies(x, y) };
    if (result) {
      countries_friendship.join(x, y);
      countries_friendship.join(enemy_of(x), enemy_of(y));
    }
    return result;
  }

  bool are_friends(size_t x, size_t y) {
    return countries_friendship.same(x, y) ||
           countries_friendship.same(enemy_of(x), enemy_of(y));
  }

  bool are_enemies(size_t x, size_t y) {
    return x != y &&
           (countries_friendship.same(x, enemy_of(y)) ||
            countries_friendship.same(enemy_of(x), y));
  }

  void evaluate(char command, size_t x, size_t y)  {
    switch (command)
    {
    case '1':
      if (!set_friends(x, y)) {
        std::cout << "-1\n";
      }
      break;
    case '2':
      if (!set_enemies(x, y)) {
        std::cout << "-1\n";
      }
      break;
    case '3':
      if (are_friends(x, y)) {
        std::cout << "1\n";
      }
      else {
        std::cout << "0\n";
      }
      break;
    case '4':
      if (are_enemies(x, y)) {
        std::cout << "1\n";
      }
      else {
        std::cout << "0\n";
      }
      break;
    break;

    default:
      break;
    }
  }
};

int main() {
  std::string line;
  std::size_t persons = getinput(), x, y;
  Solution solution{ persons };
  char command;
  while (std::cin >> command >> x >> y) {
    solution.evaluate(command, x, y);
  }

  return(0);
}