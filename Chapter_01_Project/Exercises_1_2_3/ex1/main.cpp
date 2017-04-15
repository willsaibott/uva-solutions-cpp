#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    double myDouble;
    while (scanf("%lf", &myDouble) > 0)
    {
      printf("%7.3f\n", myDouble);
    }
    return 0;
}
