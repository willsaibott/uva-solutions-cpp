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

using namespace std;
typedef unsigned char byte;
typedef unsigned long long ull;
typedef long long ll;


struct paper_t {
  int id;
  int priority;

  inline bool
  operator <(const paper_t& other) const {
    return priority < other.priority;
  }

  inline bool
  operator >(const paper_t& other) const {
    return priority > other.priority;
  }
};

struct paper_compare {
  inline bool
  operator ()(const paper_t* first, const paper_t* other) const {
    return *first < *other;
  }
};

int main()
{
  string output = "";
  int total_cases{0};
  int k{0};

  output.reserve(500000);
  cin >> total_cases;
  cin.ignore();

  while(k++ < total_cases && !cin.eof() && cin.good()) {
    std::priority_queue<paper_t> printer_by_priority;
    std::deque<paper_t> printer;
    int n{0}, start_position{0};
    cin >> n >> start_position;

    for (int ii = 0; ii < n; ii++) {
      int priority;
      cin >> priority;
      printer.push_back({ ii, priority });
      printer_by_priority.push(printer.back());
    }

    // Simultation starts...
    int result{0};
    while (printer.size()) {
      const auto& elem {printer.front()};
      if (elem.priority >= printer_by_priority.top().priority) {
        // print it!
        result++;
        if (start_position == elem.id) {
          // We founded it!
          break;
        }
        else {
          // Another element, continue!
          printer.pop_front();
          printer_by_priority.pop();
        }
      }
      else {
        // If elem doesnt have the greatest priority, push it to end of the queue
        printer.pop_front();
        printer.push_back(elem);
      }
    }
    output += std::to_string(result).append("\n");
  }

  printf("%s", output.c_str());

  return(0);
}