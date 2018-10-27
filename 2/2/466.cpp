/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * 466 - Mirror, Mirror
**/

#include <cstdio>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<string> rotate90(vector<string> &original)
{
  vector<string> rot = original;
  int n = original.size();
  for (int ii = 0; ii < n; ii++)
  {
    for (int jj = 0; jj < n; jj++)
    {
      rot[jj][n - (ii+1)] = original[ii][jj];
    }
  }
  return rot;
}

vector<string> rotate180(vector<string> &original)
{
  vector<string> rot = original;
  int n = original.size();

  for (int ii = n-1; ii >= 0; ii--)
  {
    for (int jj = n-1; jj >= 0; jj--)
    {
      rot[ii][jj] = original[n-(ii+1)][n-(jj+1)];
    }
  }
  return rot;
}

vector<string> rotate270(vector<string> &original)
{
  vector<string> rot = original;
  int n = original.size();

  for (int ii = n-1; ii >= 0; ii--)
  {
    for (int jj = n-1; jj >= 0; jj--)
    {
      rot[n-(jj+1)][ii] = original[ii][jj];
    }
  }
  return rot;
}

vector<string> verticalReflection(vector<string> &original)
{
  vector<string> rot = original;
  reverse(rot.begin(), rot.end());
  return rot;
}

bool isEqual(vector<string> &s1, vector<string> s2)
{
  bool equal = s1.size() == s2.size();

  for (int ii = 0; ii < (int)s1.size() && equal; ii++)
  {
    equal = s1[ii] == s2[ii];
  }
  return equal;
}

int main()
{
  int k = 0;
  string output = "";
  string line;

  output.reserve(500000);

  while(!cin.eof())
  {
    int n;
    cin >> n;

    if (!n || cin.eof()) break;

    vector<string> p1(n), p2(n), v(n);

    for (int ii = 0; ii < n; ii++)
    {
      cin >> p1[ii] >> p2[ii];
    }

    output += "Pattern " + to_string(++k) + " was ";
    if (isEqual(p2, p1))
    {
      output += "preserved.\n";
    }
    else if (isEqual(p2, rotate90(p1)))
    {
      output += "rotated 90 degrees.\n";
    } else if (isEqual(p2, rotate180(p1)))
    {
      output += "rotated 180 degrees.\n";
    } else if (isEqual(p2, rotate270(p1)))
    {
      output += "rotated 270 degrees.\n";
    } else if (isEqual(p2, v = verticalReflection(p1)))
    {
      output += "reflected vertically.\n";
    } else {
      if (isEqual(p2, rotate90(v)))
      {
        output += "reflected vertically and rotated 90 degrees.\n";
      } else if (isEqual(p2, rotate180(v)))
      {
        output += "reflected vertically and rotated 180 degrees.\n";
      } else if (isEqual(p2, rotate270(v)))
      {
        output += "reflected vertically and rotated 270 degrees.\n";
      } else
      {
        output += "improperly transformed.\n";
      }
    }
  }

  printf("%s", output.c_str());

  return(0);
}