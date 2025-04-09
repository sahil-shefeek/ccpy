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
} frame_t;

typedef struct ack_frame
{
  int ack;
} ack_frame_t;

typedef struct window_item
{
  frame_t frame;
  int status; // 0 = not ACKed, 1 = ACKed
} window_item_t;

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

  int base_seq = 0; // First sequence number in the window
  int next_seq = 0; // Next sequence number to be sent

  window_item_t sender_window[WINDOW_SIZE];

  while (base_seq < total_frames)
  {
    // Send new frames if window space available
    while (next_seq < base_seq + WINDOW_SIZE && next_seq < total_frames)
    {
      // Create and send a new frame
      frame.seq = next_seq;
      printf("Sending frame (seq: %d)\n", frame.seq);
      check(sendto(sock, &frame, sizeof(frame), 0, (SA *)&server_addr, sizeof(server_addr)),
            "Failed to send datagram to server");

      // Store the frame in window
      window_item_t window_item = {frame, 0};
      sender_window[next_seq % WINDOW_SIZE] = window_item;
      next_seq++;
    }

    // Try to receive ACKs
    int recv_len = recvfrom(sock, &ack, sizeof(ack), 0, NULL, NULL);

    if (recv_len > 0)
    {
      // Valid ACK received
      if (ack.ack >= base_seq && ack.ack < next_seq)
      {
        printf("Received ack with seq: %d\n", ack.ack);

        // Mark the specific acknowledged frame
        sender_window[ack.ack % WINDOW_SIZE].status = 1;

        // Slide window if base frame is acknowledged
        if (ack.ack == base_seq)
        {
          // Keep sliding until we find an unacknowledged frame
          while (base_seq < next_seq && sender_window[base_seq % WINDOW_SIZE].status == 1)
          {
            printf("Sliding window forward...\n");
            base_seq++;
          }
        }
      }
      else
      {
        printf("Received duplicate ack with seq %d. Discarding...\n", ack.ack);
      }
    }
    else
    {
      // Timeout occurred, retransmit unacknowledged frames
      printf("Timeout. Retransmitting unacknowledged frames...\n");

      for (int i = 0; i < WINDOW_SIZE && base_seq + i < next_seq; i++)
      {
        int seq = base_seq + i;
        if (!sender_window[seq % WINDOW_SIZE].status) // If not acknowledged
        {
          printf("Retransmitting frame (seq: %d)\n", seq);
          check(sendto(sock, &(sender_window[seq % WINDOW_SIZE].frame), sizeof(frame_t), 0,
                       (SA *)&server_addr, sizeof(server_addr)),
                "Failed to retransmit datagram to server");
        }
      }
    }
  }

  // Send empty frame as end marker
  sendto(sock, NULL, 0, 0, (SA *)&server_addr, sizeof(server_addr));

  printf("Successfully sent all %d frames. Transmission complete!\n", total_frames);
  close(sock);
  return 0;
}