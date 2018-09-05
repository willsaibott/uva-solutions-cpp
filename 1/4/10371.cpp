/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
**/

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <ctime>

using namespace std;

void populateTZ(map<string, double> &tz)
{
  tz["UTC"] = 0;
  tz["GMT"] = 0;
  tz["BST"] = 1;
  tz["IST"] = 1;
  tz["WET"] = 0;
  tz["WEST"] = 1;
  tz["CET"] = 1;
  tz["CEST"] = 2;
  tz["EET"] = 2;
  tz["EEST"] = 3;
  tz["MSK"] = 3;
  tz["MSD"] = 4;
  tz["AST"] = -4;
  tz["ADT"] = -3;
  tz["NST"] = -3.5;
  tz["NDT"] = -2.5;
  tz["EST"] = -5;
  tz["EDT"] = -4;
  tz["CST"] = -6;
  tz["CDT"] = -5;
  tz["MST"] = -7;
  tz["MDT"] = -6;
  tz["PST"] = -8;
  tz["PDT"] = -7;
  tz["HST"] = -10;
  tz["AKST"] = -9;
  tz["AKDT"] = -8;
  tz["AEST"] = 10;
  tz["AEDT"] = 11;
  tz["ACST"] = 9.5;
  tz["ACDT"] = 10.5;
  tz["AWST"] = 8;
}

int main()
{
  int k = 0;
  int N;
  struct tm *date;
  time_t seconds, offset;
  string output = "";
  string hour, period, tz1, tz2;
  int h, m;
  map<string, double> tz;

  populateTZ(tz);

  output.reserve(500000);
  cin >> N;
  cin.ignore();

  seconds = time(0);
  seconds -= seconds % (24 * 3600);
  // date = localtime(&seconds);

  while(k++ < N)
  {
    cin >> hour;

    if (hour == "noon")
    {
      h = 12;
      m = 0;
    } else if (hour == "midnight")
    {
      h = m = 0;
    } else
    {
      cin >> period;

      h = stoi(hour.substr(0, hour.find(":"))) % 12;
      m = stoi(hour.substr(hour.find(":") + 1));
      if (period == "p.m.")
      {
        h += 12;
      }
    }

    cin >> tz1 >> tz2;
    offset = seconds + (h + tz[tz2] - tz[tz1]) * 3600.0 + m * 60;
    date = gmtime(&offset);

    string min = to_string(date->tm_min);
    min = min.size() < 2 ? "0" + min : min;
    h = date->tm_hour % 12;
    h = !h ? 12 : h;

    if (date->tm_hour == 0 && date->tm_min == 0)
    {
      output += "midnight\n";
    } else if (date->tm_hour == 12 && date->tm_min == 0)
    {
      output += "noon\n";
    } else if (date->tm_hour >= 12)
    {
      output += to_string(h) + ":" + min + " p.m.\n";
    } else
    {
      output += to_string(h) + ":" + min + " a.m.\n";
    }
  }

  printf("%s", output.c_str());

  return(0);
}