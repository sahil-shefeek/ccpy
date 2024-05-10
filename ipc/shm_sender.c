#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <unistd.h>
int main() {
  int shmid;
  char s[25];
  shmid = shmget(1127, 1024, 0666 | IPC_CREAT);
  void *sh = shmat(shmid, NULL, 0);
  printf("Enter the limit:");
  gets(s);
  strcpy(sh, s);
  return 0;
}
