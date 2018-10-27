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
  bool begin = true;

  output.reserve(500000);

  while(!cin.eof())
  {
    int total = 0, n, value, division, m = 0;
    vector<int> v;
    vector<int> diffs;
    cin >> n;

    if (!begin || (begin = false)) output += "\n";
    if (!n) break;
    v.reserve(10);
    diffs.reserve(10);

    for (int ii = 0; ii < n; ii++)
    {
      cin >> value;
      total += value;
      v.push_back(value);
    }

    division = total / n;

    for (auto it = v.begin(); it != v.end(); it++)
    {
      m += abs(*it - division);
    }

    output += "Set #" + to_string(++k) +
              "\nThe minimum number of moves is " + to_string(m/2) + ".\n";
  }

  printf("%s", output.c_str());

  return(0);
}