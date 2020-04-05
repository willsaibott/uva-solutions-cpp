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

namespace advanced {
/**
 * Implementation of union find generic data structure
 */
class union_set_t {
  std::vector<std::pair<size_t, size_t>> _items;
  std::vector<size_t>                    _ranks;
  std::vector<ll>                        _balance;
  size_t                                 _disjoint{ 0 };
  size_t                                 _acorn{ 0 };
  bool                                   _apply_compression{ true };

public:

  /// Default not found value for find
  static const size_t not_found{ static_cast<size_t>(-1l) };

  /**
   * Default constructor { capacity: 32, apply_compression: true }
   */
  union_set_t() : union_set_t{ 32 } {}

  /**
   * @param capacity          initial union set size
   * @param apply_compression whether apply or not compression
   */
  union_set_t(const size_t& capacity, bool apply_compression = true) :
    _apply_compression{ apply_compression }
  {
    resize(capacity);
  }

  /**
   * Resizes the union set if the size is greater than the current size
   */
  bool resize(const size_t& size) {
    size_t old_size{ _items.size()   };
    bool resizable { size > old_size };
    if (resizable) {
      _items.resize(size);
      _ranks.resize(size);
      _balance.resize(size);
      for (size_t ii = old_size; ii < size; ii++) {
        insert(ii);
      }
    }
    return resizable;
  }

  /**
   * It'll insert an element into the union set
   * @return "true" if the element doesn't exist in the map, "false" otherwise
   */
  bool insert(const size_t& elem) {
    bool can_be_inserted { exists(elem) };
    if (can_be_inserted) {
      _ranks[elem] = 1;
      _items[elem] = { elem, elem };
      _disjoint++;
      _acorn++;
    }
    return !can_be_inserted;
  }

  bool set_balance(size_t elem, ll balance) {
    bool success{ exists(elem) };
    if (success) {
      _balance[elem] = balance;
    }
    return success;
  }

  /**
   * @param (set) set id
   * @return whether the given set exists or not in the union set
   */
  bool exists(const size_t& set) const {
    return set < _items.size();
  }

  /**
   * @param (first)  first  set
   * @param (second) second set
   * @return whether the sets have the same root or not
   * @note It'll call find methods internally, so it may apply
   * "path compression"
   * @see Please see find for more information
   */
  bool same(const size_t& first, const size_t& second) {
    return exists(first) && exists(second) && _same_set(first, second);
  }

  /**
   * @param (set) set id
   * @return the root set
   * @note It'll call find methods internally, so it may apply
   * "path compression". It means it'll make all possible children nodes to be
   * linked/joined to the root.
   */
  size_t find(const size_t& set) {
    if (!exists(set)) {
      return not_found;
    }
    return _find(set);
  }

  /**
   * @param (first)  first  set
   * @param (second) second set
   * @return whether the sets could be joined
   */
  bool join(const size_t& first, const size_t& second) {
    return exists(first)  &&
           exists(second) &&
           _join(_find(first), _find(second));
  }

  /**
   * @return the number of disjoint sets in the union set
   */
  size_t disjoint() const {
    return _disjoint;
  }

  /**
   * @return the number of sets that has no parent
   */
  size_t acorn() const {
    return _acorn;
  }

  /**
   * @param set_id id of the set
   * @return the number of sets that are joined in this set
   */
  size_t size_of(size_t set_id) {
    auto root = find(set_id);
    return root != not_found ? _ranks[root] : 0;
  }

  ll balance_of(size_t id) {
    auto root = find(id);
    return root != not_found ? _balance[root] : 0;
  }

private:

  /**
   * Internal function
   * @param (set) set id
   * @return the root set
   * It'll make all possible children nodes to be linked/joined to the root.
   */
  size_t _find(const size_t& elem) {
    size_t& parent      { _items[elem].second };
    size_t& rank        { _ranks[elem]        };
    size_t& parent_rank { _ranks[parent]      };
    size_t  root        { not_found           };
    auto& balance       { _balance[elem]      };
    auto& parent_balance{ _balance[parent]    };

    if (elem == parent) {
      // End of recursion
      root = elem;
    }
    else {
      if (_apply_compression) {
        // Propagate it
        root = _find(parent);
        if (root != parent) {
          // Applying compression...
          if (parent_rank > 1) {
            // parent isn't compressed yet, so remove my height from it
            parent_rank    -= rank;
            parent_balance -= balance;
          }
          else {
            // parent is already compressed, so my height is already in the root
            // then, zero it temporarily to not count it twice.
            rank    = 0;
            balance = 0;
          }
          _join_set(elem, root);
        }
        // I'm a slave of the root now
        rank    = 1;
        balance = 0;
      }
      else {
        // Propagate it
        root = _find(parent);
      }
    }
    return root;
  }

  /**
   * @param (first)  first  set
   * @param (second) second set
   * @return whether the sets have the same root or not
   * @note It'll call find methods internally, so it may apply
   * "path compression"
   * @see Please see find for more information
   */
  bool _same_set(const size_t& first, const size_t& second) {
    return first == second || _find(first) == _find(second);
  }

  /**
   * @param (first)  first  set
   * @param (second) second set
   * @return whether the sets could be joined
   */
  bool _join(const size_t& first, const size_t& second) {
    auto first_rank  { _ranks[first]            };
    auto second_rank { _ranks[second]           };
    bool same        { _same_set(first, second) };
    if (!same) {
      // The chosen master will be the node which has the greater rank/height
      if (first_rank <= second_rank) {
        _join_set(first, second);
      }
      else {
        _join_set(second, first);
      }
      _disjoint--;
      _acorn -= static_cast<size_t>(!first_rank) +
                static_cast<size_t>(!second_rank);
    }
    return !same;
  }

  /**
   * @param (slave)  set to be joined
   * @param (master) set to join
   */
  void _join_set(const size_t& slave, const size_t& master) {
    auto& slave_rank    { _ranks[slave]  };
    auto& slave_balance { _balance[slave] };
    auto& master_rank   { _ranks[master] };
    auto& master_balance{ _balance[master] };

    _items[slave].second = master;
    master_rank    += slave_rank;
    master_balance += slave_balance;
  }
};

}


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
  advanced::union_set_t people;
  size_t                population;
  std::vector<ll>       balance;

  public:

  Solution(size_t population)
    : people{ population },
      population{ population },
      balance(population, 0) { }

  void set_balance_of(size_t person, ll value) {
    balance[person] = value;
    people.set_balance(person, value);
  }

  void make_friends(size_t A, size_t B) {
    people.join(A, B);
  }

  std::string solve() {
    bool possible{ true };
    for (size_t ii = 0; ii < population && possible; ii++) {
      possible &= people.balance_of(ii) == 0l;
    }
    return possible ? "POSSIBLE\n" : "IMPOSSIBLE\n";
  };
};

int main() {
  std::string line;
  std::size_t N = getinput(), population, pairs, person_A, person_B;

  for (size_t kk = 1; kk <= N; kk++) {
    population = getinput();
    pairs      = getinput();

    Solution solution { population };
    for (size_t ii = 0; ii < population; ii++) {
      solution.set_balance_of(ii, getinput<ll>());
    }
    for (size_t ii = 0; ii < pairs; ii++) {
      person_A = getinput(); //1..n
      person_B = getinput(); //1..n
      solution.make_friends(person_A, person_B);
    }
    std::cout << solution.solve();
  }

  return(0);
}