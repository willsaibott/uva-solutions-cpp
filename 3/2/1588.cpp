/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 * uhunt page: https://uhunt.onlinejudge.org/id/899065
 *
 */

#include <bits/stdc++.h>

using namespace std;

class Solution {
  public:

  bool
  teeth_fits_when_slave_is_shifted_by(std::size_t shift, const std::string& master, const std::string& slave) {
    std::size_t max_length     = master.size() + slave.size();
    for (auto index = 0ul; index < slave.size(); index++) {
      auto& slave_ii{ slave[index] };
      auto& master_ii{ master[index + shift] };
      if (slave_ii == '2' && master_ii == '2') return false;
    }
    return true;
  }

  std::string
  solve(const std::string& master, const std::string& slave) {
    std::size_t max_length = master.size() + slave.size();
    std::size_t min_length = max_length;

    std::string master_shifted =
        std::string(slave.size(), '1') + master + std::string(slave.size(), '1');
    for (auto shift = 1ul; shift < max_length; shift++) {
      std::size_t length = max_length;
      if (teeth_fits_when_slave_is_shifted_by(shift, master_shifted, slave)) {
        length = shift < slave.size() ?
                 max_length - shift :
                 (shift < master.size() ? master.size() : shift);
      }
      min_length = std::min(min_length, length);
    }
    return std::to_string(min_length);
  };
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::string master, slave;
  while (std::cin >> master >> slave) {
    if (master.size() < slave.size()) {
      std::swap(master, slave);
    }
    std::cout << Solution{}.solve(master, slave) << "\n";
  }

  return(0);
}