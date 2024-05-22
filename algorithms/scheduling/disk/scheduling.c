#include <stdio.h>
#include <stdlib.h>

#define MAX 20

int temp;

void sort(int *a, int n) {
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - 1; j++) {
      if (a[j] > a[j + 1]) {
        temp = a[j];
        a[j] = a[j + 1];
        a[j + 1] = temp;
      }
    }
  }
}

void fcfs(int *a, int n) {
  int i, total = 0;
  printf("Sequence : %d ", a[0]);
  for (i = 0; i < n; i++) {
    printf("%d ", a[i + 1]);
    total += abs(a[i + 1] - a[i]);
  }
  printf("\nTotal head movement = %d \n", total);
}

void scan(int *c1, int n, int start) {
  int c, total = 0, loc, i, j, min, max, inc,a[MAX], b[MAX];
  for (i = 0; i < n +1; i++)
    a[i]=c1[i];
  printf("Choose 1:left or 2:right :");
  scanf("%d", &c);
  printf("Enter the Start and End of disk :");
  scanf("%d%d", &min, &max);
  a[++n] = min, a[++n] = max;
  sort(a, ++n);
  for (i = 0; i < n && a[i] != start; i++);
  loc = i;
  inc = (c == 1) ? (-1) : 1;
  for (i = loc, j = 0; i >= 0 && i < n;) {
    b[j++] = a[i];
    i += inc;
    if ((i < 0 || i > n - 1) && j < n - 1)
      inc *= (-1), i = loc + inc;
  }
  printf("Sequence : %d ", b[0]);
  for (i = 0; i < n - 1; i++) {
    printf("%d ", b[i + 1]);
    total += abs(b[i + 1] - b[i]);
  }
  printf("\nTotal head movement = %d \n", total);
}

void cscan(int c1[], int n, int start) {
  int c, total = 0, loc, i, j, min, max, inc,a[MAX], b[MAX];
  for (i = 0; i < n + 1; i++)
    a[i]=c1[i];
  printf("Choose 1:left or 2:right :");
  scanf("%d", &c);
  printf("Enter the Start and End of disk :");
  scanf("%d%d", &min, &max);
  a[++n] = min, a[++n] = max;
  sort(a, ++n);
  for (i = 0; i < n && a[i] != start; i++);
  loc = i;
  inc = (c == 1) ? (-1) : 1;
  for (i = loc, j = 0; j < n;) {
    b[j++] = a[i];
    i += inc;
    if ((i < 0 || i > n - 1) && j < n - 1)
      i = (i < 0) ? (n - 1) : 0;
  }
  printf("Sequence : %d ", b[0]);
  for (i = 0; i < n - 1; i++) {
    printf("%d ", b[i + 1]);
    total += abs(b[i + 1] - b[i]);
  }
  printf("\nTotal head movement = %d \n", total);
}

int main() {
  int i, n, a[MAX], ch, start;
  printf("Enter the number of requests :");
  scanf("%d", &n);
  for (i = 1; i < n + 1; i++)
    scanf("%d", &a[i]);
  printf("Enter the starting position :");
  scanf("%d", &start);
  a[0] = start;
  do {
    printf("Enter 1:FCFS 2:SCAN 3:CSCAN 4:Exit :\n");
    scanf("%d", &ch);
    switch (ch) {
    case 1:
      fcfs(a, n);
      break;
    case 2:
      scan(a, n, start);
      break;
    case 3:
      cscan(a, n, start);
    case 4:
      break;
    default:
      printf("Invalid input\n");
    }
  } while (ch != 4);
  return 0;
}
