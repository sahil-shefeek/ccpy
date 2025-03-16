#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define SERVER_BACKLOG 5
#define MAX_CLIENTS 10
#define SOCKET_ERROR (-1)
#define SERVER_PORT 8080
#define MAX_CLIENT_BODY 128

typedef struct sockaddr_in SA_IN;
typedef struct sockaddr SA;

pthread_mutex_t client_mutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct client {
  int sock;
  int id;
} client_t;

typedef struct msg {
  int from;
  char body[MAX_CLIENT_BODY];
} msg_t;

client_t *clients[MAX_CLIENTS] = {NULL};

int check(int exp, const char *msg) {
  if (exp == SOCKET_ERROR) {
    perror(msg);
    exit(EXIT_FAILURE);
  }
  return exp;
}

void broadcast_message(msg_t msg, int sender_sock) {
  for (int i = 0; i < MAX_CLIENTS; i++) {
    if (clients[i] && clients[i]->sock != sender_sock) {
      if (send(clients[i]->sock, &msg, sizeof(msg), 0) == -1)
        printf("Send failed\n");
    }
  }
}

void *handle_client(void *arg) {
  client_t *client = (client_t *)arg;
  int bytes_recvd;
  msg_t msg;

  while ((bytes_recvd = check(recv(client->sock, &msg, sizeof(msg), 0),
                              "Failed to recieve data"))) {
    printf("Received message from client %d: %s\n", msg.from, msg.body);
    broadcast_message(msg, client->sock);
  }

  if (!bytes_recvd)
    printf("[INFO]: Client %d disconnected\n", client->id);

  pthread_mutex_lock(&client_mutex);
  for (int i = 0; i < MAX_CLIENTS; i++) {
    if (clients[i] == client) {
      clients[i] = NULL;
      break;
    }
  }
  pthread_mutex_unlock(&client_mutex);

  close(client->sock);
  free(client);
  pthread_exit(NULL);
}

int main() {
  SA_IN server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(SERVER_PORT);
  server_addr.sin_addr.s_addr = INADDR_ANY;

  int server_sock =
      check(socket(AF_INET, SOCK_STREAM, 0), "Socket creation failed!");
  check(bind(server_sock, (SA *)&server_addr, sizeof(server_addr)),
        "Socket binding failed!");
  check(listen(server_sock, SERVER_BACKLOG), "Listening on socket failed!");
  printf("Server running on port %d\n", SERVER_PORT);

  pthread_t client_threads[MAX_CLIENTS];

  while (1) {
    int new_client_sock = check(accept(server_sock, NULL, NULL),
                                "Failed to accept client connection!");
    client_t *new_client = malloc(sizeof(client_t));
    if (!new_client) {
      perror("malloc");
      continue;
    }
    new_client->id = rand() % 10000;
    new_client->sock = new_client_sock;

    pthread_mutex_lock(&client_mutex);
    int slot_found = 0;
    for (int i = 0; i < MAX_CLIENTS; i++) {
      if (!clients[i]) {
        clients[i] = new_client;
        if (pthread_create(&client_threads[i], NULL, handle_client,
                           (void *)new_client) != 0) {
          perror("Could not create thread");
          exit(EXIT_FAILURE);
        }
        printf("[NEW]: Client %d connected!\n", new_client->id);
        slot_found = 1;
        break;
      }
    }
    pthread_mutex_unlock(&client_mutex);

    if (!slot_found) {
      printf("Max clients reached. Connection rejected.\n");
      close(new_client_sock);
      free(new_client);
    }
  }

  close(server_sock);
  return 0;
}
