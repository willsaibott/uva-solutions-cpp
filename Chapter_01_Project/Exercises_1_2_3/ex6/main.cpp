#include <iostream>
#include <algorithm>
#include <ctime>
#include <random>

using namespace std;

void fillRandom(int *v)
{
  srand(time(NULL));
  for (int i = 0; i < (int)1E6; i++)
  {
    v[i] = rand()%100;
  }
}

int binarySearch(int *v, int key, int begin, int end)
{
  if (end <= begin) return - 1;
  int pos = (begin + end) / 2;
  int diff = key - v[pos];

  if (diff > 0)
  {
    return binarySearch(v, key, pos + 1, end);
  } else if (diff < 0)
  {
    return binarySearch(v, key, begin, pos - 1);
  } else {
    return pos;
  }
}

int search(int *v, int size, int key)
{
  return binarySearch(v, key, 0, size - 1);
}

int main(int argc, char *argv[])
{
  int key;
  int v[(int)1E6];
  int pos;

  fillRandom(v);
  sort(std::begin(v), std::end(v));
  while (scanf("%d", &key) > 0)
  {
    pos = search(v, 1E6, key);
    if (pos == - 1)
      printf("Element %d not found.\n", key);
    else
      printf("Element %d found at %d.\n", key, pos);
  }
  return 0;
}
