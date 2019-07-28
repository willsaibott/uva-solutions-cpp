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

struct station_t {
  std::deque<ull> platform_A;
  std::deque<ull> platform_B;
};

int main()
{
  int k = 0, N;
  string output = "";
  const ull transition_time = 2;
  const ull operation_time = 1;

  output.reserve(500000);
  cin >> N;
  cin.ignore();

  while(k++ < N && !cin.eof() && cin.good())
  {
    size_t number_of_stations, carrier_capacity, max_queue_size,
           total_cargos = 0, delivered_cargos = 0;
    cin >> number_of_stations >> carrier_capacity >> max_queue_size;

    std::vector<station_t> stations(number_of_stations);
    std::deque<ull> carrier_queue;
    for (auto& station : stations) {
      int cargos, destination;
      cin >> cargos;
      for (int ii = 0; ii < cargos; ii++) {
        cin >> destination;
        station.platform_B.push_back(destination-1);
        total_cargos++;
      }
    }

    ull time_spent = 0;
    ull carrier_position = 0;
    while (delivered_cargos < total_cargos) {
      auto& station = stations[carrier_position];
      time_spent += transition_time;
      // unloading
      while (carrier_queue.size() && delivered_cargos < total_cargos) {
        if (carrier_position == carrier_queue.back()) {
          delivered_cargos++;
        }
        else if (station.platform_B.size() < max_queue_size) {
          station.platform_B.push_back(carrier_queue.back());
        }
        else break;
        carrier_queue.pop_back();
        time_spent += operation_time;
      }
      // loading
      while (station.platform_B.size()) {
        if (carrier_queue.size() >= carrier_capacity) break;

        carrier_queue.push_back(station.platform_B.front());
        station.platform_B.pop_front();
        time_spent += operation_time;
      }
      carrier_position = (carrier_position+1) % number_of_stations;
    }
    output.append(to_string(time_spent-transition_time)).append("\n");
  }

  printf("%s", output.c_str());

  return(0);
}