/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * 11093 - Just Finish it up
**/

#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

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
    bool possible = true;
    int n;
    cin >> n;

    if (!n || cin.eof()) break;

    vector<int> stations(n), spents(n), needed(n, 0);

    for (int ii = 0; ii < n; ii++)
    {
      cin >> stations[ii];
    }

    int fuel = 0;
    for (int ii = 0; ii < n; ii++)
    {
      cin >> spents[ii];
      fuel += stations[ii] - spents[ii];
    }

    if (fuel < 0)
    {
      possible = false;
    }

    int index;
    for (index = 0; index < n && possible; index++)
    {
      fuel = 0;
      for (int jj = 0; jj < n && fuel >= 0; jj++)
      {
        int next = (index + jj) % n;
        fuel += stations[next] -  spents[next];
      }
      if (fuel >= 0) break;
    }

    if (possible && index < n)
    {
      output += "Case " + to_string(k) +
                ": Possible from station " + to_string(index + 1) + "\n";
    } else
    {
      output += "Case " + to_string(k) + ": Not possible\n";
    }
  }

  printf("%s", output.c_str());

  return(0);
}