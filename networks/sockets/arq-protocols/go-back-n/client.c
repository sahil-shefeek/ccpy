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
#define WINDOW_SIZE 5

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
  int total_frames;
  srand(time(NULL));
  printf("Enter the number of frames to send: ");
  scanf("%d", &total_frames);
  int sock = check(socket(AF_INET, SOCK_DGRAM, 0), "Socket creation failed");
  SA_IN server_addr;
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  server_addr.sin_port = htons(PORT);
  server_addr.sin_family = AF_INET;
  struct timeval timeout = {2, 0};
  check(setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)), "Failed to set timeout");
  printf("UDP client is ready!\n Sending datagrams to 127.0.0.1:%d\n", PORT);

  frame_t frame;
  ack_frame_t ack;
  int expected_ack = 0, next_seq = 0;
  while (expected_ack < total_frames)
  {
    while (next_seq - expected_ack < WINDOW_SIZE && next_seq < total_frames)
    {
      frame.seq = next_seq;
      printf("Sending frame (seq: %d)\n", frame.seq);
      check(sendto(sock, &frame, sizeof(frame), 0, (SA *)&server_addr, sizeof(server_addr)), "Failed to send datagrams to server");
      next_seq++;
    }

    int recv_len = recvfrom(sock, &ack, sizeof(ack), 0, NULL, NULL);
    if (recv_len > 0)
    {
      if (ack.ack >= expected_ack)
      {
        printf("Received ack with seq: %d. Sliding window forward...\n", ack.ack);
        expected_ack = ack.ack + 1;
      }
      else if (ack.ack < expected_ack)
      {
        printf("Received duplicate ack with seq %d. Discarding...\n", ack.ack);
      }
    }
    else
    {
      printf("Timeout. Retransmitting frames from seq: %d\n", expected_ack);
      next_seq = expected_ack;
    }
  }
  sendto(sock, NULL, 0, 0, (SA *)&server_addr, sizeof(server_addr));
  printf("Successfully sent all %d frames. Trasnmission complete!\n", total_frames);
  close(sock);
  return 0;
}
