/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 *
 * 127 - "Accordian" Patience
 */

#include <cstdio>
#include <iostream>
#include <stack>
#include <list>

using namespace std;
typedef unsigned char byte;
typedef unsigned long long ull;
typedef long long ll;

inline bool matches(string &card1, string &card2)
{
  return card1[0] == card2[0] || card1[1] == card2[1];
}

void move(list<stack<string>> &piles,
          list<stack<string>>::iterator &pileFrom,
          list<stack<string>>::iterator &pileTo)
{
  pileTo->push(pileFrom->top());
  pileFrom->pop();
  if (!pileFrom->size())
  {
    piles.erase(pileFrom);
  }
}

int main()
{
  string output = "";
  string line;

  output.reserve(500000);

  while(!cin.eof())
  {
    bool keep = true;
    list<stack<string>> piles;

    for (int ii = 0; ii < 52; ii++)
    {
      string card;
      cin >> card;

      if (card == "#")
      {
        keep = false;
        break;
      }

      stack<string> st;
      st.push(card);
      piles.push_back(st);
    }

    if (!keep) break;

    while (keep)
    {
      bool changes = false;

      for (auto pile = next(piles.begin());
                pile != piles.end();
                pile++)
      {
        string card = pile->top();
        auto p1 = prev(pile);
        auto p2 = prev(p1);

        if (p1 != piles.begin() && p2 != piles.begin())
        {
          auto it = prev(p2);
          string card2 = it->top();

          if (matches(card, card2))
          {
            changes = true;

            move(piles, pile, it);
            pile = piles.begin();

            continue;
          }
        }

        string card2 = p1->top();

        if (matches(card, card2))
        {
          changes = true;

          move(piles, pile, p1);
          pile = piles.begin();
        }
      }
      keep = piles.size() != 1 && changes;
    }

    if (piles.size() > 1)
    {
      output += to_string(piles.size()) + " piles remaining:";
    } else
    {
      output += to_string(piles.size()) + " pile remaining:";
    }

    for (auto pile = piles.begin(); pile != piles.end(); pile++)
    {
      output += " " + to_string(pile->size());
    }

    output += "\n";
  }

  printf("%s", output.c_str());

  return(0);
}