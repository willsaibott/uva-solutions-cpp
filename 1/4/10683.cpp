/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
**/

#include <cstdio>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <cmath>

using namespace std;

typedef unsigned long long ull;

#define CENT    10
#define SECOND  100 * CENT
#define HOUR  (MIN * 60)
#define MIN  (SECOND * 60)
#define MAX  24.0 * HOUR
#define FACTOR  10000000

int main()
{
  ull sUnits;
  string output = "";
  string line;
  ull value;
  const ull second = SECOND;
  const ull cent = CENT;
  const ull hour = HOUR;
  const ull minute = MIN;
  const double max = MAX;
  const double rate = FACTOR / max;
  char s[10];

  output.reserve(50000);

  while(getline(cin, line))
  {
    sUnits = ((line[0] - '0') * 10 + (line[1] - '0')) * hour +
             ((line[2] - '0') * 10 + (line[3] - '0')) * minute +
             ((line[4] - '0') * 10 + (line[5] - '0')) * second +
             ((line[6] - '0') * 10 + (line[7] - '0')) * cent;

    value = (sUnits * rate);
    sprintf(s, "%07llu\n", value);
    output += s;
  }

  printf("%s", output.c_str());

  return(0);
}