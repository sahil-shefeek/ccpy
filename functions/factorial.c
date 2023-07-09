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

int main()
{
    int n;
    printf("Enter the number :  ");
    scanf("%d", &n);
    printf("The factorial of %d is %d\n", n, factorial(n));
    return 0;
}