/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
**/

#include <cstdio>
#include <iostream>
#include <map>
#include <string>
#include <ctime>

using namespace std;

typedef unsigned long long ull;

const ull ONE_DAY = 24 * 3600;

void populateMap(map<string, int> &m)
{
  m["January"] = 0;
  m["February"] = 1;
  m["March"] = 2;
  m["April"] = 3;
  m["May"] = 4;
  m["June"] = 5;
  m["July"] = 6;
  m["August"] = 7;
  m["September"] = 8;
  m["October"] = 9;
  m["November"] = 10;
  m["December"] = 11;
}

int main()
{
  int k = 0, year, day, daysToAdd;
  int N;
  string output = "";
  string month, line;
  char result[20];
  time_t t;
  struct tm *date = localtime(&t);
  map<string, int> m;

  output.reserve(500000);
  cin >> N;
  cin.ignore();

  populateMap(m);

  date->tm_hour = 12;
  date->tm_min  = 0;
  date->tm_sec = 0;

  while(k++ < N)
  {
    getline(cin, line, '-');
    year = stoi(line) - 1900;
    getline(cin, month, '-');
    getline(cin, line);
    day = stoi(line);

    cin >> daysToAdd;

    date->tm_mon = m[month];
    date->tm_mday = day;
    date->tm_year = year;

    t = mktime(date) + daysToAdd * ONE_DAY;
    date = localtime(&t);
    strftime(result, 20, "%Y-%B-%d", date);
    output += "Case " + to_string(k) + ": ";
    output += result;
    output += "\n";
  }

  printf("%s", output.c_str());

  return(0);
}