#include <stdio.h>

#define MAX_SIZE 10

void bubbleSort(int *arr, int num)
{
    for (int i = 0; i < num - 1; i++)
    {
        for (int j = 0; j < num - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void printArray(int *arr, int size)
{
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main()
{
    int arr[MAX_SIZE];
    int num;
    printf("Enter the number of elements in the array: ");
    scanf("%d", &num);
    for (int i = 0; i < num; i++)
        scanf("%d", &arr[i]);

    printf("Original array: ");
    printArray(arr, num);

    bubbleSort(arr, num);

    printf("Sorted array: ");
    printArray(arr, num);
    return 0;
}
