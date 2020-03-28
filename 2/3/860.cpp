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
#include <locale>
#include <utility>
#include <set>
#include <map>
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

class Solution {
  std::map<std::string, size_t> _dictionary;
  size_t                        _total_words{0};
  size_t                        _total_diff_words{0};

  public:

  void
  add(std::string& key) {
    static auto to_lower =[](unsigned char c){ return std::tolower(c);};
    std::transform(key.begin(), key.end(), key.begin(), to_lower);
    _total_words++;
    _total_diff_words += (++_dictionary[key]) <= 1;
  }

  std::pair<double, int>
  entropy() {
    std::pair<double, int> ent{0.0, 0};
    double max_ent = std::log10(_total_words);
    for (const auto& entry:_dictionary) {
      // const auto& word{entry.first};
      const auto& counts{entry.second};
      ent.first += counts * (max_ent - std::log10(counts));
    }
    ent.first /= _total_words;
    ent.second = std::max(std::round(ent.first / max_ent * 100.0), 0.0);
    return ent;
  }

  std::string
  solve() {
    static char buffer[1024] = {'\0'};
    auto ent = entropy();
    std::sprintf(buffer, "%lu %.1f %d", _total_words, ent.first, ent.second);
    return buffer;
  };

  void clear() {
    _dictionary.clear();
    _total_words = 0;
  }
};

struct custom_delimiter_t : std::ctype<char> {
  custom_delimiter_t() : std::ctype<char>(get_table()) {}
  static mask const* get_table() {
    static mask rc[table_size];
    rc[',']  = std::ctype_base::space;
    rc['.']  = std::ctype_base::space;
    rc[':']  = std::ctype_base::space;
    rc[';']  = std::ctype_base::space;
    rc['!']  = std::ctype_base::space;
    rc['?']  = std::ctype_base::space;
    rc['"']  = std::ctype_base::space;
    rc['(']  = std::ctype_base::space;
    rc[')']  = std::ctype_base::space;
    rc[' ']  = std::ctype_base::space;
    rc['\n'] = std::ctype_base::space;
    return &rc[0];
  }
};

int main() {
  string output = "";
  Solution solution;
  std::string word;

  cin.imbue(locale(cin.getloc(), new custom_delimiter_t{}));
  while(cin >> word) {
    if (word == "****END_OF_TEXT****") {
      output += solution.solve() + "\n";
      solution.clear();
    }
    else if (word == "****END_OF_INPUT****") {
      break;
    }
    else {
      solution.add(word);
    }
  }
  printf("%s", output.c_str());

  return(0);
}