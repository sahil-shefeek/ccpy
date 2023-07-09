// This program assumes the entered number is three digits

#include <stdio.h>

int isPalindrome(int num)
{
    int temp, digit, rev = 0;
    temp = num;

    while (temp != 0)
    {
        digit = temp % 10;
        rev = rev * 10 + digit;
        temp /= 10;
    }

    if (num == rev)
        return 1;
    else
        return 0;
}

int isArmstrong(int num)
{
    int originalNum, digit, result = 0;
    originalNum = num;

    while (originalNum != 0)
    {
        // digit contains the last digit
        digit = originalNum % 10;

        result += digit * digit * digit;

        // removing last digit from the orignal number
        originalNum /= 10;
    }

    if (result == num)
        return 1;
    else
        return 0;
}

int main()
{
}