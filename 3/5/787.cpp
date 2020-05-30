#include <bits/stdc++.h>

class big_integer_t {
  std::vector<std::int32_t> _number;
  bool                      _negative{ false };

  friend std::ostream& operator<<(std::ostream& os, const big_integer_t& big_int);

public:
  big_integer_t(const big_integer_t&)                       = default;
  big_integer_t(big_integer_t&&) noexcept                   = default;
  inline big_integer_t& operator=(const big_integer_t&)     = default;
  inline big_integer_t& operator=(big_integer_t&&) noexcept = default;

  big_integer_t() : _number(4, 0)
  { }

  big_integer_t(std::int64_t value) : big_integer_t{ } {
    *this = value;
  }

  inline std::int32_t
  operator[](size_t position) const {
    return _number.at(position);
  }

  big_integer_t&
  operator-=(std::int64_t value) {
    if ((_negative && value < 0) || (_negative && value >= 0)) {
      return operator+=(value);
    }

    auto this_abs { std::abs(static_cast<std::int64_t>(*this)) };
    auto that_abs { std::abs(value)                            };
    if (this_abs >= that_abs) {
      (*this) = this_abs - that_abs;
    }
    else {
      (*this) = that_abs - this_abs;
      bool has_subtracted{ false };
      for (int ii = _number.size() - 1; ii >= 0; ii--) {
        if (_number[ii]) {
          has_subtracted = true;
          _number[ii]--;
          for (size_t jj = ii; jj >= 2; jj--) {
            _number[jj] = 999999999;
          }
        }
      }
      if (!has_subtracted) {
        _negative = !_negative;
      }
    }
    return *this;
  }

  big_integer_t&
  operator+=(std::int64_t value) {
    static std::int32_t max_int32{ 999999999 };

    if ((_negative && value > 0) || (!_negative && value < 0)) {
      return operator-=(value);
    }

    auto term = std::abs(value);
    if (max_int32 - term <= _number[0]) {
      size_t index = 0;
      while (max_int32 - term > _number[index]) {
        _number[index] +=
            max_int32 - (max_int32 - term) - (max_int32 - _number[index]) - 1;
        if (index + 1 >= _number.size()) {
          _number.push_back(0);
        }
        index++;
        term = 1;
      }
    }
    else {
      _number[0] += term;
    }
    return *this;
  }

  big_integer_t&
  operator*=(std::int32_t value) {
    std::int64_t carry{ 0 }, b_term{ std::abs(value) };

    if (b_term) {
      auto first_non_zero { std::find_if(_number.rbegin(), _number.rend(), [](int value ){ return value; })  };
      std::vector<std::int32_t> number(
        _number.size() - std::distance(_number.rbegin(), first_non_zero) + 2, 0);
      for (size_t index = 0; index < _number.size(); index++) {
        std::int64_t temp = b_term * _number[index] + carry;
        number[index] += temp % static_cast<std::int64_t>(1E9);
        carry  = temp / static_cast<std::int64_t>(1E9);
      }

      bool before_state{ _negative };
      _negative = false;
      (*this) += carry;
      _negative = (before_state && (value > 0)) ||
                  (!before_state && (value < 0));

      _number = std::move(number);
    }
    else {
      std::fill(_number.begin(), _number.end(), 0);
      _negative = false;
    }

    return *this;
  }

  big_integer_t
  operator*(std::int64_t value) {
    big_integer_t that{ *this };
    that *= value;
    return that;
  }

  big_integer_t
  operator+(std::int64_t value) {
    big_integer_t that{ *this };
    that += value;
    return that;
  }

  inline operator
  std::int64_t() const {
    std::int64_t value =
      (std::int64_t)_number[0] + ((std::int64_t) _number[1] * 1E9);
    return _negative ? -value : value;
  }

  inline operator
  std::int32_t() const {
    return _negative ? -_number[0] : _number[0];
  }

  template <typename int_type = std::int16_t>
  inline operator
  int_type() const {
    int_type value = static_cast<int_type>(_number[0]);
    return _negative ? -value : value;
  }

  template <typename int_type = std::int32_t>
  inline bool
  operator<(int_type other) const {
    bool lower{ false };
    if (_negative && other >= 0) {
      lower = true;
    }
    else if (other < 0 && !_negative) {
      lower = false;
    }
    else {
      for (int ii = _number.size() - 1; ii >= 0; ii--) {
        if (ii > 1) {
          if (_number[ii]) {
            lower = _negative;
            break;
          }
        }
        else {
          int_type number64 = static_cast<int_type>(*this);
          lower = _negative ? number64 > std::abs(other) : number64 < std::abs(other);
          break;
        }
      }
    }

    return lower;
  }

  inline bool
  operator<(const big_integer_t& other) const {
    bool lower{ false };
    if (_negative != other._negative) {
      lower = _negative && !other._negative;
    }
    else {
      for (int ii = std::max(_number.size(), other._number.size()) - 1;
               ii >= 0;
               ii--)
      {
        if ((size_t)ii < other._number.size()) {
          if ((size_t)ii < _number.size()) {
            if (_number[ii] != other._number[ii]) {
              lower = _negative ?
                      _number[ii] > other._number[ii] :
                      _number[ii] < other._number[ii];
              break;
            }
          }
          else if (other._number[ii]) {
            lower = !_negative;
            break;
          }
        }
        else if (_number[ii]) {
          lower = _negative;
          break;
        }
      }
    }
    return lower;
  }

