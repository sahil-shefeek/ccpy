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
  int status; // 0 = empty, 1 = received
} window_item_t;

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

  int base_seq = 0; // Base sequence number of the receiver window
  frame_t recvd_frame;
  ack_frame_t ack;
  window_item_t receiver_window[WINDOW_SIZE];

  // Initialize receiver window
  for (int i = 0; i < WINDOW_SIZE; i++)
  {
    receiver_window[i].status = 0;
  }

  int recv_len;
  do
  {
    recv_len = recvfrom(sock, &recvd_frame, sizeof(recvd_frame), 0, (SA *)&client_addr, &client_len);
    if (recv_len <= 0)
      break;

    int drop = rand() % 10;

    // Check if the frame is within our current window
    if (recvd_frame.seq >= base_seq && recvd_frame.seq < base_seq + WINDOW_SIZE)
    {
      // Calculate position in window
      int window_pos = (recvd_frame.seq - base_seq) % WINDOW_SIZE;

      if (drop < 2)
      {
        printf("Simulating a frame loss for frame with seq %d.\n", recvd_frame.seq);
      }
      else if (drop < 4)
      {
        printf("Simulating an ack loss for frame with seq %d.\n", recvd_frame.seq);
        // Store frame even though ACK is "lost"
        receiver_window[window_pos].frame = recvd_frame;
        receiver_window[window_pos].status = 1;
      }
      else
      {
        if (receiver_window[window_pos].status == 1)
        {
          printf("Discarding a duplicate frame received with seq %d. Sending ack\n", recvd_frame.seq);
        }
        else
        {
          printf("Simulating succesful reception for frame with seq %d. Sending ack\n", recvd_frame.seq);
          receiver_window[window_pos].frame = recvd_frame;
          receiver_window[window_pos].status = 1;
        }

        // Always acknowledge with the actual sequence number of this frame
        ack.ack = recvd_frame.seq;
        sendto(sock, &ack, sizeof(ack), 0, (SA *)&client_addr, client_len);
      }

      // Check if we can slide the window
      while (receiver_window[0].status == 1)
      {
        // Shift window elements left
        for (int i = 0; i < WINDOW_SIZE - 1; i++)
        {
          receiver_window[i] = receiver_window[i + 1];
        }
        // Clear last element
        receiver_window[WINDOW_SIZE - 1].status = 0;
        base_seq++;
      }
    }
    else if (recvd_frame.seq < base_seq)
    {
      // This is an old frame, resend ACK in case original ACK was lost
      printf("Received old frame with seq %d. Resending ACK\n", recvd_frame.seq);
      ack.ack = recvd_frame.seq;
      sendto(sock, &ack, sizeof(ack), 0, (SA *)&client_addr, client_len);
    }
    else
    {
      // Frame is beyond current window
      printf("Discarding a frame with seq %d outside current window [%d-%d]\n",
             recvd_frame.seq, base_seq, base_seq + WINDOW_SIZE - 1);
    }

  } while (recv_len > 0);

  printf("Received end marker. Terminating...\n");
  close(sock);
  return 0;
}