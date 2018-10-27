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

  while (true)
  {
    int rows, minDiff = 30, total = 0;
    cin >> rows;
    cin.ignore();

    if (!rows) break;

    vector<int> counter(rows);

    for (int ii = 0; ii < rows; ii++)
    {
      int count = 0;
      getline(cin, line);

      for (char c : line)
        if (c == ' ') count++;

      counter[ii] = count;
      minDiff = min(count, minDiff);
    }

    for (auto it = counter.begin(); it != counter.end(); it++)
    {
      total += *it - minDiff;
    }

    output += to_string(total) + "\n";
  }

  printf("%s", output.c_str());

  return(0);
}