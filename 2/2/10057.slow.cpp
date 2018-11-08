/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 *
 * 10057 - A mid-summer night's dream.
**/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>


using namespace std;
typedef unsigned char byte;
typedef unsigned long long ull;

int getAs(vector<int> &x,
          vector<int>::iterator start,
          vector<int>::iterator end)
{
  int count = 0;
  int minimum = INT32_MAX;

  for (int it = *start; it <= *end; it++)
  {
    int sum = 0;
    int A = it;

    for (auto xi = x.begin(); xi != x.end(); xi++)
    {
      sum += abs(*xi - A);
    }

    count += (minimum == sum);
    if (minimum > sum)
    {
      count   = 1;
      minimum = sum;
    }
  }

  return count;
}

int main()
{
  string output = "";
  string line;

  output.reserve(500000);

  while(!cin.eof())
  {
    int n;
    cin >> n;
    if (cin.eof()) break;

    vector<int> x(n);
    int sum = 0;

    for (int ii = 0; ii < n; ii++)
    {
      cin >> x[ii];
      sum += x[ii];
    }

    int median1 = (n & 1 ? n / 2 : (n-1) / 2);
    int median2 = (n & 1 ? median1 : median1 + 1);
    int count = 0;
    sort(x.begin(), x.end());

    auto start = lower_bound(x.begin(), x.end(), x[median1]);
    auto end   = upper_bound(x.begin(), x.end(), x[median2]);

    count = end - start;

    output += to_string(x[median1]) + " " +
              to_string(count) + " " +
              to_string(getAs(x, x.begin() + median1, x.begin() + median2)) + "\n";
  }

  printf("%s", output.c_str());

  return(0);
}