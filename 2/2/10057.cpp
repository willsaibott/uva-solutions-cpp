/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 *
 * 10057 - A mid-summer night's dream.
**/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>

using namespace std;
typedef unsigned char byte;
typedef unsigned long long ull;

int main()
{
  string output = "";
  string line;

  output.reserve(500000);

  while(!cin.eof())
  {
    int n;
    cin >> n;
    if (cin.eof()) break;
    int a[65600] = {0};

    int MAX = 0;
    int MIN = INT32_MAX;
    for (int ii = 0; ii < n; ii++)
    {
      int x;
      cin >> x;
      a[x]++;
      MAX = max(x, MAX);
      MIN = min(MIN, x);
    }

    int sum = 0;
    int low = 0, high = 0;
    int median1 = (n&1 ? n/2 : (n-1)/2);
    int median2 = median1+1;
    for (int ii = MIN; ii <= MAX  && sum < n; ii++)
    {
      sum += a[ii];
      if (sum > median1)
      {
        low = ii;
        high = ii;
        if ((n & 1) == 0)
        {
          high = ii;
          sum -= a[ii];
          for (int jj = ii;
                   jj <= MAX && sum < n;
                   jj++)
          {
            sum += a[jj];
            if (sum > median2)
            {
              high = jj;
              break;
            }
          }
        }
        break;
      }
    }

    int count = (n & 1 || low == high ? a[low] : a[low] + a[high]);
    int existents = (n & 1 ? 1 : high - low + 1);

    output += to_string(low) + " " +
              to_string(count) + " " +
              to_string(existents) + "\n";
  }

  printf("%s", output.c_str());

  return(0);
}