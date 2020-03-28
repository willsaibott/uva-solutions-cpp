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

enum class gene_t {
  NON_EXISTENT = 0,
  DOMINANT,
  RECESSIVE,
  MAX
};

namespace std {
  inline std::string
  to_string(const gene_t& gene) {
    static std::string names[] = {"non-existent", "dominant", "recessive", "other"};
    return names[static_cast<int>(gene)];
  }
}

template <class T, T minimum = static_cast<T>(0), T maximum = T::MAX>
inline T
from_string(const std::string& str) {
  T result{T::MAX};
  for (T value = static_cast<T>(0);
         value < T::MAX;
         value = static_cast<T>(static_cast<int>(value)+1))
  {
    if (str == std::to_string(value)) {
      result = value;
      break;
    }
  }
  return result;
}

class Solution {
  std::map<std::string, std::pair<std::string, std::string>> _parents;
  std::map<std::string, gene_t>                              _genes;

  gene_t
  determine(const std::string&name) {
    if (_genes[name] == gene_t::MAX) {
      gene_t result{ gene_t::NON_EXISTENT };
      auto it = _parents.find(name);
      if (it != _parents.end()) {
        auto& parents = it->second;
        gene_t g1{ determine(parents.first)};
        gene_t g2{ determine(parents.second)};

        if (g1 == gene_t::DOMINANT || g2 == gene_t::DOMINANT) {
          if (g1==gene_t::NON_EXISTENT || g2==gene_t::NON_EXISTENT) {
            result = gene_t::RECESSIVE;
          }
          else {
            result = gene_t::DOMINANT;
          }
        }
        else if (g1 != gene_t::NON_EXISTENT && g2 != gene_t::NON_EXISTENT) {
          result = gene_t::RECESSIVE;
        }
      }
      _genes[name] = result;
    }
    return _genes[name];
  }

  void handle_as_parent(const std::string& name, const gene_t& gene) {
    _genes[name] = gene;
  }

  void handle_as_child(const std::string& parent, const std::string& child) {
    if (_parents.count(child)) {
      _parents[child].second = parent;
    }
    else {
      _parents[child] = {parent, ""};
      _genes[child]   = gene_t::MAX;
    }
  }

  public:

  void add(const std::string& first, const std::string& second) {
    gene_t gene_from_sec{ from_string<gene_t>(second) };
    if (gene_from_sec != gene_t::MAX) {
      handle_as_parent(first, gene_from_sec);
    }
    else {
      handle_as_child(first, second);
    }
  }

  void
  solve(std::string&output) {
    for (auto& person : _genes) {
      const auto& name{person.first};
      auto gene = determine(name);
      output += name + " " + std::to_string(gene) + "\n";
    }
  };
};


int main() {
  string output = "";
  Solution solution;
  string first, second;
  size_t total;
  cin >> total;
  while(cin >> first >> second) {
    solution.add(first, second);
  }

  solution.solve(output);
  printf("%s", output.c_str());

  return(0);
}