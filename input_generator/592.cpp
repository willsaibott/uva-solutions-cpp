#include <bits/stdc++.h>
#include "random.h"

static std::string classes[] = {
  "divine",
  "evil",
  "human",
  "lying",
};

int main(int argc, char** argv) {
  std::string line;
  std::size_t N = argc > 1 ? std::stoul(argv[1]) : 10000;
  std::ofstream input{ "./input/3/2/592" };

  if (input.is_open()) {
    std::cout << "Input file open successfully\n";
    std::cout << "Progress: \n";

    for (size_t kk = 1; kk <= N; kk++) {
      std::int64_t numberOfStatements = next_random(1, 20);
      input << numberOfStatements << "\n";

      for (auto ii = 0; ii < numberOfStatements; ii++) {
        double decision = next_random_double(0, 1);
        if (decision > 0.8) {
          char author = next_random_char("ABCDE");
          decision = next_random_double(0, 1);
          input << author << ": It is " << (decision > 0.5 ? "day" : "night") << ".\n";
        }
        else {
          char author  = next_random_char("ABCDE");
          char subject = next_random_char("ABCDE");
          double negative = next_random_double(0, 1);
          std::string inhabitant = classes[next_random(0, 3)];

          if (author == subject) {
            input << author << ": I am " << (negative > 0.8 ?  "not ": "")
              << inhabitant << ".\n";
          }
          else {
            input << author << ": " << subject << " is " << inhabitant << ".\n";
          }
        }
      }
    }

    input << "0\n";
  }
  else {
    std::cerr << "Unable to open input file.\n";
  }


  return(0);
}