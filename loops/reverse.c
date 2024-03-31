#include <stdio.h>
int main()
{
    int num, temp, digit, rev = 0;

    printf("Enter any number :  ");
    scanf("%d", &num);

    temp = num;
    while (temp != 0)
    {
        digit = temp % 10;
        rev = rev * 10 + digit;
        temp /= 10;
    }

    printf("The reversed value of %d is %d\n", num, rev);

    return 0;
}