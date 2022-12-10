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

template <class T = size_t>
T getinput() {
  static T input;
  return (std::cin >> input, std::cin.ignore(), input);
}

inline const std::string& getln() {
  static std::string line;
  return (std::getline(std::cin, line), line);
}

template <int N, int P, int Q>
struct DynamicProgramming {

  /// @brief if shortest is in the middle, when we "exclude" myself, to recursively calculate the next combinations,
  /// we have (N-1), P and Q remains the same becausethe shortest can be in any position from next to the end.
  static const std::int64_t shortestInMiddle = (N >= 2) ? DynamicProgramming<N - 1, P, Q>::combinations * (N - 2) : 0;

  /// @brief if shortest is the first, when we "exclude" myself, to recursively calculate the next combinations, we have (P - 1) and (N-1)
  static const std::int64_t shortestAtFirst = (N >= 2) ? DynamicProgramming<N - 1, P - 1, Q>::combinations : 0;

  /// @brief if shortest is the last, when we "exclude" myself, to recursively calculate the next combinations, we have (Q - 1) and (N-1)
  static const std::int64_t shortestAtEnd = (N >= 2) ? DynamicProgramming<N - 1, P, Q - 1>::combinations : 0;

  /// @brief  Sum of combinations when consifering the next people in queue (Excluding myself)
  static const std::int64_t combinations = shortestInMiddle + shortestAtFirst + shortestAtEnd;
};

template <>
struct DynamicProgramming<1, 1, 1> {
  /// @brief only 1 chance of this hapenning
  static const std::int64_t combinations = 1ll;
};

template <int P, int Q>
struct DynamicProgramming<1, P, Q> {
  /// @brief impossible scenario
  static const std::int64_t combinations = 0ll;
};

// static DynamicProgramming<13, 13, 13> preCalculation;

template <int N, int peopleFromStart>
static std::int64_t mapNPQ(int peopleFromEnd) {
  switch (peopleFromEnd) {
    case 1:   return DynamicProgramming<N, peopleFromStart, 1>::combinations;
    case 2:   return DynamicProgramming<N, peopleFromStart, 2>::combinations;
    case 3:   return DynamicProgramming<N, peopleFromStart, 3>::combinations;
    case 4:   return DynamicProgramming<N, peopleFromStart, 4>::combinations;
    case 5:   return DynamicProgramming<N, peopleFromStart, 5>::combinations;
    case 6:   return DynamicProgramming<N, peopleFromStart, 6>::combinations;
    case 7:   return DynamicProgramming<N, peopleFromStart, 7>::combinations;
    case 8:   return DynamicProgramming<N, peopleFromStart, 8>::combinations;
    case 9:   return DynamicProgramming<N, peopleFromStart, 9>::combinations;
    case 10:  return DynamicProgramming<N, peopleFromStart, 10>::combinations;
    case 11:  return DynamicProgramming<N, peopleFromStart, 11>::combinations;
    case 12:  return DynamicProgramming<N, peopleFromStart, 12>::combinations;
    case 13:  return DynamicProgramming<N, peopleFromStart, 13>::combinations;
  }
  return 0;
}

template <int N>
static std::int64_t mapNP(int peopleFromStart, int peopleFromEnd) {
  switch (peopleFromStart) {
    case 1:  return mapNPQ<N, 1>(peopleFromEnd);
    case 2:  return mapNPQ<N, 2>(peopleFromEnd);
    case 3:  return mapNPQ<N, 3>(peopleFromEnd);
    case 4:  return mapNPQ<N, 4>(peopleFromEnd);
    case 5:  return mapNPQ<N, 5>(peopleFromEnd);
    case 6:  return mapNPQ<N, 6>(peopleFromEnd);
    case 7:  return mapNPQ<N, 7>(peopleFromEnd);
    case 8:  return mapNPQ<N, 8>(peopleFromEnd);
    case 9:  return mapNPQ<N, 9>(peopleFromEnd);
    case 10:  return mapNPQ<N, 10>(peopleFromEnd);
    case 11:  return mapNPQ<N, 11>(peopleFromEnd);
    case 12:  return mapNPQ<N, 12>(peopleFromEnd);
    case 13:  return mapNPQ<N, 13>(peopleFromEnd);
  }
  return 0;
}

static std::int64_t getCombinationsFor(int n, int peopleFromStart, int peopleFromEnd) {
  switch (n) {
    case 1:  return mapNP<1>(peopleFromStart, peopleFromEnd);
    case 2:  return mapNP<2>(peopleFromStart, peopleFromEnd);
    case 3:  return mapNP<3>(peopleFromStart, peopleFromEnd);
    case 4:  return mapNP<4>(peopleFromStart, peopleFromEnd);
    case 5:  return mapNP<5>(peopleFromStart, peopleFromEnd);
    case 6:  return mapNP<6>(peopleFromStart, peopleFromEnd);
    case 7:  return mapNP<7>(peopleFromStart, peopleFromEnd);
    case 8:  return mapNP<8>(peopleFromStart, peopleFromEnd);
    case 9:  return mapNP<9>(peopleFromStart, peopleFromEnd);
    case 10: return mapNP<10>(peopleFromStart, peopleFromEnd);
    case 11: return mapNP<11>(peopleFromStart, peopleFromEnd);
    case 12: return mapNP<12>(peopleFromStart, peopleFromEnd);
    case 13: return mapNP<13>(peopleFromStart, peopleFromEnd);
  }
  return 0;
}


class Solution {
public:

  std::string solve(int n, int peopleFromStart, int peopleFromEnd) {
    return std::to_string(getCombinationsFor(n, peopleFromStart, peopleFromEnd));
  };

};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::string line;
  std::size_t N = getinput();

  int n, p, q;
  for (size_t kk = 1; kk <= N; kk++) {
    Solution solution;
    std::cin >> n >> p >> q;
    std::cout << solution.solve(n, p, q) + "\n";
  }

  return(0);
}