  template <typename int_type = std::int32_t>
  inline bool
  operator>(int_type other) const {
    bool greater{ false };
    if (_negative && other >= 0) {
      greater = false;
    }
    else if (other < 0 && !_negative) {
      greater = true;
    }
    else {
      for (int ii = _number.size() - 1; ii >= 0; ii--) {
        if (ii > 1) {
          if (_number[ii]) {
            greater = !_negative;
            break;
          }
        }
        else {
          int_type number64 = static_cast<int_type>(*this);
          greater = _negative ? number64 < std::abs(other) : number64 > std::abs(other);
          break;
        }
      }
    }
    return greater;
  }

  inline bool
  operator>(const big_integer_t& other) const {
    bool greater{ false };
    if (_negative != other._negative) {
      greater = !_negative && other._negative;
    }
    else {
      for (int ii = std::max(_number.size(), other._number.size()) - 1;
               ii >= 0;
               ii--)
      {
        if ((size_t)ii < other._number.size()) {
          if ((size_t)ii < _number.size()) {
            if (_number[ii] != other._number[ii]) {
              greater = _negative ?
                        _number[ii] < other._number[ii] :
                        _number[ii] > other._number[ii];
              break;
            }
          }
          else if (other._number[ii]) {
            greater = _negative;
            break;
          }
        }
        else if (_number[ii]) {
          greater = !_negative;
          break;
        }
      }
    }
    return greater;
  }

  inline bool
  operator==(std::int64_t other) const {
    bool equal{ true };
    for (size_t ii = 1; ii < _number.size() && equal; ii++) {
      if (_number[ii]) {
        equal = false;
      }
    }
    return equal && _number[0] == other;
  }

  inline bool
  operator==(const big_integer_t& other) const {
    bool equal{ true };
    for (size_t ii = 0; ii < std::max(_number.size(), other._number.size()) && equal; ii++) {
      if (ii < other._number.size() && ii < _number.size()) {
        equal = _number[ii] == other._number[ii];
      }
      else {
        if (ii < other._number.size()) {
          equal = !other._number[ii];
        }
        else {
          equal = !_number[ii];
        }
      }
    }
    return equal;
  }

  inline big_integer_t&
  operator=(std::int64_t value) {
    std::fill(_number.begin() + 2, _number.end(), 0);
    std::uint64_t abs_value { static_cast<std::uint64_t>(std::abs(value)) };
    _number[0] = abs_value % static_cast<std::int64_t>(1E9);
    _number[1] = (abs_value / static_cast<std::int64_t>(1E9)) % static_cast<std::int64_t>(1E9);
    _number[2] = abs_value / static_cast<std::int64_t>(1E18);
    _negative  = value < 0;
    return *this;
  }

  void invert() {
    _negative = !_negative;
  }
};

std::ostream& operator<<(std::ostream& os, const big_integer_t& big_int) {
  bool has_zero_pad{ false };
  if (big_int._negative) {
    os << "-";
  }

  for (int ii = big_int._number.size() - 1; ii >= 0; ii--) {
    if (has_zero_pad) {
      os << std::setfill('0') << std::setw(9) << big_int._number[ii];
    }
    else if (big_int._number[ii] || ii == 0) {
      os << big_int._number[ii];
    }
    has_zero_pad |= big_int._number[ii];
  }
  return os;
}

class Solution {
public:

  static big_integer_t
  calculate_max_product(const std::vector<std::int64_t>& sequence) {
    big_integer_t max_product     { std::numeric_limits<std::int64_t>::min() };
    big_integer_t curr_min_product{ 1 };
    big_integer_t curr_max_product{ 1 };
    big_integer_t one{ 1 };

    for (size_t ii = 0; ii < sequence.size(); ii++) {
      const auto& value = sequence[ii];
      if (value < 0) {
        auto new_min     = curr_max_product * value;
        auto new_max     = std::max(curr_min_product * value, one);
        curr_min_product = std::move(new_min);
        curr_max_product = std::move(new_max);
      }
      else {
        curr_min_product = std::min(curr_min_product * value, one);
        curr_max_product *= value;
      }

      if (curr_max_product == one && value != 1) {
        max_product = std::max(max_product, big_integer_t{ value });
      }
      else {
        max_product = std::max(std::max(curr_max_product, curr_min_product), max_product);
      }

      if (value == 0) {
        curr_min_product = 1;
        curr_max_product = 1;
      }
    }
    return max_product;
  }
};

int main() {
  std::string line;
  std::int64_t value{ 0 };
  const std::int64_t stop_number{ -999999 };
  while (std::cin) {
    std::vector<std::int64_t> sequence;
    do {
      getline(std::cin, line);
      std::stringstream ss{ line };
      while (ss >> value && value != stop_number) {
        sequence.push_back(value);
      }
    } while (std::cin && value != stop_number);

    if (!std::cin) {
      break;
    }
    std::cout << Solution::calculate_max_product(sequence) << "\n";
  }
}