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
  std::vector<int64_t>      _numbers;
  std::map<int64_t, size_t> _dictionary;


  public:

  void add(const int64_t& key) {
    if ((++(_dictionary[key])) <= 1) {
      _numbers.push_back(key);
    }
  }

  void
  solve(std::string&output) {
    for (const auto& number : _numbers) {
      output += std::to_string(number) + " " + std::to_string(_dictionary[number]) + "\n";
    }
  };
};


int main() {
  string output = "";
  Solution solution;
  int64_t number;
  while(cin >> number) {
    solution.add(number);
  }

  solution.solve(output);
  printf("%s", output.c_str());

  return(0);
}