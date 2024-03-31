#include <stdio.h>
int main()
{
    int num, digit, sum = 0;

    printf("Enter any number :  ");
    scanf("%d", &num);

    while (num != 0)
    {
        digit = num % 10;
        sum += digit;
        num /= 10;
    }

    printf("The sum of digits is %d\n", sum);

    return 0;
}