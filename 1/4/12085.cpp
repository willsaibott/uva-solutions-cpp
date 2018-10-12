/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
**/

#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

string diff(string &first, string &last)
{
  int ii = 0;

  for (ii = 0; ii < (int)first.size(); ii++)
  {
    if (first[ii] != last[ii]) break;
  }

  return last.substr(ii);
}

int main()
{
  int k = 0;
  string output = "";
  string line;
  bool begin = true;

  output.reserve(500000);

  while(!cin.eof())
  {
    int n, first = -1, last, sequence = -1;
    string fstr, lstr;

    cin >> n;

    if (!begin || (begin = false)) output += "\n";
    if (!n) break;

    output += "Case " + to_string(++k) + ":\n";

    for (int ii = 0; ii < n; ii++)
    {
      cin >> line;

      last = stoi(line);

      if (fstr.empty())
      {
        fstr = line;
        first = last;
        output += line;
      }

      if (last - first > 1)
      {
        output += (!sequence ? "" : "-" + diff(fstr, lstr)) + "\n";
        output += line;
        fstr = line;
        sequence = 0;
      } else
      {
        sequence++;
      }
      first = last;
      lstr = line;
    }

    output += (!sequence ? "" : "-" + diff(fstr, lstr)) + "\n";
  }

  printf("%s", output.c_str());

  return(0);
}