#include <iostream>

using namespace std;

void printSubset(int *v, int n){
  long long target = (1 << n) - 1;
  printf("\nInput %d:\n", n);

  for (long long bitmask = 0; bitmask <= target; bitmask++)
  {
    printf("\nSN %lli:", bitmask + 1);
    for (int i = 0; i < n; i++)
    {
      if (bitmask & (1 << i))
        printf("%d", v[i]);
    }
  }
}

int main(int argc, char *argv[])
{
  const int size = 20;
  int v[size];
  int n;

  for (int i = 0; i < size; i++)
    v[i] = i;

  while(scanf("%d", &n) > 0)
  {
    printSubset(v, n);
  }
  return 0;
}
