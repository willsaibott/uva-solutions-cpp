/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 *
 * 594 - One Little, Two Little, Three Little Endians
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
    int n;
    cin >> n;

    if (cin.fail()) break;

    int endian = ((n & 0x000000FFu) << 030) |
                 ((n & 0x0000FF00u) << 010) |
                 ((n & 0x00FF0000u) >> 010) |
                 ((n & 0xFF000000u) >> 030);

    output += to_string(n) + " converts to " +
              to_string(endian) + "\n";
  }

  printf("%s", output.c_str());

  return(0);
}