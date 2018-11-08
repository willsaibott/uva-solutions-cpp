/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 *
 * 10698 - Football Sort
**/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <map>

using namespace std;
typedef unsigned char byte;
typedef unsigned long long ull;

class Team {
  string name;
  string lowername;
  int wins = 0;
  int loses = 0;
  int draws = 0;
  int goalsPro = 0;
  int goalsTaken = 0;
  int goalsDiff = 0;
  int games = 0;
  int points = 0;

  public:
    Team() { }
    Team(string name) : name(name), lowername(name) {
      ::transform(lowername.begin(),
                  lowername.end(),
                  lowername.begin(),
                  ::tolower);
    }

    bool operator () (const Team &t) const {
      return (points != t.points ?
              points > t.points :
              (goalsDiff != t.goalsDiff ?
               goalsDiff > t.goalsDiff :
               (goalsPro != t.goalsPro ?
                goalsPro > t.goalsPro :
                lowername < t.lowername )));
    }

    bool operator < (const Team &t) const {
      return (points != t.points ?
              points > t.points :
              (goalsDiff != t.goalsDiff ?
               goalsDiff > t.goalsDiff :
               (goalsPro != t.goalsPro ?
                goalsPro > t.goalsPro :
                lowername < t.lowername )));
    }

    bool operator == (const Team &t) const {
      return points == t.points &&
             goalsDiff == t.goalsDiff &&
             goalsPro == t.goalsPro;
    }

    static void play(Team &t1, Team &t2, pair<int, int> scoreBoard) {
      t1.wins += scoreBoard.first > scoreBoard.second;
      t1.loses += scoreBoard.first < scoreBoard.second;
      t1.draws += scoreBoard.first == scoreBoard.second;
      t1.goalsPro += scoreBoard.first;
      t1.goalsTaken += scoreBoard.second;
      t1.goalsDiff = t1.goalsPro - t1.goalsTaken;
      t1.games++;
      t1.points += 3*(scoreBoard.first > scoreBoard.second) +
                   1*(scoreBoard.first == scoreBoard.second);

      t2.wins += scoreBoard.first < scoreBoard.second;
      t2.loses += scoreBoard.first > scoreBoard.second;
      t2.draws += scoreBoard.first == scoreBoard.second;
      t2.goalsPro += scoreBoard.second;
      t2.goalsTaken += scoreBoard.first;
      t2.goalsDiff = t2.goalsPro - t2.goalsTaken;
      t2.games++;
      t2.points += 3*(scoreBoard.second > scoreBoard.first) +
                   1*(scoreBoard.second == scoreBoard.first);

    }

    string to_string(int ranking = 0) {
      char s[60];

      if (games)
      {
        if (ranking) {
          sprintf(s, "%2d. %15s %3d %3d %3d %3d %3d %6.2f\n",
                  ranking,
                  name.c_str(),
                  points,
                  games,
                  goalsPro,
                  goalsTaken,
                  goalsDiff,
                  points / (0.03 * games));
        }
        else {
          sprintf(s, " %18s %3d %3d %3d %3d %3d %6.2f\n",
                  name.c_str(),
                  points,
                  games,
                  goalsPro,
                  goalsTaken,
                  goalsDiff,
                  points / (0.03 * games));
        }
      }
      else
      {
        if (ranking) {
          sprintf(s, "%2d. %15s %3d %3d %3d %3d %3d    N/A\n",
                  ranking,
                  name.c_str(),
                  points,
                  games,
                  goalsPro,
                  goalsTaken,
                  goalsDiff);
        }
        else {
          sprintf(s, " %18s %3d %3d %3d %3d %3d    N/A\n",
                  name.c_str(),
                  points,
                  games,
                  goalsPro,
                  goalsTaken,
                  goalsDiff);
        }
      }
      return string(s);
    }
};

class Tournament {
  vector<Team> teams;
  map<string, int> m;

  public:

    void addTeam(string name)
    {
      m[name] = teams.size()+1;
      teams.push_back(Team(name));
    }

    void addGame(string name1, string name2, pair<int, int> scoreBoard)
    {
      int t1 = m[name1]-1;
      int t2 = m[name2]-1;

      if (t1 >= 0 && t2 >= 0)
      {
        Team::play(teams[t1], teams[t2], scoreBoard);
      }
    }

    string to_string() {
      string str;
      sort(teams.begin(), teams.end());

      int ranking = 0;
      int draws = 0;
      for (auto team = teams.begin(); team != teams.end(); team++)
      {
        if (team == teams.begin() || !( *team == *(prev(team))))
        {
          ranking += 1 + draws;
          str += team->to_string(ranking);
          draws = 0;
        } else {
          str += team->to_string();
          draws++;
        }
      }
      return str;
    }
};

int main()
{
  string output = "";
  string line;
  bool begin = true;

  output.reserve(500000);

  while(!cin.eof())
  {
    int teams, games;
    cin >> teams >> games;
    cin.ignore();

    if (!teams || cin.eof()) break;
    if (!begin || (begin = false)) output += "\n";

    Tournament t;

    for (int ii = 0; ii < teams; ii++)
    {
      getline(cin, line);
      t.addTeam(line);
    }

    for (int ii = 0; ii < games; ii++)
    {
      string name1, name2;
      int g1, g2;
      char dash;
      cin >> name1 >> g1 >> dash >> g2 >> name2;
      cin.ignore();

      t.addGame(name1, name2, {g1, g2});
    }
    output += t.to_string();
  }

  printf("%s", output.c_str());

  return(0);
}