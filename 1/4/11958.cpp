/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
**/

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <climits>

using namespace std;

const int ONE_HOUR = 60;
const int ONE_DAY = 24 * ONE_HOUR;

int main()
{
  int k = 0, buses, now;
  int best, hour, minute, next, duration;
  int N;
  string output = "";
  string line;

  output.reserve(500000);
  cin >> N;
  cin.ignore();

  while(k++ < N)
  {
    best = INT_MAX;
    if (!scanf("%d %d:%d", &buses, &hour, &minute)) break;
    now = hour * ONE_HOUR + minute;

    for(int ii = 0; ii < buses; ii++) {
      if (!scanf("%d:%d %d", &hour, &minute, &duration)) break;
      next = hour * ONE_HOUR + minute;
      if (next < now) next += ONE_DAY;

      next += duration;
      best = min(best, next - now);
    }

    output += "Case " + to_string(k) + ": " + to_string(best) + "\n";
  }

  printf("%s", output.c_str());

  return(0);
}