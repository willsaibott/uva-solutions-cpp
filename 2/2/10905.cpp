/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 *
 * 10905 - Children's Game
**/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
typedef unsigned char byte;
typedef unsigned long long ull;
typedef long long ll;

int main()
{
  string output = "";
  string line;

  output.reserve(500000);

  while(!cin.eof())
  {
    ull n;
    cin >> n;

    if (!n || cin.fail()) break;

    vector<string> numbers;

    for (ull ii = 0; ii < n; ii++)
    {
      string number;
      cin >> number;
      numbers.push_back(number);
    }

    sort(numbers.begin(), numbers.end(),
         [](const string &s1, const string &s2)
          {
            for (int ii = 0;
                !ii || ii % s1.size() || ii % s2.size();
                ii++)
            {
              int index1 = ii % s1.size();
              int index2 = ii % s2.size();

              if (s1[index1] != s2[index2])
                return s1[index1] > s2[index2];
            }

            return s1.size() < s2.size();
          });

    for (auto number = numbers.begin(); number != numbers.end(); number++)
    {
      output += *number;
    }

    output += "\n";
  }

  printf("%s", output.c_str());

  return(0);
}