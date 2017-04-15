#include <iostream>
#include <cmath>

using namespace std;

double round(double value, int n)
{
  int integer = (int)value;
  double decimal = value - (double)integer;
  double precMul = pow(10, n);
  decimal = (double)(((long)(decimal * precMul + 0.5f))/(precMul));
  return decimal + (double)integer;
}

int main(int argc, char *argv[])
{
  int n;
  double pi = M_PI;
  while (scanf("%d", &n) > 0)
  {
    printf("%.*lf\n", n, round(pi, n));
  }
}
