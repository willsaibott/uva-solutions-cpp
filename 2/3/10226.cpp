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
  std::map<std::string, size_t> _dictionary;
  size_t                        _total_population{0};

  public:

  void add(const std::string& key) {
    ++_dictionary[key];
    _total_population++;
  }

  void
  solve(std::string&output) {
    static char buffer[1024] = {'\0'};
    for (const auto& tree : _dictionary) {
      const auto& freq{tree.second};
      sprintf(buffer,
              "%s %.4f\n",
              tree.first.data(),
              freq * 100.0 / (double)_total_population);
      output += buffer;
    }
    output += "\n";
  };
};


int main() {
  string output = "";
  std::string line;
  size_t total;
  cin >> total;
  cin.ignore();
  cin.ignore();

  for (size_t ii = 0; ii < total; ii++) {
    Solution solution;
    while(std::getline(cin, line), cin && line.size()) {
      solution.add(line);
    }
    solution.solve(output);
  }
  output.pop_back();
  printf("%s", output.c_str());

  return(0);
}