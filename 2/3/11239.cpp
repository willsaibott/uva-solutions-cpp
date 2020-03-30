/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 * uhunt page: https://uhunt.onlinejudge.org/id/899065
 * 11239 - Open Source
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
#include <memory>
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

namespace std {
template<typename T, typename... Args>
  unique_ptr<T> make_unique(Args&&... args) {
    return unique_ptr<T>(new T(forward<Args>(args)...));
  }
}

struct project_t {
  std::string           name;
  std::set<std::string> contribuitors;

  project_t() = default;
  project_t(const std::string& name) : name{name} {};
  bool operator<(const project_t& other) const {
    int diff { (int)contribuitors.size() - (int)other.contribuitors.size() };
    return diff ? diff > 0 : name < other.name;
  }
};

class Solution {
  std::vector<std::unique_ptr<project_t>>     _projects;
  std::unordered_set<std::string>             _invalid_users;
  std::unordered_map<std::string, project_t*> _subscription;

  public:

  project_t*
  add_project(const std::string& line) {
    _projects.push_back(std::make_unique<project_t>(line));
    return _projects.back().get();
  }

  void
  add_user(const std::string& username, project_t* project) {
    auto subscriptions = _subscription.find(username);

    if (!project) {return;}
    else if (subscriptions != _subscription.end() &&
             project != subscriptions->second)
    {
      _invalid_users.insert(username);
      subscriptions->second->contribuitors.erase(username);
    }

    if (!_invalid_users.count(username)) {
      project->contribuitors.insert(username);
      _subscription[username] = project;
    }
  }

  void
  solve(std::string& output) {
    static auto compare =
      [](const std::unique_ptr<project_t>& ptr1,
         const std::unique_ptr<project_t>& ptr2)
      {
        return *ptr1 < *ptr2;
      };

    std::sort(_projects.begin(), _projects.end(), compare);
    for (const auto& project : _projects) {
      output += project->name + " " +
                std::to_string(project->contribuitors.size()) + "\n";
    }
  }

  void
  clear() {
    _projects.clear();
    _subscription.clear();
  }
};


int main() {
  string output = "";
  std::string line;
  Solution solution;
  project_t* ref{nullptr};

  while(std::getline(cin, line), cin && line.size() && line[0] != '0') {
    char c{ line[0] };
    if (c == '1') {
      solution.solve(output);
      solution.clear();
      ref = nullptr;
    }
    else if (std::any_of(line.begin(), line.end(), [](char c){ return std::isupper(c); })){
      ref = solution.add_project(line);
    }
    else if (std::any_of(line.begin(), line.end(), [](char c){ return std::islower(c); })) {
      solution.add_user(line, ref);
    }
  }

  printf("%s", output.c_str());

  return(0);
}