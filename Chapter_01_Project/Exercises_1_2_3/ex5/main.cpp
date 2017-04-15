#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct date {
  int day;
  int month;
  int year;
};

struct dateCompare
{
  bool operator() (const date& a, const date& b)
  {
    return ((a.month != b.month)?
            (a.month < b.month):
            ((a.day != b.day)?
             (a.day < b.day):
             (a.year < b.year)));
  }
};

int main(int argc, char *argv[])
{
  date d;
  vector<date> v;
  while (scanf("%d %d %d", &d.day, &d.month, &d.year) == 3)
  {
    v.push_back(d);
  }

  sort(v.begin(), v.end(), dateCompare());
  for (int i = 0; i < (int)v.size(); i++)
  {
    d = v.at(i);
    printf("%d %d %d\n", d.month, d.day, d.year);
  }
  return 0;
}
