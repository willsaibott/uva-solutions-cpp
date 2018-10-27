/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
**/

#include <cstdio>
#include <iostream>
#include <map>
#include <utility>

using namespace std;

void populateDialPad(map<char, char> &dial)
{
  dial['A'] = dial['B'] = dial['C'] = '2';
  dial['D'] = dial['E'] = dial['F'] = '3';
  dial['G'] = dial['H'] = dial['I'] = '4';
  dial['J'] = dial['K'] = dial['L'] = '5';
  dial['M'] = dial['N'] = dial['O'] = '6';
  dial['P'] = dial['R'] = dial['S'] = '7';
  dial['T'] = dial['U'] = dial['V'] = '8';
  dial['W'] = dial['X'] = dial['Y'] = '9';
}

string convert(map<char, char> &dial, string raw)
{
  string number(8, '0');
  int index = 0;
  number[3] = '-';

  for (char c : raw)
  {
    if (c != '-')
    {
      number[index] = dial.count(c) ? dial[c] : c;
      if (index == 2) index += 2;
      else index++;
    }
  }

  return number;
}

int main()
{
  int k = 0;
  int N;
  string output = "";
  string line;
  map<char, char> dial;
  bool begin = true;

  output.reserve(500000);
  cin >> N;
  cin.ignore();

  populateDialPad(dial);

  while(k++ < N && !cin.eof())
  {
    map<string, int> numbers;

    int n;
    cin >> n;
    if (!begin || (begin = false)) output += "\n";

    for (int ii = 0; ii < n; ii++)
    {
      string raw;
      cin >> raw;
      numbers[convert(dial, raw)]++;
    }

    int duplicates = 0;
    for (auto entry = numbers.begin();
              entry != numbers.end();
              entry++)
    {
      if (entry->second > 1)
      {
        duplicates++;
        output += entry->first + " " +
                  to_string(entry->second) + "\n";
      }
    }

    if (!duplicates)
    {
      output += "No duplicates.\n";
    }
  }

  printf("%s", output.c_str());

  return(0);
}