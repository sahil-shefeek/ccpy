#include <stdio.h>
#include <stdlib.h>
int main()
{
    int *a = (int *)malloc(1);
    int *b = (int *)malloc(1);

    printf("Enter any two numbers : ");
    scanf("%d%d", a, b);

    if (*a > *b)
        printf("%d is greater than %d\n", *a, *b);
    else
        printf("%d is greater than %d\n", *b, *a);
    free(a);
    free(b);
    return 0;
}