/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
 */

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <bitset>
#include <utility>
#include <set>
#include <map>
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

int main()
{
  string output = "";
  string line;


  output.reserve(500000);

  while(!cin.eof() && cin.good())
  {
    std::vector<ull> discarded;
    std::deque<ull> cards;
    int n;
    cin >> n;
    if (!n) break;

    for (int ii = 1; ii <= n; ii++) {
      cards.push_back(ii);
    }

    while (cards.size() > 1) {
      discarded.push_back(cards.front());
      cards.pop_front();
      cards.push_back(cards.front());
      cards.pop_front();
    }

    output += "Discarded cards:";
    if (discarded.size()) {
      output += " ";
      for (ll ii = 0; ii < (ll)discarded.size()-1; ii++) {
        output += to_string(discarded[ii]).append(", ");
      }
      output += to_string(discarded.back());
    }
    output.append("\nRemaining card: ")
          .append(to_string(cards.front()))
          .append("\n");
  }

  printf("%s", output.c_str());

  return(0);
}