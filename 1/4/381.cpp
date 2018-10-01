/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
**/

#include <cstdio>
#include <iostream>
#include <string>
#include <cmath>
#include <climits>

using namespace std;

const int FINAL_GRADES[] = {4, 3, 2, 1, 0};
const int ABSENCES_LOSS = 4;
const int NO_ABSENCES_GAIN = 1;
const int BONUS_POINT_GAIN = 3;

int main()
{
  int k = 0;
  int N, students, tests, minimum;
  string output = "";
  string line;
  bool discardLowest;
  char s[20];

  output.reserve(500000);
  cin >> N;
  cin.ignore();

  output += "MAKING THE GRADE OUTPUT\n";

  while(k++ < N)
  {
    cin >> students >> tests;
    discardLowest = (tests > 2);
    int grades[students][tests];
    int absences[students];
    int bonus[students];
    double averages[students];
    char letterGrade[students];
    double totalAverages = 0;
    double sd = 0, mean = 0;
    int finalGrades = 0;

    for(int ii = 0; ii < students; ii++) {
      int total = 0;
      double divisor = tests;

      minimum = INT_MAX;
      for(int jj = 0; jj < tests; jj++) {
        cin >> grades[ii][jj];
        minimum = min(grades[ii][jj], minimum);
        total += grades[ii][jj];
      }

      cin >> bonus[ii] >> absences[ii];

      if (discardLowest)
      {
        total -= minimum;
        divisor--;
      }

      totalAverages += averages[ii] = total / divisor;
    }

    mean = totalAverages / students;

    for(int ii = 0; ii < students; ii++) {
      sd += (averages[ii] - mean) * (averages[ii] - mean);
    }

    sd = max(1.0, sqrt(sd / students));

    for(int ii = 0; ii < students; ii++) {
      averages[ii] += BONUS_POINT_GAIN * (bonus[ii] / 2);

      if (averages[ii] >= (sd + mean)) letterGrade[ii] = 'A';
      else if (averages[ii] >= mean) letterGrade[ii] = 'B';
      else if (averages[ii] >= mean - sd) letterGrade[ii] = 'C';
      else letterGrade[ii] = 'D';

      if (!absences[ii])
        letterGrade[ii] = max((int)'A',
                              letterGrade[ii] - NO_ABSENCES_GAIN);

      letterGrade[ii] = min ((int)'F',
                             letterGrade[ii] + absences[ii] / ABSENCES_LOSS);

      finalGrades += FINAL_GRADES[letterGrade[ii] - 'A'];
    }

    sprintf(s, "%.1f\n", (finalGrades / double(students)));
    output += s;
  }

  output += "END OF OUTPUT\n";
  printf("%s", output.c_str());

  return(0);
}