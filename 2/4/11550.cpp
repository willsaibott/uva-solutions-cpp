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

  std::vector<std::vector<size_t>> matrix;
  size_t rows;
  size_t columns;
  public:
  Solution (size_t rows, size_t columns)
    : matrix{ std::vector<std::vector<size_t>>(rows, std::vector<size_t>(columns, 0)) },
      rows{ rows },
      columns{ columns }
  {

  }

  void put(size_t ii, size_t jj, size_t value) {
    matrix[ii][jj] = value;
  }

  std::string solve() {
    std::set<std::pair<size_t, size_t>> edges;
    std::pair<size_t, size_t> edge;
    size_t sums{ 0  };
    bool yes{ true };

    for (size_t jj = 0; jj < columns && yes; jj++) {
      sums = 0;
      for (size_t ii = 0; ii < rows && yes; ii++) {
        if (matrix[ii][jj]) {
          switch (sums)
          {
          case 0:
            edge.first  = ii;
            break;
          case 1:
            edge.second = ii;
            yes &= edges.insert(edge).second;
            break;
          default:
            yes &= false;
            break;
          }
          sums++;
        }
      }
      yes &= sums == 2;
    }
    return yes ? "Yes\n" : "No\n";
  };
};

template <class T = size_t>
T getinput() {
  T input;
  return (std::cin >> input, std::cin.ignore(), input);
}

inline std::string getln() {
  std::string line;
  return (std::getline(std::cin, line), line);
}

int main() {
  std::size_t N, rows, columns;
  std::cin >> N;
  std::cin.ignore();

  for (size_t kk = 1; kk <= N; kk++) {
    Solution solution{ rows = getinput(), columns = getinput() };
    for (size_t ii = 0; ii < rows; ii++) {
      for (size_t jj = 0; jj < columns; jj++) {
        solution.put(ii, jj, getinput());
      }
    }
    std::cout << solution.solve();

  }

  return(0);
}