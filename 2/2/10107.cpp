/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 *
 * 10107 - What is the Median?
**/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>


using namespace std;
typedef unsigned char byte;
typedef unsigned long long ull;

int main()
{
  string output = "";

  output.reserve(500000);

  vector<ull> vi;
  vi.reserve(100000);

  while (!cin.eof())
  {
    long long value;
    cin >> value;

    if (cin.fail()) break;

    auto lower = lower_bound(vi.begin(), vi.end(), value);
    vi.insert(lower, value);

    ull n = vi.size();
    ull lowMedian = (n&1 ? n/2 : (n-1)/2);
    ull highMedian = (n&1 ? lowMedian : lowMedian + 1);
    ull median1 = vi[lowMedian];
    ull median2 = vi[highMedian];
    ull median = (median1 + median2) / 2;

    output += to_string(median) + "\n";
  }

  printf("%s", output.c_str());

  return(0);
}