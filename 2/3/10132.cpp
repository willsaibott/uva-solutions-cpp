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
  std::map<int64_t, std::vector<std::pair<size_t, std::string>>> _dictionary;
  std::map<std::string, size_t>               _ocurr;
  size_t                                      _fragments_length{0};
  size_t                                      _fragment_counter{0};
  public:

  void add(const std::string& fragment) {
    static auto id{0ull};
    _dictionary[fragment.size()].push_back({id++, fragment});
    _fragments_length += fragment.size();
    _fragment_counter++;
  }

  std::string
  solve() {
    std::pair<std::string, size_t> _most_freq{"", 0};
    auto filesize{(_fragments_length * 2) / _fragment_counter};
    for (auto entry=_dictionary.begin(); entry!=_dictionary.end(); entry++) {
      const auto&fragsize1{entry->first};
      const auto&fraglist1{entry->second};
      const auto fragsize2{filesize - fragsize1};

      auto frag2 = _dictionary.find(fragsize2);
      if (frag2 != _dictionary.end()) {
        const auto& complementary_list {frag2->second};
        for (const auto& frag1: fraglist1) {
          for (const auto& complement:complementary_list) {
            if (frag1.first != complement.first) {
              auto occur = ++_ocurr[frag1.second + complement.second];
              if (occur > _most_freq.second) {
                _most_freq.first  = frag1.second + complement.second;
                _most_freq.second = occur;
              }
            }
          }
        }
      }
    }
    return _most_freq.first;
  }
};


int main() {
  string output = "";
  int64_t total;
  std::string line;
  cin >> total;
  cin.ignore(); // \n
  cin.ignore(); // \n
  for (int ii = 0; ii < total; ii++) {
    Solution solution;
    while ((std::getline(cin, line), line.size()) && cin) {
      solution.add(line);
    }
    output += solution.solve() + "\n\n";
  }
  output.pop_back();
  printf("%s", output.c_str());

  return(0);
}