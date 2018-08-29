#include <stdio.h>
#define VAL 32

int main()
{
    char arr[] = "GeeksQuiz";
    *(arr + 0) &= ~VAL;
    *(arr + 5) &= ~VAL;
    printf("%s", arr);

    return 0;
}