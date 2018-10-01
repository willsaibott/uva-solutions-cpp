/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
**/

#include <cstdio>
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
#include <string>
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

vector<Candidate> computeVotes(map<int, Candidate> &candidates,
                               vector<queue<int>> &voting)
{
  vector<Candidate> winners, vcand;
  int highest = 0, lowest = 1000;

  for ( auto it = candidates.begin(); it != candidates.end(); it++ ) {
    it->second.reset();
  }

  for ( auto it = voting.begin(); it != voting.end(); it++ ) {
    while (!candidates.count(it->front()))
    {
      it->pop();
    }

    candidates[it->front()].incr();
  }

  for ( auto it = candidates.begin(); it != candidates.end(); it++ ) {
    vcand.push_back(it->second);
  }

  sort(vcand.begin(),
       vcand.end(),
       [](const Candidate &c1, const Candidate &c2)
       {
         return (c1.getVotes() != c2.getVotes() ?
                 c1.getVotes() < c2.getVotes() :
                 c1.getIndex() < c2.getIndex());
       });

  bool invalidate = false;
  auto it = vcand.rbegin() + 1;
  winners.push_back(vcand.back());

  for ( ; it != vcand.rend(); it++ )
  {
    if (it->getVotes() < prev(it)->getVotes())
    {
      if (it->getVotes() < (voting.size() / 2.0))
      {
        winners.clear();
        invalidate = true;
        break;
      }
    }
    else
    {
      winners.push_back(*it);
    }
  }

  if (invalidate)
  {
    for (auto fit = vcand.begin();
              fit != vcand.end();
              fit++ )
    {
      auto prox = next(fit);
      int value = fit->getVotes();
      candidates.erase(fit->getIndex());
      if (value < prox->getVotes()) { break; }
    }
  }
  return winners;
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
    vector<Candidate> winners;
    map<int, Candidate> candidates;
    vector<queue<int>> voting;

    cin >> input;
    cin.ignore();

    for(int ii = 0; ii < input; ii++) {
      getline(cin, line);
      Candidate c(line, ii + 1);
      candidates.emplace(ii + 1, c);
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
      winners = computeVotes(candidates, voting);
    } while (!winners.size());

    if (!begin || (begin = false)) output += "\n";

    for ( auto it = winners.rbegin();
               it != winners.rend();
               it++ )
    {
      output += it->getName() + "\n";
    }

    // output += to_string(k) + "\n";
  }

  printf("%s", output.c_str());

  return(0);
}