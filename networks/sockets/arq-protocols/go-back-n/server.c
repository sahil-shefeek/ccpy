#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

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

int main(int argc, char *argv[]) {
  struct pkt recvPacket, ackPacket;

  int expected_seq = 0;
  int recvSocket =
      check(socket(AF_INET, SOCK_DGRAM, 0), "Socket creation failed");
  SA_IN receiverAddr;
  receiverAddr.sin_family = AF_INET;
  receiverAddr.sin_port = htons(SERVER_PORT);
  receiverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

  check(bind(recvSocket, (SA *)&receiverAddr, sizeof(receiverAddr)),
        "Failed to bind socket");

  printf("Server running on port: %d\n", SERVER_PORT);

  while (1) {
    SA_IN senderAddr;
    socklen_t addr_size = sizeof(senderAddr);
    check(recvfrom(recvSocket, &recvPacket, sizeof(recvPacket), 0,
                   (SA *)&senderAddr, &addr_size),
          "Failed to receive data");

    if (recvPacket.seqnum == expected_seq) {
      int drop = rand() % 10;
      if (drop < 2) {
        printf("[DROP] Frame '%s' with seq #%d dropped (simulated loss).\n",
               recvPacket.data, recvPacket.seqnum);
        continue;
      } else if (drop < 4) {
        printf("[ACK DROP] Frame '%s' with seq #%d received, but ACK dropped "
               "(simulated loss).\n",
               recvPacket.data, recvPacket.seqnum);
        expected_seq++;
        continue;
      } else {
        printf("[RECEIVED] Expected frame: '%s' with seq #%d. Sending ACK.\n",
               recvPacket.data, recvPacket.seqnum);
        ackPacket.ACK = recvPacket.seqnum;
        sendto(recvSocket, &ackPacket, sizeof(ackPacket), 0, (SA *)&senderAddr,
               addr_size);
        expected_seq++;
      }
    } else if (recvPacket.seqnum < expected_seq) {
      printf("[DUPLICATE] Duplicate frame received: '%s' with seq #%d. "
             "Resending ACK.\n",
             recvPacket.data, recvPacket.seqnum);
      ackPacket.ACK = recvPacket.seqnum;
      sendto(recvSocket, &ackPacket, sizeof(ackPacket), 0, (SA *)&senderAddr,
             addr_size);
    } else { // recvPacket.seqnum > expected_seq
      printf("[OUT-OF-ORDER] Frame '%s' received with seq #%d, but expected "
             "seq #%d. Discarding frame.\n",
             recvPacket.data, recvPacket.seqnum, expected_seq);
      if (expected_seq > 0) {
        ackPacket.ACK = expected_seq - 1;
        printf("[INFO] Resending ACK for last in-order frame #%d.\n",
               ackPacket.ACK);
        sendto(recvSocket, &ackPacket, sizeof(ackPacket), 0, (SA *)&senderAddr,
               addr_size);
      }
    }
  }
  return 0;
}
