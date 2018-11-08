/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 *
 * 10880 - Colin and Ryan
**/

#include <cstdio>
#include <iostream>
#include <set>
#include <cmath>

using namespace std;
typedef unsigned char byte;
typedef unsigned long long ull;
typedef long long ll;

string getDivisors(ll c, ll r)
{
  ll q = c-r;
  if (!(q)) return " 0\n";
  if (q<0) return "\n";

  set<ll> divisors;
  ll i = 1;
  while (i <= sqrt(q))
  {
    if (q%i==0)
    {
      if (i > r) divisors.insert(i);
      if (q / i > r) divisors.insert(q / i);
    }

    i++;
  }

  if (!divisors.size()) return "\n";

  string str = " ";
  for (auto divisor = divisors.begin(); divisor != divisors.end(); divisor++)
  {
    str += to_string(*divisor) + (next(divisor) != divisors.end() ? " " : "\n");
  }

  return str;
}

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
    ll c, r;
    cin >> c >> r;

    if (cin.fail()) break;

    output += "Case #" + to_string(k) + ":" + getDivisors(c, r);
  }

  printf("%s", output.c_str());

  return(0);
}