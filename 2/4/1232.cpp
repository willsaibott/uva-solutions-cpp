/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 * uhunt page: https://uhunt.onlinejudge.org/id/899065
 *
 */

#include <bits/stdc++.h>
#include "../../advanced_library_cpp/AdvancedLibraryCpp/binary_tree.h"

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

struct range_t {
  size_t start;
  size_t end;
  size_t height{ 0 };
  bool   full{ true };
  size_t minheight{ 0 };
  size_t maxheight{ 0 };


  range_t()               = default;
  range_t(const range_t&) = default;
  range_t(range_t&&)      = default;
  range_t(size_t left, size_t right, size_t h, bool f) :
    start(left), end(right), height(h), full(f) {

    }

  size_t
  length() const {
    return end - start;
  }

  size_t
  center() const {
    return (end + start) / 2;
  }

  size_t
  overlap(const size_t& other_height) const {
    return other_height >= maxheight ? length() : 0;
  }

  inline bool
  same(const range_t& other) const {
    return start == other.start && end == other.end;
  }
};

class Solution {
  using node_t = advanced::binary_node_t<range_t>;
  using tree_t = advanced::binary_tree_t<range_t>;

  tree_t                           skyline;
  size_t                           buildings;
  size_t                           overlaps{ 0 };

  public:

  Solution(size_t min_left, size_t max_right, size_t max_buildings) :
    skyline( (range_t{ min_left, max_right, 0ul, true }) ),
    buildings{ max_buildings }
  {
    build_node(skyline.root());
  }

  void
  build_node(node_t& node) {
    range_t& range{ node.get() };
    if (range.length() > 1) {
      auto half = (range.start + range.end) / 2;
      node.add_left(range_t{ range.start, half, 0, true });
      node.add_right(range_t{ half, range.end, 0, true });
      build_node(node.left());
      build_node(node.right());
    }
  }

  void fill(node_t& node, size_t height) {
    range_t& range  = node.get();
    range.maxheight = range.minheight = height;
    range.full      = true;
    if (range.length() > 1) {
      fill(node.left(),  height);
      fill(node.right(), height);
    }
  }

  void
  find(node_t& node, size_t left, size_t right, size_t height) {
    range_t& range = node.get();
    if (height < range.minheight)               { return; }
    if (range.full && height < range.maxheight) { return; }

    if (range.start == left && range.end == right && (range.full || height >= range.maxheight)) {
      overlaps        += range.overlap(height);
      if (height > range.minheight) {
        fill(node, std::max(range.maxheight, height));
      }
    }
    else if (range.length() > 1) {
      range_t& rightchild { *(node.right()) };
      range_t& leftchild { *(node.left()) };

      auto center = range.center();
      if (left < center) {
        find(node.left(), left, std::min(center, right), height);
      }

      if (right > center) {
        find(node.right(), std::max(left, center), right, height);
      }

      range.maxheight = std::max(leftchild.maxheight, rightchild.maxheight);
      range.minheight = std::min(leftchild.minheight, rightchild.minheight);
      range.full      = range.maxheight == range.minheight;
    }
  }

  void
  add_building(const range_t& range) {
    find(skyline.root(), range.start, range.end, range.height);
  }

  std::string
  solve() {
    return std::to_string(overlaps) + "\n";
  };
};

int main() {
  std::string line;
  std::size_t number_of_buildings, min_left, max_right, N = getinput();
  range_t r;

  for (size_t ii = 0; ii < N; ii++) {
   if ((number_of_buildings = getinput())) {
      std::vector<range_t> buildings;
      buildings.reserve(number_of_buildings);
      min_left  = 1000000000;
      max_right = 0;

      for (size_t ii = 0; ii < number_of_buildings; ii++) {
        std::cin >> r.start >> r.end >> r.height;
        min_left  = std::min(r.start, min_left);
        max_right = std::max(r.end,   max_right);
        buildings.push_back(r);
      }

      Solution solution{ min_left, max_right, number_of_buildings };

      for (size_t ii = 0; ii < number_of_buildings; ii++) {
        solution.add_building(buildings[ii]);
      }

      std::cout << solution.solve();
    }

  }


  return(0);
}