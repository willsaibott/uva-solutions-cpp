/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 *
 * 11933 - Splitting Numbers
**/

#include <cstdio>
#include <iostream>

using namespace std;
typedef unsigned char byte;
typedef unsigned long long ull;
typedef long long ll;

int main()
{
  string output = "";
  string line;

  output.reserve(500000);

  while(!cin.eof())
  {
    ull n;
    cin >> n;

    if (!n) break;

    ull count = 0;
    ull a = 0, b = 0;

    for (int ii = 0; ii < 64; ii++)
    {
      ull bit = (n & (1ull << ii));
      if (bit)
      {
        count++;
        a |= (count & 1) * (bit);
        b |= (!(count & 1)) * (bit);
      }
    }

    output += to_string(a) + " " + to_string(b) + "\n";
  }

  printf("%s", output.c_str());

  return(0);
}