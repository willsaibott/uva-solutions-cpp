/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 * uhunt page: https://uhunt.onlinejudge.org/id/899065
 *
 */

#include <bits/stdc++.h>
#include "../../advanced_library_cpp/AdvancedLibraryCpp/union_find.h"

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
  advanced::union_find_t<std::string> social_networks;
  size_t                              largest{ 1 };

  public:

  Solution(size_t users) {
    social_networks.reserve(users);
  }

  void add_user(const std::string& user) {
    social_networks.insert(user);
  }

  size_t make_friends(const std::string& A, const std::string& B) {
    if (!social_networks.exists(A)) {
      add_user(A);
    }
    if (!social_networks.exists(B)) {
      add_user(B);
    }
    social_networks.join_sets(A, B);
    return social_networks.size_of(A);
  }

  size_t solve() {
    return largest;
  };
};

int main() {
  std::string line, user_A, user_B;
  std::size_t friendships, cases = getinput();

  for (size_t ii = 0; ii < cases; ii++) {
    Solution solution { friendships = getinput() };
    for (size_t jj = 0; jj < friendships; jj++) {
      user_A = getinput<std::string>();
      user_B = getinput<std::string>();
      std::cout << solution.make_friends(user_A, user_B) << "\n";
    }
  }

  return(0);
}
