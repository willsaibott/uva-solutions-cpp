/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
**/

#include <cstdio>
#include <iostream>
// #include <map>
#include <string>

using namespace std;

// void populateMap(map<char, int> &m)
// {
//   m['B'] =  m['P'] =  m['F'] =  m['V'] = 1;
//   m['C'] =  m['S'] =  m['K'] =  m['G'] =  m['J'] =  m['Q'] =  m['X'] =  m['Z'] = 2;
//   m['D'] =  m['T'] = 3;
//   m['L'] = 4;
//   m['M'] =  m['N'] = 5;
//   m['R'] = 6;
//   m['A'] =  m['E'] =  m['I'] =  m['O'] =  m['U'] =  m['Y'] =  m['W'] =  m['H'] = 0;
// }

inline int getCode(char c)
{
  switch (c)
  {
    case 'B':
    case 'P':
    case 'F':
    case 'V':
      return 1;
    case 'C':
    case 'S':
    case 'K':
    case 'G':
    case 'J':
    case 'Q':
    case 'X':
    case 'Z':
      return 2;
    case 'D':
    case 'T':
      return 3;
    case 'L':
      return 4;
    case 'M':
    case 'N':
      return 5;
    case 'R':
      return 6;
    default: return 0;
  }
}

const int MAX_CHARS = 4;

int main()
{
  // map<char, int> m;
  char f[50];
  string output = "";
  char format[] = "%9s%-25s%s\n";

  output.reserve(500000);
  // populateMap(m);

  sprintf(f, format, " ", "NAME", "SOUNDEX CODE");
  output += f;

  while(!cin.eof())
  {
    string name;
    string code;
    int last;

    cin >> name;

    if (name == "") break;

    last = getCode(name[0]);
    // last = m[name[0]];
    code += string(1, name[0]);
    for (int ii = 1; ii < (int)name.size() && code.size() < MAX_CHARS; ii++)
    {
      int c = getCode(name[ii]);
      if (c && c != last)
      {
        code += to_string(c);
      }
      last = c;
    }

    if (code.size() < MAX_CHARS)
      code += string(MAX_CHARS - code.size(), '0');

    sprintf(f, format, " ", name.c_str(), code.c_str());
    output += f;
  }

  sprintf(f, "%19s%s", " ", "END OF OUTPUT\n");
  output += f;

  printf("%s", output.c_str());

  return(0);
}