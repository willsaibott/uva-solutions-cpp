/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 *
 * 11588 - Image Coding
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
  int k = 0;
  int N;
  string output = "";
  string line;

  output.reserve(500000);
  cin >> N;
  cin.ignore();

  while(k++ < N && !cin.eof())
  {
    int rows, columns, MBytes, NBytes;
    cin >> rows >> columns >> MBytes >> NBytes;

    vector<string> image(rows);

    int freq[30] = { 0 };

    for (int ii = 0; ii < rows; ii++)
    {
      cin >> image[ii];

      for (char c : image[ii])
        freq[c-'A']++;
    }

    int important = 0;

    for (int ii = 0; ii < 30; ii++)
    {
      important = max(important, freq[ii]);
    }

    int bytes = 0;

    for (int ii = 0; ii < 30; ii++)
    {
      bytes += (freq[ii] == important ?
                freq[ii] * MBytes:
                freq[ii] * NBytes);
    }

    output += "Case " + to_string(k) +
              ": " + to_string(bytes) + "\n";
  }

  printf("%s", output.c_str());

  return(0);
}