/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
**/

#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <queue>
#include <map>
#include <sstream>
#include <iomanip>

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
  m['K'] = 12;
}

class Game
{
  private:
  int index;
  string last;
  string *cards;

  public:
  Game(string last = "", int index = 0)
     : index(index), last(last) { }

  static Game runGame(queue<string> clock[],
                      map<char, int> &m)
  {
    int index = 0, pointer;
    queue<string> *st = &clock[12];
    queue<string> debug[13];
    string last = "";

    for(int ii = 0; ii < 13; ii++) {
      debug[ii] = clock[ii];
    }

    while (st->size())
    {
      index++;
      last = (*st).front();
      st->pop();
      pointer = m[last[0]];
      st = &clock[pointer];
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
    queue<string> clock[13];
    cin >> card[0];

    if (card[0] == "#") break;

    clock[12].push(card[0]);

    for (int ii = 50; ii >= 0; ii--) {
      cin >> card[ii];
      clock[ii % 13].push(card[ii]);
    }

    Game game = Game::runGame(clock, indexMap);
    ostringstream ss;
    ss << setw(2) << setfill('0') << game.getIndex();

    output +=  ss.str() + "," + game.getLast() + "\n";
  }

  printf("%s", output.c_str());

  return(0);
}