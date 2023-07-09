#include <stdio.h>

int factorial(int temp)
{
    int fact = 1;
    while (temp != 0)
    {
        fact *= temp;
        temp--;
    }
    return fact;
}

unsigned int npr(int n, int r)
{
    unsigned int res = factorial(n) / factorial(n - r);
    return res;
}

int main()
{
    int n, r;
    printf("nPr calculator.\n");
    printf("Enter n :  ");
    scanf("%d", &n);
    printf("Enter r :  ");
    scanf("%d", &r);
    printf("%dP%d is %u\n", n, r, npr(n, r));
    return 0;
}