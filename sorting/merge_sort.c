#include <stdio.h>

void merge(int *arr, int size, int low, int mid, int high) {
  int i = low, j = mid + 1, k = low;
  int temp[size];
  while (i <= mid && j <= high) {
    if (arr[i] < arr[j]) {
      temp[k] = arr[i];
      i++;
      k++;
    } else {
      temp[k] = arr[j];
      j++;
      k++;
    }
  }

  while (i <= mid) {
    temp[k] = arr[i];
    i++;
    k++;
  }

  while (j <= high) {
    temp[k] = arr[j];
    j++;
    k++;
  }

  for (int i = low; i <= high; i++)
    arr[i] = temp[i];
}

void merge_sort(int *arr, int size, int low, int high) {
  if (low < high) {
    int mid = (low + high) / 2;
    merge_sort(arr, size, low, mid);
    merge_sort(arr, size, mid + 1, high);
    merge(arr, size, low, mid, high);
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

  merge_sort(arr, size, 0, size - 1);
  printf("Sorted array:\n");
  print_array(arr, size);
  return 0;
}
