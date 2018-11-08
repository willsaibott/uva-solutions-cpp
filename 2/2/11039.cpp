/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 *
 * 11039 - Building designing
**/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
typedef unsigned char byte;
typedef unsigned long long ull;

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
    int n;
    cin >> n;

    if (!n)
    {
      output += "0\n";
      continue;
    }

    vector<int> floors(n);

    for (int ii = 0; ii < n; ii++)
    {
      cin >> floors[ii];
    }

    sort(floors.begin(), floors.end(), [](int &v1, int &v2) {
      return abs(v1) < abs(v2);
    });

    int count = 1;
    int last = floors[0];

    for (int ii = 1; ii < n; ii++)
    {
      if ((floors[ii] > 0 && last < 0) ||
          (floors[ii] < 0 && last > 0))
      {
        count++;
        last = floors[ii];
      }
    }

    output += to_string(count) + "\n";
  }

  printf("%s", output.c_str());

  return(0);
}