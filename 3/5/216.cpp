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

struct Point {
  int64_t x;
  int64_t y;
};

class Solution {
  using distance_t       = std::vector<std::vector<long double>>;
  using distance_cache_t = std::vector<long double>;
  // using value_cache_t    = std::vector<std::vector<long double>>;
  // using cache_t          = std::vector<value_cache_t>;
  using cache_t          = std::vector<distance_cache_t>;

  std::vector<Point>  computers;
  distance_t          distance;
  size_t              size;
  size_t              max_mask;

  public:

  Solution(size_t size)
    : computers(size, { 0, 0 }),
      distance(size, std::vector<long double>(size, std::numeric_limits<double>::max() )),
      size{ size },
      max_mask((1ull << size ) - 1)
  { }

  void
  set(size_t ii, int64_t x, int64_t y) {
    computers[ii].x = x;
    computers[ii].y = y;
  }

  const distance_t&
  distances() const {
    return distance;
  }

  const std::vector<Point>&
  points() const {
    return computers;
  }

  // long double
  // memoization(size_t            index,
  //             size_t            mask,
  //             long double       summed,
  //             cache_t&          dp,
  //             const distance_t& distance)
  // {
  //   size_t point{ size + 1 };
  //   long double ans{ 0 };
  //   for (size_t ii = 0; ii < size; ii++) {
  //     size_t bit{ 1ull << ii };
  //     if ((mask & bit) == 0) {
  //       point = ii;
  //     }
  //   }

  //   if (point < size) {
  //     auto& ref{ dp[index][point][mask] };
  //     size_t bit{ (1ull << point) };
  //     if (!ref) {
  //       ref = std::min(memoization(index, mask, summed, dp, distance),
  //                      distance[index][point] + memoization(point, mask | bit, summed, dp, distance));
  //     }

  //     ans = ref;
  //   }
  //   else if (mask != max_mask) {
  //     ans = 1000000;
  //   }

  //   return ans;
  // }

  std::vector<size_t>
  solve() {
    cache_t dp(size, distance_cache_t(max_mask + 1, 0));
    std::vector<std::vector<size_t>> next(size, std::vector<size_t>(max_mask+1, 0));
    std::vector<size_t> points;

    for (size_t ii = 0; ii < size; ii++) {
      const auto& x { computers[ii].x };
      const auto& y { computers[ii].y };
      distance[ii][ii] = 0;

      for (size_t jj = ii + 1; jj < size; jj++) {
        const auto& x2{ computers[jj].x };
        const auto& y2{ computers[jj].y };
        const auto dist{ std::hypot(std::abs(x-x2), std::abs(y-y2)) };
        auto& ref1{ distance[ii][jj] };
        auto& ref2{ distance[jj][ii] };

        ref1 = ref2 = dist;
      }
    }

    for (size_t mask = max_mask-1; mask > 0; mask--) {
      for (size_t ii = 0; ii < size; ii++) {
        const auto bit{ (1ull << ii) };
        if (mask & bit) {
          auto& ref{ dp[ii][mask] };
          for (size_t jj = 0; jj < size; jj++) {
            const auto bitj     { 1ull << jj };
            const auto new_mask { mask | bitj };
            if (mask != new_mask) {
              auto& ref2{ dp[jj][new_mask] };
              if (!ref || ref > ref2 + distance[ii][jj]) {
                ref            = ref2 + distance[ii][jj];
                next[ii][mask] = jj;
              }
            }
          }
        }
      }
    }

    size_t min = 0;
    for (size_t ii = 1; ii < size; ii++) {
      const auto bit1{ 1ull << ii  };
      const auto bit2{ 1ull << min };
      if (dp[ii][bit1] < dp[min][bit2]) {
        min = ii;
      }
    }

    size_t current = min;
    size_t mask    = (1ull << min);
    points.push_back(min);
    while (mask != max_mask) {
      points.push_back(next[current][mask]);
      current = next[current][mask];
      mask = mask | (1ull << current);
    }

    return points;
  };
};

int main() {
  std::ios_base::sync_with_stdio(false);
  size_t size;
  size_t cases{ 1 };
  int64_t x, y;

  while (std::cin >> size && size) {
    Solution solution{ size };
    for (size_t ii = 0; ii < size; ii++) {
      std::cin >> x >> y;
      solution.set(ii, x, y);
    }
    const auto& points  { solution.points() };
    const auto& distance{ solution.distances() };
    const auto path = solution.solve();

    std::cout << "**********************************************************\n"
              << "Network #" << cases++ << "\n";

    long double total_distance{ 0.0 };
    for (size_t ii = 1; ii < points.size(); ii++) {
      const auto& point_A{ points[path[ii-1]] };
      const auto& point_B{ points[path[ii]]   };
      long double dist{ distance[path[ii-1]][path[ii]] + 16 };
      std::cout << "Cable requirement to connect ("
                << point_A.x << "," << point_A.y  << ") to ("
                << point_B.x << "," << point_B.y  << ") is "
                << std::setprecision(2) << std::fixed
                << dist << " feet.\n";
      total_distance += dist;
    }

    std::cout << "Number of feet of cable required is "
              << std::setprecision(2) << std::fixed
              << total_distance << ".\n";
  }

  return(0);
}