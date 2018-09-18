/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
**/

#include <cstdio>
#include <iostream>
#include <map>

using namespace std;

typedef struct tm tmst;

void populateCal(map<string, int> &cal)
{
  cal["January"] = 0;
  cal["February"] = 1;
  cal["March"] = 2;
  cal["April"] = 3;
  cal["May"] = 4;
  cal["June"] = 5;
  cal["July"] = 6;
  cal["August"] = 7;
  cal["September"] = 8;
  cal["October"] = 9;
  cal["November"] = 10;
  cal["December"] = 11;
}

int main()
{
  int k = 0, day, year;
  int N;
  string output = "";
  string line, month, comma;
  tmst bef = {0, 0, 0}, aft = {0, 0, 0};
  map<string, int> cal;

  output.reserve(500000);
  cin >> N;
  cin.ignore();

  populateCal(cal);

  while(k++ < N)
  {
    int result = 0;

    cin >> month >> day >> comma >> year;
    bef.tm_mday = day;
    bef.tm_year = year - 1900;
    bef.tm_mon = cal[month];

    cin >> month >> day >> comma >> year;
    aft.tm_mday = day;
    aft.tm_year = year - 1900;
    aft.tm_mon = cal[month];

    if (bef.tm_mon > 1)
      bef.tm_year++;
    if (aft.tm_mon < 1 || (aft.tm_mon == 1 && aft.tm_mday < 29))
      aft.tm_year--;

    result = (aft.tm_year / 4 - (bef.tm_year - 1) / 4) -
              (aft.tm_year / 100 - (bef.tm_year - 1) / 100) +
              ((aft.tm_year + 1900) / 400 - (bef.tm_year + 1900 - 1) / 400);

    output += "Case " + to_string(k) + ": " +
                        to_string(result) + "\n";
  }

  printf("%s", output.c_str());

  return(0);
}