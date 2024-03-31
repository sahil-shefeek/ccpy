#include <stdio.h>
int main()
{
    int n, fact = 1;

    printf("Enter the number :  ");
    scanf("%d", &n);

    int temp = n;

    while (temp != 0)
    {
        fact *= temp;
        temp--;
    }

    printf("The factorial of %d is %d\n", n, fact);

    return 0;
}
