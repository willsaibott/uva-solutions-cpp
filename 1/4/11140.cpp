/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
**/

#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
#include <utility>
#include <string>
#include <iomanip>
#include <set>
#include <queue>
#include <stack>
#include <sstream>
#include <cmath>
#include <climits>

using namespace std;

template <typename T, typename U>
std::pair<T,U> min(const pair<T, U> &p1, const pair<T, U> &p2)
{
  return { min(p1.first, p2.first), min(p1.second, p2.second)};
}

template <typename T, typename U>
std::pair<T,U> max(const pair<T, U> &p1, const pair<T, U> &p2)
{
  return { max(p1.first, p2.first), max(p1.second, p2.second)};
}

bool fit(vector<string> &board, vector<string> &piece)
{
  if (!piece.size() || !piece[0].size()) return false;

  bool doesFit;
  int max = board[0].size() - piece[0].size();
  int max2 = board.size() - piece.size();

  for(int jj = 0; jj < board[0].size(); jj++) {
    for(int ii = 0; ii < board.size(); ii++) {
      doesFit = true;

      for(int yy = 0;
          yy < (int)piece.size() && (yy + ii) < board.size();
          yy++)
      {
        for(int xx = 0;
            xx < (int)piece[0].size() && (xx + jj) < board[0].size(); xx++)
        {
          if (board[ii + yy][jj + xx] == '.' && piece[yy][xx] == '*')
          {
            doesFit = false;
            break;
          }
        }
        if (!doesFit) break;
      }

      if (doesFit) return true;
    }
  }

  return doesFit;
}

vector<string> getPiece(vector<string> &container)
{
  pair<int, int> pmin(container.size(), container[0].size()),
                 pmax(-1, -1);

  for(int ii = 0; ii < (int)container.size(); ii++) {
    for(int jj = 0; jj < (int)container[0].size(); jj++) {
      if (container[ii][jj] == '*')
      {
        pmin = min(pmin, {ii, jj});
        pmax = max(pmax, {ii, jj});
      }
    }
  }

  pmin = { pmin.first == (int)container.size() ? 0 : pmin.first,
           pmin.second == (int)container[0].size() ? 0 : pmin.second };

  vector<string> piece(container.begin() + pmin.first,
                       container.begin() + pmax.first + 1);
  for ( auto it = piece.begin(); it != piece.end(); it++ ) {
    *it = (*it).substr(pmin.second, 1 + pmax.second - pmin.second);
  }
  return piece;
}

int main()
{
  int k = 0;
  int m, n, s, pm, pn;
  int N;
  string output = "";
  string line;
  bool begin = true;

  output.reserve(500000);
  cin >> N;
  cin.ignore();

  while(k++ < N)
  {
    vector<string> board;
    cin >> m >> n >> s;


    if (!begin || (begin = false)) output += "\n";

    for(int ii = 0; ii < m; ii++) {
      cin >> line;
      board.push_back(line);
    }

    for(int ii = 0; ii < s; ii++) {
      vector<string> container, piece;
      cin >>  pm >> pn;

      for(int jj = 0; jj < pm; jj++) {
        cin >> line;
        container.push_back(line);
      }

      piece = getPiece(container);

      output += fit(board, piece) ? "Yes\n" : "No\n";
    }

  }

  printf("%s", output.c_str());

  return(0);
}