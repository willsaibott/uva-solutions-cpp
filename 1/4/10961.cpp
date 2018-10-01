/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
**/

#include <cstdio>
#include <iostream>
#include <utility>
#include <queue>
#include <cmath>

using namespace std;

template <typename T, typename U>
std::pair<T,U> operator+(const std::pair<T,U> &l,
                         const std::pair<T,U> &r) {
  return {l.first + r.first, l.second + r.second};
}

template <typename T, typename U>
std::pair<T,U> operator-(const std::pair<T,U> &l,
                         const std::pair<T,U> &r) {
    return {l.first - r.first, l.second - r.second};
}

bool isInPath(pair<int, int> &start,
              pair<int, int> &direction,
              pair<int, int> &center)
{
  bool inside;

  inside = ((direction.first >= 0) ?
            (start.first <= center.first &&
            (start.first + direction.first) >= center.first) :
            (start.first >= center.first &&
            (start.first + direction.first) <= center.first)) &&
           ((direction.second >= 0) ?
            (start.second <= center.second &&
            (start.second + direction.second) >= center.second) :
            (start.second >= center.second &&
            (start.second + direction.second) <= center.second));
  return inside;
}

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
    queue<pair<int, int>> lStops, dStops;
    pair<int, int> leporello, donGiovanni;
    int lSize, dSize;
    bool safe = true;

    cin >> donGiovanni.first >> donGiovanni.second;
    cin >> leporello.first >> leporello.second;

    cin >> lSize;

    for(int ii = 0; ii < lSize; ii++) {
      pair<int, int> p;
      cin >> p.first >> p.second;
      lStops.push(p);
    }

    cin >> dSize;

    for(int ii = 0; ii < dSize; ii++) {
      pair<int, int> p;
      cin >> p.first >> p.second;
      dStops.push(p);
    }

    pair<int, int> l = leporello, d = donGiovanni;
    pair<int, int> center, lc, dc;

    while (lStops.size() && dStops.size())
    {
      pair<int, int> lr = lStops.front() - l;
      pair<int, int> dr = dStops.front() - d;
      bool opposite = false;

      if (lr.first && dr.second)
      {
        center = { d.first, l.second };
        lc = center - l, dc = center - d;

        opposite = true;
        if (abs(lc.first) == abs(dc.second) &&
            abs(lc.second) == abs(dc.first) &&
            isInPath(l, lr, center) &&
            isInPath(d, dr, center))
        {
          safe = false;
          break;
        }
      } else if (lr.second && dr.first)
      {
        center = { l.first, d.second };
        lc = center - l, dc = center - d;
        opposite = true;

        if (abs(lc.first) == abs(dc.second) &&
            abs(lc.second) == abs(dc.first) &&
            isInPath(l, lr, center) &&
            isInPath(d, dr, center))
        {
          safe = false;
          break;
        }
      } else if (l.first == d.first && !(abs(l.second - d.second) & 1))
      {
        if ((lr.second >= 0 && dr.second <= 0) ||
            (lr.second <= 0 && dr.second >= 0))
        {
           center = { l.first, (l.second + d.second) / 2 };
           if (isInPath(l, lr, center) && isInPath(d, dr, center))
           {
             safe = false;
             break;
           }
        }
      } else if (l.second == d.second && !(abs(l.first - d.first) & 1))
      {
        if ((lr.first >= 0 && dr.first <= 0) ||
            (lr.first <= 0 && dr.first >= 0))
        {
           center = { (l.first + d.first) / 2, l.second };
           if (isInPath(l, lr, center) && isInPath(d, dr, center))
           {
             safe = false;
             break;
           }
        }
      }

      int hyp = hypot(lr.first, lr.second) - hypot(dr.first, dr.second);

      if (hyp > 0)
      {
        pair<int, int> offset =
          (opposite ?
           make_pair((lr.second * dr.second >= 0) ? dr.second : - dr.second,
                     (lr.first * dr.first >= 0) ? dr.first : - dr.first) :
           make_pair((lr.first * dr.first >= 0) ? dr.first : - dr.first,
                     (lr.second * dr.second >= 0) ? dr.second : - dr.second));

        l = l + offset;
        d = dStops.front();
        dStops.pop();
      } else if (hyp < 0)
      {
        pair<int, int> offset =
          (opposite ?
           make_pair((lr.second * dr.second >= 0) ? lr.second : - lr.second,
                     (lr.first * dr.first >= 0) ? lr.first : - lr.first) :
           make_pair((lr.first * dr.first >= 0) ? lr.first : - lr.first,
                     (lr.second * dr.second >= 0) ? lr.second : - lr.second));
        d = d + offset;
        l = lStops.front();
        lStops.pop();
      } else {
        l = lStops.front();
        d = dStops.front();
        lStops.pop();
        dStops.pop();
      }
    }

    safe = safe || (lStops.size() == 1 && center == lStops.back());
    if (!begin || (begin = false)) output += "\n";
    output += (safe ? "Yes\n" : "No\n");
  }

  printf("%s", output.c_str());

  return(0);
}