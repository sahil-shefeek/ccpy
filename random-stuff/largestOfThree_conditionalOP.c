#include <stdio.h>
int main()
{
    int a, b;
    printf("Enter the first number : ");
    scanf("%d", &a);
    printf("Enter the second number : ");
    scanf("%d", &b);
    int largest = a > b ? a : b;
    printf("%d is greater.\n", largest);
    return 0;
}