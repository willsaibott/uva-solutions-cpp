/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
 */

#include <iostream>
#include <vector>
#include <deque>

using namespace std;
typedef unsigned char byte;
typedef unsigned long long ull;
typedef long long ll;

const auto DIRECTION_MASK = 0x1;

struct ferry_t {
  double max, cargo;
};

template <class T = std::deque<double>>
bool
load_ferry(ferry_t& ferry, T& bank) {
  while (bank.size()) {
    if (bank.front() + ferry.cargo <= ferry.max) {
      ferry.cargo += bank.front();
      bank.pop_front();
    } else {
      break;
    }
  }
  return ferry.cargo;
}

template <class T = std::deque<double>>
bool
go_to_another_bank(ferry_t& ferry, ll& counter, uint8_t& direction) {
  ferry.cargo = 0;
  counter++;
  direction = (direction + 1) & DIRECTION_MASK;
  return true;
}

int main()
{
  int k = 0;
  int N;
  string output = "";
  string line;

  output.reserve(500000);
  cin >> N;
  cin.ignore();


  while(k++ < N && !cin.eof() && cin.good())
  {
    uint8_t direction = 0; // left;
    double length;
    ll counter = 0;
    string bank;
    std::deque<double> left, right;
    double l;
    ll m;
    cin >> l >> m;

    ferry_t ferry{l*100.0};

    for (int ii = 0; ii < m; ii++) {
      cin >> length >> bank;
      if (bank == "left") { left.push_back(length); }
      else                { right.push_back(length); }
    }

    while (left.size() || right.size()) {
      bool depart = false;
      auto& curr_bank  = direction & DIRECTION_MASK ? right : left;
      auto& other_bank = direction & DIRECTION_MASK ? left  : right;

      depart = load_ferry(ferry, curr_bank) ||
               (other_bank.size() && other_bank.front() <= ferry.max);

      if (depart) {
        go_to_another_bank(ferry, counter, direction);
      }
    }

    output += to_string(counter).append("\n");
  }

  printf("%s", output.c_str());

  return(0);
}