/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 *
 * 12291 - Polyomino Composer
**/

#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;
typedef unsigned char byte;
typedef unsigned long long ull;

vector<string> minify(vector<string> &small, int n) {
  int maxCol = 0, minCol = n-1, minRow = n-1, maxRow = 0;

  for (int ii = 0; ii < n; ii++)
  {
    for (int jj = 0; jj < n; jj++)
    {
      if (small[ii][jj] == '*')
      {
        minCol = min(minCol, jj);
        maxCol = max(maxCol, jj);
        minRow = min(minRow, ii);
        maxRow = max(maxRow, ii);
      }
    }
  }

  vector<string> minSmall(small.begin() + minRow,
                          small.begin() + maxRow+1);
  for (int ii = minRow; ii <= maxRow; ii++)
  {
    minSmall[ii-minRow] = small[ii].substr(minCol, maxCol-minCol+1);
  }

  return minSmall;
}

int runCheck(vector<string> big, vector<string> piece)
{
  int N = big.size();
  int rows = piece.size();
  int columns = piece[0].size();
  int times = 0;

  for (int ii = 0; ii <= N-rows; ii++)
  {
    for (int jj = 0; jj <= N-columns; jj++)
    {
      bool equal = true;

      for (int xx = 0; xx < columns && equal; xx++)
      {
        for (int yy = 0; yy < rows && equal; yy++)
        {
          equal = piece[yy][xx] == '.' ||
                  (piece[yy][xx] == '*' &&
                   big[ii+yy][jj+xx] == piece[yy][xx]);
        }
      }

      if (equal)
      {
        times++;
        for (int xx = 0; xx < columns; xx++)
        {
          for (int yy = 0; yy < rows; yy++)
          {
            if (piece[yy][xx] == '*')
              big[ii+yy][jj+xx] = '.';
          }
        }
      }
    }
  }

  bool clean = false;
  if (times == 2)
  {
    clean = true;
    for (int ii = 0; ii < N && clean; ii++)
    {
      for (int jj = 0; jj < N && clean; jj++)
      {
        clean = big[ii][jj] != '*';
      }
    }
  }
  return clean;
}

int main()
{
  string output = "";
  string line;

  output.reserve(500000);

  while(!cin.eof())
  {
    int N, n;
    cin >> N >> n;

    if (!n) break;

    vector<string> big(N), small(n);

    for (int ii = 0; ii < N; ii++)
    {
      cin >> big[ii];
    }

    for (int ii = 0; ii < n; ii++)
    {
      cin >> small[ii];
    }

    vector<string> piece = minify(small, n);
    output += to_string(runCheck(big, piece)) + "\n";
  }

  printf("%s", output.c_str());

  return(0);
}