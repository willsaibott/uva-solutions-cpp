#include <bits/stdc++.h>

class Solution {
  std::vector<std::vector<size_t>> quadradonia;
  std::vector<size_t> max_values;

public:

  Solution(size_t rows, size_t columns)
    : quadradonia(rows, std::vector<size_t>(columns, 0)),
      max_values(rows, 0)
  { }

  inline void
  set_block(size_t row, size_t column, size_t value) {
    quadradonia[row][column] = value;
    if (column == quadradonia[0].size() - 1) {
      max_values[row] = value;
    }
  }

  size_t
  query(size_t minor, size_t major) {
    auto begin = std::lower_bound(max_values.begin(), max_values.end(), minor);
    size_t start_index = std::distance(max_values.begin(), begin);
    size_t max_square{ 0 }, current_max_square{ 1 };
    size_t max_possible_square{
      std::min(quadradonia.size(), quadradonia[0].size())
    };

    for (size_t ii = start_index; ii < quadradonia.size(); ii++) {
      const auto& row{ quadradonia[ii] };
      const auto lower          = std::lower_bound(row.begin(), row.end(), minor);
      const auto higher         = std::upper_bound(row.begin(), row.end(), major);
      const size_t distance     = std::distance(lower, higher);
      const size_t start_column = std::distance(row.begin(), lower);
      const size_t end_column   = std::distance(row.begin(), higher);

      if (higher == row.begin()             ||
          max_square >= max_possible_square ||
          quadradonia.size() - ii <= max_square)
      {
        break;
      }

      if (distance > max_square) {
        current_max_square = distance;

        for (size_t xx = end_column - 1, yy = ii + distance - 1;
                    xx > start_column && yy > ii;
                    xx--, yy--)
        {
          if (yy < quadradonia.size()) {
            if (quadradonia[yy][xx] <= major) {
              break;
            }
          }
          current_max_square--;
        }

        max_square = std::max(max_square, current_max_square);
      }
    }

    return max_square;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  size_t rows, columns;
  size_t minor, major, queries;
  size_t value;

  while (std::cin >> rows >> columns && rows && columns) {
    Solution solution(rows, columns);
    for (size_t ii = 0; ii < rows; ii++) {
      for (size_t jj = 0; jj < columns; jj++) {
        std::cin >> value;
        solution.set_block(ii, jj, value);
      }
    }

    std::cin >> queries;
    for (size_t ii = 0; ii < queries; ii++) {
      std::cin >> minor >> major;
      std::cout << solution.query(minor, major) << "\n";
    }

    std::cout << "-\n";
  }
}