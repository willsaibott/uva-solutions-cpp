/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution ${filename}
 *
 * This is a template file for C++ Solutions of UVA Judge Online problems
**/

#include <cstdio>
#include <iostream>
#include <vector>
#include <utility>
#include <list>
#include <cfloat>

using namespace std;

typedef struct MyInterval {
  double x;
  double coef;
} interval;

void insert(list<interval> &plan,
            double coef,
            double x,
            list<interval>::iterator it)
{
  interval i;
  i.coef = coef;
  i.x = x;
  plan.insert(it, i);
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

  while(k++ < N && !cin.eof())
  {
    int n;
    pair<double, double> start, end, temp;
    list<interval> plan;
    double coef;
    char s[30];

    cin >> n;

    if (!begin || (begin = false)) output += "\n";

    insert(plan, 1.000f, -DBL_MAX, plan.begin());
    insert(plan, 1.000f, DBL_MAX, next(plan.begin()));

    for (int ii = 0; ii < n; ii++)
    {
      double s, e;
      cin >> start.first >> start.second
          >>  end.first >> end.second >> coef;

      if (end.first < start.first)
      {
        temp = start;
        start = end;
        end = temp;
      }

      s = e = false;

      for (auto it = plan.begin(); it != plan.end(); it++)
      {
        s = s || start.first == it->x;
        e = e || end.first == it->x;

        if (!s && start.first < it->x)
        {
          insert(plan, prev(it)->coef * coef, start.first, it);
          s = true;
        }

        if (!e && end.first < it->x)
        {
          insert(plan, prev(it)->coef / coef, end.first, it);
          e = true;
        }

        if (it->x > start.first && it->x < end.first)
        {
          it->coef *= coef;
        }
      }
    }

    output += to_string(plan.size() - 1) + "\n";
    for (auto it = plan.begin(); it != plan.end(); it++)
    {
      if (it->x == -DBL_MAX)
      {
        sprintf(s, "-inf %.3f 1.000\n", next(it)->x);
      } else if (next(it)->x == DBL_MAX)
      {
        sprintf(s, "%.3f +inf 1.000\n", it->x);
        output += s;
        break;
      } else
      {
        sprintf(s, "%.3f %.3f %.3f\n", it->x, next(it)->x, it->coef);
      }

      output += s;
    }
  }

  printf("%s", output.c_str());

  return(0);
}