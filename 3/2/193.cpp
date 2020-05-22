#include <bits/stdc++.h>

class graph_t {
  using edge_t  = std::set<int>;
  using edges_t = std::vector<edge_t>;
  size_t  _nodes;
  size_t  _number_of_edges;
  edges_t _edges;

  public:

  graph_t() = default;
  graph_t(size_t number_of_nodes, size_t number_of_edges)
    : _nodes{ number_of_nodes },
      _number_of_edges{ 0 },
      _edges(number_of_nodes, edge_t{})
  { }

  const edge_t&
  edge_of(size_t position) const {
    return _edges.at(position);
  }

  bool
  has_edge(size_t x, size_t y) const {
    return _edges.at(x).count(y);
  }

  void
  create_nodes(size_t nodes = 1ull) {
    _edges.resize(_edges.size() + nodes, edge_t{});
    _nodes = _edges.size();
  }

  inline size_t
  size() const {
    return _nodes;
  }

  inline size_t
  total_edges() const {
    return _number_of_edges;
  }

  bool
  add_edge(size_t x, size_t y) {
    bool inserted{ _edges.at(x).insert(y).second };
    _number_of_edges += inserted ? 1 : 0;
    return inserted;
  }
};

enum class color {
  none,
  black,
  white,
};

class Solution {
  graph_t             graph;
  std::vector<size_t> answer;
  std::vector<color>  best_coloring;
  size_t              most_blacked{ 0 };

  bool
  backtracking(std::vector<color>&                 colors,
               std::vector<color>::iterator        current_color,
               size_t                              blacks)
  {
    bool path_ok { true };
    const auto index { std::distance(colors.begin(), current_color) };
    const auto& edge { graph.edge_of(index) };

    for (const auto& node : edge) {
      path_ok &= !(*current_color == color::black && colors[node] == color::black);
      if (!path_ok || colors[node] == color::none) { break; }
    }

    if (path_ok) {
      auto next_color{ std::next(current_color) };
      if (next_color != colors.begin() + graph.size()) {
        *next_color = color::black;
        backtracking(colors, next_color, blacks + 1);

        *next_color = color::white;
        backtracking(colors, next_color, blacks);

        *next_color = color::none;
      }
      else if (blacks > most_blacked) {
        best_coloring = colors;
        most_blacked  = blacks;
      }
    }
    return path_ok;
  }

public:

  Solution(size_t nodes, size_t edges) : graph{ nodes, edges }
  { }

  void
  add_edge(size_t x, size_t y) {
    graph.add_edge(x - 1, y - 1);
    graph.add_edge(y - 1, x - 1);
  }

  const std::vector<size_t>&
  solve() {
    static std::vector<color> colors(128, color::none);

    colors[0] = color::black;
    backtracking(colors, colors.begin(), 1);
    colors[0] = color::white;
    backtracking(colors, colors.begin(), 0);

    for (size_t ii = 0; ii < graph.size(); ii++) {
      if (best_coloring[ii] == color::black) {
        answer.push_back(ii + 1);
      }
    }

    return answer;
  }
};


template <class T = size_t>
T getinput() {
  T input;
  return (std::cin >> input, std::cin.ignore(), input);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  size_t number_of_nodes;
  size_t number_of_edges;
  size_t x, y;
  size_t test_cases = getinput();

  for (size_t kk = 0; kk < test_cases; kk++) {
    number_of_nodes = getinput();
    number_of_edges = getinput();

    Solution solution{ number_of_nodes, number_of_edges };
    for (size_t ii = 0; ii < number_of_edges; ii++) {
      x = getinput();
      y = getinput();
      solution.add_edge(x, y);
    }
    const auto& answer{ solution.solve() };
    std::cout << answer.size() << "\n";

    if (answer.size()) {
      std::string ss;
      for (const auto& elem : answer) {
        ss += std::to_string(elem) + " ";
      }
      ss.back() = '\n';
      std::cout << ss;
    }
  }
}