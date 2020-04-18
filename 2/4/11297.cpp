/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 * uhunt page: https://uhunt.onlinejudge.org/id/899065
 *
 */

#include <bits/stdc++.h>
#include "../../advanced_library_cpp/AdvancedLibraryCpp/tree.h"


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

inline std::string
getln() {
  std::string line;
  return (std::getline(std::cin, line), line);
}

struct region_t {
  size_t x, y;
  size_t population;

  inline bool
  operator<(const region_t& other) const {
    return x != other.x ? x < other.x : y < other.y;
  }

  inline bool
  operator>(const region_t& other) const {
    return x != other.x ? x > other.x : y > other.y;
  }

  inline bool
  operator()(const region_t& other) const {
    return x != other.x ? x < other.x : y < other.y;
  }
};

struct quad_type {
  size_t x1, x2;
  size_t y1, y2;
  int64_t population;

  std::vector<region_t>   lazy_changes;
  size_t                  max_population{ 0 };
  size_t                  min_population{ 0 };

  inline bool
  operator==(const quad_type& other) const {
    return x1 == other.x1 && x2 == other.x2 && y1 == other.y1 && y2 == other.y2;
  }

  inline std::pair<size_t, size_t>
  center() const {
    return { (x2 + x1) / 2, (y2 + y1) / 2 };
  }

  size_t size() {
    return (y2 + 1 - y1) * (x2 + 1 - x1);
  }

  quad_type()                                      = default;
  quad_type(const quad_type& other)                = default;
  quad_type(quad_type&& other) noexcept            = default;
  quad_type& operator=(const quad_type& other)     = default;
  quad_type& operator=(quad_type&& other) noexcept = default;

  quad_type(size_t x1, size_t x2, size_t y1, size_t y2, int64_t population = 0)
    : x1{ x1 }, x2{ x2 }, y1{ y1 }, y2{ y2 }, population{ population } { }
};

class Solution {
  using node_type_t = advanced::tree_node_t<quad_type, 4>;
  using tree_t      = advanced::tree_t<quad_type, node_type_t>;

  tree_t         quad_tree;
  size_t         grid_x;
  size_t         grid_y;
  std::vector<std::vector<size_t>> matrix;

  void build(node_type_t&node) {
    auto& current{ node.get() };
    std::pair<size_t, size_t> center { current.center() };

    if (current.size() > 1) {
      node.add_child({ current.x1,       center.first, current.y1,        center.second });
      node.add_child({ current.x1,       center.first, center.second + 1, current.y2    });
      node.add_child({ center.first + 1, current.x2,   current.y1,        center.second });
      node.add_child({ center.first + 1, current.x2,   center.second + 1, current.y2    });
      build(node.child(0));
      build(node.child(1));
      build(node.child(2));
      build(node.child(3));
      current.min_population = std::min({ node.child(0).get().min_population,
                                          node.child(1).get().min_population,
                                          node.child(2).get().min_population,
                                          node.child(3).get().min_population });
      current.max_population = std::max({ node.child(0).get().max_population,
                                          node.child(1).get().max_population,
                                          node.child(2).get().max_population,
                                          node.child(3).get().max_population });
    }
    else if (current.x2 == current.x1 && current.y1 == current.y2) {
      current.min_population = current.max_population = matrix[current.x1][current.y1];
    }
    else {
      current.min_population = std::numeric_limits<size_t>::max();
      current.max_population = std::numeric_limits<size_t>::min();
    }
  }

  std::pair<int64_t, int64_t>
  query(node_type_t& node, const quad_type& region) {
    std::pair<int64_t, int64_t> response {
      std::numeric_limits<int64_t>::min(),
      std::numeric_limits<int64_t>::max()
    };
    auto& current{ node.get() };
    // invalid child
    if (current.y2 < current.y1 || current.x2 < current.x1) { return response; }

    if (current == region && current.lazy_changes.empty()) {
      response.first  = current.max_population;
      response.second = current.min_population;
    }
    else if (current.size() > 1) {
      std::pair<size_t, size_t> center { current.center() };

      // first quadrant [0 X]
      //                [X X]
      if (region.x1 <= center.first && region.y1 <= center.second) {
        quad_type quad{ region.x1, std::min(center.first,  region.x2),
                        region.y1, std::min(center.second, region.y2) };
        auto child_result = query(node.child(0), quad);
        response.first    = std::max(response.first,  child_result.first);
        response.second   = std::min(response.second, child_result.second);
      }
      // second quadrant [X O]
      //                 [X X]
      if (region.x1 <= center.first && region.y2 > center.second) {
        quad_type quad{ region.x1, std::min(center.first, region.x2),
                        std::max(center.second + 1, region.y1), region.y2 };
        auto child_result = query(node.child(1), quad);
        response.first    = std::max(response.first,  child_result.first);
        response.second   = std::min(response.second, child_result.second);
      }
      // third quadrant [X X]
      //                [O X]
      if (region.x2 > center.first && region.y1 <= center.second) {
        quad_type quad{ std::max(center.first + 1, region.x1), region.x2,
                        region.y1, std::min(center.second, region.y2) };
        auto child_result = query(node.child(2), quad);
        response.first    = std::max(response.first,  child_result.first);
        response.second   = std::min(response.second, child_result.second);
      }
      // fourth quadrant [X X]
      //                 [X O]
      if (region.x2 > center.first && region.y2 > center.second) {
        quad_type quad{ std::max(center.first  + 1, region.x1), region.x2,
                        std::max(center.second + 1, region.y1), region.y2 };
        auto child_result = query(node.child(3), quad);
        response.first    = std::max(response.first,  child_result.first);
        response.second   = std::min(response.second, child_result.second);
      }

      current.min_population = minimum_of(node);
      current.max_population = maximum_of(node);
    }
    return response;
  }

