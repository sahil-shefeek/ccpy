#include <stdio.h>

int isPrime(int num)
{
    if (num <= 1)
        return 0;

    for (int i = 2; i * i <= num; i++)
    {
        if (num % i == 0)
            return 0;
    }

    return 1;
}

int main()
{
    int element, size, arr[1000];
    printf("Enter the array size : ");
    scanf("%d", &size);
    printf("Enter the array elements :\n");

    for (int i = 0; i < size; i++)
        scanf("%d", &arr[i]);

    for (int i = 0; i < size; i++)
    {
        if (isPrime(arr[i]))
            printf("%d\t", arr[i]);
    }
    return 0;
}
