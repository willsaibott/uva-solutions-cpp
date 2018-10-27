/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
**/

#include <cstdio>
#include <iostream>
#include <vector>
#include <set>

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
    int days, nHartals;
    set<int> parties;
    cin >> days >> nHartals;

    vector<int> hartals(nHartals);

    for (auto h = hartals.begin();
              h != hartals.end();
              h++)
    {
      cin >> *h;

      for (int ii = *h; ii <= days; ii+= *h)
      {
        int rest = (ii) % 7;
        if (rest != 6 && rest)
        {
          parties.insert(ii);
        }
      }
    }

    output += to_string(parties.size()) + "\n";
  }

  printf("%s", output.c_str());

  return(0);
}