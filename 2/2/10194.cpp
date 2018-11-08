/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 *
 * 10194 - Football (aka Soccer)
**/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <sstream>


using namespace std;
typedef unsigned char byte;
typedef unsigned long long ull;

class Team {
  string name;
  string lowerName;
  int wins = 0;
  int loses = 0;
  int draws = 0;
  int goalsPro = 0;
  int goalsTaken = 0;
  int goals = 0;
  int points = 0;
  int games = 0;

  public:
    Team() { }
    Team(string name) : name(name), lowerName(name)
    {
      ::transform(lowerName.begin(),
                  lowerName.end(),
                  lowerName.begin(),
                  ::tolower);
    }

    bool operator < (const Team &t) {
      return (points != t.points ?
              points > t.points :
              (wins != t.wins ?
               wins > t.wins :
               (goals != t.goals ?
                goals > t.goals :
                (goalsPro != t.goalsPro ?
                 goalsPro > t.goalsPro :
                 (games != t.games ?
                  games < t.games :
                  lowerName < t.lowerName)))));
    }

    bool operator () (const Team &t) {
      return (points != t.points ?
              points > t.points :
              (wins != t.wins ?
               wins > t.wins :
               (goals != t.goals ?
                goals > t.goals :
                (goalsPro != t.goalsPro ?
                 goalsPro > t.goalsPro :
                 (games != t.games ?
                  games < t.games :
                  lowerName < t.lowerName)))));
    }

    void static play(Team &t1, Team &t2, int g1, int g2)
    {
      t1.goalsPro += g1;
      t2.goalsPro += g2;
      t1.goalsTaken += g2;
      t2.goalsTaken += g1;
      t1.goals += g1 - g2;
      t2.goals += g2 - g1;
      t1.wins += (g1 > g2);
      t2.wins += (g2 > g1);
      t1.loses += (g2 > g1);
      t2.loses += (g1 > g2);
      t1.draws += (g2 == g1);
      t2.draws += (g1 == g2);
      t1.games++;
      t2.games++;
      t1.points += 3*(g1 > g2) + (g1 == g2);
      t2.points += 3*(g2 > g1) + (g1 == g2);
    }

    string to_string() const
    {
      string str = name + " ";
      str += ::to_string(points) + "p, " +
             ::to_string(games) + "g (" +
             ::to_string(wins) + "-" +
             ::to_string(draws) + "-" +
             ::to_string(loses) + "), " +
             ::to_string(goals) + "gd (" +
             ::to_string(goalsPro) + "-" +
             ::to_string(goalsTaken) + ")\n";
      return str;
    }
};

class Tournament {
  string name;
  vector<Team> teams;
  map<string, int> teamMap;
  int index = 0;

  public:
    Tournament(string name, int total) : name(name)
    {
      teams = vector<Team>(total);
    }

    void addTeam(string name)
    {
      teamMap[name] = ++index;
      teams[index-1] = Team(name);
    }

    void addMatch(string name1,
                  string name2,
                  int g1,
                  int g2)
    {

      int t1 = teamMap[name1]-1;
      int t2 = teamMap[name2]-1;

      if (t1 >= 0 && t2 >= 0)
        Team::play(teams[t1], teams[t2], g1, g2);
    }

    string to_string() {
      int ranking = 1;
      string str = name + "\n";

      sort(teams.begin(), teams.end());

      for (auto team = teams.begin(); team != teams.end(); team++)
      {
        str += ::to_string(ranking++) + ") " + team->to_string();
      }

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

  while(k++ < N && !cin.eof())
  {
    if (!begin || (begin = false)) output += "\n";

    int teams, matches;
    getline(cin, line);
    cin >> teams;
    cin.ignore();

    Tournament tournament(line, teams);

    for (int ii = 0; ii < teams; ii++)
    {
      getline(cin, line);
      tournament.addTeam(line);
    }

    cin >> matches;
    cin.ignore();

    for (int ii = 0; ii < matches; ii++)
    {
      getline(cin, line);

      string team1, team2, g1, g2;
      stringstream ss(line);

      getline(ss, team1, '#');
      getline(ss, g1, '@');
      getline(ss, g2, '#');
      getline(ss, team2);
      tournament.addMatch(team1, team2, stoi(g1), stoi(g2));
    }

    output += tournament.to_string();
  }

  printf("%s", output.c_str());

  return(0);
}