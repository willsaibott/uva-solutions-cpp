/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
**/

#include <cstdio>
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

typedef unsigned long long ull;

#define SECOND  100
#define HOUR  (MIN * 60)
#define MIN  (SECOND * 60)
#define MAX  24.0 * HOUR
#define FACTOR  1000000

int main()
{
  ull hour, minute, sec, cent;
  ull sUnits;
  string output = "";
  string line;
  ull value;

  output.reserve(500000);

  while(getline(cin, line))
  {
    stringstream ss;
    hour = stoi(line.substr(0, 2));
    minute = stoi(line.substr(2, 4));
    sec = stoi(line.substr(4, 6));
    cent = stoi(line.substr(6));
    sUnits = hour * HOUR + minute * MIN + sec * SECOND + cent;
    value = (sUnits / (MAX)) * FACTOR;
    ss << std::setw(7) << std::setfill('0') << value << "\n";
    output += ss.str();
  }

  printf("%s", output.c_str());

  return(0);
}