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

unsigned int ncr(int n, int r)
{
    unsigned int res = factorial(n) / (factorial(n - r) * factorial(r));
    return res;
}

int main()
{
    int n, r;
    printf("nCr calculator.\n");
    printf("Enter n :  ");
    scanf("%d", &n);
    printf("Enter r :  ");
    scanf("%d", &r);
    printf("%dC%d is %u\n", n, r, ncr(n, r));
    return 0;
}