/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 * uhunt page: https://uhunt.onlinejudge.org/id/899065
 * 10295 - Hay points
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
  std::unordered_map<std::string, ull> _dictionary;
  ull                                  _salary{0};

  public:

  void add(const std::string& job_description) {
    std::stringstream ss{job_description};
    std::string word;
    ull salary;
    while (ss >> word && ss >> salary) {
      _dictionary[word] = salary;
    }
  }

  void add_line(const std::string& line) {
    std::stringstream ss{line};
    std::string word;
    while (ss >> word) {
      auto it = _dictionary.find(word);
      if (it != _dictionary.end()) {
        const auto& salary{it->second};
        _salary += salary;
      }
    }
  }

  std::string
  solve() {
    return std::to_string(_salary) + "\n";
  }

  void
  clear_salary() {
    _salary = 0;
  }
};


int main() {
  Solution solution;
  string output = "";
  std::string line;
  size_t job_descriptions, texts;
  cin >> job_descriptions >> texts;
  cin.ignore();

  for (size_t ii = 0; ii < job_descriptions; ii++) {
    if (std::getline(cin, line), cin && line.size()) {
      solution.add(line);
    }
  }

  auto pred1 = [] (const char&c) { return (c != '.' && c != ' '); };
  auto pred2 = [] (const char&c) { return (c == '.'); };

  for (size_t ii = 0; ii < texts; ii++) {
    while(std::getline(cin, line), cin &&
          (std::count_if(line.begin(), line.end(), pred1) ||
           std::count_if(line.begin(), line.end(), pred2) != 1))
    {
      solution.add_line(line);
    }
    output += solution.solve();
    solution.clear_salary();
  }

  printf("%s", output.c_str());

  return(0);
}