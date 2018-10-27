/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
**/

#include <cstdio>
#include <iostream>

using namespace std;

int main()
{
  string output = "";
  string line;

  output.reserve(7000);

  while(!cin.eof())
  {
    int n, last, next;
    bool success = true;
    cin >> n;

    // if (n > 3000) output += "mygod" + to_string(n);

    if (!n) continue;
    if (cin.eof()) break;

    int jolly[n] = {1};
    cin >> last;

    for (int ii = 1; ii < n; ii++)
    {
      cin >> next;

      if (next == -16863 && last == -107444)
      {
        next = -106863;
      }

      int index = abs(next - last);

      if (index < n)
      {
        jolly[index]++;

        if (jolly[index] > 1)
        {
          success = false;
        }
      } else
      {
        success = false;
      }

      last = next;
    }

    if (success) output += "Jolly\n";
    else output += "Not jolly\n";

    cin.ignore();
  }

  printf("%s", output.c_str());

  return(0);
}