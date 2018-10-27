/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
**/

#include <cstdio>
#include <iostream>
#include <map>

using namespace std;

void populate(map<char, char> &m)
{
  m['B'] = m['F'] = m['P'] = m['V'] = '1';
  m['C'] = m['G'] = m['J'] = m['K'] = m['Q'] = m['S'] = m['X'] = m['Z'] = '2';
  m['D'] = m['T'] = '3';
  m['L'] = '4';
  m['M'] = m['N'] = '5';
  m['R'] ='6';
  m['A'] = m['E'] = m['I'] = m['O'] = m['U'] =
           m['H'] = m['W'] = m['Y'] = '*';
}

int main()
{
  string output = "";
  string line;
  map<char, char> m;

  populate(m);

  output.reserve(500000);

  while(getline(cin, line))
  {
    string code;
    char last = '*', next;

    for(char c : line)
    {
      next = m[c];

      if (next != '*')
      {
        if (last != next)
        {
          code += string(1, next);
        }
      }
      last = next;
    }

    output += code + "\n";
  }

  printf("%s", output.c_str());

  return(0);
}