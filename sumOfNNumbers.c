#include <stdio.h>
int main()

{
    int n, sum = 0, i = 0;
    printf("Enter the limit :  ");
    scanf("%d", &n);
    while (i < n + 1)
    {
        sum += i;
        i++;
    }
    printf("The sum of first %d numbers is : %d\n", n, sum);

    return 0;
}