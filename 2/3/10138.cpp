/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 * uhunt page: https://uhunt.onlinejudge.org/id/899065
 *
 */

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <bitset>
#include <utility>
#include <set>
#include <map>
#include <queue>
#include <deque>
#include <stack>
#include <sstream>
#include <cmath>
#include <climits>
#include <cstdlib>
#include <string>
#include <iomanip>
#include <list>

using namespace std;
typedef unsigned char byte;
typedef unsigned long long ull;
typedef long long ll;

struct photo_t {
  std::string name;
  std::string timestamp;
  double      kilometer;
  bool        is_exit{false};

  size_t get_time() const {
    size_t month = std::stoul(timestamp.substr(0, 2)) * 31 * 24 * 3600;
    size_t day   = std::stoul(timestamp.substr(3, 2)) * 24 * 3600;
    size_t hour  = std::stoul(timestamp.substr(6, 2)) * 3600;
    size_t min   = std::stoul(timestamp.substr(9, 2)) * 60;
    return month + day + hour + min;
  }

  bool operator<(const photo_t& other) const {
    return get_time() < other.get_time();
  }
};

class Solution {
  using vehicle_t = std::map<std::string, std::vector<photo_t>>::value_type;
  std::map<std::string, std::vector<photo_t>> _vehicles;
  std::vector<double>                         _toll_price;

  public:

  static constexpr double BANK{2.0};
  static constexpr double BY_TRAVEL{1.0};

  void add_toll_prices(const std::string& toll_prices) {
    stringstream ss{toll_prices};
    int price;
    while (ss >> price) {
      _toll_price.push_back(price / 100.0);
    }
  }

  void add(const std::string& photo_entry) {
    stringstream ss{photo_entry};
    std::string direction;
    photo_t photo;
    while (ss >> photo.name      &&
           ss >> photo.timestamp &&
           ss >> direction       &&
           ss >> photo.kilometer)
    {
      photo.is_exit = direction == "exit";
      _vehicles[photo.name].push_back(photo);
    }
  }

  double
  charge(const vehicle_t& vehicle) {
    double cost{0};
    const auto& points{vehicle.second};
    auto it{ points.begin() };
    auto nit{ std::next(it) };
    while (it != points.end() && nit != points.end()) {
      if (!it->is_exit && nit->is_exit) {
        // valid point
        uint   hour       = std::stoi(it->timestamp.substr(6, 2));
        size_t kilometers = std::abs(it->kilometer - nit->kilometer);
        if (hour < _toll_price.size()) {
          cost += BY_TRAVEL + _toll_price[hour]*kilometers;
        }

        it  = std::next(nit);
        nit = std::next(it);
      }
      else {
        // ignore point
        it++;
        nit++;
      }
    }
    return cost ? cost + BANK : cost;
  }

  void
  solve(std::string&output) {
    static char buffer[1024] = {'\0'};
    for (auto& vehicle : _vehicles) {
      std::sort(vehicle.second.begin(), vehicle.second.end());
      double cost = charge(vehicle);
      if (cost) {
        sprintf(buffer,
                "%s $%.2f\n",
                vehicle.first.data(),
                cost);
        output += buffer;
      }
    }
    output += "\n";
  }
};


int main() {
  string output = "";
  int64_t total;
  std::string line;
  cin >> total;
  cin.ignore(); // \n
  cin.ignore(); // \n
  for (int ii = 0; ii < total; ii++) {
    Solution solution;
    std::getline(cin, line);
    solution.add_toll_prices(line);
    while ((std::getline(cin, line), line.size()) && cin) {
      solution.add(line);
    }
    solution.solve(output);
  }
  output.pop_back();
  printf("%s", output.c_str());

  return(0);
}