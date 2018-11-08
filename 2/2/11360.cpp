/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
**/

#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

typedef unsigned char byte;

void transpose(vector<vector<byte>> &m)
{
  int n = m.size();
  vector<vector<byte>> newM = m;

  for (int ii = 0; ii < n; ii++)
  {
    for (int jj = 0; jj < n; jj++)
    {
      newM[jj][ii] = m[ii][jj];
    }
  }

  m = newM;
}

void interchangeRow(vector<vector<byte>> &m, int a, int b)
{
  vector<vector<byte>> newM = m;

  newM[b] = m[a];
  newM[a] = m[b];

  m = newM;
}

void interchangeColumns(vector<vector<byte>> &m, int a, int b)
{
  int n = m.size();
  vector<vector<byte>> newM = m;

  for (int ii = 0; ii < n; ii++)
  {
    newM[ii][b] = m[ii][a];
    newM[ii][a] = m[ii][b];
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
    int n;
    cin >> n;

    if (!n) break;

    vector<vector<byte>> m(n, vector<byte>(n));
    int increases = 0, decreases = 0;

    for (int ii = 0; ii < n; ii++)
    {
      for (int jj = 0; jj < n; jj++)
      {
        cin >> m[ii][jj];
      }
    }

    int operations;
    cin >> operations;

    for (int ii = 0; ii < operations; ii++)
    {
      int a, b;
      string op;
      cin >> op;

      if (op == "row")
      {
        cin >> a >> b;
        interchangeRow(m, --a, --b);
      } else if (op == "col")
      {
        cin >> a >> b;
        interchangeColumns(m, --a, --b);
      } else if (op == "inc")
      {
        increases++;
      } else if (op == "dec")
      {
        decreases++;
      } else {
        transpose(m);
      }
    }

    output += "Case #" + to_string(k) + "\n";

    for (int ii = 0; ii < n; ii++)
    {
      for (uint jj = 0; jj < (uint)n; jj++)
      {
        int value = ((m[ii][jj] - '0') + increases - decreases) % 10;
        if (value < 0) value += 10;
        output += to_string(value) + (jj != m.size()-1 ? "" : "\n");
      }
    }

    output+= "\n";
  }

  printf("%s", output.c_str());

  return(0);
}