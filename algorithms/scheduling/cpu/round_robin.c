#include <stdio.h>
#define MAX 30
int q[MAX], front = -1, rear = -1;
struct process {
  int at, bt, ct, no, tt, wt, rbt;
};
void enqueue(int item) {
  if (front == -1)
    front = 0;
  q[++rear] = item;
}
int dequeue() {
  int id = -1;
  id = q[front];
  if (front == rear)
    front = rear = -1;
  else
    front = front + 1;
  return id;
}
int main() {
  int time = 0, nextp, temp, i, n, j = 0, g = 0, tq;
  float tat = 0, twt = 0;
  struct process p[MAX], key, gant[MAX], idle;
  printf("Enter the number of processes :");
  scanf("%d", &n);
  printf("Enter the Time quantum :");
  scanf("%d", &tq);
  for (i = 0; i < n; i++) {
    printf("Enter Arrival time and Burst Time of process %d : \n", i + 1);
    scanf("%d%d", &p[i].at, &p[i].bt);
    p[i].no = i + 1;
    p[i].rbt = p[i].bt;
  }

  // sort based on arrival time
  for (i = 1; i < n; i++) {
    key = p[i];
    j = i - 1;
    while (j >= 0 && p[j].at > key.at) {
      p[j + 1] = p[j];
      j = j - 1;
    }
    p[j + 1] = key;
  }

  idle.bt = 0;
  j = 0;
  nextp = -1;
  while (front >= 0 || j < n) {
    for (; j < n && p[j].at <= time; j++)
      enqueue(j);
    if (g != 0 && nextp != -1 && p[nextp].rbt != 0)
      enqueue(nextp);
    if (front >= 0) {
      nextp = dequeue();
      gant[g] = p[nextp];
      temp = ((tq < gant[g].rbt) ? tq : gant[g].rbt);
      time += temp;
      p[nextp].rbt -= temp;
      gant[g++].ct = time;
      p[nextp].ct = time;
    } else {
      gant[g] = idle;
      gant[g++].ct = time = p[j].at;
    }
  }

  for (i = 0; i < n; i++) {
    p[i].tt = p[i].ct - p[i].at;
    p[i].wt = p[i].tt - p[i].bt;
    twt = twt + p[i].wt;
    tat = tat + p[i].tt;
  }
  printf("Gantt chart:\n");
  for (i = 0; i < g; i++) {
    if (gant[i].bt == 0)
      printf("| Idle   ");
    else
      printf("| p%d    ", gant[i].no);
  }
  printf("|\n");
  printf("0\t");
  for (i = 0; i < g; i++)
    printf("%2d\t", gant[i].ct);
  printf("\nTable :\n");
  printf(" _________________________________\n");
  printf("|Process| AT | BT | CT | TT | WT |\n");
  printf("|--------------------------------|\n");
  for (i = 0; i < n; i++) {
    printf("|p%d \t| %2d | %2d | %2d | %2d | %2d |\n", p[i].no, p[i].at,
           p[i].bt, p[i].ct, p[i].tt, p[i].wt);
  }
  printf(" _________________________________\n");
  twt = twt / n;
  tat = tat / n;
  printf("\nAverage WT:%f\n", twt);
  printf("Average TT:%f\n", tat);
  return 0;
}
