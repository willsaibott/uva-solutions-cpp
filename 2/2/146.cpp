/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 *
 * 146 - ID Codes
**/

#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;
typedef unsigned char byte;
typedef unsigned long long ull;

int main()
{
  string output = "";
  string line;

  output.reserve(500000);

  while(getline(cin, line))
  {
    if (line == "#") break;
    string sorted = line;
    sort(sorted.begin(), sorted.end());
    next_permutation(line.begin(), line.end());

    if (line == sorted)
    {
      output += "No Successor\n";
    } else
    {
      output += line + "\n";
    }
  }

  printf("%s", output.c_str());

  return(0);
}