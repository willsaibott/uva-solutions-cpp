/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 *
 * 11760 - Brother Arif, Please feed us!
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

const int MAX = 10008;

int main()
{
  int k = 0;
  string output = "";
  string line;

  output.reserve(500000);
  bitset<MAX> rows(0), columns(0);

  while(!cin.eof())
  {
    bool escaped = true;
    int r, c, n;
    cin >> r >> c >> n;

    if (!n && !r && !c) break;
    rows.reset();
    columns.reset();

    for (int ii = 0; ii < n; ii++)
    {
      uint row, column;
      cin >> row >> column;
      rows.set(row);
      columns.set(column);
    }

    int row, column;
    cin >> row >> column;

    escaped = !(rows[row]             || columns[column])             ||
              !(rows[min(row+1, r-1)] || columns[column])             ||
              !(rows[row]             || columns[min(column+1, c-1)]) ||
              !(rows[max(row-1, 0)]   || columns[column])             ||
              !(rows[row]             || columns[max(0, column-1)]);

    output += "Case " + to_string(++k) + ": ";

    if (escaped)
    {
      output += "Escaped again! More 2D grid problems!\n";
    } else
    {
      output += "Party time! Let's find a restaurant!\n";
    }
  }

  printf("%s", output.c_str());

  return(0);
}