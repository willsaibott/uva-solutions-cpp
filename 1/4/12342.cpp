/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
**/

#include <cstdio>
#include <iostream>
#include <climits>
#include <cmath>

using namespace std;

typedef long long ll;

const ll intervals[] = {
  180000,
  300000,
  400000,
  300000,
  LLONG_MAX};

const double taxes[] = {
  0.10,
  0.15,
  0.20,
  0.25};

const ll MIN_TAX = 2000;

ll calculateTax(ll salary)
{
  ll value;
  double taxd = 0.0;

  if (salary > intervals[0])
  {
    salary -= intervals[0];

    for(int ii = 1; ii <= 4 && (salary > 0); ii++) {
      value = min(salary, intervals[ii]);
      taxd += taxes[ii - 1] * (value);
      salary -= intervals[ii];
    }

    taxd = taxd > MIN_TAX ? ceil(taxd) : MIN_TAX;
  }

  return (ll) taxd;
}

int main()
{
  int k = 0;
  int N;
  string output = "";
  string line;
  ll salary;

  output.reserve(500000);
  cin >> N;
  cin.ignore();

  while(k++ < N)
  {
    cin >> salary;
    output += "Case " + to_string(k) + ": " +
              to_string(calculateTax(salary)) + "\n";
  }

  printf("%s", output.c_str());

  return(0);
}