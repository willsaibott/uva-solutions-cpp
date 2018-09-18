/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
**/

#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
#include <utility>
#include <string>
#include <iomanip>
#include <set>
#include <queue>
#include <stack>
#include <sstream>
#include <ctime>

using namespace std;

const int GESTATION = 40 * 7 * 24 * 3600;

// Aquarius January, 21 February, 19
// Pisces February, 20 March, 20
// Aries March, 21 April, 20
// Taurus April, 21 May, 21
// Gemini May, 22 June, 21
// Cancer June, 22 July, 22
// Leo July, 23 August, 21
// Virgo August, 22 September, 23
// Libra September, 24 October, 23
// Scorpio October, 24 November, 22
// Sagittarius November, 23 December, 22
// Capricorn December, 23 January, 20

string getZodiac(struct tm *date)
{
  switch(date->tm_mon)
  {
    case 0:  return (date->tm_mday < 21 ? "capricorn"   : "aquarius");
    case 1:  return (date->tm_mday < 20 ? "aquarius"    : "pisces");
    case 2:  return (date->tm_mday < 21 ? "pisces"      : "aries");
    case 3:  return (date->tm_mday < 21 ? "aries"       : "taurus");
    case 4:  return (date->tm_mday < 22 ? "taurus"      : "gemini");
    case 5:  return (date->tm_mday < 22 ? "gemini"      : "cancer");
    case 6:  return (date->tm_mday < 23 ? "cancer"      : "leo");
    case 7:  return (date->tm_mday < 22 ? "leo"         : "virgo");
    case 8:  return (date->tm_mday < 24 ? "virgo"       : "libra");
    case 9:  return (date->tm_mday < 24 ? "libra"       : "scorpio");
    case 10: return (date->tm_mday < 23 ? "scorpio"     : "sagittarius");
    case 11: return (date->tm_mday < 23 ? "sagittarius" : "capricorn");
    default: return "";
  }
}

int main()
{
  int k = 0, dd, mm, yyyy;
  int N;
  string output = "";
  string line;
  char s[20];
  time_t tt;
  struct tm *date = localtime(&tt);

  output.reserve(500000);
  cin >> N;
  cin.ignore();

  date->tm_hour = 12;
  date->tm_min = 0;
  date->tm_sec = 0;

  while(k++ < N)
  {
    if(!scanf("%2d%2d%4d", &mm, &dd, &yyyy)) break;

    date->tm_mday = dd;
    date->tm_mon = mm - 1;
    date->tm_year = yyyy - 1900;

    tt = mktime(date) + GESTATION;
    date = localtime(&tt);
    strftime(s, 20, " %m/%d/%Y ", date);

    output+= to_string(k) + s + getZodiac(date) + "\n";
  }

  printf("%s", output.c_str());

  return(0);
}