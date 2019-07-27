/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 *
 * 11988 - Broken Keyboard (a.k.a. Beiju Text)
**/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <list>

using namespace std;
typedef unsigned char byte;
typedef unsigned long long ull;
typedef long long ll;

int main()
{
  string output = "";
  string line;

  output.reserve(500000);

  while (getline(cin, line))
  {
    list<char> out;
    bool end = true;
    list<char>::iterator it;

    for (char c : line)
    {

      if (c == '[' || c == ']')
      {
        it = out.begin();
        end = c == ']';
      }
      else if (end)
      {
        out.push_back(c);
      }
      else
      {
        out.insert(it, c);
      }
    }

    for (char c : out)
    {
      output += string(1, c);
    }

    output += "\n";
  }

  printf("%s", output.c_str());

  return(0);
}