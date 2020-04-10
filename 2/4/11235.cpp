/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 * uhunt page: https://uhunt.onlinejudge.org/id/899065
 *
 */

#include <bits/stdc++.h>
#include "../../advanced_library_cpp/AdvancedLibraryCpp/segment_tree.h"

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

struct element_t {
  ll     value;
  size_t freq;

  inline bool
  operator<(const element_t&other) const {
    return freq < other.freq;
  }

  inline static element_t
  join(const element_t& one, const element_t& other) {
    return { one.value, one.freq + other.freq };
  }
};

struct node_t {
  element_t left;
  element_t right;
  element_t best;
};

struct transform_t : advanced::segment_node_t<ll, node_t> {

    inline virtual node_t
    join(const std::vector<ll>& array,
         const node_t&          left,
         const node_t&          right) const override
    {
      node_t result;
      if (left.left.value == right.right.value) {
        // full range: left.left ... right.right
        result.left = result.right = result.best =
          element_t::join(left.left, right.right);
      }
      else if (left.left.value == right.left.value) {
        // left.left ... right.left
        result.left  = element_t::join(left.left, right.left);
        result.right = right.right;
        result.best  = std::max(std::max(right.best, left.best), result.left);
      }
      else if (left.right.value == right.right.value) {
        // left.right ... right.right
        result.left  = left.left;
        result.right = element_t::join(left.right, right.right);
        result.best  = std::max(std::max(right.best, left.best), result.right);
      }
      else if (left.right.value == right.left.value) {
        // left.right ... right.left
        auto tmp = element_t::join(left.right, right.left);
        result.right = right.right;
        result.left  = left.left;
        result.best  = std::max(std::max(right.best, left.best), tmp);
      }
      else {
        // left.right != right.left
        // union of two completely separated ranges:
        result.right = right.right;
        result.left  = left.left;
        result.best  = std::max(right.best, left.best);
      }
      return result;
    }

    inline virtual node_t
    build(const ll& element, const size_t& position) const override {
      return { { element, 1 }, { element, 1}, { element, 1} };
    }
};

class Solution {
  using segment_tree_t = advanced::segment_tree_t<ll, node_t, transform_t>;
  segment_tree_t segment_tree;

  public:

  Solution(const std::vector<ll>& array) {
    segment_tree.rebuild(array);
  }

  size_t
  query(size_t start, size_t end) {
    auto elem = segment_tree.query(start, end);
    return elem.best.freq;
  }
};

int main() {
  std::string line;
  std::size_t number_of_elements, number_of_queries, start, end;

  while (std::cin >> number_of_elements >> number_of_queries) {
    std::vector<ll> elements;
    elements.reserve(number_of_elements);

    for (size_t kk = 0; kk < number_of_elements; kk++) {
      elements.push_back(getinput<ll>());
    }

    Solution solution{ elements };

    for (size_t kk = 0; kk < number_of_queries; kk++) {
      start = getinput() - 1;
      end   = getinput() - 1;
      std::cout << solution.query(start, end) << "\n";
    }
  }

  return(0);
}