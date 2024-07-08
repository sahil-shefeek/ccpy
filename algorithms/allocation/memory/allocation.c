#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Models a process with its pid, memory requirement and a flag (to show if it's
// allocated or not).
typedef struct process {
  int pid;
  int memory_req;
  bool is_allocated;
} process_t;

// Models a memory block with it's size and information regarding the process
// that is allocated to it.
// Allocation status of NULL means no process has allocated that memory block.
typedef struct mem_block {
  int size;
  process_t *allocation_status;
} mem_block_t;

// A function to print horizontal lines. (Prevents excessive code duplication)
void print_hr(int count) {
  for (int i = 0; i < count; i++)
    printf("------");
  printf("\n");
}

void display(mem_block_t *memory_blks, int num_blocks, process_t *processes,
             int num_processes) {
  int hr_len = num_blocks + num_processes;
  printf("Memory blocks\n");
  print_hr(hr_len);
  for (int i = 0; i < num_blocks; i++) {
    printf("|%3d   ", memory_blks[i].size);
  }
  printf("|\n"), print_hr(hr_len);
  printf("\nMemory blocks after allocation\n");
  print_hr(hr_len), printf("|");
  int total_fragmentation = 0;
  for (int i = 0; i < num_blocks; i++) {
    if (memory_blks[i].allocation_status == NULL) {
      printf("  %d  |", memory_blks[i].size);
    } else {
      int fragmentation =
          memory_blks[i].size - memory_blks[i].allocation_status->memory_req;
      total_fragmentation += fragmentation;
      printf(" %d + %d |", memory_blks[i].allocation_status->memory_req,
             fragmentation);
    }
  }
  printf("\n"), print_hr(hr_len), printf("\n");

  for (int i = 0; i < num_blocks; i++) {
    if (memory_blks[i].allocation_status == NULL) {
      printf("      ");
    } else {
      printf("     %d     ", memory_blks[i].allocation_status->pid);
    }
  }
  printf("\n");

  for (int i = 0; i < num_processes; i++) {
    if (!processes[i].is_allocated)
      printf("Process %d was not allocated.\n", processes[i].pid);
  }
  printf("\n");
  printf("Total internal fragmentation = %d\n", total_fragmentation);
}

// Comparison functions gives the sorting logic to qsort()
// Can be removed if qsort() is replced with another sorting alogorithm

int ascending_compare(const void *a, const void *b) {
  mem_block_t block_a = *((mem_block_t *)a);
  mem_block_t block_b = *((mem_block_t *)b);
  return block_a.size - block_b.size;
}

int descending_compare(const void *a, const void *b) {
  mem_block_t block_a = *((mem_block_t *)a);
  mem_block_t block_b = *((mem_block_t *)b);
  return block_b.size - block_a.size;
}

void handle_firstfit(mem_block_t *memory_blks, int num_blocks,
                     process_t *processes, int num_processes) {
  for (int i = 0; i < num_processes; i++) {
    for (int j = 0; j < num_blocks; j++) {
      if (processes[i].memory_req <= memory_blks[j].size &&
          memory_blks[j].allocation_status == NULL) {
        memory_blks[j].allocation_status = &processes[i];
        processes[i].is_allocated = true;
        break;
      }
    }
  }
  display(memory_blks, num_blocks, processes, num_processes);
}

void handle_bestfit(mem_block_t *memory_blks, int num_blocks,
                    process_t *processes, int num_processes) {
  // Sorts the memory blocks in the ascending order of their block sizes. Can be
  // replaced with any sorting alogorithm.
  qsort(memory_blks, num_blocks, sizeof(mem_block_t), ascending_compare);
  handle_firstfit(memory_blks, num_blocks, processes, num_processes);
}

void handle_worstfit(mem_block_t *memory_blks, int num_blocks,
                     process_t *processes, int num_processes) {
  // Sorts the memory blocks in the descending order of their block sizes. Can
  // be replaced with any sorting alogorithm.
  qsort(memory_blks, num_blocks, sizeof(mem_block_t), descending_compare);
  handle_firstfit(memory_blks, num_blocks, processes, num_processes);
}

int main() {
  int num_blocks, num_processes;
  printf("Enter the number of memory blocks: ");
  scanf("%d", &num_blocks);
  mem_block_t memory_blks[num_blocks];
  printf("Enter the memory blocks: ");
  for (int i = 0; i < num_blocks; i++) {
    scanf("%d", &memory_blks[i].size);
    memory_blks[i].allocation_status = NULL;
  }

  printf("Enter the number of processes: ");
  scanf("%d", &num_processes);
  process_t processes[num_processes];
  printf("Enter the process memory requirements:\n");
  for (int i = 0; i < num_processes; i++) {
    scanf("%d", &processes[i].memory_req);
    processes[i].pid = i + 1;
    processes[i].is_allocated = false;
  }
  int choice = -1;
  while (1) {
    mem_block_t copy_of_memory_blks[num_blocks];
    memcpy(copy_of_memory_blks, memory_blks, sizeof(memory_blks));
    process_t copy_of_processes[num_processes];
    memcpy(copy_of_processes, processes, sizeof(processes));
    printf("Select allocation method:\n"
           "1. First-fit\n"
           "2. Best-fit\n"
           "3. Worst-fit\n"
           "4. Exit\n");
    scanf("%d", &choice);
    switch (choice) {
    case 1:
      handle_firstfit(copy_of_memory_blks, num_blocks, copy_of_processes,
                      num_processes);
      break;
    case 2:
      handle_bestfit(copy_of_memory_blks, num_blocks, copy_of_processes,
                     num_processes);
      break;
    case 3:
      handle_worstfit(copy_of_memory_blks, num_blocks, copy_of_processes,
                      num_processes);
      break;
    case 4:
      return 0;
    default:
      printf("Invalid choice!\n");
    }
  }
  return 0;
}
