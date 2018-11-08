/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 *
 * 700 - Date Bugs
**/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
typedef unsigned char byte;
typedef unsigned long long ull;
typedef long long ll;

typedef struct yearStruct {
  int y;
  int a;
  int b;
  int diff;
} Year;

const int MAX = 10000;

int main()
{
  string output = "";
  string line;
  bool begin = true;
  int k = 0;

  output.reserve(500000);

  while(!cin.eof())
  {
    vector<bool> years(10000, true);
    int n;
    cin >> n;

    if (!begin || (begin = false)) output += "\n";
    if (!n) break;

    vector<Year> ys(n);
    int actual = MAX+1;
    for (int ii = 0; ii < n; ii++)
    {
      cin >> ys[ii].y >> ys[ii].a >> ys[ii].b;
      ys[ii].diff = ys[ii].b - ys[ii].a;

      for (int jj = ys[ii].y-1; jj >= 0; jj--)
      {
        years[jj] = false;
      }

      for (int jj = ys[ii].y; jj < 10000; jj++)
      {
        if (jj != ys[ii].y && (jj - ys[ii].y) % (ys[ii].diff) != 0)
        {
          years[jj] = false;
        }
      }
    }

    output += "Case #" + to_string(++k) + ":\n";

    for (int ii = 0; ii < MAX; ii++)
    {
      if (years[ii])
      {
        actual = ii;
        break;
      }
    }

    if (actual > MAX)
    {
      output += "Unknown bugs detected.\n";
    } else
    {
      output += "The actual year is " +
                to_string(actual) + ".\n";
    }
  }

  printf("%s", output.c_str());

  return(0);
}