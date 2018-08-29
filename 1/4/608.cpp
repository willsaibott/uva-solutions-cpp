/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
**/

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <map>

using namespace std;

typedef enum { undefined, light, heavy } state;

void check(string &weight, string &left, string &right,
           map<char, state> &suspects)
{
  if (weight == "even")
  {
    for(uint jj = 0; jj < left.size(); jj++) {
      suspects.erase(left[jj]);
      suspects.erase(right[jj]);
    }
  }
  else
  {
    map<char, state> current;
    for(uint jj = 0 ; jj < left.size(); jj++) {
      char l = left[jj], r = right[jj];

      if (weight == "up")
      {
        if (suspects.count(l))
        {
          if (suspects[l] == state::light)
          {
            suspects.erase(l);
          }
          else{
            suspects[l] = state::heavy;
            current[l] = state::heavy;
          }
        }

        if (suspects.count(r))
        {
          if (suspects[r] == state::heavy)
          {
            suspects.erase(r);
          }
          else
          {
            suspects[r] = state::light;
            current[r] = state::light;
          }
        }
      }
      else
      {
        if (suspects.count(l))
        {
          if (suspects[l] == state::heavy)
          {
            suspects.erase(l);
          }
          else
          {
            suspects[l] = state::light;
            current[l] = state::light;
          }
        }

        if (suspects.count(r))
        {
          if (suspects[r] == state::light)
          {
            suspects.erase(r);
          } else
          {
            suspects[r] = state::heavy;
            current[r] = state::heavy;
          }
        }
      }
    }

    if (current.size() == 1)
    {
      suspects.clear();
      suspects[current.begin()->first] = current.begin()->second;
    }
    else
    {
      for (auto it = suspects.begin(); it != suspects.end(); it++)
      {
        if ((it)->second == state::undefined ||
            !current.count(it->first))
        {
          suspects.erase((it)->first);
        }
      }
    }
  }
}

void populateSuspects(map<char, state> &m)
{
  for(char ii = 'A'; ii <= 'L'; ii++) {
    m[ii] = state::undefined;
  }
}

int main()
{
  int k = 0;
  int N;
  string output = "";
  cin >> N;
  cin.ignore();
  string left[3], right[3], weight[3];

  output.reserve(70*40);

  while(k++ < N)
  {
    map<char, state> suspects;

    populateSuspects(suspects);

    for(int ii = 0; ii < 3; ii++) {
      cin >> left[ii] >> right[ii] >> weight[ii];
      cin.ignore();
    }

    int ii = 0;
    while (suspects.size() > 1)
    {
      check(weight[ii], left[ii], right[ii], suspects);
      ii = (ii + 1) % 3;
    }

    bool heavy = (suspects.begin()->second == state::heavy);
    char suspect = suspects.begin()->first;

    output += string(1, suspect) + " is the counterfeit coin and it is ";
    output += (heavy ? "heavy.\n" : "light.\n");
  }
  printf("%s", output.c_str());
  return(0);
}