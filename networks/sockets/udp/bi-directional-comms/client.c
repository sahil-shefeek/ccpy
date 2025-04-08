#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <string.h>

#define SOCKET_ERROR (-1)
#define PORT 8080
#define BUF_SIZE 1024

typedef struct sockaddr SA;
typedef struct sockaddr_in SA_IN;

int check(int exp, const char *msg)
{
  if (exp == SOCKET_ERROR)
  {
    perror(msg);
    exit(EXIT_FAILURE);
  }
  return exp;
}

void *handle_server_messages(void *server_sock)
{
  int server = *(int *)server_sock;
  char recv_buf[BUF_SIZE];
  int recvd_bytes;

  while (1)
  {
    recvd_bytes = check(recvfrom(server, recv_buf, BUF_SIZE, 0, NULL, NULL), "Error receiving data from server");
    recv_buf[recvd_bytes] = '\0';
    printf("Server: %s\n", recv_buf);
  }
  printf("Exiting receiver thread!\n");
  pthread_exit(0);
}

int main()
{
  int sock = check(socket(AF_INET, SOCK_DGRAM, 0), "Socket creation failed");
  SA_IN server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  printf("UDP client ready - sending to server at localhost:%d\n", PORT);

  pthread_t recv_thread;
  pthread_create(&recv_thread, NULL, handle_server_messages, (void *)&sock);
  pthread_detach(recv_thread);

  char send_buf[BUF_SIZE];
  while (1)
  {
    printf("Enter data to send: ");
    fgets(send_buf, BUF_SIZE, stdin);
    check(sendto(sock, send_buf, strlen(send_buf), 0, (SA *)&server_addr, sizeof(server_addr)),
          "Failed to send data to server");
  }
  close(sock);
  return 0;
}
