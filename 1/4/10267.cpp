/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
**/

#include <cstdio>
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

void paint(vector<string> &picture, char old,
           int xx, int yy, int n, int m, char c)
{
  picture[yy][xx] = c;
  if ((xx-1) >= 0 && (yy-1) >= 0 && picture[yy-1][xx-1] == old)
    paint(picture, old, xx-1, yy-1, n, m, c);

  if ((xx-1) >= 0 && picture[yy][xx-1] == old)
    paint(picture, old, xx-1, yy, n, m, c);

  if ((xx-1) >= 0 && (yy+1) < n && picture[yy+1][xx-1] == old)
    paint(picture, old, xx-1, yy+1, n, m, c);

  if ((xx+1) < m && (yy-1) >= 0 && picture[yy-1][xx+1] == old)
    paint(picture, old, xx+1, yy-1, n, m, c);

  if ((xx+1) < m && picture[yy][xx+1] == old)
    paint(picture, old, xx+1, yy, n, m, c);

  if ((xx+1) < m && (yy+1) < n && picture[yy+1][xx+1] == old)
    paint(picture, old, xx+1, yy+1, n, m, c);

  if ((yy-1) >= 0 && picture[yy-1][xx] == old)
    paint(picture, old, xx, yy-1, n, m, c);

  if ((yy+1) < n && picture[yy+1][xx] == old)
    paint(picture, old, xx, yy+1, n, m, c);
}

int main()
{
  int n, m, xx, xxx, yy, yyy;
  int temp;
  string output = "";
  string line, name;
  vector<string> picture;

  output.reserve(500000);

  int k = 0;
  while(getline(cin, line))
  {
    if (++k == 7)
      {
        int b = 0;
      }
    if (!line.compare("X")) break;
    stringstream ss(line);
    char c, old;
    ss >> c;

    switch(c)
    {
      case 'I':
        ss >> m >> n;
      case 'C':
        picture.clear();
        picture = vector<string>(n, string(m, 'O'));
        break;
      case 'L':
        ss >> xx >> yy >> c;
        picture[yy - 1][xx - 1] = c;
        break;
      case 'V':
        ss >> xx >> yy >> yyy >> c;
        xx--;

        temp = yy;
        yy  = min(yy, yyy) - 1;
        yyy = max(temp, yyy);
        for(int ii = yy; ii < yyy; ii++) {
          picture[ii][xx] = c;
        }
        break;
      case 'H':
        ss >> xx >> xxx >> yy >> c;
        yy--;
        temp = xx;
        xx  = min(xx, xxx) - 1;
        xxx = max(temp, xxx);

        for(int ii = xx; ii < xxx; ii++) {
          picture[yy][ii] = c;
        }
        break;
      case 'K':
        ss >> xx >> yy >> xxx >> yyy >> c;
        temp = yy;
        yy  = min(yy, yyy) - 1;
        yyy = max(temp, yyy);
        temp = xx;
        xx  = min(xx, xxx) - 1;
        xxx = max(temp, xxx);

        for(int ii = yy; ii < yyy; ii++) {
          for(int jj = xx; jj < xxx; jj++) {
            picture[ii][jj] = c;
          }
        }
        break;
      case 'F':
        ss >> xx >> yy >> c;
        old = picture[--yy][--xx];
        if (c != old) paint(picture, old, xx, yy, n, m, c);
        break;
      case 'S':
        ss >> name;
        output += name + "\n";
        for(int ii = 0; ii < n; ii++) {
          output += picture[ii] + "\n";
        }
        break;
      case 'X':
      default:
        break;
    }
  }

  printf("%s", output.c_str());

  return(0);
}