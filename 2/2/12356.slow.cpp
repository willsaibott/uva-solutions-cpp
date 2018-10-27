/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
**/

#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
#include <utility>
#include <string>
#include <iomanip>
#include <set>
#include <queue>
#include <stack>
#include <sstream>
#include <cmath>

using namespace std;

bool isInside(pair<int, int> interval, int index)
{
  return (index >= interval.first &&
          index <= interval.second);
}

int main()
{
  string output = "";
  string line;
  bool begin = true;

  output.reserve(50000);
  while(!cin.eof())
  {
    int n, reports;
    cin >> n >> reports;

    if (!begin || (begin = false)) output += "-\n";
    if (!n || cin.eof()) break;

    set<int> soldiers;

    for (int ii = 1; ii <= n; ii++)
    {
      soldiers.insert(ii);
    }

    for (int ii = 0; ii < reports; ii++)
    {
      int l, r;
      cin >> l >> r;
      auto left = soldiers.find(l);
      auto buddy = prev(left);
      auto start = left;

      if (left != soldiers.begin())
      {
        output += to_string(*buddy) + " ";
      } else
      {
        output += "* ";
      }

      left = next(left);
      while (*left <= r && left != soldiers.end())
      {
        soldiers.erase(left);
        left = next(start);
        if (!soldiers.size()) break;
      }

      buddy = next(start);
      if (buddy != soldiers.end())
      {
        output += to_string(*buddy) + "\n";
      } else
      {
        output += "*\n";
      }

      soldiers.erase(start);
    }
  }

  printf("%s", output.c_str());

  return(0);
}
