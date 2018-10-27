/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * 11222 - Only I did it!
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
    vector<set<int>> unsolveds(3), solveds(3);

    for (int p = 0; p < 3; p++)
    {
      int n;
      cin >> n;

      for (int ii = 0; ii < n; ii++)
      {
        int problem;
        cin >> problem;
        solveds[p].insert(problem);
      }
    }

    for (int p = 0; p < 3; p++)
    {
      for (auto it = solveds[p].begin(); it != solveds[p].end(); it++)
      {
        if (!solveds[(p + 1) % 3].count(*it) &&
            !solveds[(p + 2) % 3].count(*it))
        {
          unsolveds[p].insert(*it);
        }
      }
    }

    uint major = 0;
    for (int p = 0; p < 3; p++)
    {
      major = max(major, (uint)unsolveds[p].size());
    }

    output += "Case #" + to_string(k) + ":\n";
    for (int p = 0; p < 3; p++)
    {
      if (major == unsolveds[p].size())
      {
        output += to_string(p+1) + " " + to_string(major);
        for (auto it = unsolveds[p].begin();
                  it != unsolveds[p].end();
                  it++)
        {
          output += " " + to_string(*it);
        }

        output += "\n";
      }
    }
  }

  printf("%s", output.c_str());

  return(0);
}