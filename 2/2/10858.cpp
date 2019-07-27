/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
// #include "../../lib/divisor.h"

using namespace std;
typedef unsigned char byte;
typedef unsigned long long ull;
typedef long long ll;

std::vector<uint64_t>
divisors_of(uint64_t n, bool sorting = false) {
  std::vector<uint64_t> divisors;
  uint64_t square = std::sqrt(n);
  for(uint64_t ii = 2; ii <= square; ii++) {
    if(n % ii == 0ull) {
      divisors.push_back(ii);
      if(ii * ii != n) {
        divisors.push_back(n / ii);
      }
    }
  }
  if (sorting) {
    std::sort(divisors.begin(), divisors.end());
  }
  return divisors;
}

inline void
unique_factorization_recursive(std::vector<std::vector<uint64_t>>& answer,
                               std::vector<uint64_t>&              divisors,
                               uint64_t                            n,
                               uint64_t                            index,
                               uint64_t                            index_from,
                               uint64_t&                           count)
{
  static std::vector<uint64_t> buffer(10000, 0ull);
  if (n == 1ull) {
    if (answer.size() <= count) {
      answer.push_back(std::vector<uint64_t>());
    }
    for (auto ii = 0ull; ii < index; ii++) {
      answer[count].push_back(buffer[ii]);
    }
    count++;
  } else {
    for (auto ii = index_from; ii < divisors.size(); ii++) {
      auto div      = divisors[ii];
      auto dividend =  n / div;
      if (((dividend >= div) || (n == div)) && (n % div == 0ull)) {
        buffer[index] = div;
        unique_factorization_recursive(answer,
                                       divisors,
                                       dividend,
                                       index + 1,
                                       ii,
                                       count);
      }
    }
  }
}

inline std::string
solve(const uint64_t &n) {
  std::vector<std::vector<uint64_t>> answers;
  // auto divisors = divisor::divisors_of(n, true);
  auto divisors = divisors_of(n, true);
  uint64_t counter = 0ull;

  if (divisors.size()) {
    unique_factorization_recursive(answers, divisors, n, 0ull, 0ull, counter);
  }

  string res = to_string(counter).append("\n");
  for (auto& ans : answers) {
    for (auto& value : ans) {
      res += to_string(value).append(" ");
    }
    res.pop_back();
    res += "\n";
  }
  return res;
}

int main() {
  string output = "";
  string line;

  output.reserve(500000);

  while(cin.good() && !cin.eof()) {
    int n;
    cin >> n;
    cin.ignore();
    if (!n) break;

    output += std::move(solve(n));
  }

  printf("%s", output.c_str());

  return(0);
}