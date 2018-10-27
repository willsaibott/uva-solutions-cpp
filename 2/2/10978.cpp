/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
**/

#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
  string output = "";
  string line;

  output.reserve(500000);

  while(true)
  {
    int n;
    cin >> n;

    if (!n) break;

    vector<string> cards(n);
    string cd, spell;
    int index = -1;

    for (int ii = 0; ii < n; ii++)
    {
      cin >> cd >> spell;

      for (uint k = 1; k <= spell.size();)
      {
        if (cards[(index + k) % n] != "")
        {
          index++;
        } else
        {
          k++;
        }
      }
      index = (index + spell.size()) % n;
      cards[index] = cd;
    }

    for (auto card = cards.begin(); card != cards.end(); card++)
    {
      output += *card + (next(card) == cards.end() ? "\n" : " ");
    }
  }

  printf("%s", output.c_str());

  return(0);
}