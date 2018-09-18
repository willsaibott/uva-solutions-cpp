/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
**/

#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
#include <utility>
#include <string>
#include <iomanip>
#include <set>
#include <queue>
#include <stack>
#include <sstream>
#include <cmath>

using namespace std;
int invalidMap = 0;

typedef struct vt {
  queue<int> candidate;
  bool valid = true;
} vote;

typedef pair<int, int> computed;

struct Comparator
{
  bool operator () (const computed &cp1, const computed &cp2)
  {
    return cp1.first < cp2.first;
  }
};

bool compareVotes(const computed &lhs, const computed &rhs)
{
  return lhs.second < rhs.second;
}

string getResults(vector<int> vt, int k, int invalids)
{
  string output = "Election #" + to_string(k) + "\n";

  if (invalids)
  {
    output += "   " + to_string(invalids) + " bad ballot(s)\n";
  }

  if (vt.size() > 1)
  {
    output += "   The following candidates are tied:";

    for ( auto it = vt.begin(); it != vt.end(); it++ ) {
      output+= " " + to_string(*it);
    }

    output += "\n";
  } else
  {
    output += "   Candidate " + to_string(vt.front()) +
              " is elected.\n";
  }

  return output;
}

vector<int> isElected(vector<computed> count, int voters)
{
  vector<int> elected, empty;

  if (count.back().second > (voters / 2 + 1))
  {
    elected.push_back(count.back().first);
    return elected;
  }

  for ( auto it = count.begin() + 1; it != count.end(); it++ ) {
    int mask = (1 << it->first);
    if (!(invalidMap & mask))
    {
      if (it->second < count.back().second)
      {
        invalidMap |= mask;
        return empty;
      }

      elected.push_back(it->first);
    }
  }

  return elected;
}

int main()
{
  int k = 0;
  int candidates, voters;
  string output = "";
  string line;

  output.reserve(500000);

  while(!cin.eof())
  {
    cin >> candidates >> voters;
    if (!candidates || !voters) break;
    int votes[voters][candidates];
    int doubled[voters] = {0};
    int invalid = 0;
    vector<vote> validVotes;
    invalidMap = 0;

    vector<computed> count;
    for(int ii = 0; ii < 6; ii++) {
      count.push_back(make_pair(ii, 0));
    }

    for(int ii = 0; ii < voters; ii++) {
      vote v;

      for(int jj = 0; jj < candidates; jj++) {
        cin >> votes[ii][jj];
        int mask = (1 << (votes[ii][jj] - 1));

        v.candidate.push(votes[ii][jj]);
        if (!((doubled[ii] ^ mask) & (mask)) ||
            votes[ii][jj] > candidates ||
            votes[ii][jj] < 1)
        {
          v.valid = false;
          invalidMap |= (1 << ii);
        } else {
          doubled[ii] |= mask;
        }
      }

      if (v.valid)
      {
        count[v.candidate.front()].second++;
        count[v.candidate.front()].first = v.candidate.front();
        validVotes.push_back(v);
      } else
      {
        invalid++;
      }
    }

    vector<int> elected;
    do
    {
      sort(count.begin(), count.end(), compareVotes);

      elected = isElected(count, voters - invalid);
      if (!elected.size())
      {
        for ( auto it = count.begin(); it != count.end(); it++ ) {
            it->second = 0;
            it->first = it - count.begin();
        }

        for ( auto it = validVotes.begin();
                   it != validVotes.end();
                   it++ )
        {
          int mask = (1 << it->candidate.front());
          while ((mask & invalidMap) && it->candidate.size())
          {
            it->candidate.pop();
            mask = (1 << it->candidate.front());
          }
          if (it->candidate.size())
            count[it->candidate.front()].second++;
        }
      }
    } while (!elected.size());

    output += getResults(elected, ++k, invalid);
  }

  printf("%s", output.c_str());

  return(0);
}