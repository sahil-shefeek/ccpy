#include <stdio.h>

#define MAX_SIZE 10

void bubble_sort(int *arr, int size) {
  for (int i = 0; i < size - 1; i++) {
    int flag = 0;
    for (int j = 0; j < size - i - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        int temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
        flag = 1;
      }
    }
    if (flag == 0)
      return;
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

  printf("Original array: ");
  print_array(arr, num);

  bubble_sort(arr, num);

  printf("Sorted array: ");
  print_array(arr, num);
  return 0;
}
