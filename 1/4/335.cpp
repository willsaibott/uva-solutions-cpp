/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
**/

#include <cstdio>
#include <algorithm>
#include <iostream>
#include <map>
#include <utility>
#include <string>
#include <set>
#include <list>
#include <climits>

using namespace std;

typedef pair<int, string> domain;

inline bool operator < (domain &lhs, domain &rhs)
{
  return lhs.first < rhs.first;
}

struct comparator
{
  bool operator() (const domain &lhs, const domain &rhs)
  {
    return lhs.first != rhs.first ?
           lhs.first < rhs.first :
           lhs.second < rhs.second;
  }

  bool operator() (const domain &lhs, const int &rhs)
  {
    return lhs.first < rhs;
  }

  bool operator() (const int &lhs, const domain &rhs)
  {
    return lhs < rhs.first;
  }
};

typedef set<domain, comparator> address;

inline bool operator > (domain &lhs, domain &rhs)
{
  return lhs.first > rhs.first;
}

inline bool operator >= (domain &lhs, domain &rhs)
{
  return lhs.first >= rhs.first;
}

inline bool operator <= (domain &lhs, domain &rhs)
{
  return lhs.first <= rhs.first;
}

bool isNumber(string &str )
{
  auto it = str.begin();
  while(!str.empty() && it != str.end() && isdigit(*it)) it++;
  return !str.empty() && it == str.end();
}

domain min(domain &lhs, domain &rhs)
{
  return (lhs < rhs ? lhs : rhs);
}

int main()
{
  int preference;
  int N;
  string output = "";
  string line, input, last, dest;
  map<string, address> router;
  set<string> downMachines, wildcards;
  domain MAXDOMAIN = make_pair(INT_MAX, "");

  output.reserve(500000);
  cin >> N;
  cin.ignore();

  for(int ii = 0; ii < N; ii++) {
    cin >> input;

    if (isNumber(input))
    {
      preference = stoi(input);
      input = last;
    } else
    {
      last = input;
      cin >> preference;
    }
    cin >> dest;

    if (input[0] == '*')
    {
      string rev = input.substr(1);
      reverse(rev.begin(), rev.end());
      wildcards.insert(rev);
    }

    router[input].insert(make_pair(preference, dest));
  }

  while(!cin.eof())
  {
    cin >> input;

    if (input == "X") break;
    cin >> dest;

    if (input == "A")
    {
      address l = router[dest], l2;
      domain d = MAXDOMAIN;
      output += dest + " =>";

      for ( auto it = l.begin(); it != l.end(); it++ ) {
        if (!downMachines.count(it->second))
        {
          d = *it;
          break;
        }
      }

      string rev = dest;
      reverse(rev.begin(), rev.end());
      int index = (rev.find("."));
      do
      {
        string sub = rev.substr(0, index + 1);

        if (wildcards.count(sub))
        {
          string sub2 = sub;
          reverse(sub2.begin(), sub2.end());
          l2 = router["*" + sub2];
          for ( auto it = l2.begin(); it != l2.end(); it++ ) {
            if (!downMachines.count(it->second))
            {
              d = min(d, *it);
              break;
            }
          }
        }

        index = (rev.find(".", index + 1));
      } while (dest.size() > 1 && index > 0);

      if (d >= MAXDOMAIN)
      {
        output += "\n";
        continue;
      }

      output += " " + d.second + "\n";
    } else if (input == "D")
    {
      downMachines.insert(dest);
    } else if (input == "U")
    {
      downMachines.erase(dest);
    }
  }

  printf("%s", output.c_str());

  return(0);
}