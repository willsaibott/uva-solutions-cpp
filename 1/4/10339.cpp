/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
**/

#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

// int gcd(int a, int b)
// {
//   return b == 0 ? a : gcd(b, (a % b));
// }

int main()
{
  uint k, m, seconds, hour, minute, diff;
  const uint ONE_DAY = 24 * 3600;
  const uint HALF_DAY = 12 * 3600;
  char s[30];
  string output = "";
  string line;

  output.reserve(500000);

  while(true)
  {
    cin >> k >> m;
    cin.ignore();

    if (cin.eof()) break;

    diff = (k > m) ? k - m : m - k;

    // The 30 seconds makes it round automatically
    seconds = (HALF_DAY * (ONE_DAY - k) / diff) % HALF_DAY + 30;

    hour = (seconds / 3600) % 12;
    hour = (!hour ? 12 : hour);
    minute = (seconds / 60) % 60;

    sprintf(s, "%d %d %02d:%02d\n", k, m, hour, minute);
    output += s;
  }

  printf("%s", output.c_str());

  return(0);
}