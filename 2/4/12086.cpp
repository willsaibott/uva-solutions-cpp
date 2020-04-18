/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 * uhunt page: https://uhunt.onlinejudge.org/id/899065
 *
 */

#include <bits/stdc++.h>
#include "../../advanced_library_cpp/AdvancedLibraryCpp/fenwick_tree.h"

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

class Solution {
  using tree_t = advanced::fenwick_tree_t<int>;

  tree_t                     resistance_range;
  std::vector<int>           potentiometers;
  std::vector<int>::iterator pit;

  public:

  Solution(size_t capacity) : potentiometers(capacity, 0) {
    pit = potentiometers.begin();
  }

  void
  add_potentiometer(size_t ohms) {
    *pit = ohms; pit++;
  }

  void
  modify(size_t pos, size_t ohms) {
    const auto value = (int)ohms - potentiometers[pos-1];
    resistance_range.update(pos, value);
    // just for consistency:
    potentiometers[pos-1] = ohms;
  }

  size_t
  query(size_t start, size_t end) {
    const size_t current_size = std::distance(potentiometers.begin(), pit);
    const size_t fixed_start  = start;
    const size_t fixed_end    = end;
    return (size_t)resistance_range.query(fixed_start, fixed_end);
  }

  void
  clear() {
    pit = potentiometers.begin();
  }

  void
  build() {
    resistance_range.rebuild(potentiometers,
                             std::distance(potentiometers.begin(), pit));
  }
};

int main() {
  static char buffer[10000000] = { '\0' };
  std::ios_base::sync_with_stdio(false);
  std::cin.rdbuf()->pubsetbuf(buffer, 10000000);
  std::size_t potentiometers, resistance, position, start, end;
  Solution solution{ 200000 };
  std::string line;
  char command;
  size_t k = 0;

  while ((std::cin >> potentiometers) && potentiometers) {
    std::cin.ignore();
    for (size_t ii = 0; ii < potentiometers; ii++) {
      solution.add_potentiometer(getinput());
    }

    solution.build();

    if (k++) {
      std::cout << "\nCase " << k << ":\n";
    }
    else {
      std::cout << "Case 1:\n";
    }

    while ((line = getln()).size() && line != "END") {
      std::stringstream ss{ line };
      ss >> command;
      switch (command) {
      case 'S':
        ss >> position >> resistance;
        solution.modify(position, resistance);
        break;
      case 'M':
        ss >> start >> end;
        std::cout << solution.query(start, end) << "\n";
        break;
      default:
        break;
      }
    }

    solution.clear();
  }

  return(0);
}