/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * 10855 - Rotated square
**/

#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

vector<string> rotate90(vector<string> &array)
{
  vector<string> result = array;
  int n = array.size();

  for (int ii = 0; ii < n; ii++)
  {
    for (int jj = 0; jj < n; jj++)
    {
      result[n-(jj+1)][ii] = array[ii][jj];
    }
  }

  return result;
}

vector<string> rotate180(vector<string> &array)
{
  vector<string> result = array;
  int n = array.size();

  for (int ii = 0; ii < n; ii++)
  {
    for (int jj = 0; jj < n; jj++)
    {
      result[n-(ii+1)][n-(jj+1)] = array[ii][jj];
    }
  }

  return result;
}

vector<string> rotate270(vector<string> &array)
{
  vector<string> result = array;
  int n = array.size();

  for (int ii = 0; ii < n; ii++)
  {
    for (int jj = 0; jj < n; jj++)
    {
      result[jj][n-(ii+1)] = array[ii][jj];
    }
  }

  return result;
}

int count(vector<string> big, vector<string> &small)
{
  int counter=0;
  int n = small.size();
  int N = big.size();

  for (int ii = 0; ii <= N-n; ii++)
  {
    for (int jj = 0; jj <= N-n; jj++)
    {
      bool equal = true;
      for (int k = 0; k < n && equal; k++)
      {
        string sub = big[ii + k].substr(jj, n);
        equal = (sub == small[k]);
      }
      counter += equal;
    }
  }
  return counter;
}

int main()
{
  string output = "";
  string line;

  output.reserve(500000);

  while(!cin.eof())
  {
    int N, n;
    cin >> N >> n;

    if (!N && !n) break;
    vector<string> big(N), small(n);

    for (int ii = 0; ii < N; ii++)
    {
      cin >> big[ii];
    }
    for (int ii = 0; ii < n; ii++)
    {
      cin >> small[ii];
    }

    output += to_string(count(big, small)) + " " +
              to_string(count(rotate90(big), small)) + " " +
              to_string(count(rotate180(big), small)) + " " +
              to_string(count(rotate270(big), small)) + "\n";
  }

  printf("%s", output.c_str());

  return(0);
}