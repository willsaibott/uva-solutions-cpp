/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
**/

#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <sstream>

using namespace std;

const int MAX = 28;
const int MIN = 8;


uint calculateMaxFontSize(string *input,
                         const uint X,
                         const uint Y,
                         const uint paragraphs)
{
  uint solution = 0, xChars, yChars;
  uint index = 0;
  uint lines = 0;
  string line, word, in;
  stringstream ss;


  for(int font = MAX; font >= MIN && !solution; font--) {
    xChars = X / font;
    yChars = Y / font;
    index = 0;
    lines = paragraphs;
    line = "";

    ss = stringstream(input[0]);
    while (lines <= yChars && xChars)
    {
      ss >> word;
      if (line.size() + word.size() + 1 <= xChars)
      {
        if (!line.empty()) line += " ";
        line += word;
      } else if (word.size() <= xChars)
      {
        if (!line.empty()) lines++;
        line = word;
      } else
      {
        break;
      }

      if (ss.eof())
      {
        if (index < paragraphs - 1)
        {
          ss = stringstream(input[++index]);
          line = "";
        }
        else
        {
          if (lines <= yChars)
          {
            solution = font;
            break;
          }
        }
      }
    }
  }

  return solution;
}

int main()
{
  int k = 0;
  int N;
  string output = "", line = "";

  output.reserve(500000);
  cin >> N;
  cin.ignore();

  while(k++ < N)
  {
    uint paragraphs, X, Y;
    cin >> paragraphs;
    cin.ignore();

    string input[paragraphs];

    for(uint ii = 0; ii < paragraphs; ii++) {
      getline(cin, input[ii]);
    }

    cin >> X >> Y;
    cin.ignore();

    uint size = calculateMaxFontSize(input, X, Y, paragraphs);
    if (size)
    {
      output += to_string(size) + "\n";
      // cout << to_string(size) + "\n";
    } else {
      output += "No solution\n";
      // cout <<  "No solution\n";
    }
  }

  printf("%s", output.c_str());

  return(0);
}