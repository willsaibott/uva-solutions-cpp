/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * 541 - Error Correction
**/

#include <cstdio>
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

int main()
{
  string output = "";
  string line;

  output.reserve(500000);

  while(!cin.eof())
  {
    int n;
    cin >> n;
    if (!n) break;

    vector<vector<int>> m(n, vector<int>(n));
    vector<int> hor(n), ver(n);
    pair<int, int> change;

    for (int ii = 0; ii < n; ii++)
    {
      for (int jj = 0; jj < n; jj++)
      {
        cin >> m[ii][jj];

        hor[ii] += m[ii][jj];
        ver[jj] += m[ii][jj];
      }
    }

    int changes = 0;
    int diffs = 0;
    for (int ii = 0; ii < n; ii++)
    {
      diffs += (hor[ii] & 1) + (ver[ii] & 1);
      for (int jj = 0; jj < n; jj++)
      {
        if (hor[ii] & 1 && ver[jj] & 1) {
          changes++;
          change = {ii+1, jj+1};
        }
      }
    }

    if (!diffs)
    {
      output += "OK\n";
    } else if (changes == 1)
    {
      output += "Change bit (" + to_string(change.first) + "," +
                                 to_string(change.second) + ")\n";
    } else
    {
      output += "Corrupt\n";
    }
  }

  printf("%s", output.c_str());

  return(0);
}