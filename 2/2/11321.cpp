/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 *
 * 11321 - Sort! Sort!! and Sort!!!
**/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
typedef unsigned char byte;
typedef unsigned long long ull;
typedef long long ll;

int main()
{
  string output = "";
  string line;

  output.reserve(500000);

  while(!cin.eof())
  {
    ll n, m;
    cin >> n >> m;

    output += to_string(n) + " " + to_string(m) + "\n";

    vector<ll> vi(n);
    if (!n && !m) break;

    for (ll ii = 0; ii < n; ii++)
    {
      cin >> vi[ii];
    }

    sort(vi.begin(), vi.end(), [m](ll &v1, ll &v2) {
      pair<ll, ll> mods = { v1 % m, v2 % m };
      pair<bool, bool> odd = { v1 & 1, v2 & 1 };

      return (mods.first != mods.second ?
              mods.first < mods.second :
              (odd.first && odd.second ?
               v1 > v2 :
               (!odd.first && !odd.second ?
                v1 < v2 :
                (odd.first && !odd.second))));
    });

    for (auto it = vi.begin(); it != vi.end(); it++)
    {
      output += to_string(*it) + "\n";
    }
  }

  printf("%s", output.c_str());

  return(0);
}