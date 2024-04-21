#include <stdio.h>
#include <string.h>

int main() {
  int num_of_processes, num_of_res_types;
  printf("Enter the number of processes: \n");
  scanf("%d", &num_of_processes);
  printf("Enter the number of resource types: \n");
  scanf("%d", &num_of_res_types);
  int alloc[num_of_processes][num_of_res_types],
      max_res[num_of_processes][num_of_res_types],
      need[num_of_processes][num_of_res_types], total_res[num_of_res_types],
      available[num_of_res_types], finish[num_of_processes],
      sequence[num_of_processes], sequence_counter = 0;
  memset(finish, 0, num_of_processes * sizeof(int));
  memset(sequence, -1, num_of_processes * sizeof(int));
  for (int i = 0; i < num_of_res_types; i++) {
    printf("Total number of instances of Resource R%d: ", i);
    scanf("%d", &total_res[i]);
  }
  for (int i = 0; i < num_of_processes; i++) {
    printf("Process-%d\n", i);
    for (int j = 0; j < num_of_res_types; j++) {
      printf("How many instances of resource R%d are allocated?\n", j);
      scanf("%d", &alloc[i][j]);
    }
    for (int j = 0; j < num_of_res_types; j++) {
      printf("How many instances of resource R%d are needed at max?\n", j);
      scanf("%d", &max_res[i][j]);
      need[i][j] = max_res[i][j] - alloc[i][j];
    }
  }
  for (int i = 0; i < num_of_res_types; i++) {
    int temp = 0;
    for (int j = 0; j < num_of_processes; j++) {
      temp += alloc[j][i];
    }
    available[i] = total_res[i] - temp;
  }

  printf("Resource allocation table\n"
         "Process  |  Allocation  |  Max  |  Avaliable  |  Need\n");
  for (int i = 0; i < num_of_processes; i++) {
    printf("P-%d:  ", i);
    for (int j = 0; j < num_of_res_types; j++) {
      printf("%d ", alloc[i][j]);
    }
    printf("   ");
    for (int j = 0; j < num_of_res_types; j++) {
      printf("%d ", max_res[i][j]);
    }
    printf("   ");
    for (int j = 0; j < num_of_res_types; j++) {
      printf("%d ", available[j]);
    }
    printf("   ");
    for (int j = 0; j < num_of_res_types; j++) {
      printf("%d ", need[i][j]);
    }
    printf("\n");
  }
  printf("Total number of resources:\n");
  for (int i = 0; i < num_of_res_types; i++) {
    printf("%d  ", total_res[i]);
  }
  printf("\n");

  int req_process, req_needs[num_of_res_types];
  printf("Enter pid of requesting process: ");
  scanf("%d", &req_process);
  for (int i = 0; i < num_of_res_types; i++) {
    printf("How many instances of resource R%d is needed? ", i);
    scanf("%d", &req_needs[i]);
  }
  for (int i = 0; i < num_of_processes; i++) {
    for (int j = 0; j < num_of_res_types; j++) {
      if (need[req_process][j] < req_needs[j] || available[j] < req_needs[j]) {
        printf("Allocation failed!\n");
      }
    }
  }
  for (int i = 0; i < num_of_res_types; i++) {
    alloc[req_process][i] += req_needs[i];
    need[req_process][i] -= req_needs[i];
    available[i] -= req_needs[i];
  }
  printf("Modified Resource allocation table\n"
         "|  Process  |  Allocation  |  Max  |  Avaliable  |  Need  |\n");
  for (int i = 0; i < num_of_processes; i++) {
    printf("|  P-%d:  ", i);
    for (int j = 0; j < num_of_res_types; j++) {
      printf("%d ", alloc[i][j]);
    }
    printf(" | ");
    for (int j = 0; j < num_of_res_types; j++) {
      printf("%d ", max_res[i][j]);
    }
    printf(" | ");
    for (int j = 0; j < num_of_res_types; j++) {
      printf("%d ", available[j]);
    }
    printf(" | ");
    for (int j = 0; j < num_of_res_types; j++) {
      printf("%d ", need[i][j]);
    }
    printf("|\n");
  }
  for (int i = 0; i < num_of_processes; i++) {
    for (int j = 0; j < num_of_processes; j++) {
      int flag = 0;
      if (finish[j] == 0) {
        for (int k = 0; k < num_of_res_types; k++) {
          if (need[j][k] > available[k]) {
            flag = 1;
            break;
          }
        }
        if (flag == 0) {
          printf("Process %d completed!\n", j);
          for (int k = 0; k < num_of_res_types; k++) {
            available[k] += alloc[j][k];
          }
          finish[j] = 1;
          sequence[sequence_counter] = j;
          sequence_counter++;
        }
      }
    }
  }
  int is_completed = 1;
  for (int i = 0; i < num_of_processes; i++) {
    if (finish[i] == 0) {
      is_completed = 0;
      break;
    }
  }
  if (is_completed) {
    printf("Finish:\n");
    for (int i = 0; i < num_of_processes; i++) {
      printf("%d", finish[i]);
    }
    printf("\nSafety sequence:\n");
    for (int i = 0; i < num_of_processes; i++) {
      printf("P%d -> ", sequence[i]);
    }
  } else {
    printf("Deadlock condition\n");
  }

  return 0;
}
