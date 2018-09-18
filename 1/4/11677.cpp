/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
**/

#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

const int ONE_HOUR = 60;

int main()
{
  int h1, m1, h2, m2, total;
  string output = "";

  output.reserve(500000);

  while(true)
  {
    cin >> h1 >> m1 >> h2 >> m2;

    if (!(h1 || m1 || h1 || m2)) break;

    h2 = (h2 > h1 ? h2 : ((h2 < h1 || m1 > m2) ? h2 + 24 : h2 ));
    total = (h2 - h1) * ONE_HOUR + (m2 - m1);
    output +=  to_string(total) + "\n";
  }

  printf("%s", output.c_str());

  return(0);
}