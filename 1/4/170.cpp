/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
**/

#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <stack>
#include <map>

using namespace std;

void populateMap(map<char, int> &m)
{
  m['A'] = 0;
  m['2'] = 1;
  m['3'] = 2;
  m['4'] = 3;
  m['5'] = 4;
  m['6'] = 5;
  m['7'] = 6;
  m['8'] = 7;
  m['9'] = 8;
  m['T'] = 9;
  m['J'] = 10;
  m['Q'] = 11;
  m['K'] = -1;
}

class Game
{
  private:
  int index = 0;
  string last;
  string *cards;

  public:
  Game(string last, int index) : last(last), index(index)
  {
    this->cards = cards;
  }

  static Game runGame(stack<string> cards, map<char, int> &m)
  {
    int index = 0;
    int end = 0b111111111111;
    int clock = 0;
    string last;

    while (end > clock && cards.size())
    {
      index++;
      last = cards.top();
      clock |= (1 << m[last[0]]);
      cards.pop();
    }

    return Game(last, index);
  }

  int getIndex() { return index; }
  string getLast() { return last; }
};

int main()
{
  string output = "";
  string card[52];
  map<char, int> indexMap;

  output.reserve(500000);

  populateMap(indexMap);

  while(true)
  {
    cin >> card[0];

    if (card[0] == "#") break;

    stack<string> pile;

    pile.push(card[0]);

    for (int ii = 1; ii < 52; ii++) {
      cin >> card[ii];
      pile.push(card[ii]);
    }

    Game game = Game::runGame(pile, indexMap);

    output += to_string(game.getIndex()) + "," + game.getLast() + "/n";
  }

  printf("%s", output.c_str());

  return(0);
}