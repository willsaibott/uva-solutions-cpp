/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 * uhunt page: https://uhunt.onlinejudge.org/id/899065
 * 10282 - Babelfish
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
  std::unordered_map<std::string, std::string> _dictionary;

  public:

  void add(const std::string& key) {
    std::stringstream ss{key};
    std::string word, translation;
    while (ss >> translation && ss >> word) {
      _dictionary[word] = translation;
    }
  }

  std::string
  solve(const std::string& key) {
    std::string translation{ "eh\n" };
    auto it = _dictionary.find(key);
    if (it != _dictionary.end()) {
      translation = it->second + "\n";
    }
    return translation;
  }
};


int main() {
  Solution solution;
  string output = "";
  std::string line;

  while(std::getline(cin, line), cin && line.size()) {
    solution.add(line);
  }
  while(std::getline(cin, line), cin && line.size()) {
    output += solution.solve(line);
  }
  printf("%s", output.c_str());

  return(0);
}