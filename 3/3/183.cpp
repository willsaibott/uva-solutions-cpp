#include <bits/stdc++.h>

enum class quad {
  mixed,
  all_one,
  all_zero,
  unknown
};

struct quadrant {
  size_t row;
  size_t col;
  size_t row_end;
  size_t col_end;
};

class Solution {
  std::vector<std::vector<char>>  board;
  size_t                          rows, columns;

public:
  Solution(size_t rows, size_t columns)
    : board(rows, std::vector<char>(columns, ' ')),
      rows{ rows },
      columns{ columns }
  {

  }

  void
  set(size_t ii, size_t jj, char value) {
    board[ii][jj] = value;
  }

  quad
  classify(const quadrant& quarter) {
    quad classification{ quad::unknown };
    if (quarter.row < board.size() && quarter.col < board[0].size()) {
      char unique = board[quarter.row][quarter.col];

      for (size_t ii = quarter.row; ii < quarter.row_end && classification != quad::mixed; ii++) {
        for (size_t jj = quarter.col; jj < quarter.col_end && classification != quad::mixed; jj++) {
          if (unique != board[ii][jj]) {
            classification = quad::mixed;
          }
        }
      }

      if (classification == quad::unknown) {
        classification = unique == '1' ? quad::all_one : quad::all_zero;
      }
    }

    return classification;
  }

  std::string
  B_to_D() {
    std::string answer;
    std::stack<quadrant> stack;
    stack.push(quadrant{ 0 , 0, board.size(), board[0].size() });
    while (!stack.empty()) {
      const auto quarter = stack.top(); stack.pop();
      quad classe = classify(quarter);
      switch (classe) {
      case quad::all_one:  answer.push_back('1'); break;
      case quad::all_zero: answer.push_back('0'); break;
      case quad::mixed: {
        answer.push_back('D');
        size_t row_size = quarter.row_end - quarter.row;
        size_t col_size = quarter.col_end - quarter.col;
        size_t row_mid  = quarter.row + (row_size + 1) / 2;
        size_t col_mid  = quarter.col + (col_size + 1) / 2;

        if (row_size == 1) {
          stack.push(quadrant{ quarter.row, col_mid,     quarter.row_end, quarter.col_end });
          stack.push(quadrant{ quarter.row, quarter.col, quarter.row_end, col_mid });
        }
        else if (col_size == 1) {
          stack.push(quadrant{ row_mid,     quarter.col, quarter.row_end, quarter.col_end });
          stack.push(quadrant{ quarter.row, quarter.col, row_mid,         quarter.col_end });
        }
        else if (row_size > 1 && col_size > 1) {
          stack.push(quadrant{ row_mid,     col_mid,     quarter.row_end, quarter.col_end });
          stack.push(quadrant{ row_mid,     quarter.col, quarter.row_end, col_mid });
          stack.push(quadrant{ quarter.row, col_mid,     row_mid,         quarter.col_end });
          stack.push(quadrant{ quarter.row, quarter.col, row_mid,         col_mid });
        }

        break;
      }
      default:
        break;
      }
    }
    return answer;
  }

  std::string::const_iterator
  expand(std::string&                answer,
         size_t                      row,
         size_t                      col,
         size_t                      row_end,
         size_t                      col_end,
         std::string::const_iterator it)
  {
    if (row >= rows || col >= columns || row >= row_end || col >= col_end) {
       return it;
    }
    if (*it == 'D') {
      size_t diff_row = row_end - row;
      size_t diff_col = col_end - col;
      size_t row_mid  = row + (diff_row + 1) / 2;
      size_t col_mid  = col + (diff_col + 1) / 2;
      it++;

      if (diff_col > 1 && diff_row > 1) {
        it = expand(answer, row    , col    , row_mid, col_mid, it);
        it = expand(answer, row    , col_mid, row_mid, col_end, it);
        it = expand(answer, row_mid, col    , row_end, col_mid, it);
        it = expand(answer, row_mid, col_mid, row_end, col_end, it);
      }
      else if (diff_col == 1){
        it = expand(answer, row    , col    , row_mid, col_end, it);
        it = expand(answer, row_mid, col    , row_end, col_end, it);
      }
      else if (diff_row == 1){
        it = expand(answer, row    , col    , row_end, col_mid, it);
        it = expand(answer, row    , col_mid, row_end, col_end, it);
      }
    }
    else {
      for (size_t ii = row; ii < row_end; ii++) {
        for (size_t jj = col; jj < col_end; jj++) {
          size_t index = ii * columns + jj;
          answer[index] = *it;
        }
      }
      it++;
    }
    return it;
  }

  std::string
  D_to_B(const std::string& line) {
    std::string answer;
    if (line.size() == 1u) {
      answer = std::string(rows * columns, line[0]);
    }
    else {
      answer.resize(rows * columns, ' ');
      std::string::const_iterator it = line.begin();
      it = expand(answer, 0u, 0u, rows, columns, it);
    }
    return answer;
  }
};

int main() {
  std::string line;
  size_t rows{ 0 }, cols{ 0 }, splitted_lines{ 0 };
  char type{ 'C' };

  while (std::cin) {
    std::string input;
    std::getline(std::cin, line);
    std::stringstream ss{ line };
    ss >> type >> rows >> cols;
    splitted_lines = 0;

    if (!std::cin || type == '#') {
      break;
    }

    if (!rows || !cols) {
      continue;
    }

    Solution solution{ rows, cols };

    if (type == 'B') {
      while (input.size() < rows * cols) {
        std::getline(std::cin, line);
        input += line;
        splitted_lines++;
      }
    }
    else {
      std::getline(std::cin, line);
      input = line;
      splitted_lines = 1;
    }

    std::cout << (type == 'B' ? "D" : "B")
              << std::setw(4) << rows
              << std::setw(4) << cols
              << "\n";

    if (rows && cols) {
      std::string result;
      if (type == 'D') {
        result = solution.D_to_B(input);
      }
      else if (type == 'B') {
        for (size_t ii = 0; ii < rows; ii++) {
          for (size_t jj = 0; jj < cols; jj++) {
            solution.set(ii, jj, input[ii * cols + jj]);
          }
        }
        result = solution.B_to_D();
      }

      for (size_t ii = 0; ii * 50 < result.size(); ii++) {
        std::cout << result.substr(ii * 50, 50) << "\n";
      }
    }
  }
}