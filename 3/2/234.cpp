/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 * uhunt page: https://uhunt.onlinejudge.org/id/899065
 *
 */

#include <bits/stdc++.h>

using namespace std;

template <class T = size_t>
T getInput() {
  static T input;
  return (std::cin >> input, std::cin.ignore(), input);
}

struct AlignmentPoint {
  size_t level;
  size_t time;
};

inline std::istream& operator >>(std::istream& iss, AlignmentPoint& align_point) {
  return iss >> align_point.level >> align_point.time;
}

struct SortByTime {
  bool operator ()(const AlignmentPoint& point1, const AlignmentPoint& point2) const {
    return point1.time < point2.time;
  }
};

struct Permutation {
  std::vector<size_t> program_durations;
  std::array<std::size_t, 5> misses_by_level = { 0, 0, 0, 0, 0};

  inline bool operator<(const Permutation& other) const {
    return std::lexicographical_compare(misses_by_level.begin(), misses_by_level.end(),
                                        other.misses_by_level.begin(), other.misses_by_level.end());
  }

  Permutation& compute_points(const std::vector<AlignmentPoint>& alignment_points) {
    size_t elapsed{ 0ull };
    auto program = program_durations.begin();
    for (auto& point : alignment_points) {
      while (program != program_durations.end() && elapsed < point.time) {
        if (elapsed + *program > point.time) {
          misses_by_level[point.level - 1] += point.time - elapsed;
          misses_by_level[point.level - 1] += elapsed + *program - point.time;
        }

        elapsed += *program;
        program++;
      }
    }
    return *this;
  }

  std::string to_string() const {
    std::stringstream ss;
    ss << "Order:";

    for (const auto& program : program_durations) {
      ss << " " << program;
    }

    ss << "\nError: " << std::accumulate(misses_by_level.begin(), misses_by_level.end(), 0);
    return ss.str();
  }
};

class Solution {
public:

  std::string solve(std::vector<size_t> program_durations, std::vector<AlignmentPoint> alignment_points) {
    std::sort(alignment_points.begin(), alignment_points.end(), SortByTime{});
    std::sort(program_durations.begin(), program_durations.end());

    Permutation max_permutation;
    max_permutation.misses_by_level[0] = std::numeric_limits<size_t>::max();

    do {
      Permutation permutation;
      permutation.program_durations = program_durations;
      permutation.compute_points(alignment_points);
      max_permutation = std::min(max_permutation, permutation);
    } while (std::next_permutation(program_durations.begin(), program_durations.end()));

    return max_permutation.to_string();
  };
};


int main() {
  std::ios_base::sync_with_stdio(false);
  size_t data_set{ 1 };
  size_t total_programs;
  size_t total_alignment_points;

  while (std::cin >> total_programs && total_programs) {
    std::vector<size_t> program_durations;
    std::vector<AlignmentPoint> alignment_points;
    Solution solution;

    for (auto ii = 0ul; ii < total_programs; ii++) {
      program_durations.push_back(getInput());
    }

    std::cin >> total_alignment_points;

    for (auto ii = 0ul; ii < total_alignment_points; ii++) {
      AlignmentPoint point;
      std::cin >> point;
      alignment_points.push_back(point);
    }

    std::cout << "Data set " << data_set++ << "\n"
              << solution.solve(program_durations, alignment_points) + "\n";
  }

  return(0);
}