/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
**/

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <ctime>

#define toDig(x)  (x - '0')
#define YEAR  (365)
#define toYears(x)  (x / )

using namespace std;

const int MAX = 130;

int main()
{
  int k = 0;
  int N, result, mm, dd, yyyy;
  string output = "";
  string line;
  struct tm today, birthday;

  output.reserve(500000);
  cin >> N;
  cin.ignore();

  while(k++ < N)
  {
    cin.ignore(); // blank line
    if (!scanf("%d/%d/%d", &dd, &mm, &yyyy)) break;

    today.tm_mday = dd;
    today.tm_mon = mm - 1;
    today.tm_year = yyyy - 1900;

    if (!scanf("%d/%d/%d", &dd, &mm, &yyyy)) break;

    birthday.tm_mday = dd;
    birthday.tm_mon = mm - 1;
    birthday.tm_year = yyyy - 1900;

    result = (today.tm_year - birthday.tm_year) -
             (today.tm_mon != birthday.tm_mon ?
              today.tm_mon < birthday.tm_mon :
              today.tm_mday < birthday.tm_mday);

    if (result < 0)
    {
      output += "Case #" + to_string(k) + ": Invalid birth date\n";
    } else if (result > MAX)
    {
      output += "Case #" + to_string(k) + ": Check birth date\n";
    } else
    {
      output += "Case #" + to_string(k) + ": " +
                to_string(result) + "\n";
    }
  }

  printf("%s", output.c_str());

  return(0);
}