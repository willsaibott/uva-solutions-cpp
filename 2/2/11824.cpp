/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 *
 * 11824 - A Minimum Land Price
**/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;
typedef unsigned char byte;
typedef unsigned long long ull;
typedef long long ll;

const ull MAX = 5000000;

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
    vector<ull> prices;

    prices.reserve(40);

    while (true)
    {
      int price;
      cin >> price;

      if (!price) break;
      prices.push_back(price);
    }

    sort(prices.begin(), prices.end(), greater<ull>());

    ull total = 0;
    for (int ii = 0;
         ii < (int)prices.size() && total < MAX;
         ii++)
    {
      total += 2 * (pow(prices[ii], ii+1));
    }

    if (total > MAX)
    {
      output += "Too expensive\n";
    } else
    {
      output += to_string(total) + "\n";
    }
  }

  printf("%s", output.c_str());

  return(0);
}