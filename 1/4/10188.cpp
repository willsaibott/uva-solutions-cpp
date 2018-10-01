/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
**/

#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

#define ACCEPTED 0
#define PRESENTATION_ERROR 1
#define WRONG_ANSWER 2

void readInput(vector<string> &lines,
               vector<char> &digits,
               int n)
{
  string line;
  for(int ii = 0; ii < n; ii++) {
    getline(cin, line);
    lines.push_back(line);

    for(uint jj = 0; jj < line.size(); jj++) {
      if (isdigit(line[jj]))
      {
        digits.push_back(line[jj]);
      }
    }
  }
}

int main()
{
  int k = 0;
  string output = "";
  string line;
  int n, m;

  output.reserve(500000);

  while(!cin.eof())
  {
    cin >> n;
    cin.ignore();

    vector<char> digits1, digits2;
    vector<string> lines1, lines2;
    int result = ACCEPTED;

    if (!n) break;

    readInput(lines1, digits1, n);

    cin >> m;
    cin.ignore();

    readInput(lines2, digits2, m);

    size_t size = max(n, m);
    size_t sizeMin = min(n, m);

    if (n != m) result = PRESENTATION_ERROR;

    for(uint ii = 0; ii < size && result == ACCEPTED; ii++) {
      if (ii < sizeMin)
      {
        if (result == ACCEPTED && lines1[ii] != lines2[ii])
        {
          result = PRESENTATION_ERROR;
          break;
        }
      }
    }

    if (result == PRESENTATION_ERROR)
    {
      if (digits1.size() != digits2.size())
      {
        result = WRONG_ANSWER;
      } else
      {
        for ( auto it1 = digits1.begin(), it2 = digits2.begin();
                   it1 != digits1.end() && it2 != digits2.end();
                   it1++, it2++)
        {
          if (*it1 != *it2)
          {
            result = WRONG_ANSWER;
            break;
          }
        }
      }
    }

    output += "Run #" + to_string(++k) + ": ";
    switch(result)
    {
      case ACCEPTED:
        output += "Accepted\n";
        break;
      case PRESENTATION_ERROR:
        output += "Presentation Error\n";
        break;
      case WRONG_ANSWER:
        output += "Wrong Answer\n";
        break;
    }
  }

  printf("%s", output.c_str());

  return(0);
}