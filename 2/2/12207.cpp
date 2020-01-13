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
#include <queue>
#include <deque>
#include <stack>
#include <sstream>
#include <cmath>
#include <climits>
#include <cstdlib>
#include <string>
#include <iomanip>
#include <list>

using namespace std;
typedef unsigned char byte;
typedef unsigned long long ull;
typedef long long ll;

int main()
{
  int k = 0;
  string output = "";

  output.reserve(500000);

  long long population{0}, commands{0};

  while(!cin.eof() && cin.good()) {
    char command;
    cin >> population >> commands;

    if (!population && !commands) {
      // end
      break;
    }

    std::list<long long> pacients;
    long long pacient{1};
    while (pacients.size() < std::min(commands, population)) {
      pacients.push_back(pacient++);
    }

    output += "Case " + to_string(++k).append(":\n");

    for (int ii = 0; ii < commands; ii++) {
      cin >> command;
      if (command == 'N') {
        const auto& elem{pacients.front()};
        output += to_string(elem).append("\n");
        pacients.pop_front();
        pacients.push_back(elem);
      }
      else {
        int elem;
        cin >> elem;
        auto it = find(pacients.begin(), pacients.end(), elem);
        if (it != pacients.end()) {
          pacients.erase(it);
        }
        pacients.push_front(elem);
      }
    }
  }

  printf("%s", output.c_str());

  return(0);
}