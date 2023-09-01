#include <stdio.h>
#include <stdlib.h>

int main()
{
    int *size = (int *)malloc(1);
    int *sum = (int *)malloc(1);

    printf("Enter the array size : ");
    scanf("%d", size);
    int *arr = (int *)malloc((*size) * sizeof(int));

    printf("Enter the array elements :\n");
    for (int i = 0; i < *size; i++)
        scanf("%d", arr + i);

    for (int i = 0; i < *size; i++)
        *sum += *(arr + i);

    printf("Sum of elements in the array : %d\n", *sum);
    free(size);
    free(sum);
    free(arr);
    return 0;
}