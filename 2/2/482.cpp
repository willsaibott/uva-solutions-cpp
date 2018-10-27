/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * 482 - Permutation Arrays
**/

#include <cstdio>
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

int main()
{
  int k = 0;
  int N;
  string output = "";
  string line;
  bool begin = true;

  output.reserve(500000);
  cin >> N;
  cin.ignore();

  while(k++ < N && !cin.eof())
  {
    if (!begin || (begin = false)) output += "\n";
    cin.ignore(); // skip blank line
    getline(cin, line);

    stringstream ss(line);
    vector<int> indexes;
    vector<string> elements;

    indexes.reserve(10);

    while (!ss.eof())
    {
      int index;
      ss >> index;
      indexes.push_back(index);
    }

    getline(cin, line);
    ss = stringstream(line);

    while (!ss.eof())
    {
      string word;
      ss >> word;
      elements.push_back(word);
    }

    vector<string> perm(elements.size());

    for (int ii = 0; ii < (int)elements.size(); ii++)
    {
      perm[indexes[ii] - 1] = elements[ii];
    }

    for (auto it = perm.begin(); it != perm.end(); it++)
    {
      output += *it + "\n";
    }
  }

  printf("%s", output.c_str());

  return(0);
}