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

int main()
{
  int k = 0;
  int N;
  string output = "";
  string line;

  output.reserve(500000);
  cin >> N;
  cin.ignore();

  // for (int ii = 1; ii < 31; ii++)
  // {
  //   output += to_string(ii * 5) + " " + to_string(31 - ii) + "\n";
  // }

  while(k++ < N && !cin.eof())
  {
    int maxWeight, n, pos = 0, weight = 0,
        w, x, distance = 0;

    cin >> maxWeight >> n;

    queue<pair<int, int>> stop;
    pair<int, int> last, curr;

    for (int ii = 0; ii < n; ii++)
    {
      cin >> x >> w;
      stop.push({ x, w });
    }

    while (!stop.empty())
    {
      curr = stop.front();
      w = curr.second;
      x = curr.first;

      distance += x - pos;

      if (weight + w <= maxWeight)
      {
        weight += w;

        last = curr;
        stop.pop();

        pos = x;
        if (stop.empty() || weight == maxWeight)
        {
          pos = weight = 0;
          distance += x;
        }
      }
      else
      {
        last = curr;
        stop.pop();
        distance += 2 * x;
        pos = x;
        weight = w;
      }

      if (stop.empty() && pos)
      {
        pos = 0;
        distance += x;
      }
    }

    output += to_string(distance) + "\n";
    //output += to_string(maxWeight) + "-" + to_string(n) + "\n";
  }

  printf("%s", output.c_str());

  return(0);
}