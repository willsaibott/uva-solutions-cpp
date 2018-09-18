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

const int ONE_DAY = 24 * 3600;

bool isLeap(int year)
{
  return (!(year & 3) && ( (year % 100) || !(year & 15) ));
}

bool beforeFebruary29(struct tm &date)
{
  return (date.tm_mon < 1) ||
         (date.tm_mon == 1 && (date.tm_mday <= 29));
}

time_t nextFebruary29(struct tm &date)
{
  struct tm february29 = {0, 0, 0, 29, 1, date.tm_year};
  int year = (date.tm_year + 1900);

  if ((!beforeFebruary29(date) || !(isLeap(year))))
  {
    while (!isLeap(++year));
    february29.tm_year = year - 1900;
  }

  return mktime(&february29);
}

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
  time_t before, after;
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

    after = mktime(&aft);
    before = nextFebruary29(bef);

    while (difftime(after, before) >= 0)
    {
      before += ONE_DAY;
      bef = *(localtime(&before));
      result++;
      before = nextFebruary29(bef);
    }

    output += "Case " + to_string(k) + ": " +
                        to_string(result) + "\n";
  }

  printf("%s", output.c_str());

  return(0);
}