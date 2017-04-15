#include <iostream>

using namespace std;

int permutations = 0;

void swap(char *c, int i, int j){
  char temp = c[i];
  c[i] = c[j];
  c[j] = temp;
}

void permute(char *c, int begin, int n)
{
  if (n == begin)
    printf("%.*s perm=%d\n", n, c, ++permutations);
  else
    for (int i = begin; i < n; i++)
    {
      swap(c, begin, i);
      permute(c, begin + 1, n);
      swap(c, begin, i);
    }
}

void permute(char *c, int n)
{
  permute(c, 0, n);
}

int main(int argc, char *argv[])
{
  char c[27];
  int n;
  for (int i = 0; i <= 25; i++)
    c[i] = 'a' + i;
  c[26] = '\0';
  while (scanf("%d", &n) > 0)
  {
    permutations = 0;
    printf("Input: %d\n", n);
    permute(c, n);
  }
  return 0;
}
