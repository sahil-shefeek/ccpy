#include <stdio.h>
int main ()
{
    int a = 0, b = 1, n, i, c;
    printf("Enter the range for the fibonacci series :\n");
    scanf("%d",&n);
    printf("The fibonacci series upto %d terms is :\n%d,%d",n,a,b);
    while (i <= (n-2))
    {
        c = a+b;
        printf(",%d",c);
        a = b;
        b = c;
        i++;
    }
    printf("\n");
    return 0;
}