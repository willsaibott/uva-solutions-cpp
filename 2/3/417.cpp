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
  std::map<std::string, int> _dictionary;
  size_t                     _max_size{0};
  size_t                     _last_index{0};

  void add(const std::string& key) {
    _dictionary[key] = ++_last_index;
  }

  void
  next(std::string& str,
       size_t       max_depth,
       char begin = 'a',
       char end   = 'z',
       int depth  = 0)
  {
    if (depth < max_depth) {
      for (char c = begin; c <= end; c++) {
        str[depth] = c;
        next(str, max_depth, c+1, end, depth+1);
      }
    }
    else {
      add(str);
    }
  }

  public:


  void
  make_dictionary(size_t length) {
    std::string key;
    for (size_t len = _max_size+1; len <= length; len++) {
      key.resize(len);
      next(key, len);
    }
    _max_size = std::max(_max_size, length);
  }

  std::string
  solve(const std::string& line) {
    make_dictionary(line.size());
    return std::to_string(_dictionary[line]);
  };
};


int main() {
  string output = "";
  string line;

  Solution solution;
  while(!cin.eof() && cin.good()) {
    std::getline(cin, line);
    if (line.empty()) { break; }
    output += solution.solve(line)  + "\n";
  }

  printf("%s", output.c_str());

  return(0);
}