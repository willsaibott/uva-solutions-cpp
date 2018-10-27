/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
**/

#include <cstdio>
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

void moveOver(vector<vector<int>> &world,
              vector<int> &positions,
              int a,
              int b)
{
  world[b].push_back(a);
  if (world[positions[a]].back() != a)
  {
    for (auto it = world[positions[a]].begin();
              it != world[positions[a]].end();
              it++)
    {
      if (*it == a)
      {
        world[positions[a]].erase(it);
        break;
      }
    }
  } else
  {
    world[positions[a]].pop_back();
  }
  positions[a] = b;
}

int main()
{
  string output = "";
  string operation, over;

  output.reserve(500000);

  int n;
  cin >> n;
  vector<vector<int>> world(n);
  vector<int> positions(25);
  int a, b;

  for (int ii = 0; ii < n; ii++)
  {
    positions[ii] = ii;
    world[ii].push_back(ii);
  }

  while (!cin.eof())
  {
    cin >> operation >> a >> over >> b;

    if (operation == "quit") break;

    if (a==b || a >= n || b >= n || a < 0 || b < 0 ||
        positions[a] == positions[b]) continue;

    if (operation == "move")
    {
      if (over == "over")
      {
        for (int ii = world[positions[a]].size()-1;
                 ii >= 0 && world[positions[a]][ii] != a;
                 ii--)
        {
          int value = world[positions[a]][ii];
          moveOver(world, positions, value, value);
        }

        moveOver(world, positions, a, positions[b]);
      } else
      {
        for (int ii = world[positions[b]].size()-1;
                 ii >= 0 && world[positions[b]][ii] != b;
                 ii--)
        {
          int value = world[positions[b]][ii];
          moveOver(world, positions, value, value);
        }

        for (int ii = world[positions[a]].size()-1;
                 ii >= 0 && world[positions[a]][ii] != a;
                 ii--)
        {
          int value = world[positions[a]][ii];
          moveOver(world, positions, value, value);
        }

        moveOver(world, positions, a, positions[b]);
      }
    } else
    {
      if (over == "over")
      {
        stack<int> temp;
        int index = world[positions[a]].size() - 1;
        while (world[positions[a]][index] != a &&
               index >= 0)
        {
          temp.push(world[positions[a]][index]);
          index--;
        }

        temp.push(a);

        while (temp.size())
        {
          moveOver(world, positions, temp.top(), positions[b]);
          temp.pop();
        }
      } else
      {
        stack<int> temp;

        int index = world[positions[a]].size() - 1;
        while (world[positions[a]][index] != a &&
               index >= 0)
        {
          temp.push(world[positions[a]][index]);
          index--;
        }

        temp.push(a);

        for (int ii = world[positions[b]].size()-1;
                 ii >= 0 && world[positions[b]][ii] != b;
                 ii--)
        {
          int value = world[positions[b]][ii];
          moveOver(world, positions, value, value);
        }

        while (temp.size())
        {
          moveOver(world, positions, temp.top(), positions[b]);
          temp.pop();
        }
      }
    }
  }

  for (int ii = 0; ii < n; ii++)
  {
    output += to_string(ii) + ":";
    for (auto it = world[ii].begin();
              it != world[ii].end();
              it++)
    {
      output += " " + to_string(*it);
    }

    output += "\n";
  }
  printf("%s", output.c_str());

  return(0);
}