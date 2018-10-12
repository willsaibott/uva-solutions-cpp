/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
**/

#include <cstdio>
#include <iostream>

using namespace std;

int memo[(uint)1E6] = {0};

int main()
{
  string output = "";
  string line;

  output.reserve(500000);

  while(!cin.eof())
  {
    int start, end, maxLife = 0, clife, fin;

    if (scanf("%d %d\n", &start, &end) != 2) break;

    fin = max(end, start);
    for (int cicle = min(start, end); cicle <= fin; cicle++)
    {
      int n = cicle;
      clife = memo[cicle];

      if (!clife)
      {
        while (n != 1)
        {
          clife++;
          n = (n & 1 ? 3 * n + 1 : n >> 1);
        }
        clife++;
        memo[cicle] = clife;
      }

      maxLife = max(maxLife, clife);
    }

    output += to_string(start) + " " + to_string(end) + " " +
              to_string(maxLife) + "\n";
  }

  printf("%s", output.c_str());

  return(0);
}