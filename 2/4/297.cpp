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

inline std::string getln() {
  std::string line;
  return (std::getline(std::cin, line), line);
}

class Solution {
  public:
  enum Color {
    white  = 0,
    mixed  = 1,
    black  = 2
  };

  enum image_type_t {
    first,
    second
  };

  private:

  struct image_node_t {
    Color  color;
    size_t pixels;

    image_node_t(Color c, size_t pix) : color{ c }, pixels{ pix } {

    }
  };

  using image_t = advanced::tree_t<image_node_t, 4>;
  image_t image1, image2;
  size_t  pixels;

  void
  build(image_t::node_type&    img_node,
        std::string::iterator& img_str,
        std::string::iterator  img_end,
        size_t                 pixels)
  {
    size_t child_pixels = pixels >> 2;
    if (img_str != img_end) {
      char c = *img_str;
      switch (c) {
      case 'p':
        img_node.add_child(new image_node_t(Color::mixed, child_pixels));
        img_node.add_child(new image_node_t(Color::mixed, child_pixels));
        img_node.add_child(new image_node_t(Color::mixed, child_pixels));
        img_node.add_child(new image_node_t(Color::mixed, child_pixels));
        build(img_node.child(0), ++img_str, img_end, child_pixels);
        build(img_node.child(1), ++img_str, img_end, child_pixels);
        build(img_node.child(2), ++img_str, img_end, child_pixels);
        build(img_node.child(3), ++img_str, img_end, child_pixels);
        break;

      case 'f':
          (*img_node).color = Color::black;
        break;

      case 'e':
          (*img_node).color = Color::white;
        break;

      default:
        break;
      }
    }
  }

  size_t
  count_blacks(const image_t::node_type& quad) {
    size_t blacks{ 0 };
    switch ((*quad).color)
    {
    case Color::black:
      blacks += (*quad).pixels;
      break;

    case Color::mixed:
      blacks += count_blacks(quad.child(0));
      blacks += count_blacks(quad.child(1));
      blacks += count_blacks(quad.child(2));
      blacks += count_blacks(quad.child(3));
      break;

    default:
      break;
    }
    return blacks;
  }

  size_t
  compare(const image_t::node_type& quad1, const image_t::node_type& quad2) {
    size_t blacks{ 0 };
    if ((*quad1).color == Color::black || (*quad2).color == Color::black) {
      blacks = (*quad1).pixels;
    }
    else if ((*quad1).color == Color::mixed && (*quad2).color == Color::mixed) {
      blacks += compare(quad1.child(0), quad2.child(0));
      blacks += compare(quad1.child(1), quad2.child(1));
      blacks += compare(quad1.child(2), quad2.child(2));
      blacks += compare(quad1.child(3), quad2.child(3));
    }
    else if ((*quad1).color == Color::mixed) {
      blacks = count_blacks(quad1);
    }
    else if ((*quad2).color == Color::mixed) {
      blacks = count_blacks(quad2);
    }
    return blacks;
  }

  public:
  Solution(size_t pixels) :
    image1(Color::mixed, pixels),
    image2(Color::mixed, pixels),
    pixels{ pixels }
  { }

  void
  build(image_type_t img, std::string& img_str) {
    auto& tree{ img == image_type_t::first ? image1 : image2 };
    std::string::iterator it = img_str.begin();
    build(tree.root(), it, img_str.end(), pixels);
  }

  size_t
  compare() {
    return compare(image1.root(), image2.root());
  }
};

int main() {
  std::string line;
  std::size_t N = getinput();

  for (size_t kk = 1; kk <= N; kk++) {
    Solution solution{ 1024 };
    solution.build(Solution::image_type_t::first,  line = getln());
    solution.build(Solution::image_type_t::second, line = getln());
    std::cout << "There are " << solution.compare() << " black pixels.\n";
  }

  return(0);
}