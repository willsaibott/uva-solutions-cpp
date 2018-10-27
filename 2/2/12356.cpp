/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
**/

#include <cstdio>
#include <iostream>

using namespace std;

int main()
{
  string output = "";
  string line;
  bool begin = true;
  int left[100005], right[100005];

  output.reserve(50000);
  while(!cin.eof())
  {
    int n, reports;
    cin >> n >> reports;

    if (!begin || (begin = false)) output += "-\n";
    if (!n || cin.eof()) break;

    for (int ii = 1; ii <= n; ii++)
    {
      left[ii] = ii - 1;
      right[ii] = ii + 1;
    }
    right[n] = left[1] = -1;

    int l,r;
    for (int ii = 0; ii < reports; ii++)
    {
      cin >> l >> r;
      left[right[r]] = left[l];
      output += ((left[l] != -1) ? to_string(left[l]) + " " : "* ");
      right[left[l]] = right[r];
      output += ((right[r] != -1) ? to_string(right[r]) + "\n" : "*\n");
    }
  }

  printf("%s", output.c_str());

  return(0);
}