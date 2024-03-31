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

    if (num == rev)
        printf("Palindrome\n");
    else
        printf("Not palindrome\n");

    return 0;
}