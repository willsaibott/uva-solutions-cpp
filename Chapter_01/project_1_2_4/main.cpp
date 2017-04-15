#include <cstdio>

using namespace std;

int N;          // uing global variables in contests can be a good strategy
char x[110];    // make it a habit toset array size a bit larger than needed

int main(int argc, char *argv[])
{
    scanf("%d\n", &N);
     while (N--) {
        scanf("0.%[0-9]...\n", &x);     // & is opitional when x is a char array
        printf("The digits are 0.%s\n", x);
    }
    return 0;
}
