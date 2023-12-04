#include <stdio.h>

#define MAX_SIZE 10

void selectionSort(int arr[], int length)
{
    for (int i = 0; i < length - 1; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < length; j++)
        {
            if (arr[j] < arr[minIndex])
            {
                int temp = arr[j];
                arr[j] = arr[minIndex];
                arr[minIndex] = temp;
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

    printf("Original array: \n");
    printArray(arr, num);

    selectionSort(arr, num);

    printf("Sorted array: \n");
    printArray(arr, num);
    return 0;
}
