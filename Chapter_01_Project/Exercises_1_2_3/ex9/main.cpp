#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

char getDigit(char rest)
{
  return ((rest > 9)?
          (char('a' + rest)):
          (char('0' + rest)));
}

long long revertDigit(char digit)
{
  return ((digit >= '0' && digit <= '9')?
           ((long long)(digit - '0')):
           ((digit >= 'a' && digit <= 'z')?
            ((long long)(digit - 'a')):
            ((long long)(digit - 'A' + 10))));
}

long long parse(char *number, char* base)
{
  int size = strlen(number);
  long long n = 0;
  for (int i = size - 1; i >= 0; i--)
  {
    long long dig = revertDigit(number[i]);
    n += (dig) * pow(stoi(base), (size - 1) - i);
  }
  return n;
}

string parse(long long number, char* base)
{
  string str = "";
  long long n = number;
  long long b = stoi(base);
  long long r;
  while (n > 0)
  {
    r = n % b;
    n /= b;
    str = getDigit(r) + str;
  }
  return str;
}

int main(int argc, char *argv[])
{
  char number[10], base1[10], base2[10];
  while(scanf("%s %s %s", number, base1, base2) == 3)
  {
    long long n = parse(number, base1);
    printf("Input %s in base %s to base %s: %s\n", number, base1, base2, parse(n, base2).c_str());
  }
  return 0;
}
