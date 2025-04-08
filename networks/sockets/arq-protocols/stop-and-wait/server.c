#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <sys/types.h>
#include <stdbool.h>

#define PORT 8081
#define SOCKET_ERROR (-1)
#define BUF_SIZE 128

typedef struct sockaddr_in SA_IN;
typedef struct sockaddr SA;

int check(int exp, const char *msg)
{
  if (exp == SOCKET_ERROR)
  {
    perror(msg);
    exit(EXIT_FAILURE);
  }
  return exp;
}

typedef struct frame
{
  char data[BUF_SIZE];
  int seq;
  bool is_ack;
} frame_t;

typedef struct ack_frame
{
  int ack;
} ack_frame_t;

int main()
{
  int sock = check(socket(AF_INET, SOCK_DGRAM, 0), "Socket creation failed");
  SA_IN server_addr, client_addr;
  socklen_t client_len = sizeof(client_addr);
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  server_addr.sin_port = htons(PORT);
  server_addr.sin_family = AF_INET;
  check(bind(sock, (SA *)&server_addr, sizeof(server_addr)), "Socket binding failed");
  printf("UDP server listening at 127.0.0.1:%d\n", PORT);
  int frames_recvd = 0, expected_seq = 0;
  frame_t recvd_frame;
  ack_frame_t ack;
  int recv_len;
  do
  {
    recv_len = recvfrom(sock, &recvd_frame, sizeof(recvd_frame), 0, (SA *)&client_addr, &client_len);
    int drop = rand() % 10;
    if (drop < 2)
    {
      printf("Simulating a frame loss for %dth frame with seq %d.\n", frames_recvd, recvd_frame.seq);
    }
    else if (drop < 4)
    {
      printf("Simulating an ack loss for %dth frame with seq %d.\n", frames_recvd, recvd_frame.seq);
      expected_seq = (expected_seq + 1) % 2;
    }
    else
    {
      if (expected_seq == recvd_frame.seq)
      {
        printf("Simulating succesful reception for %dth frame with seq %d. Sending ack\n", frames_recvd, recvd_frame.seq);
        ack.ack = expected_seq;
        sendto(sock, &ack, sizeof(ack), 0, (SA *)&client_addr, client_len);
        expected_seq = (expected_seq + 1) % 2;
        frames_recvd++;
      }
      else
      {
        printf("Received out of order frame with seq %d. Sending ack for last successfully received frame\n", recvd_frame.seq);
        sendto(sock, &ack, sizeof(ack), 0, (SA *)&client_addr, client_len);
      }
    }
  } while (recv_len > 0);
  printf("Received end marker. Terminating...\n");
  close(sock);
  return 0;
}
