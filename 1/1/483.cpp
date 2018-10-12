/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
**/

#include <cstdio>
#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main()
{
  string output = "";
  string line;

  output.reserve(500000);

  while(getline(cin, line))
  {
    string word;
    stringstream ss(line);

    for (int ii = 0; ii < (int)line.size(); ii++)
    {
      if (line[ii] == ' ')
      {
        output += " ";
      } else
      {
        ss >> word;
        reverse(word.begin(), word.end());
        output += word;
        ii += word.size();
        if (!ss.eof())
          output += " ";
      }
    }

    output += "\n";
  }

  printf("%s", output.c_str());

  return(0);
}