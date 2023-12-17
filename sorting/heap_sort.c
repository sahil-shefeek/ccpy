#include <stdio.h>

#define OFFSET 1

void max_heapify(int *arr, int index, int size)
{
    int temp = arr[index];
    int child = 2 * index;
    while (child <= size)
    {
        if (child < size && arr[child + 1] > arr[child])
            child++;

        if (temp <= arr[child])
        {
            arr[child / 2] = arr[child];
            child = 2 * child;
        }
    }
    arr[child / 2] = temp;
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