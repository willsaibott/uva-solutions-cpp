/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
**/

#include <cstdio>
#include <algorithm>
#include <iostream>
#include <string>
#include <cmath>

using namespace std;


template<uint n>
struct Factorial
{
  static const unsigned long value = n * Factorial<n-1>::value;
};

template<>
struct Factorial<0> {
  static const unsigned long value = 1;
};


long fat(ulong n)
{
  long value;
  switch (n)
  {
    case 1: value = Factorial<1>::value; break;
    case 2: value = Factorial<2>::value; break;
    case 3: value = Factorial<3>::value; break;
    case 4: value = Factorial<4>::value; break;
    case 5: value = Factorial<5>::value; break;
    case 6: value = Factorial<6>::value; break;
    case 7: value = Factorial<7>::value; break;
    case 8: value = Factorial<8>::value; break;
    case 9: value = Factorial<9>::value; break;
    case 10: value = Factorial<10>::value; break;
    case 11: value = Factorial<11>::value; break;
    case 12: value = Factorial<12>::value; break;
    case 13: value = Factorial<13>::value; break;
    case 14: value = Factorial<14>::value; break;
    case 15: value = Factorial<15>::value; break;
    case 16: value = Factorial<16>::value; break;
    case 17: value = Factorial<17>::value; break;
    case 18: value = Factorial<18>::value; break;
    case 19: value = Factorial<19>::value; break;
    case 20: value = Factorial<20>::value; break;
    default: value = Factorial<0>::value;
  }
  return value;
}

const int MAX_CHARS = 26;
int main()
{
  int k = 0;
  int N;
  string output = "";
  string line;

  output.reserve(500000);
  cin >> N;
  cin.ignore();

  while(k++ < N && !cin.eof())
  {
    long n, size;
    cin >> line >> n;

    size = line.size();

    // normalize the input
    long total = fat(size);
    if (n > total) n %= total;
    for (int ii = 0; ii < size; ii++)
    {
      sort(line.begin() + ii, line.end());
      if (!n) break; // end

      long numberOfPermutations = fat(size - ii - 1);
      int pos = ii + (n / numberOfPermutations);
      swap(line[ii], line[pos]);  // found the correct position
      n = n % numberOfPermutations; // calculate for the rest of the positions
    }

    output += line + "\n";
  }

  printf("%s", output.c_str());

  return(0);
}
