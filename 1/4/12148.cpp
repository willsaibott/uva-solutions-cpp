/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
**/

#include <cstdio>
#include <iostream>
#include <string>
#include <cstring>
#include <ctime>

using namespace std;

const int ONE_DAY = 24 * 3600;

int main()
{
  int measures, value, newValue, day, month, year, cont;
  string output = "";
  string line;
  time_t before, after;

  output.reserve(500000);

  while(true)
  {
    int result = cont = 0;
    cin >> measures;
    cin.ignore();

    if (cin.eof() || !measures) break;

    cin >> day >> month >> year >> value;

    struct tm dBefore = { 0, 0, 0, day, month - 1, year + 100 };

    while (--measures)
    {
      cin >> day >> month >> year >> newValue;

      struct tm dAfter = { 0, 0, 0, day, month - 1, year + 100 };

      before = mktime(&dBefore);
      after  = mktime(&dAfter);

      if (difftime(after, before) == ONE_DAY)
      {
        cont++;
        result += newValue - value;
      }

      memcpy(&dBefore, &dAfter, sizeof(dAfter));
      value = newValue;
    }

    output += to_string(cont) + " " +
              to_string(result) + "\n";
  }

  printf("%s", output.c_str());

  return(0);
}