#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define SERVER_PORT 8080
#define SOCKET_ERROR (-1)
#define SERVER_BUF_SIZE 128
#define CLIENT_BUF_SIZE 128

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
  int sock = *(int *)arg;
  char client_buf[CLIENT_BUF_SIZE];

  while (1) {
    memset(client_buf, 0, CLIENT_BUF_SIZE);
    if (fgets(client_buf, CLIENT_BUF_SIZE, stdin) != NULL) {
      int ret = send(sock, client_buf, strlen(client_buf), 0);
      if (ret < 0) {
        perror("Failed sending server data");
        break;
      }
    }
  }
  return NULL;
}

void *recv_msg(void *arg) {
  int sock = *(int *)arg;
  char server_buf[SERVER_BUF_SIZE];

  while (1) {
    memset(server_buf, 0, SERVER_BUF_SIZE);
    int bytes_recvd = recv(sock, server_buf, SERVER_BUF_SIZE, 0);
    if (bytes_recvd > 0) {
      printf("[SERVER]: %s\n", server_buf);
    } else if (bytes_recvd == 0) {
      printf("Server disconnected!\n");
      break;
    } else {
      perror("Error receiving data");
      break;
    }
  }
  return NULL;
}

int main() {
  int sock = check(socket(AF_INET, SOCK_STREAM, 0), "Socket creation failed!");

  SA_IN server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(SERVER_PORT);
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

  check(connect(sock, (SA *)&server_addr, sizeof(server_addr)),
        "Connection to server failed!");

  pthread_t send_thread, recv_thread;
  if (pthread_create(&send_thread, NULL, send_msg, (void *)&sock) != 0) {
    perror("Could not create send thread");
    exit(EXIT_FAILURE);
  }
  if (pthread_create(&recv_thread, NULL, recv_msg, (void *)&sock) != 0) {
    perror("Could not create recv thread");
    exit(EXIT_FAILURE);
  }
  printf("Server connected!\n");

  pthread_join(send_thread, NULL);
  pthread_join(recv_thread, NULL);

  close(sock);
  return 0;
}
