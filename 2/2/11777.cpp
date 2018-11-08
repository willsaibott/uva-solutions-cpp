/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 *
 * 11777 - Automate the Grades
**/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
typedef unsigned char byte;
typedef unsigned long long ull;
typedef long long ll;

int main()
{
  int k = 0;
  int N;
  string output = "";
  string line;

  output.reserve(500000);
  cin >> N;
  cin.ignore();

  while(k++ < N && !cin.eof())
  {
    int term1, term2, finalTerm, attendance;
    vector<double> tests(3);

    cin >> term1 >> term2 >> finalTerm >> attendance;

    for (int ii = 0; ii < 3; ii++)
    {
      cin >> tests[ii];
    }

    sort(tests.begin(), tests.end());

    double average = (tests[1] + tests[2]) / 2.0;
    double sum = term1 + term2 + finalTerm + attendance+
                 average;

    output += "Case " + to_string(k) +
              ": ";

    if (sum >= 90)
    {
      output += "A\n";
    } else if (sum >= 80)
    {
      output += "B\n";
    } else if (sum >= 70)
    {
      output += "C\n";
    } else if (sum >= 60)
    {
      output += "D\n";
    } else
    {
      output += "F\n";
    }
  }

  printf("%s", output.c_str());

  return(0);
}