/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 * uhunt page: https://uhunt.onlinejudge.org/id/899065
 *
 */

#include <bits/stdc++.h>

using namespace std;

template <class T = size_t>
T getInput() {
  static T input;
  return (std::cin >> input, std::cin.ignore(), input);
}

struct Player {
  std::string name;
  std::int32_t attacking;
  std::int32_t defense;
};

struct SortByAttack {
  bool operator()(const Player& p1, const Player& p2) const {
    if (p1.attacking == p2.attacking) {
      if (p1.defense == p2.defense) {
        return p1.name < p2.name;
      }
      return p1.defense < p2.defense;
    }
    return p1.attacking > p2.attacking;
  }
};

struct SortByName {
  bool operator()(const Player& p1, const Player& p2) const {
    return p1.name < p2.name;
  }
};

inline std::istream& operator >>(std::istream& iss, Player& player) {
  iss >> player.name >> player.attacking >> player.defense;
  return iss;
}

inline std::ostream& operator <<(std::ostream& oss, const Player& player) {
  return oss << player.name;
}

class Team {
  std::vector<Player> attacking;
  std::vector<Player> defending;

  public:

  Team&
  addAttacker(const Player& player) {
    attacking.push_back(player);
    return *this;
  }

  Team&
  addDefender(const Player& player) {
    defending.push_back(player);
    return *this;
  }

  Team&
  sortLexicographical() {
    std::sort(attacking.begin(), attacking.end(), SortByName{});
    std::sort(defending.begin(), defending.end(), SortByName{});
    return *this;
  }

  std::string
  to_string() const {
    std::stringstream ss;
    ss << "(" << attacking[0] << ", " << attacking[1] << ", " << attacking[2] << ", " << attacking[3] << ", " << attacking[4] << ")" << "\n";
    ss << "(" << defending[0] << ", " << defending[1] << ", " << defending[2] << ", " << defending[3] << ", " << defending[4] << ")";
    return ss.str();
  }
};

class Solution {
public:

  std::string solve(std::vector<Player> players) {
    std::sort(players.begin(), players.end(), SortByAttack{});
    Team team;
    team.addAttacker(players[0])
        .addAttacker(players[1])
        .addAttacker(players[2])
        .addAttacker(players[3])
        .addAttacker(players[4])
        .addDefender(players[5])
        .addDefender(players[6])
        .addDefender(players[7])
        .addDefender(players[8])
        .addDefender(players[9])
        .sortLexicographical();
    return team.to_string();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::string line;
  std::size_t N = getInput();
  std::vector<Player> players = std::vector<Player>(10);

  for (size_t kk = 1; kk <= N; kk++) {
    for (auto ii = 0; ii < 10; ii++) {
      std::cin >> players[ii];
    }
    Solution solution;
    std::cout << "Case " << kk << ":\n" << solution.solve(players) + "\n";
  }

  return(0);
}