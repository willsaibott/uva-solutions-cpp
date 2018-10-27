/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * 434 - Matty's Blocks
**/

#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

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
    int n, minBlocks = 0, extras = 0,
        fronts = 0, rights = 0, total = 0;

    cin >> n;

    vector<int> front(n), right(n), fsum(10), rsum(10);
    vector<vector<int>> fTable(n),
                        rTable(n, vector<int>(n)),
                        table(n, vector<int>(n));


    for (int ii = 0; ii < n; ii++)
    {
      cin >> front[ii];
      fronts += front[ii];
    }
    for (int ii = 0; ii < n; ii++)
    {
      cin >> right[ii];
      rights += right[ii];
    }

    // minBlocks += max(fronts, rights);

    for (int ii = 0; ii < n; ii++)
    {
      fTable[ii] = front;

      for (int jj = 0; jj < n; jj++)
      {
        rTable[ii][jj] = right[ii];
      }
    }

    for (int ii = 0; ii < n; ii++)
    {
      for (int jj = 0; jj < n; jj++)
      {
        table[ii][jj] = min(fTable[ii][jj], rTable[ii][jj]);
        total += table[ii][jj];
      }
    }

    for (int ii = 0; ii < n; ii++)
    {
      fsum[front[ii]]++;
      rsum[right[ii]]++;
    }

    for (int ii = 0; ii < 10; ii++)
    {
      minBlocks += ii * (max(fsum[ii], rsum[ii]));
    }

    extras = total - minBlocks;

    output += "Matty needs at least " + to_string(minBlocks) +
              " blocks, and can add at most " + to_string(extras) +
              " extra blocks.\n";
  }

  printf("%s", output.c_str());

  return(0);
}