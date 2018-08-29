/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
**/

#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

string digits[5][10] =
//  0      1      2      3      4      5      6     7      8       9
{{" - ", "   ", " - ", " - ", "   ", " - ", " - ", " - ", " - ", " - "},
 {"| |", "  |", "  |", "  |", "| |", "|  ", "|  ", "  |", "| |", "| |"},
 {"   ", "   ", " - ", " - ", " - ", " - ", " - ", "   ", " - ", " - "},
 {"| |", "  |", "|  ", "  |", "  |", "  |", "| |", "  |", "| |", "  |"},
 {" - ", "   ", " - ", " - ", "   ", " - ", " - ", "   ", " - ", " - "}};

int getRow(int index, int s)
{
  int mid = (2*s + 3)/2 + 1;
  if (index <= 1) return 0;
  if (index < (mid)) return 1;
  if (index == (mid)) return 2;
  if (index < (2*s + 3)) return 3;
  return 4;
}

int getColumn(int index, int s)
{
  if (index <= 1) return 0;
  if (index >= (s + 2)) return 2;
  return 1;
}

int main()
{
  string output = "";
  string number;
  int s;
  bool begin = true;

  output.reserve(500000);

  while(!cin.eof())
  {
    cin >> s >> number;
    cin.ignore();
    if (!begin || (begin = false)) output += "\n";
    if (!s) break;

    int limitRow = (2*s + 3);
    int row, col, length = number.size();
    for(int ii = 1; ii <= limitRow; ii++) {
      row = getRow(ii, s);

      for(int jj = 0; jj < length; jj++) {
        int digit = number[jj] - '0';

        for(int kk = 1; kk <= (s + 2); kk++) {
          col = getColumn(kk, s);
          output += digits[row][digit][col];
        }

        output += " ";
      }
      output.pop_back();
      output += "\n";
    }
  }

  printf("%s", output.c_str());

  return(0);
}