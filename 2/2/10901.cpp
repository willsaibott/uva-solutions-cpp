/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
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

using namespace std;
typedef unsigned char byte;
typedef unsigned long long ull;
typedef long long ll;

const ll CAR = 1;
const ll LEFT = 0x0;
const ll RIGHT = 0x1;
const ll DIRECTION_MASK = 0x1;

struct Car {
  ll time;
  ll id;
};

template< class T = std::deque<Car>, class B = ll>
void change_direction (T& direction, B&time, const B&t) {
  direction = (direction + 1) & DIRECTION_MASK;
  time += t;
}

template< class T = std::deque<Car>, class B = ll> bool
load_ferry(T& ferry, T&bank, B& current_time, const B&max_cargo) {
  while (bank.size() &&
         current_time >= bank.front().time &&
         ferry.size() < (size_t)max_cargo)
  {
    ferry.push_back(bank.front());
    bank.pop_front();
  }
  return ferry.size();
}

template< class T = std::deque<Car>, class B = ll> void
unload_ferry(T& ferry, B& current_time, std::vector<B>& car_time) {
  while (ferry.size()) {
    car_time[ferry.front().id] = current_time;
    ferry.pop_front();
  }
}

int main() {
  int k = 0;
  int N;
  string output = "";
  bool begin = true;
  string line;

  output.reserve(500000);
  cin >> N;
  cin.ignore();

  const auto NO_VALUE = (ll)1e20;

  while(k++ < N && !cin.eof() && cin.good())
  {
    std::deque<Car> ferry, left, right;
    string command;
    ll direction = 0; // 0: left 1: going right 2:right 3: going left //
    ll n, t , m, time, current_time = 0;
    cin >> n >> t >> m;
    std::vector<ll> car_time(m);
    ll car_id = 0;
    direction = LEFT;
    if (!n) break;
    if (!begin || (begin = false)) output += "\n";
    bool depart = false;
    for (ll ii = 0; ii < m; ii++) {
      cin >> time >> command;
      Car car{time, car_id++};
      if (command == "left") { left.push_back(car);  }
      else                   { right.push_back(car); }
    }

    while (left.size() || right.size()) {
      auto& ferry_location = direction & DIRECTION_MASK ? right : left;
      auto& other_bank     = direction & DIRECTION_MASK ? left  : right;
      auto other_time      = other_bank.size()     ? other_bank.front().time     : NO_VALUE;
      auto location_time   = ferry_location.size() ? ferry_location.front().time : NO_VALUE;
      depart = load_ferry(ferry, ferry_location, current_time, n);
      if (!depart && other_time < location_time) {
        depart       = true;
        current_time = max(other_time, current_time);
      }
      if (depart) {
        change_direction(direction, current_time, t);
        unload_ferry(ferry, current_time, car_time);
      } else {
        current_time = max(location_time, current_time);
      }
    }

    for (auto& time : car_time) {
      output += std::to_string(time).append("\n");
    }
  }

  printf("%s", output.c_str());

  return(0);
}