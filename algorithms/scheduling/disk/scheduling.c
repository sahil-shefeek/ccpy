#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OFFSET 3

enum { LOOK = 0, SCAN } mode;

int ascending_compare(const void *a, const void *b) {
  int num_a = *((int *)a);
  int num_b = *((int *)b);
  return num_a - num_b;
}

void fcfs(int *requests, int number_of_request) {
  int total_head_movement = 0;
  // Print 1st served request
  printf("Sequence : %d ", requests[0]);
  // Go through traversed requests array
  // Number_of_request is less than actual as we didn't count initial_position
  for (int i = 0; i < number_of_request; i++) {
    // Print the rest serves
    printf(",  %d", requests[i + 1]);
    total_head_movement += abs(requests[i + 1] - requests[i]);
  }
  printf("\nTotal head movement = %d \n", total_head_movement);
}

void scan_or_look(int *requests, int number_of_request, int initial_position,
                  int mode) {
  int choice, total_head_movement = 0;
  int traversed[number_of_request];

  printf("Choose direction\n"
         "1. Left\n"
         "2. Right\n");
  scanf("%d", &choice);
  // Initial chosen direction
  // Increment(+1) or Decrement(-1) from initial_position
  int inc = (choice == 1) ? (-1) : 1;

  // sort requests
  qsort(requests, number_of_request, sizeof(int), ascending_compare);

  // Find index of initial_position in request array
  int i = 0;
  while (i < number_of_request && requests[i] != initial_position)
    i++;
  int loc = i;

  // MAIN LOGIC
  int traverse_index = 0;
  while (traverse_index < number_of_request - mode) {
    // Go through all sorted requests starting from initial position
    traversed[traverse_index++] = requests[i];
    // Increment index in chosen direction
    i += inc;
    // When head reaches end of disk (0 or n-1 index)
    if ((i < 0 || i > number_of_request - 1) &&
        traverse_index < number_of_request - 1) {
      inc *= (-1);
      i = loc + inc;
    }
  }
  fcfs(traversed, traverse_index - 1);
}

void cscan(int *requests, int number_of_request, int initial_position) {
  int choice, total_head_movement = 0;
  int traversed[number_of_request];

  printf("Choose direction\n"
         "1. Left\n"
         "2. Right\n");
  scanf("%d", &choice);
  // Initial chosen direction
  // Increment(+1) or Decrement(-1) from initial_position
  int inc = (choice == 1) ? (-1) : 1;

  // sort requests
  qsort(requests, number_of_request, sizeof(int), ascending_compare);

  // Find index of initial_position in request array
  int i = 0;
  while (i < number_of_request && requests[i] != initial_position)
    i++;
  int loc = i;

  // MAIN LOGIC
  int traverse_index = 0;
  while (traverse_index < number_of_request) {
    // Go through all sorted requests starting from initial position
    traversed[traverse_index++] = requests[i];
    // Increment index in chosen direction
    i += inc;
    // When head reaches end of disk (0 or n-1 index)
    if ((i < 0 || i > number_of_request - 1) &&
        traverse_index < number_of_request - 1) {
      // Reset index to next to initial_position to start traversal from that
      // request to other end Reset direction to opposite of initial chosen
      // direction by changing increment
      i = i < 0 ? number_of_request - 1 : 0;
    }
  }
  fcfs(traversed, traverse_index - 1);
}

int main() {
  int number_of_request, initial_position;
  printf("Enter the number of requests: ");
  scanf("%d", &number_of_request);
  int requests[number_of_request + OFFSET];
  printf("Enter the Requests:\n");
  for (int i = 1; i < number_of_request + 1; i++)
    scanf("%d", &requests[i]);

  int disk_start, disk_end;
  printf("Enter the Start and End of disk: ");
  scanf("%d%d", &disk_start, &disk_end);
  // Add disk start and end to request array
  requests[++number_of_request] = disk_start;
  requests[++number_of_request] = disk_end;

  // Enter the initial position
  printf("Enter the initial position: ");
  scanf("%d", &initial_position);
  requests[0] = initial_position;
  number_of_request++;

  int choice = -1;
  while (1) {
    // Choose the scheduling
    int copy_of_requests[number_of_request + OFFSET];
    memcpy(copy_of_requests, requests, sizeof(requests));
    printf("Menu\n"
           "1. FCFS\n"
           "2. SCAN\n"
           "3. CSCAN\n"
           "4. SCAN\n"
           "5. CSCAN\n"
           "6. Exit\n");
    scanf("%d", &choice);
    switch (choice) {
    case 1:
      fcfs(copy_of_requests, number_of_request - 3);
      break;
    case 2:
      scan_or_look(copy_of_requests, number_of_request, initial_position, SCAN);
      break;
    case 3:
      cscan(copy_of_requests, number_of_request, initial_position);
      break;
    case 4:
      scan_or_look(copy_of_requests, number_of_request - 2, initial_position,
                   LOOK);
      break;
    case 5:
      cscan(copy_of_requests, number_of_request - 2, initial_position);
      break;
    case 6:
      return 0;
    default:
      printf("Invalid input\n");
    }
  }
  return 0;
}

// 8 98 183 37 122 14 124 65 67 0 199 53 1 2 1 2 2 3 1 3 2 4 1 4 2 5 1 5 2
