#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define SERVER_BACKLOG 2
#define SOCKET_ERROR (-1)
#define SERVER_PORT 8080
#define CLIENT_BUF_SIZE 128
#define SERVER_BUF_SIZE 128

typedef struct sockaddr_in SA_IN;
typedef struct sockaddr SA;

int check(int exp, const char *msg) {
  if (exp == SOCKET_ERROR) {
    perror(msg);
    exit(EXIT_FAILURE);
  }
  return exp;
}

void *send_msg(void *arg) {
  int client_sock = *(int *)arg;
  char server_buf[SERVER_BUF_SIZE];

  while (1) {
    memset(server_buf, 0, SERVER_BUF_SIZE);
    if (fgets(server_buf, SERVER_BUF_SIZE, stdin) != NULL) {
      int ret = send(client_sock, server_buf, strlen(server_buf), 0);
      if (ret < 0) {
        perror("Failed sending client data");
        break;
      }
    }
  }
  return NULL;
}

void *recv_msg(void *arg) {
  int client_sock = *(int *)arg;
  char client_buf[CLIENT_BUF_SIZE];

  while (1) {
    memset(client_buf, 0, CLIENT_BUF_SIZE);
    int bytes_recvd = recv(client_sock, client_buf, CLIENT_BUF_SIZE, 0);
    if (bytes_recvd > 0) {
      printf("[CLIENT]: %s\n", client_buf);
    } else if (bytes_recvd == 0) {
      printf("Client disconnected!\n");
      break;
    } else {
      perror("Error receiving data");
      break;
    }
  }
  return NULL;
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

  int client_sock = check(accept(server_sock, NULL, NULL),
                          "Failed to accept client connection!");

  pthread_t send_thread, recv_thread;
  if (pthread_create(&send_thread, NULL, send_msg, (void *)&client_sock) != 0) {
    perror("Could not create send thread");
    exit(EXIT_FAILURE);
  }
  if (pthread_create(&recv_thread, NULL, recv_msg, (void *)&client_sock) != 0) {
    perror("Could not create recv thread");
    exit(EXIT_FAILURE);
  }
  printf("Client connected!\n");

  pthread_join(send_thread, NULL);
  pthread_join(recv_thread, NULL);

  close(client_sock);
  close(server_sock);
  return 0;
}
