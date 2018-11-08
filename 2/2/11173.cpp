/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 *
 * 11173 - Grey Codes
**/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;
typedef unsigned char byte;
typedef unsigned long long ull;
typedef long long ll;

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
    ull n, position;
    cin >> n >> position;

    ull greyCode = position ^ (position >> 1);

    output += to_string(greyCode) + "\n";
  }

  printf("%s", output.c_str());

  return(0);
}