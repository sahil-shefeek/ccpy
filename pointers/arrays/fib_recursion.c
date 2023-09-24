#include <stdio.h>
#include <stdlib.h>
#define BUFFER 10

int fib(int num, int *arr)
{
    if (num == 0 || num == 1)
        return num;

    if (arr[num] != 0)
        return arr[num];

    int result = fib(num - 1, arr) + fib(num - 2, arr);
    arr[num] = result;
    return result;
}

int main()
{
    int num;
    printf("Enter the term to get the fibonacci value for :");
    scanf("%d", &num);
    int *arr = (int *)calloc(num + BUFFER, sizeof(int));
    if (arr == NULL)
    {
        printf("Memory allocation failed. Exiting...\n");
        return 1;
    }
    printf("The %d'term in fibonacci series is: %d\n", num, fib(num, arr));
    free(arr);
}