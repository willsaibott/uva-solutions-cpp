#include <bits/stdc++.h>

template <class T = size_t>
T getinput() {
  T input;
  return (std::cin >> input, std::cin.ignore(), input);
}

inline std::string getln() {
  std::string line;
  return (std::getline(std::cin, line), line);
}

struct comparator_t
{
  inline bool
  operator()(const std::vector<int>& v1, const std::vector<int>& v2) const {
    return std::lexicographical_compare(v2.begin(), v2.end(),
                                        v1.begin(), v1.end());
  }
};


class Solution {
  using answer_t = std::set<std::vector<int>, comparator_t>;
  answer_t                                 _answers;
  std::unordered_set<size_t>               _inserted_masks;
  std::vector<int>                         _input;
  int                                      _target_sum;

  void
  backtracking(std::vector<int>::iterator current,
               size_t                     mask,
               int                        curr_sum)
  {
    if (current != _input.end()) {
      const auto index{ std::distance(_input.begin(), current) };
      const auto bit  { (1u << index) };
      const auto sum  { curr_sum + *current };
      const auto new_mask { mask | bit };
      if (sum == _target_sum && !_inserted_masks.count(new_mask)) {
        std::vector<int> ans;
        for (size_t ii = 0; ii < 12; ii++) {
          auto included = (new_mask & (1u << ii)) != 0u;
          if (included) {
            ans.push_back(_input[ii]);
          }
        }
        _inserted_masks.insert(new_mask);
        _answers.insert(ans);
      }
      if (sum < _target_sum) {
        for (auto it = current+1; it != _input.end(); it++) {
          backtracking(it, new_mask, sum);
        }
      }
    }
  }

public:

  Solution(int target_sum)
    : _target_sum{ target_sum }
  { }

  Solution&
  add_input(int value) {
    _input.push_back(value);
    return *this;
  }

  const answer_t&
  solve() {
    std::vector<int> ans;
    for (auto it = _input.begin(); it != _input.end(); it++) {
      backtracking(it, 0, 0);
    }
    return _answers;
  }
};

int main() {
  size_t array_size;
  int target_sum;
  while (std::cin >> target_sum >> array_size && (target_sum || array_size)) {
    Solution solution{ target_sum };
    for (size_t ii = 0; ii < array_size; ii++) {
      solution.add_input(getinput<int>());
    }
    std::cout << "Sums of " << target_sum << ":\n";
    const auto& answers{ solution.solve() };

    if (answers.size()) {
      for (const auto& answer : answers) {
        for (size_t ii = 0; ii < answer.size(); ii++) {
          std::cout << (ii ? "+" + std::to_string(answer[ii]) : std::to_string(answer[ii]));
        }
        std::cout << "\n";
      }
    }
    else {
      std::cout << "NONE\n";
    }
  }
}