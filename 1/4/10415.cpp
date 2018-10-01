/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
**/

#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;

int notes [] = {
  0b0000000111,  // A
  0b0000000011,  // B
  0b0000000100,  // C
  0b0111001111,  // D
  0b0011001111,  // E
  0b0001001111,  // F
  0b0000001111,  // G
  0b0000000110,  // a
  0b0000000010,  // b
  0b1111001110,  // c
  0b0111001110,  // d
  0b0011001110,  // e
  0b0001001110,  // f
  0b0000001110,  // g
};

void calculatePresses(const string &line, int *count)
{
  int last = 0;
  for(uint ii = 0; ii < line.size(); ii++) {
    char c = line[ii];
    int note, changes, jj = 0;

    if (c >= 'a')
    {
      note = notes[c - 'a' + 7];
    } else
    {
      note = notes[c - 'A'];
    }

    changes = last ^ note;

    while (changes)
    {
      count[jj++] += (changes & 1) && !(last & 1);
      changes >>= 1;
      last >>= 1;
    }

    last = note;
  }
}

int main()
{
  int k = 0;
  int N;
  int count[10] = {0};
  string output = "";
  string line;

  output.reserve(500000);
  cin >> N;
  cin.ignore();

  while(k++ < N)
  {
    getline(cin, line);

    calculatePresses(line, count);

    for(int ii = 0; ii < 9; ii++) {
      output += to_string(count[ii]) + " ";
    }

    output += to_string(count[9]) + "\n";
    memset(count, 0, sizeof count);
  }

  printf("%s", output.c_str());

  return(0);
}