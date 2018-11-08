/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 *
 * 790 - Head Judge Headache
**/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <sstream>
#include <climits>


using namespace std;
typedef unsigned char byte;
typedef unsigned long long ull;

class Submission {
  int team;
  char problem;
  bool solved;
  vector<int> timestamps;
  int solvedAt = INT32_MAX;

  public:
    Submission() {}
    Submission(int team, char problem)
      : team(team), problem(problem)
    {
      solved = false;
    }

    void addTime(int time) {
      if (time <= solvedAt)
      {
        timestamps.push_back(time);
      }
    }

    void solve(int time) {
      this->solved = true;

      if (time < solvedAt)
      {
        solvedAt = time;
        addTime(time);
      }
    }

    bool isSolved() const { return this->solved; }

    int isSolvedAt() const { return solvedAt; }

    int getTime() const
    {
      int time = -20;
      for (auto ts = timestamps.begin(); ts != timestamps.end(); ts++)
      {
        time += 20 * (*ts <= solvedAt);
      }
      return solvedAt + time;
    }

    int getTeam() const { return team; }
    char getProblem() const { return problem; }
};

class Team {
  int team;
  int problems = -1;
  int time = 0;
  map<char, Submission> submissions;

  public:
    Team(int index) : team(index) {}

  int getProblems() const { return problems; };
  int getTime()     const { return time; };
  int getId()       const { return team; };

  bool operator () (const Team &t) const {
    return problems != t.problems ?
           problems > t.problems :
           (time != t.time ?
            time < t.time :
            team < t.team);
  }

  bool operator < (const Team &t) const {
    return problems != t.problems ?
           problems > t.problems :
           (time != t.time ?
            time < t.time :
            team < t.team);
  }

  void submit(char problem, bool solved, int time) {
    Submission sub;
    if (submissions.count(problem))
    {
      sub = submissions[problem];

    } else
    {
      sub = Submission(team, problem);
      submissions[problem] = sub;
    }

    if (solved)
    {
      submissions[problem].solve(time);
    } else
    {
      submissions[problem].addTime(time);
    }
  }

  void calcProblems() {
    if (problems < 0)
    {
      problems = 0;
      for (auto sub = submissions.begin(); sub != submissions.end(); sub++)
      {
        if (sub->second.isSolved())
        {
          problems++;
          time += sub->second.getTime();
        }
      }
    }
  }

  bool equal (const Team &t) const {
    return problems == t.problems && time == t.time;
  }
};

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
  cin.ignore();

  while (k++ < N && !cin.eof())
  {
    vector<Team> teams;
    int maxID = 0;

    for (int ii = 0; ii < 30; ii++)
    {
      teams.push_back(Team(ii));
    }

    while(!cin.eof())
    {
      int teamId, time;
      string timestamp;
      char problem, yn;

      getline(cin, line);
      if (line == "") break;

      stringstream ss(line);
      ss >> teamId >> problem >> timestamp >> yn;

      maxID = max(maxID, teamId);
      int index = timestamp.find(":");
      time = stoi(timestamp.substr(0, index)) * 60 +
             stoi(timestamp.substr(index+1));

      teams[teamId].submit(problem, (yn == 'Y'), time);
    }

    teams.erase(teams.begin());

    for (auto team = teams.begin(); team != teams.end(); team++)
    {
      team->calcProblems();
    }

    sort(teams.begin(), teams.end());

    if (!begin || (begin = false)) output += "\n";
    output += "RANK TEAM PRO/SOLVED TIME\n";

    int ranking = 1;
    int drawings = 0;
    char s[50];
    Team last = *(teams.begin());
    for (auto team = teams.begin();
              team != teams.end() && team->getId() <= maxID;
              team++)
    {
      ranking += !team->equal(last);
      if (team->equal(last) && team != teams.begin())
      {
        drawings++;
      } else if (drawings)
      {
        ranking += drawings;
        drawings = 0;
      }

      if (team->getProblems())
      {
        sprintf(s,
                "%4d %4d %4d %10d\n",
                ranking,
                team->getId(),
                team->getProblems(),
                team->getTime());
      } else
      {
        sprintf(s, "%4d %4d\n", ranking, team->getId());
      }

      output += string(s);
      last = *(team);
    }
  }

  printf("%s", output.c_str());

  return(0);
}