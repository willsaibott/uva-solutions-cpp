/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 * uhunt page: https://uhunt.onlinejudge.org/id/899065
 *
 */

#include <bits/stdc++.h>
#include "random.h"

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

template <class T = size_t>
T getinput() {
  T input;
  return (std::cin >> input, std::cin.ignore(), input);
}

inline std::string getln() {
  std::string line;
  return (std::getline(std::cin, line), line);
}

class Solution {
  public:
  std::string solve() { return ""; };
};

int main(int argc, char** argv) {
  std::string line;
  std::size_t N = argc > 1 ? std::stoul(argv[1]) : 10000;
  std::ofstream input{ "./input/2/4/11402" };

  if (input.is_open()) {
    std::cout << "Input file open successfully\n";
    std::cout << "Progress: \n";

    input << N << "\n";
    for (size_t kk = 1; kk <= N; kk++) {
      size_t total_pirates{ 0 };
      size_t M       = kk != 10 ? next_random(1, 100) : 0;
      size_t queries = next_random(1, 1000);
      input << M << "\n";
      for (size_t ii = 0; ii < M; ii++) {
        size_t repeat = kk != 20 ? next_random(1, 200) : 0;
        line = next_random_string(next_random(1, 50), "01");
        input << repeat << "\n";
        input << line << "\n";
        total_pirates += repeat * line.size();
      }

      input << queries << "\n";

      for (size_t ii = 0; ii < queries; ii++) {
        size_t a = next_random(0, total_pirates - 1);
        size_t b = next_random(0, total_pirates - 1);
        input << next_random_char("FEIS") << " " << std::min(a, b) << " " << std::max(a, b) << "\n";
      }

      std::cout << ((double)kk) * 100.0 / N << "%\r";
    }
  }
  else {
    std::cerr << "Unable to open input file.\n";
  }


  return(0);
}