#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

typedef struct process {
  pid_t pid;
  size_t arriv_time, burst_time, complt_time, taround_time, wait_time;
} process_t;

void get_process_list(process_t *list, int num_of_processes) {
  for (int i = 0; i < num_of_processes; i++) {
    printf("Enter the details of 'Process-%d':\n", i + 1);
    list[i].pid = i + 1;
    printf("Enter the arrival time: ");
    scanf("%zu", &list[i].arriv_time);
    printf("Enter the burst time: ");
    scanf("%zu", &list[i].burst_time);
  }
}

int ascending_compare(const void *a, const void *b) {
  process_t process_a = *((process_t *)a);
  process_t process_b = *((process_t *)b);
  return process_a.arriv_time - process_b.arriv_time;
}

void queify(process_t *list, int num_of_processes) {
  for (int i = 0, cpu_time = 0; i < num_of_processes; i++) {
    int idle_time = list[i].arriv_time - cpu_time;
    cpu_time += idle_time > 0 ? idle_time : 0;
    cpu_time += list[i].burst_time;
    list[i].complt_time = cpu_time;
    list[i].taround_time = cpu_time - list[i].arriv_time;
    list[i].wait_time = list[i].taround_time - list[i].burst_time;
  }
}

void print_hr(int cols) {
  for (int i = 0; i < cols; i++) {
    printf("--------");
  }
  printf("\n");
}

void print_process_table(process_t *list, int num_of_processes) {
  if (!num_of_processes)
    return;
  printf("Process table:\n");
  print_hr(6);
  printf("|  PID  |  AT   |  BT   |  CT   |  TT   |  WT   |\n");
  print_hr(6);
  for (int i = 0; i < num_of_processes; i++) {
    printf("|%4d   |%4zu   |%4zu   |%4zu   |%4zu   |%4zu   |\n", list[i].pid,
           list[i].arriv_time, list[i].burst_time, list[i].complt_time,
           list[i].taround_time, list[i].wait_time);
    print_hr(6);
  }
  printf("\n");
}

void print_gantt_chart(process_t *list, int num_of_processes) {
  printf("Gantt chart:\n");
  print_hr(num_of_processes);
  printf("|");
  for (int i = 0, cpu_time = 0; i < num_of_processes; i++) {
    int idle_time = list[i].arriv_time - cpu_time;
    if (idle_time > 0) {
      cpu_time += idle_time;
      printf("  idle  |");
    }
    cpu_time += list[i].burst_time;
    printf("   P%-4d|", list[i].pid);
  }
  printf("\n");
  printf("0        ");
  for (int i = 0, cpu_time = 0; i < num_of_processes; i++) {
    int idle_time = list[i].arriv_time - cpu_time;
    if (idle_time > 0) {
      cpu_time += idle_time;
      printf("%-9d", cpu_time);
    }
    cpu_time += list[i].burst_time;
    printf("%-8d", cpu_time);
  }
  printf("\n");
}

int main(int argc, char *argv[]) {
  int num_of_processes;
  printf("Enter the number of processes: ");
  scanf("%d", &num_of_processes);
  process_t process_list[num_of_processes];
  get_process_list(process_list, num_of_processes);
  qsort(process_list, num_of_processes, sizeof(process_t), ascending_compare);
  queify(process_list, num_of_processes);
  print_process_table(process_list, num_of_processes);
  print_gantt_chart(process_list, num_of_processes);
  int total_wt = 0, total_tt = 0;
  for (int i = 0; i < num_of_processes; i++) {
    total_tt += process_list[i].taround_time;
    total_wt += process_list[i].wait_time;
  }
  double avg_tt = (double)total_tt / num_of_processes;
  double avg_wt = (double)total_wt / num_of_processes;
  printf("Average turn-around time: %.3lf\n"
         "Average waiting time: %.3lf\n",
         avg_tt, avg_wt);
  return 0;
}
