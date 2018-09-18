/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
**/

#include <cstdio>
#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <cmath>

using namespace std;

#define SARDINES 0
#define MACKERELS 1
#define SALMONS 2
#define GROUPERS 3
#define TURTLES 4
#define DOLPHINS 5
#define WHALES 6
#define SHARKS 7

typedef unsigned long long ull;

class Fish
{
  bool square = false;
  bool rectangle = false;
  pair<int, int> position;
  pair<int, int> size;

  Fish(bool square,
       bool rectangle,
       pair<int, int> &position,
       pair<int, int> &size)
    : square(square), rectangle(rectangle),
      position(position), size(size)
  { }
  public:

  pair<int, int> static isRectangle(vector<string> &photo,
                                    vector<ull> &photoMap,
                                    pair<int, int> &pos,
                                    char fish)
  {
    int y = 0, x = 0;
    int maxY = photo.size() - 1;
    int minX = 0;
    int maxX = photo[0].size() - 1;
    bool valid = true;

    for(int ii = pos.first; ii <= maxY; ii++) {
      int x2 = 0;
      for(int jj = pos.second;
          jj <= maxX &&
          ((x && jj - pos.second < x) ||
           (photo[ii][jj] == fish));
          jj++)
      {
        if (photo[ii][jj] == fish)
        {
          x2++;
          photoMap[ii] |= (ull)1 << (ull)jj;
        }
      }

      if (!x2) break;

      if (x)
      {
        if (x2 != x)
          valid = false;
        if (pos.second  > minX && photo[ii][pos.second - 1] == fish)
        {
          photoMap[ii] |= (ull)1 << (pos.second - 1);
          valid = false;
        }
      }

      x = x2;
      y++;
    }

    return (valid ? make_pair(y, x) : make_pair(0, 0));
  }

  static Fish defineFish(vector<string> &photo,
                         vector<int> &counter,
                         vector<ull> &photoMap,
                         pair<int, int> &start)
  {
    char fish = photo[start.first][start.second];
    pair<int, int> size = isRectangle(photo, photoMap, start, fish);
    bool square = false, rectangle = false;

    if (size.first)
    {
      rectangle = true;

      if (size.first == size.second)
      {
        square = true;
        if (size.first == 1)
        {
          counter[SARDINES]++;
        } else
        {
          counter[TURTLES]++;
        }
      } else
      {
        int minor = min(size.first, size.second);
        int major = max(size.first, size.second);

        switch (minor)
        {
          case 1:
            if (major == 2) counter[MACKERELS]++;
            else counter[SALMONS]++;
            break;
          case 2: counter[GROUPERS]++; break;
          case 3: counter[DOLPHINS]++; break;
          case 4: counter[WHALES]++; break;
        }
      }
    } else
    {
      counter[SHARKS]++;
    }

    return Fish(square, rectangle, start, size);
  }

  static string check(vector<string> &photo)
  {
    vector<int> counter(8, 0);
    vector<ull> photoMap(64, 0);
    char s[100];

    for(uint ii = 0; ii < photo.size(); ii++) {
      for(uint jj = 0; jj < photo[ii].size(); jj++) {
        char c = photo[ii][jj];
        ull mask = (ull)1 << jj;

        if (c != '.' && !(photoMap[ii] & mask))
        {
          pair<int, int> pos(ii, jj);
          Fish::defineFish(photo, counter, photoMap, pos);
        }
      }
    }

    sprintf(s,
            "%d %d %d %d %d %d %d %d\n",
            counter[SARDINES],
            counter[MACKERELS],
            counter[SALMONS],
            counter[GROUPERS],
            counter[TURTLES],
            counter[DOLPHINS],
            counter[WHALES],
            counter[SHARKS]);

    return s;
  }
};

int main()
{
  int k = 0;
  int N;
  string output = "";
  string line;
  bool begin = true;

  output.reserve(500000);
  cin >> N;
  cin.ignore();

  while(k++ < N)
  {
    int rows, columns;

    vector<string> photo;
    cin >> rows >> columns;
    cin.ignore();

    for(int ii = 0; ii < rows; ii++) {
      getline(cin, line);
      photo.push_back(line);
    }

    if (!begin || (begin = false)) output += "\n";

    output += Fish::check(photo);
  }

  printf("%s", output.c_str());

  return(0);
}