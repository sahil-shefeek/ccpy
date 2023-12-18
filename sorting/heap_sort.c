#include <stdio.h>

#define OFFSET 1

void max_heapify(int *arr, int index, int size)
{
    int parent = arr[index];
    int child_index = 2 * index;
    while (child_index <= size)
    {
        if (child_index < size && arr[child_index + 1] > arr[child_index])
            child_index++;

        if (parent <= arr[child_index])
        {
            arr[child_index / 2] = arr[child_index];
            child_index *= 2;
        }
        else
            break;
    }
    arr[child_index / 2] = parent;
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

void print_array(int *arr, int size)
{
    for (int i = 1; i <= size; i++)
        printf("%d  ", arr[i]);
    printf("\n");
}

int main()
{
    int size;
    printf("Enter number of elements in the array: ");
    scanf("%d", &size);
    int arr[size + OFFSET];
    printf("Enter the array elements:\n");
    for (int i = 1; i <= size; i++)
        scanf("%d", &arr[i]);
    printf("Unsorted array:\n");
    print_array(arr, size);
    build_maxheap(arr, size);
    heapsort(arr, size);
    printf("Sorted array:\n");
    print_array(arr, size);
    return 0;
}
