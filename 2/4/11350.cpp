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

struct fraction_t {
  size_t      a;
  size_t      b;
  fraction_t* left;
  fraction_t* right;
};

class Solution {
  using node_type_t = advanced::binary_node_t<fraction_t>;
  using tree_t = advanced::binary_tree_t<fraction_t>;

  tree_t                         stern_brocot_tree;
  std::unique_ptr<fraction_t>    left;
  std::unique_ptr<fraction_t>    right;

  public:

  Solution() :
    stern_brocot_tree{ fraction_t{ 1ul, 1ul } },
    left { new fraction_t{ 0ul, 1ul } },
    right{ new fraction_t{ 1ul, 0ul } }
  {
    auto& root{stern_brocot_tree.root().get() };
    root.left  = left.get();
    root.right = right.get();
  }

  void
  query(const std::string& line) {
    auto it = line.begin();
    query(stern_brocot_tree.root(), line.end(), it);
  }

  private:
  void
  query(node_type_t&                       node,
        const std::string::const_iterator& end,
        const std::string::const_iterator& it)
  {
    auto& fraction { node.get() };
    if (it == end) {
      std::cout << fraction.a << "/" << fraction.b << "\n";
    }
    else {
      if (*it == 'L') {
        if (!node.has_left()) {
          node.add_left({ (fraction.a + fraction.left->a),
                          (fraction.b + fraction.left->b),
                          (fraction.left),
                          &fraction });
        }
        query(node.left(),  end, std::next(it));
      }
      else {
        if (!node.has_right()) {
          node.add_right({ (fraction.a + fraction.right->a),
                           (fraction.b + fraction.right->b),
                           (&fraction),
                           (fraction.right) });
        }
        query(node.right(), end, std::next(it));
      }
    }
  }
};

int main() {
  std::string line;
  std::size_t N = getinput();
  Solution solution;

  for (size_t kk = 1; kk <= N; kk++) {
    solution.query(getln());
  }

  return(0);
}