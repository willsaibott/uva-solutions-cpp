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

struct MovieSignature {
  std::size_t index;
  std::string signature;

  inline bool operator <(const MovieSignature& other) const {
    if (signature.size() != other.signature.size()) {
      return signature.size() > other.signature.size();
    }
    return index < other.index;
  }
};

class Solution {
  std::size_t min_hamming_distance = std::numeric_limits<std::size_t>::max();
  std::size_t min_index = std::numeric_limits<std::size_t>::max();

  size_t
  calculate_hamming_distance_for_substring(const std::string& movie, size_t startBit, const std::string& clip_signature)
  {
    std::size_t hamming_distance = 0ul;
    for (auto bit = 0ul; bit < clip_signature.size(); bit++) {
      hamming_distance += movie[startBit + bit] != clip_signature[bit];
    }
    return hamming_distance;
  }

public:

  size_t calculate_hamming_distance(const std::string& movie, const std::string& clip_signature) {
    const auto offset = 1ul + movie.size() - clip_signature.size();
    std::size_t hamming_distance = std::numeric_limits<std::size_t>::max();
    for (auto ii = 0ul; ii < offset; ii++) {
      hamming_distance =
          std::min(calculate_hamming_distance_for_substring(movie, ii, clip_signature), hamming_distance);
    }
    return hamming_distance;
  }

  size_t
  solve(const std::vector<MovieSignature>& movies, const std::string& clip_signature) {
    for (auto index = 0ul; index < movies.size(); index++) {
      const auto& movie = movies[index];
      if (movie.signature.size() < clip_signature.size()) continue;

      std::size_t hamming_distance = calculate_hamming_distance(movie.signature, clip_signature);
      if (hamming_distance < min_hamming_distance) {
        min_hamming_distance = hamming_distance;
        min_index = index + 1;
      }
    }

    return min_index;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::size_t total_movie_signatures = getInput();
  std::size_t total_clip_signatures = getInput();
  std::string signature;
  std::vector<MovieSignature> movies;

  for (size_t kk = 1; kk <= total_movie_signatures; kk++) {
    std::cin >> signature;
    movies.emplace_back(MovieSignature{ kk, signature });
  }

  for (size_t kk = 1; kk <= total_clip_signatures; kk++) {
    std::cin >> signature;

    Solution solution;
    std::cout << solution.solve(movies, signature) << "\n";
  }

  return(0);
}