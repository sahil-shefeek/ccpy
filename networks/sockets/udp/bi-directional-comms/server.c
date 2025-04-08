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

SA_IN last_client_addr;
int has_client = 0;

int check(int exp, const char *msg)
{
  if (exp == SOCKET_ERROR)
  {
    perror(msg);
    exit(EXIT_FAILURE);
  }
  return exp;
}

void *handle_client_messages(void *server_sock)
{
  int server = *(int *)server_sock;
  char recv_buf[BUF_SIZE];
  int recvd_bytes;
  SA_IN client_addr;
  socklen_t addr_size = sizeof(client_addr);

  while (1)
  {
    recvd_bytes = check(recvfrom(server, recv_buf, BUF_SIZE, 0, (SA *)&client_addr, &addr_size), "Error receiving data from client");
    recv_buf[recvd_bytes] = '\0';
    printf("Client (%s:%d): %s\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port), recv_buf);
    if (!has_client)
    {
      memcpy(&last_client_addr, &client_addr, sizeof(client_addr));
      has_client = 1;
    }
  }

  pthread_exit(0);
}

int main()
{
  int sock = check(socket(AF_INET, SOCK_DGRAM, 0), "Socket creation failed");
  SA_IN server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

  check(bind(sock, (SA *)&server_addr, sizeof(server_addr)), "Socket binding failed");
  printf("UDP Server listening at port %d\n", PORT);

  pthread_t recv_thread;
  pthread_create(&recv_thread, NULL, handle_client_messages, (void *)&sock);
  pthread_detach(recv_thread);

  char send_buf[BUF_SIZE];
  while (1)
  {
    printf("Enter data to send: ");
    fgets(send_buf, BUF_SIZE, stdin);
    if (has_client)
    {
      check(sendto(sock, send_buf, strlen(send_buf), 0, (SA *)&last_client_addr, sizeof(last_client_addr)), "Failed to send data to client");
    }
    else
    {
      printf("No client has connected yet. Message not sent.\n");
    }
  }
  close(sock);
  return 0;
}
