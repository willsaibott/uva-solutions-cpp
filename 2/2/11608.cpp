/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
**/

#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
  int k = 0;
  string output = "";
  string line;

  output.reserve(500000);

  while(!cin.eof())
  {
    int initial, problems;
    vector<int> created(12), required(12);
    cin >> initial;

    if (initial < 0) break;
    problems = initial;

    for (int ii = 0; ii < 12; ii++)
    {
      cin >> created[ii];
    }

    output += "Case " + to_string(++k) + ":\n";
    for (int ii = 0; ii < 12; ii++)
    {
      cin >> required[ii];
      bool success = (problems - required[ii]) >= 0;

      if (success)
      {
        output += "No problem! :D\n";
        problems -= required[ii];
      }
      else
      {
        output += "No problem. :(\n";
      }
      problems += created[ii];
    }
  }

  printf("%s", output.c_str());

  return(0);
}