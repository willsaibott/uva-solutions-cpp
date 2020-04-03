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

class Solution {

  public:
  using aij = std::pair<std::pair<size_t, size_t>, ll> ;

  Solution (size_t rows, size_t columns) : _columns{ rows }, _rows{ columns } {
    matrix.resize(columns+1);
  }

  std::string print_row(const std::vector<aij>& row) {
    std::stringstream output;
    output << row.size();
    for (size_t jj = 0; jj < row.size(); jj++) {
      output << " " << row[jj].first.second;
    }
    output << "\n";
    for (size_t jj = 0; jj < row.size(); jj++) {
      if (jj) { output << " "; }
      output << row[jj].second;
    }
    output << "\n";
    return output.str();
  }

  void add(const aij& element) {
    auto& ii   { element.first.first  };
    if (ii <= _rows) {
      matrix[ii].push_back(element);
    }
  }

  std::string solve() {
    std::stringstream ss;
    ss << _rows << " " << _columns << "\n";
    for (size_t ii = 1; ii <= _rows; ii++) {
      std::sort(matrix[ii].begin(), matrix[ii].end());
      ss << print_row(matrix[ii]);
    }
    return ss.str();
  };

  private:
  std::vector<std::vector<aij> > matrix;
  std::size_t                    _columns;
  std::size_t                    _rows;
};

int main() {
  std::string line;
  std::size_t rows, columns, non_zeros;
  std::vector<Solution::aij> elements;

  while (std::cin >> rows >> columns) {
    Solution solution{ rows, columns };
    for (size_t ii = 0; ii < rows; ii++) {
      std::cin >> non_zeros;
      if (non_zeros) {
        elements.resize(non_zeros);
        for (size_t jj = 0; jj < non_zeros; jj++) {
          std::cin >> elements[jj].first.first;
          elements[jj].first.second = ii+1;
        }
        for (size_t jj = 0; jj < non_zeros; jj++) {
          std::cin >> elements[jj].second;
        }
        for (const auto& element : elements) {
          solution.add(element);
        }
      }
    }
    std::cout << solution.solve();
  }

  return(0);
}