/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
**/

#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>

using namespace std;

int main()
{
  int k = 0;
  string output = "";
  string line;

  while(getline(cin, line))
  {
    output += line + "\n";
  }

  printf("%s", output.c_str());

  return(0);
}