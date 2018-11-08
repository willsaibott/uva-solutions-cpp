/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 *
 * 12187 - Brothers
**/

#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;
typedef unsigned char byte;
typedef unsigned long long ull;

void runBattle(vector<vector<int>> &kingdom,
               int rows,
               int columns,
               int heirs)
{
  vector<vector<int>> newM = kingdom;

  for (int r = 0; r < rows; r++)
  {
    for (int c = 0; c < columns; c++)
    {
      int hated = (kingdom[r][c] + 1) % heirs;
      int me = kingdom[r][c];

      if (r && kingdom[r-1][c] == hated)
        newM[r-1][c] = me;
      if (r<(rows-1) && kingdom[r+1][c] == hated)
        newM[r+1][c] = me;
      if (c && kingdom[r][c-1] == hated)
        newM[r][c-1] = me;
      if (c<(columns-1) && kingdom[r][c+1] == hated)
        newM[r][c+1] = me;
    }
  }

  kingdom = newM;
}

int main()
{
  string output = "";
  string line;

  output.reserve(500000);

  while(!cin.eof())
  {
    int heirs, rows, columns, battles;
    cin >> heirs >> rows >> columns >> battles;

    if (!(heirs && rows && columns && battles)) break;

    vector<vector<int>> kingdom(rows, vector<int>(columns));

    for (int r = 0; r < rows; r++)
    {
      for (int c = 0; c < columns; c++)
      {
        cin >> kingdom[r][c];
      }
    }

    for (int battle = 0; battle < battles; battle++)
    {
      runBattle(kingdom, rows, columns, heirs);
    }

    for (int r = 0; r < rows; r++)
    {
      for (int c = 0; c < columns; c++)
      {
        output += to_string(kingdom[r][c]) +
                  (c != (columns-1) ? " " : "\n");
      }
    }
  }

  printf("%s", output.c_str());

  return(0);
}