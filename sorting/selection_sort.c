#include <stdio.h>

#define MAX_SIZE 10

void selection_sort(int *arr, int size) {
  for (int i = 0; i < size - 1; i++) {
    int minIndex = i;
    for (int j = i + 1; j < size; j++) {
      if (arr[j] < arr[minIndex]) {
        int temp = arr[j];
        arr[j] = arr[minIndex];
        arr[minIndex] = temp;
      }
    }
  }
}

void print_array(int *arr, int size) {
  for (int i = 0; i < size; i++)
    printf("%d ", arr[i]);
  printf("\n");
}

int main() {
  int arr[MAX_SIZE];
  int num;
  printf("Enter the number of elements in the array: ");
  scanf("%d", &num);
  for (int i = 0; i < num; i++)
    scanf("%d", &arr[i]);

  printf("Original array: \n");
  print_array(arr, num);

  selection_sort(arr, num);

  printf("Sorted array: \n");
  print_array(arr, num);
  return 0;
}
