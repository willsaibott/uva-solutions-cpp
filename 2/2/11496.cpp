/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
**/

#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
  string output = "";
  string line;

  output.reserve(500000);

  while(!cin.eof())
  {
    int n, last = 0, next = 0, peaks = 0;
    bool isIncreasing = true;
    cin >> n;
    if (!n) break;

    vector<int> wave(n);

    for (int ii = 0; ii < n; ii++)
    {
      cin >> wave[ii];
    }

    isIncreasing = wave.front() > wave.back();
    last = wave.back();

    for (int ii = 0; ii < n; ii++)
    {
      next = wave[ii];
      if ((isIncreasing && next < last) ||
          (!isIncreasing && next > last))
      {
        peaks++;
        isIncreasing = !isIncreasing;
      }

      last = next;
    }

    next = wave.front();
    peaks += (isIncreasing && next < last) || (!isIncreasing && next > last);
    output += to_string(peaks) + "\n";
  }

  printf("%s", output.c_str());

  return(0);
}