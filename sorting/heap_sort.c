#include <stdio.h>

#define OFFSET 1

void max_heapify(int *arr, int index, int size)
{
    int temp = arr[index];
    int left = 2 * index;
    while (left <= size)
    {
        if (left < size && arr[left + 1] > arr[left])
            left++;
        if (temp > arr[left])
        {
            break;
        }
        else if (temp <= arr[left])
        {
            arr[left / 2] = arr[left];
            left = 2 * left;
        }
    }
    arr[left / 2] = temp;
    return;
}

void heapsort(int *arr, int size)
{
    for (int i = size; i >= 2; i--)
    {
        int temp = arr[i];
        arr[i] = arr[1];
        arr[1] = temp;
        max_heapify(arr, 1, i - 1);
    }
}

void build_maxheap(int *arr, int size)
{
    for (int i = size / 2; i >= 1; i--)
        max_heapify(arr, i, size);
}

int main()
{
    int size, i;
    printf("Enter number of elements in the array: ");
    scanf("%d", &size);
    int arr[size + OFFSET];
    printf("Enter the array elements:\n");
    for (i = 1; i <= size; i++)
        scanf("%d", arr + i);

    build_maxheap(arr, size);
    heapsort(arr, size);
    printf("Sorted Output\n");
    for (i = 1; i <= size; i++)
    {
        printf("%d  ", arr[i]);
    }
}