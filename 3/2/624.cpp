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
  size_t time;
  size_t total_tracks;
  size_t total_sum{ 0 };
  std::vector<std::pair<size_t, size_t>>           tracks; // pair { track size, original position }
  std::vector<size_t>                              original_tracks;
  std::vector<std::pair<size_t, size_t>>::iterator tit;
  std::vector<size_t>::iterator                    tit2;

  public:

  void
  resize(size_t time, size_t tracks) {
    if (tracks > this->tracks.size()) {
      this->original_tracks.assign(tracks, 0);
      this->tracks.assign(tracks, std::make_pair<size_t, size_t>(0, 0));
    }
    tit  = this->tracks.begin();
    tit2 = original_tracks.begin();
    total_tracks = tracks;
    this->time   = time;
    total_sum    = 0;
  }

  void
  add_track(size_t minutes) {
    tit->first = minutes; tit->second = std::distance(tracks.begin(), tit); tit++;
    *tit2 = minutes; tit2++;
    total_sum += minutes;
  }

  std::string
  solve() {
    std::stringstream ss;
    size_t sum  = total_sum,                           // total sum of sizes
           mask = std::numeric_limits<size_t>::max();  // binary: 111111111....1

    // only search for an answer if the total sum is greater than the CD capacity,
    // otherwise, the best space usage is including all CDs
    if (total_sum > time) {
      // start from the greatest to improve speed
      std::sort(tracks.begin(),
                tit,
                std::greater<std::pair<size_t, size_t>>{});

      auto result = backtrack(0, time);
      mask = result.second;
      sum  = time - result.first;
    }

    for (size_t ii = 0; ii < total_tracks; ii++) {
      if (mask & (1 << ii)) {
        ss << original_tracks[ii] << " ";
      }
    }

    ss << "sum:" << sum << "\n";
    return ss.str();
  };

  private:

  std::pair<size_t, size_t>
  backtrack(size_t mask, size_t remaining_time) {
    std::pair<size_t, size_t> tmp, res { remaining_time, mask };
    size_t bit_th;
    if (remaining_time) {
      // while we do not have a full answer, search:
      for (size_t ii = 0;
                  ii < total_tracks && res.first;
                  ii++)
      {
        // mark the bit corresponding to the original position in the array
        bit_th = (1 << tracks[ii].second);
        if ((mask & bit_th) == 0 && tracks[ii].first <= remaining_time) {
          tmp = backtrack(mask | bit_th, remaining_time - tracks[ii].first);

          // if we find a better answer:
          if (tmp.first < res.first) {
            res.first  = tmp.first;
            res.second = tmp.second;
          }
        }
      }
    }
    return res;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::string line;
  std::size_t time, tracks;
  Solution solution;

  while (std::cin >> time >> tracks) {
    solution.resize(time, tracks);
    for (size_t ii = 0; ii < tracks; ii++) {
      solution.add_track(getinput());
    }
    std::cout << solution.solve();
  }

  return(0);
}