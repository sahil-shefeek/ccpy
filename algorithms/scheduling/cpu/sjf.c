#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#define GANTT_SIZE 10

typedef struct process {
  pid_t pid;
  int arrival_time, burst_time;
  int completion_time, turn_around_time, waiting_time;
} process_t;

int ascending_compare(const void *a, const void *b) {
  process_t process_a = *((process_t *)a);
  process_t process_b = *((process_t *)b);
  return process_a.arrival_time - process_b.arrival_time;
}

void sjf(process_t *processes, int num_of_processes, process_t *gantt_chart) {
  int cpu_time = 0, g_index = 0;
  process_t cpu_idle;
  cpu_idle.burst_time = 0;
  for (int i = 0; i < num_of_processes; i++) {
    if (cpu_time < processes[i].arrival_time) {
      // No process has arrived yet. Fast forwarding cpu_time...
      // Add cpu idling to gantt chart
      gantt_chart[g_index] = cpu_idle;
      cpu_time = processes[i--].arrival_time;
      gantt_chart[g_index++].completion_time = cpu_time;
    } else {
      // We have a process!
      // Finding the shortest job from the arrived jobs.
      int sji = i;
      process_t shortest_job = processes[i];
      for (int j = i;
           j < num_of_processes && processes[j].arrival_time < cpu_time; j++) {
        if (processes[j].burst_time < shortest_job.burst_time) {
          shortest_job = processes[j];
          sji = j;
        }
      }
      if (i != sji) {
        processes[sji] = processes[i];
        processes[i] = shortest_job;
      }
      cpu_time += processes[i].burst_time;
      processes[i].completion_time = cpu_time;
      gantt_chart[g_index++] = processes[i];
    }
  }

  double total_waiting_time = 0, total_turn_around_time = 0;
  for (int i = 0; i < num_of_processes; i++) {
    processes[i].turn_around_time =
        processes[i].completion_time - processes[i].arrival_time;
    processes[i].waiting_time =
        processes[i].turn_around_time - processes[i].burst_time;
    total_waiting_time += processes[i].waiting_time;
    total_turn_around_time += processes[i].turn_around_time;
  }
  total_waiting_time = (double)total_waiting_time / num_of_processes;
  total_turn_around_time = (double)total_turn_around_time / num_of_processes;

  printf("Gantt chart:\n");
  for (int i = 0; i < g_index; i++) {
    if (gantt_chart[i].burst_time == 0)
      printf("| Idle   ");
    else
      printf("| p%d    ", gantt_chart[i].pid);
  }
  printf("|\n");
  printf("0\t");
  for (int i = 0; i < g_index; i++)
    printf("%2d\t", gantt_chart[i].completion_time);
  printf("\nTable :\n");
  printf(" _________________________________\n");
  printf("|Process| AT | BT | CT | TT | WT |\n");
  printf("|--------------------------------|\n");
  for (int i = 0; i < num_of_processes; i++) {
    printf("|p%d \t| %2d | %2d | %2d | %2d | %2d |\n", processes[i].pid,
           processes[i].arrival_time, processes[i].burst_time,
           processes[i].completion_time, processes[i].turn_around_time,
           processes[i].waiting_time);
  }
  printf(" _________________________________\n");

  printf("\nAverage WT:%lf\n", total_waiting_time);
  printf("Average TT:%lf\n", total_turn_around_time);
}

int main() {
  int num_of_processes;
  printf("Enter the number of processes: ");
  scanf("%d", &num_of_processes);
  process_t processes[num_of_processes];
  for (int i = 0; i < num_of_processes; i++) {
    printf("Enter the arrival time and burst time of: Process %d\n", i + 1);
    scanf("%d%d", &processes[i].arrival_time, &processes[i].burst_time);
    processes[i].pid = i + 1;
  }
  // Sort processes according to Arrival time.
  qsort(processes, num_of_processes, sizeof(processes), ascending_compare);
  process_t gantt_chart[GANTT_SIZE];
  sjf(processes, num_of_processes, gantt_chart);

  return 0;
}
