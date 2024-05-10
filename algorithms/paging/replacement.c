#include <stdio.h>
#define MAX 100
int count[MAX], time[MAX], inframe[MAX], q[200];
void fifo(int a[], int n, int frames) {
  int miss = 0, i, c = 0, j = 0;
  for (i = 0; i < n; i++) {
    if (inframe[a[i]] == 0) {
      if (c < frames)
        q[c++] = a[i];
      else {
        inframe[q[j]] = 0;
        q[j] = a[i];
        j = (j + 1) % frames;
      }
      inframe[a[i]] = 1;
      printf("Frames: ");
      for (int k = 0; k < c; k++) {
      	printf("%d  ", q[k]);
      }
      printf("\n");
      miss++;
    }
  }
  printf("Page faults = %d\n", miss);
}
void lru(int a[], int n, int frames) {
  int miss = 0, c = 0, loc, min, i, j;
  for (i = 0; i < n; i++) {
    time[a[i]] = i;
    if (inframe[a[i]] == 0) {
      if (c < frames)
        q[c++] = a[i];
      else {
        for (j = 1, loc = 0, min = time[q[0]]; j < frames; j++) {
          if ((time[q[j]]) < min) {
            min = time[q[j]];
            loc = j;
          }
        }
        inframe[q[loc]] = 0;
        q[loc] = a[i];
      }
      inframe[a[i]] = 1;
      printf("Frames: ");
      for (int k = 0; k < c; k++) {
      	printf("%d  ", q[k]);
      }
      printf("\n");
      miss++;
    }
  }
  printf("Page faults = %d\n", miss);
}
void lfu(int a[], int n, int frames) {
  int miss = 0, c = 0, loc, min, i, j;
  for (i = 0; i < n; i++) {
    count[a[i]]++;
    if (inframe[a[i]] == 0) {
      if (c < frames)
        q[c++] = a[i];
      else {
        for (j = 1, loc = 0, min = count[q[0]]; j < frames; j++) {
          if ((count[q[j]]) < min) {
            min = count[q[j]];
            loc = j;
          }
        }
        inframe[q[loc]] = 0;
        q[loc] = a[i];
      }
      inframe[a[i]] = 1;
      printf("Frames: ");
      for (int k = 0; k < c; k++) {
      	printf("%d  ", q[k]);
      }
      printf("\n");
      miss++;
    }
  }
  printf("Page faults = %d\n", miss);
}
int main() {
  int i, n, a[MAX], frames, ch;
  printf("Enter the number of references in reference string :");
  scanf("%d", &n);
  for (i = 0; i < n; i++)
    scanf("%d", &a[i]);
  printf("Enter the number of frames :");
  scanf("%d", &frames);
  do {
    for (i = 0; i < n; i++) {
      count[a[i]] = 0;
      time[a[i]] = 0;
      inframe[a[i]] = 0;
    }
    printf("Enter 1:FIFO 2:LRU 3:LFU 4:Exit :\n");
    scanf("%d", &ch);

    switch (ch) {
    case 1:
      fifo(a, n, frames);
      break;
    case 2:
      lru(a, n, frames);
      break;
    case 3:
      lfu(a, n, frames);
    case 4:
      break;
    default:
      printf("Invalid input\n");
    }
  } while (ch != 4);
  return 0;
}
