#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define BUFFER_SIZE 10

int buffer[BUFFER_SIZE];
int count;
sem_t sem_full, sem_empty;
pthread_mutex_t mutex_buffer;

void *producer_routine() {
  while (1) {
    int produce = (rand() % 100) + 1;
    sleep(1);
    printf("Produced %d\n", produce);
    sem_wait(&sem_empty);
    pthread_mutex_lock(&mutex_buffer);
    buffer[count++] = produce;
    pthread_mutex_unlock(&mutex_buffer);
    sem_post(&sem_full);
  }
}

void *consumer_routine() {
  while (1) {
    sem_wait(&sem_full);
    pthread_mutex_lock(&mutex_buffer);
    int consumption = buffer[count - 1];
    count--;
    printf("Got %d\n", consumption);
    pthread_mutex_unlock(&mutex_buffer);
    sem_post(&sem_empty);
  }
}

int main() {
  srand(time(NULL));
  sem_init(&sem_empty, 0, BUFFER_SIZE);
  sem_init(&sem_full, 0, 0);
  pthread_mutex_init(&mutex_buffer, NULL);
  int num_producers, num_consumers;
  printf("Enter the number of producers: ");
  scanf("%d", &num_producers);
  printf("Enter the number of consumers: ");
  scanf("%d", &num_consumers);
  pthread_t producers[num_producers], consumers[num_consumers];
  for (int i = 0; i < num_producers; i++) {
    pthread_create(&producers[i], NULL, &producer_routine, NULL);
  }
  for (int i = 0; i < num_consumers; i++) {
    pthread_create(&consumers[i], NULL, &consumer_routine, NULL);
  }
  for (int i = 0; i < num_producers; i++) {
    pthread_join(producers[i], NULL);
  }
  for (int i = 0; i < num_consumers; i++) {
    pthread_join(consumers[i], NULL);
  }
  sem_destroy(&sem_full);
  sem_destroy(&sem_empty);
  pthread_mutex_destroy(&mutex_buffer);
  return 0;
}
