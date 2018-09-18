/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
**/

#include <cstdio>
#include <iostream>

using namespace std;

int main()
{
  int k = 0;
  string output = "";
  string line;

  output.reserve(50000);

  while(getline(cin, line))
  {
    k = stoi(line);

    output+= (!((k) % 6)  ? "Y\n" : "N\n");
  }

  printf("%s", output.c_str());
  return(0);
}