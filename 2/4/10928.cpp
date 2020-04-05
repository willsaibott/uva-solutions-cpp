/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 * uhunt page: https://uhunt.onlinejudge.org/id/899065
 *
 */

#include <bits/stdc++.h>

using namespace std;
typedef unsigned char byte;
typedef unsigned long long ull;
typedef long long ll;

namespace std {
template<typename T, typename... Args>
  unique_ptr<T> make_unique(Args&&... args) {
    return unique_ptr<T>(new T(forward<Args>(args)...));
  }
}

class Solution {
  using places_t = std::pair<size_t, std::vector<int>>;
  std::vector<places_t> neighbours;

  public:

  Solution(size_t number_places) {
    neighbours.resize(number_places);
    for (size_t ii = 0; ii < number_places; ii++) {
      neighbours[ii].first = ii+1;
    }
  }

  void add_neighbour(size_t place, int neighbour) {
    if (place < neighbours.size()) {
      neighbours[place].second.push_back(neighbour);
    }
  }

  std::string solve() {
    std::string output;

    std::sort(neighbours.begin(),
              neighbours.end(),
              [] (const places_t& p1, const places_t&p2) {
                int diff { (int)p1.second.size() - (int)p2.second.size() };
                return diff ? diff < 0 : p1.first < p2.first;
              });

    auto best = neighbours.front().second.size();
    for (const auto& place : neighbours) {
      if (place.second.size() > best) {
        break;
      }
      output += std::to_string(place.first) + " ";
    }
    output.pop_back();
    return output;
  };
};

int main() {
  std::string line;
  std::size_t N, places, neighbour;
  std::cin >> N;
  std::cin.ignore();

  for (size_t kk = 1; kk <= N; kk++) {
    Solution solution{( std::cin >> places, places )};
    std::cin.ignore();
    for (size_t ii = 0; ii < places; ii++) {
      std::stringstream ss{ (std::getline(std::cin, line), line) };
      while (ss >> neighbour) {
        solution.add_neighbour(ii, neighbour);
      }
    }
    std::cout << solution.solve() + "\n";
  }

  return(0);
}