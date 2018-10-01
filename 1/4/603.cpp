/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
**/

#include <cstdio>
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;


inline bool LessComparator (const pair<int, int> &lhs, const pair<int, int> &rhs)
{
  return lhs.second <= rhs.second;
}

inline bool GreaterComparator (const pair<int, int> &lhs, const pair<int, int> &rhs)
{
  return lhs.second >= rhs.second;
}

int main()
{
  int k = 0;
  int N;
  string output = "";
  string line;
  bool begin = true;

  output.reserve(500000);
  cin >> N;
  cin.ignore();

  while(k++ < N && !cin.eof())
  {
    vector<int> cars;
    vector<pair<int, int>> availableCars;
    int input;
    int spots[21] = {0};

    if (!begin || (begin = false)) output += "\n";

    cin >> input;
    // output += to_string(k) + "\n";
    while (input != 99)
    {
      cars.push_back(input);
      availableCars.push_back(make_pair(input, input));
      cin >> input;
    }

    cin.ignore();

    sort(availableCars.begin(), availableCars.end(), LessComparator);


    while (getline(cin, line))
    {
      int diff;
      if (line == "") break;

      input = stoi(line);

      auto it = lower_bound(availableCars.begin(),
                            availableCars.end(),
                            make_pair(input, input),
                            LessComparator);

      if (it != availableCars.begin())
      {
        --it;
        spots[it->first] = input;
        diff = (input - it->second);
        availableCars.erase(it);
      }
      else
      {
        spots[availableCars.back().first] = input;
        diff = (20 + input - (availableCars.back().second));
        availableCars.pop_back();
      }

      if (diff)
      {
        vector<pair<int, int>> elementsToAdd;

        for ( auto iter = availableCars.rbegin();
                   iter != availableCars.rend();
                   iter++ ) {
          iter->second = (iter->second + diff);

          if (iter->second > 20)
          {
            int first = iter->first;
            int second = iter->second;

            availableCars.erase(next(iter).base());
            elementsToAdd.push_back(make_pair(first, second - 20));
          }
        }

        availableCars.insert(
          availableCars.begin(),
          elementsToAdd.rbegin(),
          elementsToAdd.rend());
      }
    }

    for ( auto it = cars.begin(); it != cars.end(); it++ ) {
      if (spots[*it])
      {
        output += "Original position " + to_string(*it) +
                  " parked in " + to_string(spots[*it]) + "\n";
      } else
      {
        output += "Original position " + to_string(*it) +
                  " did not park\n";
      }
    }
    // output+= to_string(k) + "\n";
  }

  printf("%s", output.c_str());

  return(0);
}
