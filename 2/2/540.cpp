/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
 */

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <set>
#include <deque>
#include <cstdlib>
#include <string>
#include <list>

using namespace std;
typedef unsigned char byte;
typedef unsigned long long ull;
typedef long long ll;

struct Team {
  const int id;
  const int insertion_order;
  std::deque<ull> players;

  Team(int team)            : Team(team, 0) {  };
  Team(int team, int order) : id(team), insertion_order(order) {  };
  Team()                             = default;
  Team(const Team& other)            = default;
  Team(Team&& other)                 = default;
  Team& operator=(const Team& other) = default;
  Team& operator=(Team&& other)      = default;

  inline bool operator<(const Team& other) const noexcept {
    return insertion_order < other.insertion_order;
  }
  inline bool operator==(const Team& other) const noexcept {
    return id == other.id;
  }
};

int main()
{
  int k = 0;
  string output = "";

  output.reserve(500000);

  while(!cin.eof() && cin.good()) {
    size_t number_of_teams;
    ull player;
    std::string command;
    cin >> number_of_teams;
    if (!number_of_teams) break;
    output.append("Scenario #").append(to_string(++k)).append("\n");
    std::set<Team>                 team_queues;
    std::unordered_map<ull, ull>   team_players;
    std::unordered_map<ull, Team*> teams_to_queue;
    for (ull ii = 0; ii < number_of_teams; ii++) {
      ull number_of_players;
      cin >> number_of_players;
      for (ull jj = 0; jj < number_of_players; jj++) {
        cin >> player;
        team_players[player] = ii;
      }
    }

    int instances = 0;
    do {
      cin >> command;
      if (command == "ENQUEUE") {
        cin >> player;
        auto& team_id  = team_players[player];
        auto it = teams_to_queue.find(team_id);
        if (it != teams_to_queue.end()){
          auto& team = *it->second;
          team.players.push_back(player);
        } else {
          auto res = team_queues.insert(Team(team_id, instances++));
          teams_to_queue[team_id] = (Team*)&(*res.first);
          const_cast<Team&>(*res.first).players.push_back(player);
        }
      } else if (command == "DEQUEUE" && team_queues.size()) {
        auto& team = const_cast<Team&>(*team_queues.begin());
        if (team.players.size())
        {
          output.append(to_string(team.players.front())).append("\n");
          team.players.pop_front();
        }
        if (team.players.empty()) {
          teams_to_queue.erase(team.id);
          team_queues.erase(team);
        }
      }
    } while (command != "STOP");
    cin.ignore();
    output += "\n";
  }

  printf("%s", output.c_str());
  return(0);
}