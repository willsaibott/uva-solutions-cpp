/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 *
 * 11581 - Grid Successors
**/

#include <cstdio>
#include <iostream>
#include <vector>


using namespace std;

typedef unsigned char byte;

bool finished(vector<vector<byte>> m)
{
  bool end = true;

  for (int ii = 0; ii < 3; ii++)
  {
    for (int jj = 0; jj < 3 && end; jj++)
    {
      end = m[ii][jj] == '0';
    }
  }

  return end;
}

void apply(vector<vector<byte>> &m)
{
  vector<vector<byte>> newM = m;
  for (int ii = 0; ii < 3; ii++)
  {
    for (int jj = 0; jj < 3; jj++)
    {
      int sum = 0;

      if (ii) sum += (m[ii-1][jj] - '0');
      if (ii<2) sum += (m[ii+1][jj] - '0');
      if (jj) sum += (m[ii][jj-1] - '0');
      if (jj<2) sum += (m[ii][jj+1] - '0');

      // for (int x = max(0, jj-1); x < min(3, jj+1); x++)
      // {
      //   for (int y = max(0, ii-1); y < min(3, ii+1); y++)
      //   {
      //     sum += (m[y][x] - '0');
      //   }
      // }

      newM[ii][jj] = '0' + (sum & 1);
    }
  }

  m = newM;
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
    int index = -1;
    vector<vector<byte>> m(3, vector<byte>(3));

    for (int ii = 0; ii < 3; ii++)
    {
      for (int jj = 0; jj < 3; jj++)
      {
        cin >> m[ii][jj];
      }
    }

    while (!finished(m))
    {
      apply(m);
      index++;
    }

    output += to_string(index) + "\n";
  }

  printf("%s", output.c_str());

  return(0);
}