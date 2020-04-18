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

enum pirate_t {
  nothing = 0,
  barbary,
  buccaneer,
  invert,
};

struct update_t : advanced::empty_update_t {
  pirate_t pirate{ pirate_t::nothing };

  update_t(size_t s, size_t e, pirate_t p)
    : advanced::empty_update_t{ s, e }, pirate{ p }
  { }

  update_t() : update_t{ 0, 0, pirate_t::nothing } { }
  update_t(const update_t& other)               = default;
  update_t(update_t&& other) noexcept           = default;
  update_t&operator=(const update_t& other)     = default;
  update_t&operator=(update_t&& other) noexcept = default;

  inline operator
  bool() const {
    return static_cast<bool>(pirate);
  }
};

struct range_t {
  size_t barbaries;
  size_t buccaneer;

  range_t() : barbaries{0}, buccaneer{0} { }
  range_t(size_t bar, size_t buc)
    : barbaries{bar}, buccaneer{buc}
  { }

  range_t(const range_t& other)               = default;
  range_t(range_t&& other) noexcept           = default;
  range_t&operator=(const range_t& other)     = default;
  range_t&operator=(range_t&& other) noexcept = default;
};

class Solution {

  public:
  struct transform_t;
  using tree_t = advanced::segment_tree_t<pirate_t, range_t, transform_t, update_t>;

  Solution(size_t total_pirates) : pirates(total_pirates, pirate_t::barbary) {
    pit = pirates.begin();
  }

  void
  describe(const std::string& line) {
    for (const auto& c : line) {
      *pit = static_cast<pirate_t>(c- '0' + 1); pit++;
    }
  }

  void
  build() {
    seg_tree.rebuild(pirates, std::distance(pirates.begin(), pit));
  }

  void
  mutate(pirate_t pirate, size_t start, size_t end) {
    seg_tree.query_update(start, end, update_t{ start, end, pirate });
  }

  void
  invert(size_t start, size_t end) {
    mutate(pirate_t::invert, start, end);
  }

  size_t
  query(size_t start, size_t end) {
    auto range = seg_tree.query(start, end);
    return range.buccaneer;
  }

  void
  clear() {
    pit = pirates.begin();
  }

  private:
  static tree_t                   seg_tree;
  std::vector<pirate_t>           pirates;
  std::vector<pirate_t>::iterator pit;
};

Solution::tree_t Solution::seg_tree;

struct Solution::transform_t : advanced::segment_node_t<pirate_t, range_t, transform_t, update_t> {
  using base_class = advanced::segment_node_t<pirate_t, range_t, transform_t, update_t>;
  using node_t     = base_class::node_t;
  /**
   * method to be called when two nodes, left and right have their values
   * combined in the parent.
   * parent has the sum of barbaries and buccaneers
   */
  virtual void
  join(range_t&       parent,
       const range_t& left,
       const range_t& right) const override
  {
    parent.barbaries = left.barbaries + right.barbaries;
    parent.buccaneer = left.buccaneer + right.buccaneer;
  }

  /**
   * leaf node: { 1, 0 } if barbary, { 0, 1 } if buccaneer
   */
  virtual void
  build(range_t& node, const pirate_t& element, const size_t& position) const override {
    node.barbaries = (size_t)(element == pirate_t::barbary);
    node.buccaneer = (size_t)(element == pirate_t::buccaneer);
  }

  /**
   * Method called when the current node has lazy updates and must propagate
   * them to children. This is logic dependent.
   * Just apply the modifications in the children nodes
   */
  virtual void
  propagate(node_t& parent, node_t& left, node_t& right) const override {
    auto& change{ parent.lazy_update };
    apply(left, change);
    apply(right, change);
    change.pirate = pirate_t::nothing;
    change.start  = parent.start;
    change.end    = parent.end;
  }

  /**
   * It defines the rules of multiple changes combinated into a single one
   */
  static pirate_t
  combine(pirate_t old_value, pirate_t new_value) {
    switch (new_value) {
      case pirate_t::barbary:
      case pirate_t::buccaneer:
      case pirate_t::nothing:
        return new_value;
      case pirate_t::invert:
      {
        switch(old_value) {
          case pirate_t::barbary:   return pirate_t::buccaneer;
          case pirate_t::buccaneer: return pirate_t::barbary;
          case pirate_t::nothing:   return pirate_t::invert;
          case pirate_t::invert:    return pirate_t::nothing;
          default:
            std::cerr << "Impossible\n";
          break;
        }
        break;
      }
      default:
       std::cerr << "Impossible\n";
      break;
    }
    return pirate_t::nothing;
  }

  /**
   * It apply changes on the range, and save the change as a lazy update.
   */
  virtual void
  apply(node_t& node, const update_t& other) const override {
    if (other.pirate == pirate_t::invert) {
      invert(node.value);
    }
    else if (other.pirate != pirate_t::nothing) {
      update(node.value, node.start, node.end, other.pirate);
    }
    node.lazy_update.pirate = node.leaf() ?
                              pirate_t::nothing :
                              combine(node.lazy_update.pirate, other.pirate);
    node.lazy_update.start  = node.start;
    node.lazy_update.end    = node.end;
  }

  /**
   * mark the range as barbary or buccaneer
   */
  static void
  update(range_t&       range,
        const size_t&   start,
        const size_t&   end,
        const pirate_t& pirate)
  {
    if (pirate == pirate_t::barbary) {
      range.barbaries = (end+1) - start;
      range.buccaneer = 0;
    }
    else if (pirate == pirate_t::buccaneer) {
      range.buccaneer = (end+1) - start;
      range.barbaries = 0;
    }
  }

  /**
   * invert the count of barbaries and buccaneers
   */
  static void
  invert(range_t& range) {
    std::swap(range.barbaries, range.buccaneer);
  }
};

int main() {
  std::string line;
  std::size_t N = getinput(), queries, start, end, total_repetitions, local_repeat;
  Solution solution{ 1025000 };
  char command;

  for (size_t kk = 1; kk <= N; kk++) {
    std::cout << "Case " << kk << ":\n";
    size_t query_counter{ 1 };

    total_repetitions = getinput();
    for (size_t ii = 0; ii < total_repetitions; ii++) {
      local_repeat = getinput();
      line         = getln();
      for (size_t jj = 0; jj < local_repeat; jj++) {
        solution.describe(line);
      }
    }

    solution.build();

    queries = getinput();
    for (size_t ii = 0; ii < queries; ii++) {
      command = getinput<char>();
      start   = getinput();
      end     = getinput();

      switch (command)
      {
      case 'F': solution.mutate(pirate_t::buccaneer, start, end); break;
      case 'E': solution.mutate(pirate_t::barbary,   start, end); break;
      case 'I': solution.invert(start, end);                      break;
      case 'S':
        std::cout << "Q" << query_counter++ << ": "
                  << solution.query(start, end) << "\n";
        break;
      default: break;
      }
    }
    solution.clear();
  }

  return(0);
}
