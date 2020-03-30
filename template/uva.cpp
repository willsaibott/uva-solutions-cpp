/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 * uhunt page: https://uhunt.onlinejudge.org/id/899065
 *
 */

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <bitset>
#include <utility>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <memory>
#include <queue>
#include <deque>
#include <stack>
#include <sstream>
#include <cmath>
#include <climits>
#include <cstdlib>
#include <string>
#include <iomanip>

using namespace std;
typedef unsigned char byte;
typedef unsigned long long ull;
typedef long long ll;


class Solution {
  public:
  std::string solve() { return ""; };
};


int main()
{
  int k = 0;
  int N;
  string output = "";
  bool begin = true;
  string line;

  output.reserve(500000);
  cin >> N;
  cin.ignore();

  while(k++ < N && !cin.eof() && cin.good())
  {
    Solution solution;
    int n;
    cin >> n;

    if (!begin || (begin = false)) output += "\n";
    if (!n) break;

    output += solution.solve() + "\n";
  }

  printf("%s", output.c_str());

  return(0);
}