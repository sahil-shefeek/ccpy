#include <stdio.h>

int main()
{
    int sum = 0, mode, size, arr[1000];
    printf("Enter the array size : ");
    scanf("%d", &size);
    printf("Enter the array elements :\n");

    for (int i = 0; i < size; i++)
        scanf("%d", &arr[i]);

choice:
    printf("Select mode :\n1. Sum of all elements\n2. Sum of even elements\n3. Sum of odd elements\n");
    scanf("%d", &mode);

    switch (mode)
    {
    case 1:
        for (int i = 0; i < size; i++)
            sum += arr[i];
        break;

    case 2:
        for (int i = 0; i < size; i++)
        {
            if (arr[i] % 2 == 0)
                sum += arr[i];
        }
        break;

    case 3:
        for (int i = 0; i < size; i++)
        {
            if (arr[i] % 2 != 0)
                sum += arr[i];
        }
        break;

    default:
        printf("Invalid input try again.");
        goto choice;
    }

    printf("The sum is : %d\n", sum);

    return 0;
}