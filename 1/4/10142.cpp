/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
**/

#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
#include <sstream>

using namespace std;

class Candidate
{
  string name;
  int votes;
  int index;

  public:

  Candidate(string name, int index)
    : name(name), votes(0), index(index) {}
  Candidate()
    : name(""), votes(0), index(0) {}

  void incr()
  {
    votes++;
  }

  string getName() const { return name; }
  int getVotes() const { return votes; }
  int getIndex() const { return index; }
  void reset() { votes = 0; }
};

uint hasWinner(vector<Candidate> &candidates,
               vector<queue<int>> &voting,
               vector<bool> &invalids)
{
  vector<Candidate> winners, vcand;
  int highest = 0, lowest = 1000;

  for ( auto it = candidates.begin(); it != candidates.end(); it++ ) {
    it->reset();
  }

  for ( auto it = voting.begin(); it != voting.end(); it++ ) {
    while (invalids[it->front()])
    {
      it->pop();
    }

    candidates[it->front()-1].incr();
  }

  for ( auto it = candidates.begin(); it != candidates.end(); it++ ) {
    if (!invalids[it->getIndex()])
    {
      lowest = min(it->getVotes(), lowest);
      highest = max(it->getVotes(), highest);
    }
  }

  if (highest == lowest ||
      (uint)highest * 2 > voting.size())
  {
    return highest;
  }

  bool reset = false;
  for ( auto it = candidates.begin();
             it != candidates.end();
             it++ ) {
    if(it->getVotes() == lowest)
      invalids[it->getIndex()] = true;
    // if (reset) it = candidates.begin();
    // reset = false;

    // if (it->second.getVotes() == lowest)
    // {
    //   it++;
    //   if (it != candidates.begin())
    //     it--;
    //   else
    //     reset = true;
    // }
  }

  return 0;
}

int main()
{
  int k = 0;
  int N, input, vote;
  string output = "";
  string line;
  bool begin = true;

  output.reserve(500000);
  cin >> N;
  cin.ignore();
  cin.ignore(); // blank line

  while(k++ < N)
  {
    uint winners;
    vector<Candidate> candidates;
    vector<queue<int>> voting;

    cin >> input;
    cin.ignore();

    vector<bool> invalids(input + 1, false);

    for(int ii = 0; ii < input; ii++) {
      getline(cin, line);
      Candidate c(line, ii + 1);
      candidates.push_back(c);
    }

    while (getline(cin, line))
    {
      if (line == "") break;
      stringstream ss(line);

      queue<int> q;

      while (!ss.eof())
      {
        ss >> vote;
        q.push(vote);
      }

      voting.push_back(q);
    }

    do
    {
      winners = hasWinner(candidates, voting, invalids);
    } while (!winners);

    if (!begin || (begin = false)) output += "\n";

    for ( auto it = candidates.begin(); it != candidates.end(); it++ ) {
      if ((uint)it->getVotes() == winners)
      {
        output += it->getName() + "\n";
      }
    }

    // output += to_string(k) + "\n";
  }

  printf("%s", output.c_str());

  return(0);
}