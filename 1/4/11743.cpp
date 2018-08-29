/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
**/

#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>

using namespace std;

int sumDigits(int value)
{
  int sum = 0;
  while (value)
  {
    sum += value % 10;
    value /= 10;
  }

  return sum;
}

int runLuhn(string card[])
{
  int sum1[8] = {0}, sum2 = 0, sum3 = 0, index;

  for(int ii = 0; ii < 4; ii++)
  {
    index = ii * 2;
    sum1[index]     = 2 * (card[ii][0] - '0');
    sum1[index + 1] = 2 * (card[ii][2] - '0');

    sum2 += sumDigits(sum1[index]);
    sum2 += sumDigits(sum1[index + 1]);

    sum3 += (card[ii][1] - '0');
    sum3 += (card[ii][3] - '0');
  }

  return sum2 + sum3;
}

int main()
{
  int k = 0;
  int N, invalid;
  string output = "";
  string creditCard[4];

  output.reserve(500000);
  cin >> N;
  cin.ignore();

  while(k++ < N)
  {
    for(int ii = 0; ii < 4; ii++) {
      cin >> creditCard[ii];
    }

    invalid = runLuhn(creditCard) % 10;

    if (!invalid)
    {
      output += "Valid\n";
    }
    else
    {
      output += "Invalid\n";
    }
  }

  printf("%s", output.c_str());

  return(0);
}