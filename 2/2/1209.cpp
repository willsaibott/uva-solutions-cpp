/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 *
 * 1209 - Wordfish
**/

#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;
typedef unsigned char byte;
typedef unsigned long long ull;

class Password {
  int maxDiff = 0;
  string username;
  string password;

  public:
    Password(string username) : username(username)
    {
      password = setPassword();
    }

    string setPassword() {
      string word = username;
      string pass = word;
      int start = getMinDiff(word);
      maxDiff = start;

      for (int ii = 0; ii < 21; ii++)
      {
        next_permutation(word.begin(), word.end());
        int diff = getMinDiff(word);
        if (maxDiff < diff) {
          pass = word;
          maxDiff = diff;
        }
      }

      word = username;

      for (int ii = 0; ii < 10; ii++)
      {
        prev_permutation(word.begin(), word.end());
        int diff = getMinDiff(word);
        if (maxDiff < diff) {
          pass = word;
          maxDiff = diff;
        }
        if (maxDiff == diff) {
          pass = min(pass, word);
        }
      }

      return pass + to_string(maxDiff);
    }

    int getMinDiff(string word)
    {
      char c = word.front();
      int diff = 30;

      for (uint ii = 1; ii < word.length(); ii++)
      {
        diff = min(diff, abs(c-word[ii]));
        c = word[ii];
      }

      return diff;
    }

    string getPassword() const { return password; }
};

int main()
{
  string output = "";
  string line;

  output.reserve(500000);

  while(getline(cin, line))
  {
    Password p(line);
    output += p.getPassword() + "\n";
  }

  printf("%s", output.c_str());

  return(0);
}