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

template <class T = size_t>
T getInput() {
  static T input;
  return (std::cin >> input, std::cin.ignore(), input);
}

struct SocialConstraint {
  size_t member1;
  size_t member2;
  int64_t seats_apart;
};

inline std::istream& operator >>(std::istream& iss, SocialConstraint& constraint) {
  return iss >> constraint.member1 >> constraint.member2 >> constraint.seats_apart;
}

class Solution {
  static std::array<int, 10> group;

  bool has_violations(const std::vector<SocialConstraint>& constraints) {
    for (auto& constraint : constraints) {
      auto it1 = std::find(group.begin(), group.end(), constraint.member1);
      auto it2 = std::find(group.begin(), group.end(), constraint.member2);
      auto distance = std::distance(it1, it2);

      if (constraint.seats_apart > 0) {
        if (std::abs(distance) > constraint.seats_apart) return true;
      }
      else if (constraint.seats_apart < 0) {
        if (std::abs(distance) < std::abs(constraint.seats_apart)) return true;
      }
    }
    return false;
  }

public:

  size_t solve(size_t group_size, const std::vector<SocialConstraint>& constraints) {
    size_t no_violations_of_constraints = 0ul;
    do {
      no_violations_of_constraints += !has_violations(constraints);
    } while (std::next_permutation(group.begin(), group.begin() + group_size));
    return no_violations_of_constraints;
  }
};

std::array<int, 10> Solution::group = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

int main() {
  std::ios_base::sync_with_stdio(false);
  size_t group_size;
  size_t number_of_constraints;

  while (std::cin >> group_size >> number_of_constraints && (group_size || number_of_constraints)) {
    std::vector<SocialConstraint> social_constraints;
    for (auto ii = 0ul; ii < number_of_constraints; ii++) {
      social_constraints.emplace_back(getInput<SocialConstraint>());
    }

    Solution solution;
    std::cout << solution.solve(group_size, social_constraints) << "\n";
  }

  return(0);
}