#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>

#define SOCKET_ERROR (-1)
#define SERVER_PORT 8080

typedef struct sockaddr_in SA_IN;
typedef struct sockaddr SA;

int check(int exp, const char *msg) {
  if (exp == SOCKET_ERROR) {
    perror(msg);
    exit(EXIT_FAILURE);
  }
  return exp;
}

struct pkt {
  int ACK;
  int seqnum;
  char data[25];
};

#define WINDOW_SIZE 3

int main(int argc, char *argv[]) {
  int total_frames, expected_ack = 0;
  char input[25];
  struct timeval timeout = {2, 0};

  int next_frame_seq = 0;
  struct pkt send_packet, recv_packet;

  int senderSocket =
      check(socket(AF_INET, SOCK_DGRAM, 0), "Socket creation failed");
  SA_IN receiverAddr;
  receiverAddr.sin_family = AF_INET;
  receiverAddr.sin_port = htons(SERVER_PORT);
  receiverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  socklen_t addr_size = sizeof(receiverAddr);

  printf("Enter the total number of frames to send: ");
  scanf("%d", &total_frames);
  printf("Enter the message to send: ");
  scanf("%s", input);

  strcpy(send_packet.data, input);

  printf("\n[START] Sending initial window (up to %d frames)...\n",
         WINDOW_SIZE);
  for (int i = 0; i < WINDOW_SIZE && next_frame_seq < total_frames; i++) {
    send_packet.seqnum = next_frame_seq;
    sendto(senderSocket, &send_packet, sizeof(send_packet), 0,
           (SA *)&receiverAddr, addr_size);
    printf("[SENT] Frame with seq #%d sent.\n", send_packet.seqnum);
    next_frame_seq++;
  }

  setsockopt(senderSocket, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout,
             sizeof(timeout));

  while (expected_ack < total_frames) {
    int recvlen = recvfrom(senderSocket, &recv_packet, sizeof(recv_packet), 0,
                           (SA *)&receiverAddr, &addr_size);
    if (recvlen >= 0) {
      if (recv_packet.ACK == expected_ack) {
        printf("[ACK RECEIVED] ACK for frame #%d received.\n", expected_ack);
        expected_ack++;
        if (next_frame_seq < total_frames) {
          send_packet.seqnum = next_frame_seq;
          sendto(senderSocket, &send_packet, sizeof(send_packet), 0,
                 (SA *)&receiverAddr, addr_size);
          printf("[SENT] Frame with seq #%d sent.\n", send_packet.seqnum);
          next_frame_seq++;
        }
      } else if (recv_packet.ACK < expected_ack) {
        printf(
            "[DUPLICATE ACK] Duplicate ACK received for frame #%d. Ignoring.\n",
            recv_packet.ACK);
      } else {
        printf("[OUT-OF-ORDER ACK] Received ACK for frame #%d, but expected "
               "ACK for frame #%d. Ignoring.\n",
               recv_packet.ACK, expected_ack);
      }
    } else {
      printf("[TIMEOUT] No ACK received for frame #%d. Retransmitting frames "
             "starting at seq #%d...\n",
             expected_ack, expected_ack);
      next_frame_seq = expected_ack;
      for (int i = 0; i < WINDOW_SIZE && next_frame_seq < total_frames; i++) {
        send_packet.seqnum = next_frame_seq;
        sendto(senderSocket, &send_packet, sizeof(send_packet), 0,
               (SA *)&receiverAddr, addr_size);
        printf("[RESENT] Frame with seq #%d retransmitted.\n",
               send_packet.seqnum);
        next_frame_seq++;
      }
    }
  }

  printf("[COMPLETE] All %d frames have been acknowledged. Transmission "
         "complete.\n",
         total_frames);
  return 0;
}
