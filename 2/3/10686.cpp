/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 * uhunt page: https://uhunt.onlinejudge.org/id/899065
 * 10686 - SQF Problems
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
#include <memory>

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

struct category_t {
  std::string           name;
  size_t                minimum_to_fit;
  std::set<std::string> keywords;
  std::set<std::string> mached_keywords;

  category_t() = default;
  category_t(const std::string& name, const size_t& minimum)
    : name{name}, minimum_to_fit{minimum}
    {};
};

struct word_splliter_t : std::ctype<char> {
  word_splliter_t() : std::ctype<char>(get_table()) {}
  static mask const* get_table() {
    static mask rc[table_size];
    for (size_t c = 0; c < table_size; c++) {
      if (!std::isalpha(c)) {
        rc[c] = std::ctype_base::space;
      }
    }
    return &rc[0];
  }
};

class Solution {
  std::map<std::string, std::unique_ptr<category_t>> _categories;
  std::vector<category_t*>                           _categories_sequence;
  std::map<std::string, std::vector<category_t*>>    _categories_by_keywords;

  public:

  void
  add_category(const std::string& category_name, const std::size_t& minimum) {
    auto& category = _categories[category_name];
    category = std::make_unique<category_t>(category_name, minimum);
    _categories_sequence.push_back(category.get());
  }

  void add(const std::string& category_name, const std::string& keyword) {
    auto& category = _categories[category_name];
    if (category->keywords.insert(keyword).second) {
      _categories_by_keywords[keyword].push_back(category.get());
    }
  }

  void add_line(const std::string& line) {
    std::stringstream ss{line};
    std::string word;

    ss.imbue(std::locale{cin.getloc(), new word_splliter_t{}});
    while (ss >> word) {
      auto it = _categories_by_keywords.find(word);
      if (it != _categories_by_keywords.end()) {
        const auto& categories{ it->second };
        for (const auto& category : categories) {
          category->mached_keywords.insert(word);
        }
      }
    }
  }

  std::string
  solve() {
    std::string all_categories;
    for (const auto& category : _categories_sequence) {
      if (category->mached_keywords.size() >= category->minimum_to_fit) {
        all_categories += category->name + ",";
      }
    }
    if (all_categories.empty()) {
      all_categories = "SQF Problem.\n";
    }
    else {
      all_categories.back() = '\n';
    }
    return all_categories;
  }
};

int main() {
  string output = "";
  std::string line, category_name, keyword;
  size_t categories, test_cases, minimum_to_fit, number_of_keywords;

  // std::cin.imbue(locale(cin.getloc(), new word_splliter_t{}));
  cin >> test_cases;
  cin.ignore();

  for (size_t ii = 0; ii < test_cases; ii++) {
    Solution solution;

    cin >> categories;
    for (size_t jj = 0; jj < categories; jj++) {
      cin >> category_name >> number_of_keywords >> minimum_to_fit;
      solution.add_category(category_name, minimum_to_fit);
      for (size_t kk = 0; kk < number_of_keywords; kk++) {
        cin >> keyword;
        solution.add(category_name, keyword);
      }
    }
    cin.ignore();

    while(std::getline(cin, line), cin && line.size()) {
      solution.add_line(line);
    }
    output += solution.solve();
  }

  printf("%s", output.c_str());

  return(0);
}