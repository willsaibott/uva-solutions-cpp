/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 *
 * 12398 - NumPuzz I
**/

#include <cstdio>
#include <iostream>
#include <vector>


using namespace std;
typedef unsigned char byte;
typedef unsigned long long ull;

int main()
{
  int k = 0;
  string output = "";
  string line;

  output.reserve(500000);

  while(getline(cin, line))
  {
    vector<vector<int>> m(3, vector<int>(3));
    output += "Case #" + to_string(++k) + ":\n";

    while (line.size())
    {
      char c = line.back();
      int ii = (c-'a') / 3;
      int jj = (c-'a') % 3;

      m[ii][jj] = (m[ii][jj] + 1) % 10;
      if (ii)
        m[ii-1][jj] = (m[ii-1][jj] + 1) % 10;
      if (ii<2)
        m[ii+1][jj] = (m[ii+1][jj] + 1) % 10;
      if (jj)
        m[ii][jj-1] = (m[ii][jj-1] + 1) % 10;
      if (jj<2)
        m[ii][jj+1] = (m[ii][jj+1] + 1) % 10;

      line.pop_back();
    }

    for (int ii = 0; ii < 3; ii++)
    {
      for (int jj = 0; jj < 3; jj++)
      {
        output += to_string(m[ii][jj]) + (jj != 2 ? " " : "\n");
      }
    }
  }

  printf("%s", output.c_str());

  return(0);
}