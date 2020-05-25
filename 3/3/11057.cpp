#include <bits/stdc++.h>

class Solution{
  std::vector<size_t>           books;
  std::vector<size_t>::iterator it;
public:

  Solution(size_t number_of_books) : books(number_of_books, 0) {
    it = books.begin();
  }

  void
  add_book_price(size_t price) {
    *it = price; it++;
  }

  std::pair<size_t, size_t>
  solve(size_t balance) {
    std::sort(books.begin(), books.end());
    auto mid       = std::lower_bound(books.begin(), books.end(), (balance + 1) / 2);
    auto mid_next  = std::next(mid);
    while (mid_next == books.end() || (*mid + *mid_next) != balance) {
      if (mid == books.begin()) {
        break;
      }
      mid--;
      mid_next = std::lower_bound(books.begin(), books.end(), balance - *mid);
    }
    return { *mid, *mid_next };
  }
};

template <class T = size_t>
T getinput() {
  T input;
  return (std::cin >> input, std::cin.ignore(), input);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  size_t number_of_books;
  while (std::cin >> number_of_books) {
    Solution solution(number_of_books);

    for (size_t ii = 0; ii < number_of_books; ii++) {
      solution.add_book_price(getinput());
    }

    const auto chosen_books = solution.solve(getinput());
    std::cout << "Peter should buy books whose prices are " << chosen_books.first
              << " and " << chosen_books.second << ".\n\n";
  }
}