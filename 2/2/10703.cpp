/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * 10703 - Free spots
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

  while(!cin.eof())
  {
    int n, w, h;
    cin >> w >> h >> n;
    if (!n && !w && !h) break;
    vector<vector<int>> m(h, vector<int>(w, 0));
    int freeStops = w*h;

    for (int ii = 0; ii < n; ii++)
    {
      int x0, xf, y0, yf, temp;
      cin >> x0 >> y0 >> xf >> yf;

      temp = x0;
      x0 = min(x0-1, xf-1);
      xf = max(temp-1, xf-1);
      temp = y0;
      y0 = min(y0-1, yf-1);
      yf = max(temp-1, yf-1);

      for (int x = x0; x <= xf; x++)
      {
        for (int y = y0; y <= yf; y++)
        {
          freeStops -= !(m[y][x]++);
        }
      }
    }

    if (!freeStops) output += "There is no empty spots.\n";
    else if (freeStops == 1) output += "There is one empty spot.\n";
    else output += "There are " + to_string(freeStops) + " empty spots.\n";
  }

  printf("%s", output.c_str());

  return(0);
}