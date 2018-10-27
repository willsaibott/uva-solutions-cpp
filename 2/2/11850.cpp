/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * 11850 - Alaska
**/

#include <cstdio>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

#define MAX_DISTANCE 1422

int main()
{
  string output = "";
  string line;


  output.reserve(500000);

  while(!cin.eof())
  {
    int n;
    bool possible = true;
    int charge = 0;
    cin >> n;

    if (!n) break;

    vector<int> stations(n);

    for (int ii = 0; ii < n; ii++)
    {
      cin >> stations[ii];
    }

    sort(stations.begin(), stations.end());

    int last = 0, next;

    for (int ii = 0; ii < n && possible; ii++)
    {
      next = stations[ii];
      possible = (last + charge >= next);
      last = next;
      charge = 200;
    }

    if (possible)
    {
      possible = (last + charge) >= MAX_DISTANCE + 2 * abs(MAX_DISTANCE - last);
    }

    if (possible) output += "POSSIBLE\n";
    else output += "IMPOSSIBLE\n";
  }

  printf("%s", output.c_str());

  return(0);
}