/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
**/

#include <cstdio>
#include <iostream>

using namespace std;

const int ONE_HOUR = 60;

typedef struct time {
  int hour;
  int minute;

  inline bool operator < (struct time &tt)
  {
    return (hour != tt.hour ? (hour < tt.hour) : (minute < tt.minute));
  }
} timest;

typedef struct interval {
  timest start;
  timest end;

  inline bool operator < (struct interval &ii)
  {
    return ii.end < start;
  }

  inline bool operator > (struct interval &ii)
  {
    return end < ii.start;
  }
} intervalst;

int main()
{
  int k = 0;
  int N;
  string output = "";
  string line, result;
  timest t1, t2;
  intervalst i1, i2;

  output.reserve(500000);
  cin >> N;
  cin.ignore();

  while(k++ < N)
  {
    if (!scanf("%d:%d %d:%d",
               &(t1.hour),
               &(t1.minute),
               &(t2.hour),
               &(t2.minute))) break;

    i1.start = t1; i1.end = t2;

    if (!scanf("%d:%d %d:%d",
               &(t1.hour),
               &(t1.minute),
               &(t2.hour),
               &(t2.minute))) break;

    i2.start = t1; i2.end = t2;

    result = ((i2 < i1 || i2 > i1) ?
              "Hits Meeting\n" :
              "Mrs Meeting\n");

    output += "Case " + to_string(k) + ": " + result;
  }

  printf("%s", output.c_str());

  return(0);
}