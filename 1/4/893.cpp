/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
**/

#include <cstdio>
#include <iostream>
#include <ctime>

typedef long long ll;
using namespace std;

struct tm convert(int day, int month, int year)
{
  struct tm date = { 0, 0 , 0};

  date.tm_year = year - 1900; // 1900...INF
  date.tm_mon = month - 1; // 0..11
  date.tm_mday = day; // 1..31

  return date;
}

struct tm setDate(struct tm &date, ll days)
{
  static const time_t ONE_DAY = 24 * 3600;

  // Seconds since start of epoch
  time_t date_seconds = mktime(&date) + (days * ONE_DAY);

  // Update caller's date
  // Use localtime because mktime converts to UTC so may change datep
  return *localtime( &date_seconds );
}

int main()
{
  int  day, month, year;
  string output = "";
  string line;
  struct tm date; // nominal time midday (arbitrary)
  ll daysToAdd;

  output.reserve(500000);

  while(true)
  {
    cin >> daysToAdd >> day >> month >> year;

    if (!daysToAdd && !day && !month && !year) break;

    date = convert(day, month, year);
    date = setDate(date, daysToAdd);

    output += to_string(date.tm_mday) + " " +
              to_string(date.tm_mon + 1) + " " +
              to_string(date.tm_year + 1900) + "\n";

    // cout << asctime(&date) << endl;
  }

  printf("%s", output.c_str());

  return(0);
}