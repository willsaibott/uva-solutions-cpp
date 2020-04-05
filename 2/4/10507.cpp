/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 * uhunt page: https://uhunt.onlinejudge.org/id/899065
 *
 */

#include <bits/stdc++.h>
#include "../../advanced_library_cpp/AdvancedLibraryCpp/union_set.h"

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
  std::vector<advanced::union_set_t> brain;
  std::bitset<26>                    awaken;
  std::bitset<26>                    present;
  size_t                             cells;

  public:

  Solution(size_t slept) :
    brain{ std::vector<advanced::union_set_t>(26, advanced::union_set_t{ 26 }) },
    cells{ slept }
  { }

  void wake_up(size_t position) {
    awaken.set(position);
    present.set(position);
  }

  void connect(size_t first, size_t second) {
    brain[first].join(first, second);
    brain[second].join(first, second);
    present.set(first);
    present.set(second);
  }

  size_t run() {
    size_t count{ 0 };
    std::vector<size_t> to_be_awaken;
    for (size_t ii = 0; ii < 26; ii++) {
      count = 0;
      if (present.test(ii) && !awaken.test(ii)) {
        for (size_t jj = 0; jj < 26 && count < 3; jj++) {
          // It should not be necessary to test if ii != jj, because
          // awaken.test(ii) is false for this piece of code, but it's here for
          // consistency:
          count += ii != jj && awaken.test(jj) && brain[ii].same(ii, jj);
        }
        if (count >= 3) {
          to_be_awaken.push_back(ii);
        }
      }
    }
    for (const auto& slept : to_be_awaken) {
      wake_up(slept);
    }
    return awaken.count();
  }

  std::string solve() {
    std::string output{ "THIS BRAIN NEVER WAKES UP\n" };
    size_t last_awaken{ (size_t)-1 }, current_awaken{ awaken.count() };
    size_t years{ 0 };

    while (last_awaken != current_awaken && current_awaken < cells) {
      years++;
      last_awaken    = current_awaken;
      current_awaken = run();
    }

    if (current_awaken >= cells) {
      output = "WAKE UP IN, " + std::to_string(years) + ", YEARS\n";
    }
    return output;
  };
};

int main() {
  std::string line;
  std::size_t cells, connections;

  while (std::cin >> cells >> connections) {
    Solution solution{ cells };
    std::cin.ignore();
    line = getln();
    solution.wake_up(line[0] - 'A');
    solution.wake_up(line[1] - 'A');
    solution.wake_up(line[2] - 'A');

    for (size_t ii = 0; ii < connections; ii++) {
      line = getln();
      if (line.size()>=2) {
        solution.connect(line[0]-'A', line[1]-'A');
      }
    }
    std::cout << solution.solve();
  }

  return(0);
}