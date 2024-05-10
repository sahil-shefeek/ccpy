
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
int main() {
  int shmid = shmget(1127, 1024, 0666);
  void *shmem = shmat(shmid, NULL, 0);
  int n = atoi(shmem);
  printf("Data read is %d\n", n);
  int f = 1;
  for (int i = 1; i <= n; i++) {
    f = f * i;
  }
  printf("Factorial of %d : %d", n, f);
  return 0;
}
