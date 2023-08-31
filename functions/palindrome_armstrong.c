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

        // removing last digit from the original number
        originalNum /= 10;
    }

    if (result == num)
        return 1;
    else
        return 0;
}

int main()
{
    int num, option;

    printf("Enter a three-digit number: ");
    scanf("%d", &num);

    printf("Choose an option:\n");
    printf("1. Check for Palindrome\n");
    printf("2. Check for Armstrong number\n");
    scanf("%d", &option);

    switch (option)
    {
    case 1:
        if (isPalindrome(num))
            printf("%d is a palindrome.\n", num);
        else
            printf("%d is not a palindrome.\n", num);
        break;
    case 2:
        if (isArmstrong(num))
            printf("%d is an Armstrong number.\n", num);
        else
            printf("%d is not an Armstrong number.\n", num);
        break;
    default:
        printf("Invalid option.\n");
        break;
    }

    return 0;
}
