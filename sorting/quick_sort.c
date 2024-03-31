#include <stdio.h>

void swap(int *first, int *second) {
  int temp = *first;
  *first = *second;
  *second = temp;
}

void quick_sort(int *arr, int low, int high) {
  if (low < high) {
    int pivot = arr[low];
    int i = low;
    int j = high;
    while (i < j) {
      while (arr[i] < pivot)
        i++;
      while (arr[j] > pivot)
        j--;
      if (i < j)
        swap(&arr[i], &arr[j]);
    }
    swap(&arr[j], &pivot);
    quick_sort(arr, low, j - 1);
    quick_sort(arr, j + 1, high);
  }
}

void print_array(int *arr, int size) {
  for (int i = 0; i < size; i++)
    printf("%d  ", arr[i]);
  printf("\n");
}

int main() {
  int size, choice;
  printf("Enter the number of elements in the array: ");
  scanf("%d", &size);
  int arr[size];
  printf("Enter the array elements:\n");
  for (int i = 0; i < size; i++)
    scanf("%d", &arr[i]);
  printf("Unsorted array:\n");
  print_array(arr, size);
  quick_sort(arr, 0, size - 1);
  printf("Sorted array:\n");
  print_array(arr, size);
  return 0;
}
