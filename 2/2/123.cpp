/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 *
 * 123 - Searching Quickly
**/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <sstream>

using namespace std;
typedef unsigned char byte;
typedef unsigned long long ull;

class KWIC
{
  int index;
  string keyword;
  string line;
  int pos;

  public:
    KWIC(int index, string keyword, string line, int pos)
      : index(index),
        keyword(keyword),
        line(line),
        pos(pos)
        { }

    string phrase() {
      string KEYWORD = keyword;
      transform(KEYWORD.begin(),
                KEYWORD.end(),
                KEYWORD.begin(),
                ::toupper);
      transform(line.begin(),
                line.end(),
                line.begin(),
                ::tolower);
      line.replace(line.find(keyword, pos),
                   keyword.length(),
                   KEYWORD);
      return line + "\n";
    }

    bool operator() (const KWIC &kwic) {
      return (kwic.keyword != this->keyword ?
              this->keyword < kwic.keyword :
              this->index < kwic.index);
    }

    bool operator < (const KWIC &kwic) {
      return (kwic.keyword != this->keyword ?
              this->keyword < kwic.keyword :
              this->index < kwic.index);
    }
};

int main()
{
  string output = "";
  string line;
  set<string> ignored;
  vector<KWIC> kwics;

  output.reserve(500000);

  while(getline(cin, line))
  {
    if (line == "::") break;
    ignored.insert(line);
  }

  int index = 0;
  while (getline(cin, line))
  {
    if (line == "") continue;
    stringstream ss(line);
    string keyword;
    int pos = 0;
    int last = 0;

    while (!ss.eof())
    {
      ss >> keyword;
      transform(keyword.begin(),
                keyword.end(),
                keyword.begin(),
                ::tolower);

      pos = ss.tellg();
      if (pos < 0)
      {
        pos = last;
      }
      last = pos;

      if (!ignored.count(keyword))
      {
        int position = max(0, (int)pos - (int)keyword.length());
        kwics.push_back(
          KWIC(index++, keyword,
               line, position));
      }
    }
  }

  sort(kwics.begin(), kwics.end());

  for (auto it = kwics.begin(); it != kwics.end(); it++)
  {
    output += it->phrase();
  }

  printf("%s", output.c_str());

  return(0);
}