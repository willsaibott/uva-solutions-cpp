/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 *
 * 514 - Rails
 */

#include <cstdio>
#include <iostream>
#include <vector>
#include <stack>
#include <sstream>

using namespace std;
typedef unsigned char byte;
typedef unsigned long long ull;
typedef long long ll;

int main()
{
  string output = "";
  string line;
  bool begin = true;

  output.reserve(500000);

  while(!cin.eof())
  {
    int n;
    cin >> n;
    cin.ignore();

    if (!begin || (begin = false)) output += "\n";
    if (!n) break;

    bool end = false;
    while (!end) {
      while (true)
      {
        vector<int> vi;
        vi.reserve(20);

        getline(cin, line);

        if (line == "0")
        {
          end = true;
          break;
        }

        stringstream ss(line);

        while (!ss.eof())
        {
          int value;
          ss >> value;
          vi.push_back(value);
        }

        int currCoach = 1;
        int targetIndex = 0;

        stack<int> station;
        while (currCoach <= n)
        {
          station.push(currCoach);

          while (!station.empty() && station.top() == vi[targetIndex]) {
            station.pop();
            targetIndex++;
            if (targetIndex >= n) break;
          }

          currCoach++;
        }

        output += (station.size() ? "No\n" : "Yes\n");
      }
    }
  }

  printf("%s", output.c_str());

  return(0);
}