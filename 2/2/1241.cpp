/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 *
 * 1241 - Jollybee Tournament
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
    int n, m;
    cin >> n >> m;

    int size = pow(2, n);
    int WOs = 0;
    vector<bool> players(size, true);

    for (int ii = 0; ii < m; ii++)
    {
      int index;
      cin >> index;
      players[index-1] = false;
    }

    while (size > 1)
    {
      int newSize = size/2;
      vector<bool> nextPlayers(newSize);

      for (int ii = 0; ii < newSize; ii++)
      {
        int index1 = 2*ii;
        int index2 = 2*ii + 1;

        nextPlayers[ii] = players[index1] || players[index2];
        WOs += (players[index1] && !players[index2]) ||
               (!players[index1] && players[index2]);
      }

      size = newSize;
      players = nextPlayers;
    }

    output += to_string(WOs) + "\n";
  }

  printf("%s", output.c_str());

  return(0);
}