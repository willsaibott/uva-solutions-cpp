/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 * uhunt page: https://uhunt.onlinejudge.org/id/899065
 *
 */

#include <bits/stdc++.h>
#include "../../advanced_library_cpp/AdvancedLibraryCpp/fenwick_tree.h"

using namespace std;
typedef unsigned char byte_t;
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
  using tree_t = advanced::fenwick_tree_t<int>;
  tree_t                     negatives;
  tree_t                     zeroes;
  std::vector<int>           seq_negatives;
  std::vector<int>           seq_zeroes;
  std::vector<int>::iterator sit_nz;
  std::vector<int>::iterator sit_z;

  public:

  Solution(size_t capacity)
    : seq_negatives(capacity, 0), seq_zeroes(capacity, 0)
  {
    clear();
  }

  void
  add_element(int number) {
    *sit_z  = number == 0; sit_z++;
    *sit_nz = number < 0;  sit_nz++;
  }

  void
  modify(size_t pos, int value) {
    // If the element is negative and will be changed to a positve
    if (seq_negatives[pos-1] && value >= 0) {
      // clear the negative
      negatives.update(pos, -1);
    }
    // If the element is positive and will be changed to a negative
    else if (!seq_negatives[pos-1] && value < 0) {
      negatives.update(pos, 1); // mark as negative
    }
    // If the element is zero and will be changed to a non-zero value
    if (seq_zeroes[pos-1] && value != 0) {
      zeroes.update(pos, -1); // clear the zero
    }
    // If the element is non-zero and will be changed to zero
    else if ((!seq_zeroes[pos-1]) && (value == 0)) {
      zeroes.update(pos, 1); // mark as zero
    }
    seq_negatives[pos-1] = value < 0;
    seq_zeroes[pos-1]    = value == 0;
  }

  char
  query(size_t start, size_t end) {
    auto has_zero = zeroes.query(start, end);
    char c = '0';
    if (!has_zero) {
      auto value = negatives.query(start, end);
      c = value & 1 ? '-' : '+';
    }
    return c;
  }

  void
  build() {
    negatives.rebuild(seq_negatives, std::distance(seq_negatives.begin(), sit_nz));
    zeroes.rebuild(seq_zeroes, std::distance(seq_zeroes.begin(), sit_z));
  }

  void
  clear() {
    sit_nz = seq_negatives.begin();
    sit_z  = seq_zeroes.begin();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::string line;
  std::size_t numbers, queries, first;
  Solution solution{ 110000 };
  // size_t kk { 0 };
  char command;
  int second;

  while (std::cin >> numbers >> queries) {
    std::cin.ignore();
    for (size_t ii = 0; ii < numbers; ii++) {
      solution.add_element(getinput<int>());
    }

    solution.build();

    for (size_t ii = 0; ii < queries; ii++) {
      command = getinput<char>();
      first   = getinput();
      second  = getinput<int>();

      switch (command) {
      case 'P': std::cout << solution.query(first, second); break;
      case 'C': solution.modify(first, second);             break;

      default:
        break;
      }
    }
    std::cout << "\n";
    solution.clear();
  }

  return(0);
}