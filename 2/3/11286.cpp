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

struct course_t;

struct frosh_t {
  int                    id;
  std::vector<course_t*> courses;

  frosh_t() = default;
  frosh_t(int id) : id{id} {}
};

struct course_t {
  int                 id;
  std::set<frosh_t*> froshs;

  course_t() = default;
  course_t(int id) : id{id} {};

  bool operator<(const course_t&other) const  {
    return id < other.id;
  }
};

struct combination_t {
  std::vector<int> courses;

  combination_t(const std::vector<course_t*>& courses_chosen) {
    for (const auto&  course: courses_chosen) {
      courses.push_back(course->id);
    }
    std::sort(courses.begin(), courses.end());
  };

  bool operator<(const combination_t&other) const {
    return std::lexicographical_compare(courses.begin(),
                                        courses.end(),
                                        other.courses.begin(),
                                        other.courses.end());
  }

  bool operator=(const combination_t&other) const {
    return std::equal(courses.begin(),
                      courses.end(),
                      other.courses.begin());
  }
};

class Solution {
  std::vector<std::unique_ptr<frosh_t>>      _froshs;
  std::map<int, std::unique_ptr<course_t>>   _courses;

  public:

  frosh_t*
  new_frosh() {
    _froshs.push_back(std::make_unique<frosh_t>(_froshs.size()));
    return _froshs.back().get();
  }

  void
  add(frosh_t* frosh, int course_id) {
    if (frosh) {
      auto& course = _courses[course_id];
      if (!course) {
        course = std::make_unique<course_t>(course_id);
      }
      course->froshs.insert(frosh);
      frosh->courses.push_back(course.get());
    }
  }

  std::string
  solve() {
    std::map<combination_t, size_t> freq;
    size_t max_element{ 0 };
    for (auto& frosh: _froshs) {
      combination_t combo{frosh->courses};
      max_element = std::max(max_element, ++freq[combo]);
      // std::cout << "freq[combo] = freq {"
      //           << combo.courses[0] << ", "
      //           << combo.courses[1] << ", "
      //           << combo.courses[2] << ", "
      //           << combo.courses[3] << ", "
      //           << combo.courses[4]
      //           << "} = "
      //           << freq[combo]
      //           << " freq size: "
      //           << freq.size()
      //           << std::endl;
    }
    size_t count       =
      std::count_if(freq.begin(),
                    freq.end(),
                    [max_element](const std::map<combination_t, size_t>::value_type& elem) {
                      return elem.second == max_element;
                    });
    return _froshs.size() ? std::to_string(count*max_element) + "\n" : "0\n";
  }
};


int main() {
  string output = "";
  size_t froshs;

  while(cin >> froshs && froshs) {
    Solution solution;
    int course_id;
    for (size_t ii = 0; ii < froshs; ii++) {
      auto frosh = solution.new_frosh();
      for (size_t jj = 0; jj < 5; jj++) {
        cin >> course_id;
        solution.add(frosh, course_id);
      }
    }

    std::cout << solution.solve();
  }

  return(0);
}