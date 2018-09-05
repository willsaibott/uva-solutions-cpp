/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
**/

#include <cstdio>
#include <iostream>
#include <map>

using namespace std;

string tzolkin[] = {
  "imix", "ik", "akbal", "kan", "chicchan",
  "cimi", "manik", "lamat", "muluk", "ok",
  "chuen", "eb", "ben", "ix", "mem", "cib",
  "caban", "eznab", "canac", "ahau"
};

string haab[] = {
  "pop", "no", "zip",  "zotz",  "tzec",  "xul",
  "yoxkin",  "mol",  "chen",  "yax",  "zac",
  "ceh",  "mac",  "kankin",  "muan",  "pax",
  "koyab",  "cumhu", "uayet"
};

const int tzolkinLength = 260;

typedef unsigned long long ull;

void populateHaabCalender(map<string, int> &m)
{
  for(int ii = 0; ii < 19; ii++) {
    m[haab[ii]] = ii * 20;
  }
}

ull getDays(string day,
            string month,
            int year,
            map<string, int> &m)
{
  day.pop_back();
  return year * 365 + (m[month]) + stoi(day);
}

string translate(ull days)
{
  int year = days / 260;
  int rest = days % 260;
  int name = (rest % 20);
  int number = (rest % 13) + 1;

  return to_string(number) + " " + tzolkin[name] + " " +
         to_string(year) + "\n";
}

int main()
{
  int k = 0;
  int N, year;
  ull days;
  string output = "";
  string day, month;
  map<string, int> haabCal;

  populateHaabCalender(haabCal);

  output.reserve(500000);
  cin >> N;

  output += to_string(N) + "\n";

  while(k++ < N)
  {
    cin >> day >> month >> year;
    days = getDays(day, month, year, haabCal);
    output += translate(days);
  }

  printf("%s", output.c_str());

  return(0);
}