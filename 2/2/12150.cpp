/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * 12150 - Pole Position
**/

#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

int main()
{
  string output = "";
  string line;

  output.reserve(500000);

  while(!cin.eof())
  {
    int n;
    cin >> n;

    if (!n) break;

    // vector<pair<string, int>> cars(n);
    vector<string> start(n);
    string car;
    int variation;
    bool success = true;

    for (int ii = 0; ii < n; ii++)
    {
      int position;
      cin >> car >> variation;
      position = ii + variation;

      success = success &&
                position >= 0 &&
                position < n &&
                start[position] == "";
      if (success)
      {
        start[position] = car;
      }
    }

    if (success)
    {
      for (auto c = start.begin(); c != start.end(); c++)
      {
        output += *c + (next(c) != start.end() ? " " : "\n");
      }
    } else
    {
      output += "-1\n";
    }
  }

  printf("%s", output.c_str());

  return(0);
}