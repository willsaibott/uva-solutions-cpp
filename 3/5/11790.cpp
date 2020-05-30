/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 * uhunt page: https://uhunt.onlinejudge.org/id/899065
 *
 */

#include <bits/stdc++.h>

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

template <class T = size_t>
T getinput() {
  static T input;
  return (std::cin >> input, std::cin.ignore(), input);
}

inline const std::string& getln() {
  static std::string line;
  return (std::getline(std::cin, line), line);
}

class Solution {
  std::vector<size_t> widths;
  std::vector<size_t> heights;
  size_t              N;

  public:

  Solution (size_t N) : widths(N, 0), heights(N, 0), N{ N }
  { }

  void
  set_height(size_t ii, size_t height) {
    heights[ii] = height;
  }

  void
  set_width(size_t ii, size_t width) {
    widths[ii] = width;
  }

  size_t lis() {
    std::vector<size_t> max_widths(N, 0);
    std::vector<size_t> lis(N, 0);
    size_t max_width{ 0 };

    for (size_t ii = 0; ii < N; ii++) {
      const auto& value { heights[ii] };
      size_t curr_max{ 0 };
      int64_t index{ -1 };
      for (int64_t jj = ii - 1; jj >= 0; jj--) {
        if (lis[jj] < value) {
          if (max_widths[jj] > curr_max) {
            curr_max = max_widths[jj];
            index    = jj;
          }
        }
      }

      lis[ii] = value;

      if (index >= 0) {
        max_widths[ii] = max_widths[index] + widths[ii];
      }
      else {
        max_widths[ii] = widths[ii];
      }

      max_width = std::max(max_width, max_widths[ii]);
    }

    return max_width;
  }

  size_t lds() {
    std::vector<size_t> max_widths(N, 0);
    std::vector<size_t> lds(N, 0);
    size_t max_width{ 0 };

    for (size_t ii = 0; ii < N; ii++) {
      const auto& value { heights[ii] };
      size_t curr_max{ 0 };
      int64_t index{ -1 };
      for (int64_t jj = ii - 1; jj >= 0; jj--) {
        if (lds[jj] > value) {
          if (max_widths[jj] > curr_max) {
            curr_max = max_widths[jj];
            index    = jj;
          }
        }
      }

      lds[ii] = value;

      if (index >= 0) {
        max_widths[ii] = max_widths[index] + widths[ii];
      }
      else {
        max_widths[ii] = widths[ii];
      }

      max_width = std::max(max_width, max_widths[ii]);
    }

    return max_width;
  }

  std::pair<size_t, size_t>
  solve() {
    std::pair<size_t, size_t> pair;
    pair.first  = lis();
    pair.second = lds();
    return pair;
  };
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::size_t test_cases = getinput();

  for (size_t kk = 1; kk <= test_cases; kk++) {
    size_t N = getinput();
    Solution solution{ N };
    for (size_t ii = 0; ii < N; ii++) {
      solution.set_height(ii, getinput());
    }
    for (size_t ii = 0; ii < N; ii++) {
      solution.set_width(ii, getinput());
    }
    const auto pair{ solution.solve() };
    if (pair.first >= pair.second) {
      std::cout << "Case " << kk << ". Increasing (" << pair.first << "). "
                                 << "Decreasing (" << pair.second << ").\n";
    }
    else {
      std::cout << "Case " << kk << ". Decreasing (" << pair.second << "). "
                                 << "Increasing (" << pair.first << ").\n";
    }
  }

  return(0);
}