  void
  update(node_type_t& node, const region_t& change) {
    auto& quad{ node.get() };
    if (quad.size() == 1) {
      quad.min_population = quad.max_population = change.population;
    }
    else {
      std::pair<size_t, size_t> center { quad.center() };
      if (change.x <= center.first && change.y <= center.second) {
        update(node.child(0), change);
      }
      if (change.x <= center.first && change.y > center.second) {
        update(node.child(1), change);
      }
      if (change.x > center.first && change.y <= center.second) {
        update(node.child(2), change);
      }
      if (change.x > center.first && change.y > center.second) {
        update(node.child(3), change);
      }
      quad.min_population = std::min({ node.child(0).get().min_population,
                                       node.child(1).get().min_population,
                                       node.child(2).get().min_population,
                                       node.child(3).get().min_population });
      quad.max_population = std::max({ node.child(0).get().max_population,
                                       node.child(1).get().max_population,
                                       node.child(2).get().max_population,
                                       node.child(3).get().max_population });
    }
  }

  size_t
  minimum_of(node_type_t& node) {
    auto& quad{ node.get() };
    size_t minimum{ std::numeric_limits<size_t>::max() };
    if (quad.size() == 1 || quad.lazy_changes.empty()) {
      minimum = quad.min_population;
    }
    else {
      minimum = std::min({ minimum_of(node.child(0)),
                           minimum_of(node.child(1)),
                           minimum_of(node.child(2)),
                           minimum_of(node.child(3))});
    }
    return minimum;
  }

  size_t
  maximum_of(node_type_t& node) {
    auto& quad{ node.get() };
    size_t maximum{ std::numeric_limits<size_t>::min() };
    if (quad.size() == 1 || quad.lazy_changes.empty()) {
      maximum = quad.max_population;
    }
    else {
      maximum = std::max({ maximum_of(node.child(0)),
                           maximum_of(node.child(1)),
                           maximum_of(node.child(2)),
                           maximum_of(node.child(3))});
    }
    return maximum;
  }

  void
  update_propagate(node_type_t& node) {
    auto& quad{ node.get() };
    for (const auto& change : quad.lazy_changes) {
      std::pair<size_t, size_t> center { quad.center() };
      if (change.x <= center.first && change.y <= center.second) {
        update(node.child(0), change);
      }
      if (change.x <= center.first && change.y > center.second) {
        update(node.child(1), change);
      }
      if (change.x > center.first && change.y <= center.second) {
        update(node.child(2), change);
      }
      if (change.x > center.first && change.y > center.second) {
        update(node.child(3), change);
      }
    }
    quad.lazy_changes.clear();
  }

  public:

  Solution(size_t sizex, size_t sizey)
    : quad_tree( quad_type{ 0ul, sizex - 1, 0ul, sizey - 1, 0ll } ),
      grid_x{ sizex },
      grid_y{ sizey },
      matrix( sizex, std::vector<size_t>(sizey, 0) )
  {
  }

  void
  add_region(const region_t& region) {
    matrix[region.x][region.y] = region.population;
  }

  void build() {
    build(quad_tree.root());
  }

  std::string
  query(const quad_type& region) {
    auto result { query(quad_tree.root(), region) };
    return std::to_string(result.first) + " " + std::to_string(result.second) + "\n";
  }

  void
  update(const region_t& region) {
    update(quad_tree.root(), region);
  }

  std::string solve() { return ""; };
};

int main() {
  std::string line;
  std::size_t regions, queries;
  region_t    region;
  quad_type   quadrant;
  char        command;

  while (std::cin >> regions) {
    Solution solution{ regions, regions };
    for (size_t ii = 0; ii < regions; ii++) {
      for (size_t jj = 0; jj < regions; jj++) {
        solution.add_region({ ii, jj, getinput() });
      }
    }

    solution.build();

    if (std::cin >> queries) {
      for (size_t ii = 0; ii < queries; ii++) {
        command = getinput<char>();
        if (command == 'q') {
          quadrant.x1 = getinput() - 1;
          quadrant.y1 = getinput() - 1;
          quadrant.x2 = getinput() - 1;
          quadrant.y2 = getinput() - 1;
          std::cout << solution.query(quadrant);
        }
        else if (command == 'c') {
          region.x          = getinput() - 1;
          region.y          = getinput() - 1;
          region.population = getinput();
          solution.update(region);
        }
        else {
          std::cerr << "Invalid command\n";
        }
      }
    }
  }

  return(0);
}