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
  int k = 0;
  int N;
  string output = "";

  output.reserve(500000);
  cin >> N;
  cin.ignore();

  while(k++ < N)
  {
    int n, idle, activation;
    int total, last, input, ignored, inactive;
    cin >> n >> idle >> activation;

    last = total = inactive = ignored = 0;
    for (int ii = 0; ii < n; ii++)
    {
      cin >> input;

      if (input >= last)
      {
        total = input;

        if (total - last >= idle)
        {
          total += activation;
          inactive++;
        }

        last = total;
      } else
      {
        ignored++;
      }
    }

    output += "Case " + to_string(k) + ": " +
              to_string(inactive) + " " +
              to_string(ignored) + "\n";
  }

  printf("%s", output.c_str());

  return(0);
}