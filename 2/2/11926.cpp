/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 *
 * 11926 - Multitasking
**/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <bitset>

using namespace std;
typedef unsigned char byte;
typedef unsigned long long ull;
typedef long long ll;

const uint MAX = 1000008;
int main()
{
  string output = "";
  string line;

  output.reserve(500000);
  bitset<MAX> time(0);

  while(!cin.eof())
  {
    uint n, m;
    cin >> n >> m;

    if (!n && !m) break;

    time.reset();

    bool conflicts = false;
    for (uint ii = 0; ii < n; ii++)
    {
      uint start, end;
      cin >> start >> end;

      for (uint jj = start+1; jj <= end && !conflicts; jj++)
      {
        conflicts = time[jj];
        time.set(jj);
      }
    }

    for (uint ii = 0; ii < m; ii++)
    {
      uint start, end, interval;
      cin >> start >> end >> interval;

      for (uint k = start;
                k < MAX && !conflicts;
                k+= interval, end = min(MAX-1, end + interval))

      {
        for (uint jj = k+1; jj <= end && !conflicts; jj++)
        {
          conflicts = time[jj];
          time.set(jj);
        }
      }
    }

    output += (conflicts ? "CONFLICT\n" : "NO CONFLICT\n");
  }

  printf("%s", output.c_str());

  return(0);
}