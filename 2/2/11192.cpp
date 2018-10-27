/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
**/

#include <cstdio>
#include <algorithm>
#include <iostream>

using namespace std;

int main()
{
  string output = "";
  string line;

  output.reserve(500000);

  while(!cin.eof())
  {
    int n, length;
    cin >> n >> line;
    if (!n || cin.eof()) break;

    length = line.size() / n;

    for (uint ii = 0; ii < line.size(); ii+=length)
    {
      string group = line.substr(ii, length);

      reverse(group.rbegin(), group.rend());

      output += group;
    }

    output += "\n";
  }

  printf("%s", output.c_str());

  return(0);
}