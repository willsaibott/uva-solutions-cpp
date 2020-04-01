/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 * uhunt page: https://uhunt.onlinejudge.org/id/899065
 *
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
#include <queue>
#include <deque>
#include <stack>
#include <sstream>
#include <cmath>
#include <climits>
#include <cstdlib>
#include <string>
#include <iomanip>

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

class Solution {
  std::set<std::string> _dictionary;

  public:

  void
  add(const std::string& word) {
    std::string word_lower{ word };
    std::transform(word_lower.begin(),
                   word_lower.end(),
                   word_lower.begin(),
                   ::tolower);
    _dictionary.insert(word_lower);
  }

  void solve() {
    for (const auto& word : _dictionary) {
      std::cout << word << "\n";
    }
  };
};


struct word_delimiter_t : std::ctype<char> {
  word_delimiter_t () : std::ctype<char>(ctable()) { }

  static mask const* ctable () {
    static mask table[table_size];
    for (size_t ii = 0; ii < table_size; ii++) {
      if (!std::isalpha(ii) && ii != '-') {
        table[ii] = std::ctype_base::space;
      }
    }
    return &(table[0]);
  }
};



int main() {
  Solution solution;
  std::string word, part;

  std::cin.imbue(std::locale{ cin.getloc(), new word_delimiter_t{} });
  char c;

  while (std::cin >> word) {
    while (word.back() == '-') {
      std::cin >> std::noskipws >> c >> std::skipws;
      if (c == '\n') {
        word.pop_back();
      }
      else if (std::isalpha(c)) {
        word.push_back(c);
      }
      else {
        break;
      }
      std::cin >> part;
      word += part;
    }
    solution.add(word);
  }

  solution.solve();

  return(0);
}