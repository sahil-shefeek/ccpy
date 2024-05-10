#include <stdio.h>
#define MAX 100
int temp, q[MAX];

void display(int m[], int n, int pr[], int c) {
  int j, totalfrag = 0, frag;
  for (j = 0; j < n + c; j++)
    printf("_____");
  printf("\n");
  for (j = 0; j < n; j++) {
    temp = (j < c) ? pr[q[j] - 1] : m[j];
    printf("|%3d ", temp);
    frag = m[j] - temp;
    totalfrag += frag;
    if (frag != 0)
      printf("+%3d ", frag);
  }
  printf("|\n");
  for (j = 0; j < n + c; j++)
    printf("-----");
  printf("\n");
  for (j = 0; j < c; j++)
    printf("  P%d\t  ", q[j]);
  printf("\n");
  printf("Total internal fragmentation = %d\n", totalfrag);
}

void firstfit(int m[], int n, int pr[], int p) {
  int i, j, c = 0;
  for (i = 0; i < p; i++) {
    for (j = c; j < n; j++) {
      if (m[j] >= pr[i]) {
        temp = m[j];
        m[j] = m[c];
        m[c] = temp;
        q[c] = i + 1;
        c++;
        break;
      }
    }
  }
  display(m, n, pr, c);
}

void bestfit(int m[], int n, int pr[], int p) {
  int j, c = 0, i;
  // sort memory in ASC order
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - 1; j++) {
      if (m[j] > m[j + 1]) {
        temp = m[j];
        m[j] = m[j + 1];
        m[j + 1] = temp;
      }
    }
  }
  // same as ffit
  for (i = 0; i < p; i++) {
    for (j = c; j < n; j++) {
      if (m[j] >= pr[i]) {
        temp = m[j];
        m[j] = m[c];
        m[c] = temp;
        q[c] = i + 1;
        c++;
        break;
      }
    }
  }
  display(m, n, pr, c);
}

void worstfit(int m[], int n, int pr[], int p) {
  int j, c = 0, i;
  // sort memory in DESC order
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - 1; j++) {
      if (m[j] < m[j + 1]) {
        temp = m[j];
        m[j] = m[j + 1];
        m[j + 1] = temp;
      }
    }
  }

  for (i = 0; i < p; i++) {
    for (j = c; j < n; j++) {
      if (m[j] >= pr[i]) {
        temp = m[j];
        m[j] = m[c];
        m[c] = temp;
        q[c] = i + 1;
        c++;
        break;
      }
    }
  }
  display(m, n, pr, c);
}

int main() {
  int i, n, ch, pr[MAX], p, m[MAX];
  printf("Enter the number of blocks:");
  scanf("%d", &n);
  printf("Enter the mem blocks :");
  for (i = 0; i < n; i++)
    scanf("%d", &m[i]);
  printf("Enter the number of processes :");
  scanf("%d", &p);
  printf("Enter the process mem :");
  for (i = 0; i < p; i++)
    scanf("%d", &pr[i]);
  do {
    printf("Enter 1:Firstfit 2:Bestfit 3:Worstfit 4:Exit :\n");
    scanf("%d", &ch);
    switch (ch) {
    case 1:
      firstfit(m, n, pr, p);
      break;
    case 2:
      bestfit(m, n, pr, p);
      break;
    case 3:
      worstfit(m, n, pr, p);
    case 4:
      break;
    default:
      printf("Invalid input\n");
    }
  } while (ch != 4);
  return 0;
}
