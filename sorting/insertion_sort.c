#include <stdio.h>

#define MAX_SIZE 10

void insertion_sort(int *arr, int size) {
  for (int i = 0; i < size; i++) {
    int temp = arr[i];
    int index = i;
    while (index > 0 && arr[index - 1] > temp) {
      arr[index] = arr[index - 1];
      index--;
    }
    arr[index] = temp;
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

  insertion_sort(arr, num);

  printf("Sorted array: \n");
  print_array(arr, num);
  return 0;
}
