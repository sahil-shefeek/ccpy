#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define SERVER_PORT 8080
#define MAX_CLIENT_BODY 128
#define SOCKET_ERROR (-1)

typedef struct sockaddr_in SA_IN;
typedef struct sockaddr SA;

int check(int exp, const char *msg) {
  if (exp == SOCKET_ERROR) {
    perror(msg);
    exit(EXIT_FAILURE);
  }
  return exp;
}

typedef struct msg {
  int from;
  char body[MAX_CLIENT_BODY];
} msg_t;

void *receive_messages(void *arg) {
  int sockfd = *(int *)arg;
  msg_t msg;
  int bytes_recvd;
  while ((bytes_recvd = check(recv(sockfd, &msg, sizeof(msg), 0),
                              "Failed to recieve data"))) {
    printf("Message received from %d: %s\n", msg.from, msg.body);
  }
  if (!bytes_recvd)
    printf("Server disconnected\n");
  close(sockfd);
  pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: %s <client_id>\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  int client_id = atoi(argv[1]);
  SA_IN server_addr;
  int server_sock =
      check(socket(AF_INET, SOCK_STREAM, 0), "Socket creation failed");
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(SERVER_PORT);
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  check(connect(server_sock, (SA *)&server_addr, sizeof(server_addr)),
        "Server connection failed");
  printf("Connected to the server on port %d\n", SERVER_PORT);

  pthread_t receive_thread;
  if (pthread_create(&receive_thread, NULL, receive_messages, &server_sock) !=
      0) {
    perror("Could not create receive thread");
    exit(EXIT_FAILURE);
  }

  msg_t msg;
  msg.from = client_id;
  while (1) {
    if (fgets(msg.body, MAX_CLIENT_BODY, stdin) == NULL)
      break;
    check(send(server_sock, &msg, sizeof(msg_t), 0), "Failed to send data");
  }

  close(server_sock);
  pthread_join(receive_thread, NULL);
  return 0;
}
