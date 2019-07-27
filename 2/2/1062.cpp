/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
 */

#include <iostream>
#include <vector>
#include <deque>
#include <string>

using namespace std;
typedef unsigned char byte;
typedef unsigned long long ull;
typedef long long ll;

inline void
add_to_stack(std::vector<std::deque<char>>& stacks, char &_container) {
  static const auto empty_stack =  std::deque<char>();
  bool included = false;
  for (auto& stack : stacks) {
    if ((included = stack.empty() || stack.back() >= _container)) {
      stack.push_back(_container);
      break;
    }
  }

  if (!included) {
    stacks.push_back(empty_stack);
    stacks.back().push_back(_container);
  }
}

int main()
{
  int k = 0;
  string output = "";

  output.reserve(500000);
  while(cin.good() && !cin.eof())
  {
    std::vector<std::deque<char>> stacks;
    string _containers;
    cin >> _containers;
    cin.ignore();
    if (_containers=="end")
      break;
    for (auto& c: _containers) {
      add_to_stack(stacks, c);
    }
    output += "Case " + to_string(++k).append(": ")
                                      .append(to_string(stacks.size()))
                                      .append("\n");
  }

  printf("%s", output.c_str());

  return(0);
}