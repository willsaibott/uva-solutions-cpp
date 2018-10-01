/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
**/

#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
#include <utility>
#include <string>
#include <iomanip>
#include <set>
#include <queue>
#include <stack>
#include <sstream>
#include <cmath>

using namespace std;

const int MAX_AMOUNT = 40;

string run(int n, int k)
{
  int students[26] = {0};
  int amount = 1;
  int sum = 1;
  char s[10];
  queue<int> q;
  string output = "";

  for(int ii = 1; ii <= n; ii++) {
    q.push(ii);
  }

  while (q.size())
  {
    int student = q.front();
    int credit =  min(40 - students[student], amount);

    amount -= credit;
    students[student] += credit;

    if (amount <= 0)
    {
      sum = (sum < k  ? sum + 1 : 1);
      amount = sum;
    }

    if (students[student] < MAX_AMOUNT)
    {
      q.push(student);
    } else
    {
      sprintf(s, "%3d", student);
      output += s;
    }

    q.pop();
  }

  return output;
}

int main()
{
  int k;
  int n;
  string output = "";
  string line;
  char s[10];

  while(!cin.eof())
  {
    cin >> n >> k;
    cin.ignore();

    if (!n && !k) break;
    if (n == 1)
    {
      sprintf(s, "%3d", 1);
      output += s;
      output += "\n";
      continue;
    }

    output += run(n, k) + "\n";
  }

  printf("%s", output.c_str());

  return(0);
}