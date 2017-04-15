#include <iostream>
#include <random>
#include <algorithm>
#include <ctime>
#include <vector>

using namespace std;

void fillRandom(vector<int> *v)
{
  srand(time(NULL));
  for (int i = 0; i < 200; i++)
  {
    v->push_back(rand()%100);
  }
}

int main(int argc, char *argv[])
{
  vector<int> v;
  fillRandom(&v);
  sort(v.begin(), v.end(), [](const int& a,const int& b)
  {
    return (a < b);
  });
  int prev = v.at(0);
  printf("%d\n", v.at(0));
  for (int i = 1; i < 200; i++)
  {
    if (v.at(i) != prev)
      printf("%d\n", v.at(i));
    prev = v.at(i);
  }
  return 0;
}
