/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 *
 * 11349 - Symmetric Matrix
**/

#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

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
    int n;
    cin >> line >> line >> n;
    if (!n) break;

    vector<vector<ll>> m(n, vector<ll>(n));
    bool symmetric = true;

    for (int ii = 0; ii < n; ii++)
    {
      for (int jj = 0; jj < n; jj++)
      {
        cin >> m[ii][jj];
        symmetric = symmetric && (m[ii][jj] >= 0);
      }
    }

    for (int ii = 0; ii < n && symmetric; ii++)
    {
      for (int jj = 0; jj < n && symmetric; jj++)
      {
        symmetric = (m[n-(ii+1)][n-(jj+1)] == m[ii][jj]);
      }
    }

    output += "Test #" + to_string(k) + ": " +
              (symmetric ? "Symmetric.\n" : "Non-symmetric.\n");

  }

  printf("%s", output.c_str());

  return(0);
}