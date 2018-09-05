/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
**/

#include <cstdio>
#include <cstdlib>
#include <iostream>
// #include <ctime>

using namespace std;


// bool isLeapYear(int year)
// {
//   tm february29 = {0, 0, 0, 29, 1, year - 1900};

//   return static_cast<time_t>(-1) != mktime(&february29) &&
//          february29.tm_mday == 29 &&
//          february29.tm_mon == 1 &&
//          february29.tm_year == year - 1900;
// }

// bool isHuluculuYear(int year)
// {
//   return year % 15;
// }

// bool isBulukuluYear(int year)
// {
//   return year % 55;
// }

bool isLeapYear(string year)
{
  int size = year.size();
  int fYear = stoi(year.substr(max(size - 4, 0)));
  return !(fYear & 3) &&
         ((fYear % 100) || !(fYear & 15));
}

bool isHuluculuYear(string year)
{
  bool leapYear = false;
  int size = year.size();
  int sum = 0;

  if (year.back() == '0' || year.back() == '5')
  {
    for(int ii = 0; ii < size; ii++) {
      sum += year[ii] - '0';
    }
    leapYear = (sum % 3) == 0;
  }
  return leapYear;
}

bool isBulukuluYear(string year)
{
  bool leapYear = false;
  int size = year.size();
  int sum = 0;

  if (year.back() == '0' || year.back() == '5')
  {
    for(int ii = 0; ii < size; ii++) {
      sum += (year[ii] - '0') * ( ii & 1 ? 1 : -1);
    }
    leapYear = (sum % 11) == 0;
  }
  return leapYear;
}

int main()
{
  int k = 0;
  string output = "";
  string line;
  bool leapYear;

  output.reserve(500000);

  while(getline(cin, line))
  {
    int matches = 0;
    leapYear = isLeapYear(line);

    if (k++) output += "\n";

    if (leapYear)
    {
      output += "This is leap year.\n";
      matches++;
    }
    if (isHuluculuYear(line))
    {
      output += "This is huluculu festival year.\n";
      matches++;
    }
    if (leapYear && isBulukuluYear(line))
      output += "This is bulukulu festival year.\n";

    if (!matches)
      output += "This is an ordinary year.\n";
  }

  printf("%s", output.c_str());

  return(0);
}