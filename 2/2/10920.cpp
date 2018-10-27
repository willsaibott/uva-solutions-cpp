/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * 10920 - Spiral Tap
**/

#include <cstdio>
#include <iostream>
#include <cmath>


using namespace std;

#define UP_DOWN 0
#define RIGHT_LEFT 1
#define DOWN_UP 2
#define LEFT_RIGHT 3

typedef unsigned long long ull;

inline ull nextOdd(ull number)
{
  return number + ((number+1) & 1);
}

int main()
{
  string output = "";
  string line;

  output.reserve(500000);

  while(!cin.eof())
  {
    ull n, pos;
    cin >> n >> pos;

    if (!n && !pos) break;

    ull ring = nextOdd(ceil(pow(pos, 0.5)));
    ull start = ring * ring;
    ull end = start - ring + 1;
    ull direction = UP_DOWN;

    ull ringId = ring / 2;
    ull center = n / 2 + 1;
    pos = min(n*n, pos);

    while(end > pos)
    {
      direction = (direction + 1) & 3;
      start = end;
      end = start - ring + 1;
    }

    ull x = center, y = center;

    switch(direction)
    {
      case UP_DOWN:
        x = center + ringId;
        y = center + ringId - (start - pos);
        break;
      case DOWN_UP:
        x = center - ringId;
        y = center - ringId + (start - pos);
        break;
      case RIGHT_LEFT:
        x = center + ringId - (start - pos);
        y = center - ringId;
        break;
      case LEFT_RIGHT:
        x = center - ringId + (start - pos);
        y = center + ringId;
        break;
    }

    output += "Line = " + to_string(y) +
              ", column = " + to_string(x) + ".\n";
  }

  printf("%s", output.c_str());

  return(0);
}