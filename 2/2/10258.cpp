/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 *
 * 10258 - Contest Scoreboard
**/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>
#include <climits>

using namespace std;

class Team {
  int index;
  vector<int> problem[10];
  int solvedAt[10] = { INT32_MAX, INT32_MAX, INT32_MAX, INT32_MAX, INT32_MAX,
                       INT32_MAX, INT32_MAX, INT32_MAX, INT32_MAX, INT32_MAX,};
  bool solved[10] = { false };
  int time = 0;
  int problems = 0;
  int submittions = 0;

  public:
    Team() {}
    Team(int index) : index(index) { }

    void submit(int problem, int timestamp, char result)
    {
      submittions++;
      switch (result)
      {
        case 'C':
          this->solved[problem] = true;
          this->solvedAt[problem] = min(timestamp, this->solvedAt[problem]);
          break;
        case 'I':
          if (timestamp <= this->solvedAt[problem] && !solved[problem])
            this->problem[problem].push_back(timestamp);
          break;
        case 'R':
        case 'U':
        case 'E':
          break;
      }
    }

    void process()
    {
      time = 0;
      problems = 0;
      for (int ii = 1; ii < 10; ii++) {
        if (solved[ii])
        {
          time += solvedAt[ii];
          for (auto it = problem[ii].begin(); it != problem[ii].end(); it++)
          {
            time += 20 * (*it <= solvedAt[ii]);
          }
          problems++;
        }
      }
    }

    bool operator () (const Team &t) const {
      return (problems != t.problems ?
              problems > t.problems :
              (time != t.time ?
               time < t.time :
               index < t.index));
    }

    bool operator < (const Team &t) const {
      return (problems != t.problems ?
              problems > t.problems :
              (time != t.time ?
               time < t.time :
               index < t.index));
    }

    bool valid() const { return submittions; }

    string to_string() const {
      string str = ::to_string(index) + " " +
                   ::to_string(problems) + " " +
                   ::to_string(time) + "\n";
      return str;
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
  getline(cin, line); // blanks;

  while(k++ < N && !cin.eof())
  {
    vector<Team> teams(100);

    for (int ii = 0; ii < 100; ii++) {
      teams[ii] = Team(ii+1);
    }

    while (!cin.eof())
    {
      getline(cin, line);
      if (line == "") break;

      stringstream ss(line);
      int team, problem, timestamp;
      char result;

      ss >> team >> problem >> timestamp >> result;

      teams[team-1].submit(problem, timestamp, result);
    }

    teams.erase(
      remove_if(teams.begin(), teams.end(), [](const Team &t) {
        return !t.valid();
      }),
      teams.end());

    for (auto team = teams.begin(); team != teams.end(); team++)
    {
      team->process();
    }

    sort(teams.begin(), teams.end());

    if (!begin || (begin = false)) output += "\n";

    for (auto team = teams.begin(); team != teams.end(); team++)
    {
      output += team->to_string();
    }

  }

  printf("%s", output.c_str());

  return(0);
}