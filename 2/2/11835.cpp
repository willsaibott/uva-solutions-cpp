/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
**/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>


using namespace std;
typedef unsigned char byte;
typedef unsigned long long ull;

typedef struct MY_STRUCT {
  int index;
  int points;
  vector<int> positions;
} pilot;

int main()
{
  string output = "";
  string line;

  output.reserve(500000);

  while(!cin.eof())
  {
    int races, pilots;
    cin >> races >> pilots;

    if (!races && !pilots) break;
    vector<pilot> p(pilots);

    for (int ii = 0; ii < pilots; ii++)
    {
      p[ii] = {ii+1, 0, vector<int>(races)};
    }

    for (int race = 0; race < races; race++)
    {
      for (int pi = 0; pi < pilots; pi++)
      {
        cin >> p[pi].positions[race];
      }
    }

    int systems;
    cin >> systems;
    vector<vector<int>> sys(systems);

    for (int ss = 0; ss < systems; ss++)
    {
      vector<int> pontuation(pilots);
      int nPoints;
      cin >> nPoints;

      for (int ii = 0; ii < nPoints; ii++)
      {
        cin >> pontuation[ii];
      }

      sys[ss] = pontuation;

      for (int pi = 0; pi < pilots; pi++)
      {
        p[pi].points = 0;
        for (int pos : p[pi].positions)
        {
          p[pi].points += pontuation[pos-1];
        }
      }

      sort(p.begin(), p.end(), [](pilot &p1, pilot &p2) {
        return (p1.points != p2.points ?
                p1.points > p2.points :
                p1.index < p2.index);
      });

      int top = p[0].points;
      for (int pi = 0; pi < pilots; pi++) {
        if (p[pi].points < top) break;

        output += to_string(p[pi].index) + " ";
      }

      output[output.size()-1] = '\n';
    }
  }

  printf("%s", output.c_str());

  return(0);
}