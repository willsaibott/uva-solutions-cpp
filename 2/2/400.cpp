/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 *
 * 400 - Unix ls
**/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>


using namespace std;
typedef unsigned char byte;
typedef unsigned long long ull;

int main()
{
  string output = "";
  string line;
  char s[61];

  output.reserve(500000);

  while(!cin.eof())
  {
    int n;
    cin >> n;

    if (!n || cin.eof()) break;
    output += "------------------------------------------------------------\n";

    vector<string> filenames(n);

    for (int ii = 0; ii < n; ii++)
    {
      cin >> filenames[ii];
    }

    sort(filenames.begin(), filenames.end());

    int size = 0;
    for (string file : filenames)
    {
      size = max(size, (int)file.length());
    }


    int columns = 1;
    for (int ii = size+2; ii <= 60 - size; ii+=size+2, columns++);
    int rows = ceil((double)n / columns);
    vector<vector<string>> table(rows, vector<string>(columns));


    for (int jj = 0; jj < columns; jj++)
    {
      for (int ii = 0; ii < rows && ii + jj*rows < n; ii++)
      {
        table[ii][jj] = filenames[ii + jj*rows];
      }
    }

    for (int ii = 0; ii < rows; ii++)
    {
      for (int jj = 0; jj < columns; jj++)
      {
        if (ii + jj*rows < n)
        {
          sprintf(s, "%-*s", size, table[ii][jj].c_str());
          output += (jj ? "  " : "") + string(s);
        }
      }
      output += "\n";
    }
  }

  printf("%s", output.c_str());

  return(0);
}