/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
**/

#include <cstdio>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cmath>

using namespace std;

int main()
{
  string output = "";
  string line;
  int hour, minute, index;
  double angleHour, angleMin, angle, total = 12 * 60.0;
  double diff;

  output.reserve(500000);

  while(getline(cin, line))
  {
    if (line == "0:00") break;
    index = line.find(":");

    hour    = stoi(line.substr(0, index)) % 12;
    minute  = stoi(line.substr(index + 1));
    angleHour = double(hour * 60 + minute) / total * 360.0;
    angleMin  = double(minute) / 60.0 * 360.0;
    diff   = abs(angleHour - angleMin);
    angle  = min(diff, 360.0 - diff);

    stringstream ss;
    ss << fixed;
    ss.precision(3);
    ss << angle;

    output += ss.str() + "\n";
  }

  printf("%s", output.c_str());

  return(0);
}