#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#define MAX 30

int queue[MAX], front = -1, rear = -1;

typedef struct process {
  pid_t pid;
  int arrival_time, burst_time, completion_time, turn_around_time, waiting_time,
      remaining_burst;
} process_t;

void enqueue(int item) {
  if (front == -1)
    front = 0;
  queue[++rear] = item;
}

void enqueue_front(int item) {
  if (front == -1) {
    front = 0;
    queue[++rear] = item;
  } else {
    for (int i = rear; i >= front; i--) {
      queue[i + 1] = queue[i];
    }
    rear++;
    queue[front] = item;
  }
}

int ascending_compare(const void *a, const void *b) {
  process_t process_a = *((process_t *)a);
  process_t process_b = *((process_t *)b);
  return process_a.arrival_time - process_b.arrival_time;
}

int dequeue_srtj(process_t *processes) {
  int srtj = -1;
  if (front != -1) {
    // Sort the queue in ascending order of arrival time
    qsort(queue + front, rear - front, sizeof(int), ascending_compare);
    // Assume first process as the srtj
    int srtj_loc = front;
    srtj = queue[front];
    for (int i = front; i <= rear; i++) {
      if (processes[queue[i]].remaining_burst <
          processes[srtj].remaining_burst) {
        // If the job at queue[i] is shorter, srtj = queue[i]
        srtj = queue[i];
        srtj_loc = i;
      }
    }
    if (srtj_loc != front) {
      // Swap the current queue[front] with the srtj
      queue[srtj_loc] = queue[front];
      queue[front] = srtj;
    }
    // normal dequeue() logic
    srtj = queue[front];
    if (front == rear)
      front = rear = -1;
    else
      front = front + 1;
  }
  return srtj;
}

void handle_srtj(process_t *processes, int num_of_processes) {
  int cpu_time = 0, time_unit = 1;
  process_t idle, gantt[MAX];
  idle.burst_time = 0;

  int i = 0, preemp_proc = -1, g_index = 0;

  while (front > -1 || i < num_of_processes) {
    // !queue.is_empty() || not allocated for all processes.
    while (i < num_of_processes && processes[i].arrival_time <= cpu_time) {
      // arrived processes
      enqueue(i);
      i++;
    }

    if (front >= 0) {
      preemp_proc = dequeue_srtj(processes);
      gantt[g_index] = processes[preemp_proc];
      int temp = ((time_unit < gantt[g_index].remaining_burst)
                      ? time_unit
                      : gantt[g_index].remaining_burst);
      cpu_time += temp;
      processes[preemp_proc].remaining_burst -= temp;
      gantt[g_index++].completion_time = cpu_time;
      processes[preemp_proc].completion_time = cpu_time;
      if (preemp_proc != -1 && processes[preemp_proc].remaining_burst != 0)
        // add the preempted process back to the ready queue
        enqueue_front(preemp_proc);
    } else {
      gantt[g_index] = idle;
      gantt[g_index++].completion_time = cpu_time = processes[i].arrival_time;
    }
  }
  double tat = 0, twt = 0;
  for (i = 0; i < num_of_processes; i++) {
    processes[i].turn_around_time =
        processes[i].completion_time - processes[i].arrival_time;
    processes[i].waiting_time =
        processes[i].turn_around_time - processes[i].burst_time;
    twt = twt + processes[i].waiting_time;
    tat = tat + processes[i].turn_around_time;
  }
  printf("Gantt chart:\n");
  for (i = 0; i < g_index - 1; i++) {
    if (gantt[i].burst_time == 0)
      printf("| Idle   ");
    else if (gantt[i].pid != gantt[i + 1].pid)
      printf("| p%d    ", gantt[i].pid);
  }
  printf("| p%d    |\n", gantt[i].pid);
  printf("0\t");
  for (i = 0; i < g_index - 1; i++) {
    if (gantt[i].pid != gantt[i + 1].pid)
      printf("%2d\t", gantt[i].completion_time);
  }
  printf("%2d\t", gantt[i].completion_time);
  printf("\nTable :\n");
  printf(" _________________________________\n");
  printf("|Process| AT | BT | CT | TT | WT |\n");
  printf("|--------------------------------|\n");
  for (i = 0; i < num_of_processes; i++) {
    printf("|p%d \t| %2d | %2d | %2d | %2d | %2d |\n", processes[i].pid,
           processes[i].arrival_time, processes[i].burst_time,
           processes[i].completion_time, processes[i].turn_around_time,
           processes[i].waiting_time);
  }
  printf(" _________________________________\n");
  twt = twt / num_of_processes;
  tat = tat / num_of_processes;
  printf("\nAverage WT:%f\n", twt);
  printf("Average TT:%f\n", tat);
}

int main() {
  int num_of_processes;
  process_t processes[MAX];
  printf("Enter the number of processes: ");
  scanf("%d", &num_of_processes);
  for (int i = 0; i < num_of_processes; i++) {
    printf("Enter Arrival time and Burst Time of process %d: \n", i + 1);
    scanf("%d%d", &processes[i].arrival_time, &processes[i].burst_time);
    processes[i].pid = i + 1;
    // rbt = bt
    processes[i].remaining_burst = processes[i].burst_time;
  }
  // sort process based on arrival time

  qsort(processes, num_of_processes, sizeof(process_t), ascending_compare);

  handle_srtj(processes, num_of_processes);
  return 0;
}

// 5 2 6 5 2 1 8 0 3 4 4
// 5 2 6 0 3 0 3 0 3 4 4
