/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
**/

#include <cstdio>
#include <iostream>
#include <string>
#include <ctime>

using namespace std;

const int _2011 = 2011 - 1900;
int main()
{
  int k = 0, month, day;
  int N;
  string output = "";
  char s[20];

  output.reserve(500000);
  cin >> N;
  cin.ignore();

  while(k++ < N)
  {
    cin >> month >> day;
    struct tm date = {0, 0, 0, day, month - 1, _2011};
    mktime(&date);
    strftime(s, 20,  "%A\n", &date);
    output += s;
  }

  printf("%s", output.c_str());

  return(0);
}