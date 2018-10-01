/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
**/

#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;
typedef unsigned int uint;

char* simulate(uint dna[10], int day)
{
  static char output[41];
  static uint *last = new uint[42], *next = new uint[42];
  const char m[] = {' ', '.', 'x', 'W'};
  uint * temp;

  output[40] = '\n';

  if (day == 0)
  {
    fill(last, last + 42, 0);
    fill(next, next + 42, 0);
    last[20] = 1;
    next[0] = next[41] = 0;
  }

  for(int ii = 1; ii <= 40; ii++) {
    next[ii] = dna[last[ii - 1] + last[ii] + last[ii + 1]];
    output[ii - 1] = m[last[ii]];
  }

  temp = next;
  next = last;
  last = temp;

  return output;
}

int main()
{
  int k = 0;
  int N, DAYS = 50;
  string output = "";
  string line;
  bool begin = true;
  uint dna[10];

  output.reserve(500000);
  cin >> N;
  cin.ignore();

  while(k++ < N)
  {
    cin.ignore();

    for(int ii = 0; ii < 10; ii++) {
      cin >> dna[ii];
    }

    if (!begin || (begin = false)) output += "\n";

    for(int ii = 0; ii < DAYS; ii++) {
      output += simulate(dna, ii);
    }
  }

  printf("%s", output.c_str());

  return(0);
}