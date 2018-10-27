/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * 10016 - Flip-Flop the Squarelotron
**/

#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

void upDown(vector<vector<int>> &m, int ring)
{
  vector<vector<int>> newM = m;
  int n = m.size();
  int last = n-(ring+1);

  for (int jj = ring; jj <= last; jj++)
  {
    newM[last][jj] = m[ring][jj];
    newM[ring][jj] = m[last][jj];
    newM[n-(jj+1)][last] = m[jj][last];
    newM[n-(jj+1)][ring] = m[jj][ring];
  }

  m = newM;
}

void leftRight(vector<vector<int>> &m, int ring)
{
  vector<vector<int>> newM = m;
  int n = m.size();
  int last = n-(ring+1);
  for (int jj = ring; jj <= last; jj++)
  {
    newM[jj][last] = m[jj][ring];
    newM[jj][ring] = m[jj][last];
    newM[last][n-(jj+1)] = m[last][jj];
    newM[ring][n-(jj+1)] = m[ring][jj];
  }
  m = newM;
}

void inverseDiag(vector<vector<int>> &m, int ring)
{
  vector<vector<int>> newM = m;
  int n = m.size();
  int last = n-(ring+1);

  for (int jj = ring; jj <= last; jj++)
  {
    newM[jj][last] = m[last][jj];
    newM[jj][ring] = m[ring][jj];
    newM[last][jj] = m[jj][last];
    newM[ring][jj] = m[jj][ring];
  }
  m = newM;
}

void mainDiag(vector<vector<int>> &m, int ring)
{
  vector<vector<int>> newM = m;
  int n = m.size();
  int last = n-(ring+1);
  for (int jj = ring; jj <= last; jj++)
  {
    int index = n-(jj+1);
    newM[index][ring] = m[last][jj];
    newM[index][last] = m[ring][jj];
    newM[ring][index] = m[jj][last];
    newM[last][index] = m[jj][ring];
  }
  m = newM;
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
    int n, t;
    cin >> n;
    if (!n) break;

    vector<vector<int>> m(n, vector<int>(n));

    for (int ii = 0; ii < n; ii++)
    {
      for (int jj = 0; jj < n; jj++)
      {
        cin >> m[ii][jj];
      }
    }

    for (int ring = 0; ring < (n+1)/2; ring++)
    {
      cin >> t;
      vector<int> moves(t);
      for (int ii = 0; ii < t; ii++)
      {
        cin >> moves[ii];
      }

      for (int ii = 0; ii < t; ii++)
      {
        switch (moves[ii])
        {
          case 1: upDown(m, ring); break;
          case 2: leftRight(m, ring); break;
          case 3: inverseDiag(m, ring); break;
          case 4: mainDiag(m, ring); break;
        }
      }
    }

    for (int ii = 0; ii < n; ii++)
    {
      for (int jj = 0; jj < n; jj++)
      {
        output += to_string(m[ii][jj]) + (jj != n-1 ? " " : "\n");
      }
    }
  }

  printf("%s", output.c_str());

  return(0);
}