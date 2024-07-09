#include <stdio.h>
#include <stdlib.h>
typedef struct page {
  int page_no;
  int ref_index;
  int freq;
} page_t;

void fifo(int *refs, int num_refs, int num_frames) {}
void lru(int *refs, int num_refs, int num_frames) {}

int page_in_frame(int key_page_no, page_t *frames, int num_frames) {
  for (int i = 0; i < num_frames; i++) {
    if (frames[i].page_no == key_page_no) {
      return i;
    }
  }
  return -1;
}

int ascending_compare(const void *a, const void *b) {
  page_t page_a = *((page_t *)a);
  page_t page_b = *((page_t *)b);
  return page_a.ref_index - page_b.ref_index;
}

int get_lfu_index(page_t *frames, int num_frames) {
  int min_index = 0;
  qsort(frames, num_frames, sizeof(page_t), ascending_compare);
  page_t min_index_page = frames[0];
  for (int i = 0; i < num_frames; i++) {
    if (frames[i].freq < min_index_page.freq) {
      min_index_page = frames[i];
      min_index = i;
    }
  }
  return min_index;
}

void print_frames(page_t *frames, int num_frames) {
  for (int i = 0; i < num_frames; i++) {
    printf("|  %d  ", frames[i].page_no);
  }
  printf("|\n");
}

void lfu(int *refs, int num_refs, int num_frames) {
  page_t frames[num_frames];
  int frame_index = 0, page_faults = 0;
  for (int i = 0; i < num_refs; i++) {
    if (i < num_frames) {
      page_t page = {refs[i], i, 1};
      frames[i] = page;
      page_faults++;
      print_frames(frames, i + 1);
    } else {
      int index = page_in_frame(refs[i], frames, num_frames);
      if (index != -1) {
        frames[index].freq += 1;
      } else {
        page_t new_page = {refs[i], i, 1};
        int lfu_index = get_lfu_index(frames, num_frames);
        frames[lfu_index] = new_page;
        page_faults++;
        print_frames(frames, num_frames);
      }
    }
  }
  printf("Page faults = %d\n", page_faults);
}

int main() {
  int num_refs, num_frames;
  printf("Enter the number of references: ");
  scanf("%d", &num_refs);
  int refs[num_refs];
  printf("Enter the reference string: ");
  for (int i = 0; i < num_refs; i++)
    scanf("%d", &refs[i]);
  printf("Enter the number of frames: ");
  scanf("%d", &num_frames);
  while (1) {

    int choice;
    printf("Enter 1:FIFO 2:LRU 3:LFU 4:Exit :\n");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
      fifo(refs, num_refs, num_frames);
      break;
    case 2:
      lru(refs, num_refs, num_frames);
      break;
    case 3:
      lfu(refs, num_refs, num_frames);
    case 4:
      return 0;
    default:
      printf("Invalid input\n");
    }
  }
  return 0;
}

// 7 0 2 4 3 1 4 7 2 0 4 3 0 3 2 7
