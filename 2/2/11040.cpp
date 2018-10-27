/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 *
 * 11040 - Add bricks in the wall
**/

#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

void fillBlanks(vector<vector<int>> &wall)
{
  for (int ii = 8; ii >= 2; ii--)
  {
    if (ii == 8) {
      for (uint jj = 0; jj < wall[ii].size()-2; jj+=2)
      {
        int left   = wall[ii][jj];
        int right  = wall[ii][jj+2];
        int top    = wall[ii-2][jj];
        int center = (top - left - right) / 2;

        wall[ii][jj+1] = center;
        wall[ii-1][jj] = left + center;
        wall[ii-1][jj+1] = center + right;
      }
    } else
    {
      for (uint jj = 0; jj < wall[ii].size()-2; jj++)
      {
        int left   = wall[ii][jj];
        int right  = wall[ii][jj+2];
        int center = wall[ii][jj+1];

        wall[ii-1][jj] = left + center;
        wall[ii-1][jj+1] = center + right;
      }
    }
  }
}

int main()
{
  int k = 0;
  int N;
  string output = "";
  string line;

  output.reserve(500000);
  cin >> N;
  cin.ignore();

  while(k++ < N && !cin.eof())
  {
    vector<vector<int>> wall(9);

    for (int ii = 2; ii < 9; ii+=2)
    {
      wall[ii-1] = vector<int>(ii);
    }

    for (int ii = 1; ii <= 9; ii+=2)
    {
      vector<int> v(ii);

      for (int jj = 1; jj <= ii; jj+=2)
      {
        cin >> v[jj-1];
      }

      wall[ii-1] = v;
    }

    fillBlanks(wall);

    for (int ii = 0; ii < 9; ii++)
    {
      for (uint jj = 0; jj < wall[ii].size(); jj++)
      {
        output += to_string(wall[ii][jj]) +
                  (jj != wall[ii].size()-1 ? " " : "\n");
      }
    }
  }

  printf("%s", output.c_str());

  return(0);
}