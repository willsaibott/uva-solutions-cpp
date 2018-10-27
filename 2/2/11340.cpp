/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * 11340	Newspaper
**/

#include <cstdio>
#include <iostream>
// #include <map>

using namespace std;

typedef unsigned long long ull;
typedef unsigned char byte;
int main()
{
  int k = 0;
  int N;
  string output = "";
  string line;
  char s[30];

  output.reserve(500000);
  cin >> N;
  cin.ignore();

  while(k++ < N && !cin.eof())
  {
    ull n, lines, value = 0;
    long long m[256] = {0};

    cin >> n;

    for (ull ii = 0; ii < n; ii++)
    {
      byte c;
      long long cents;
      cin >> c >> cents;

      m[(int)c] = cents;
    }

    cin >> lines;
    cin.ignore();

    for (ull ii = 0; ii < lines; ii++)
    {
      byte c;
      while((c = getchar()) != '\n')
        value += m[(int)c];
    }

    sprintf(s, "%.2f$\n", (value / 100.0));
    output += s;
  }

  printf("%s", output.c_str());

  return(0);
}