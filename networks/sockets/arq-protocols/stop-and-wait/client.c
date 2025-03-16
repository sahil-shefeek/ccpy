#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>

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

struct pkt {
  int ACK;
  int seqno;
  char data[25];
};

int main() {
  struct pkt sendPkt, recvPkt;
  SA_IN addr;
  struct timeval timeout = {2, 0};
  int sockfd = check(socket(AF_INET, SOCK_DGRAM, 0), "Socket creation failed");
  addr.sin_family = AF_INET;
  addr.sin_port = htons(4000);
  addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  socklen_t addrSize = addrSize = sizeof(addr);
  int counter = 0;

  while (1) {
    printf("\nEnter data: ");
    scanf(" %s", sendPkt.data);
    sendPkt.ACK = 0;
    sendPkt.seqno = counter;
    sendto(sockfd, &sendPkt, sizeof(sendPkt), 0, (SA *)&addr, addrSize);
    check(
        setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)),
        "Failed to set socket options");

    while (1) {
      int recvLen = recvfrom(sockfd, &recvPkt, sizeof(recvPkt), 0, (SA *)&addr,
                             &addrSize);
      if (recvLen >= 0) {
        if (recvPkt.seqno == sendPkt.seqno) {
          printf("\nACK recieved for packet no. %d \n", recvPkt.seqno);
          counter = (counter + 1) % 2;
          break;
        } else {
          printf("\nOut of order ACK recieved for packet no. %d...ignoring "
                 "it.. \n",
                 recvPkt.seqno);
        }
      } else {
        printf("\nTimeout! Pkt will be resent\n");
        sendto(sockfd, &sendPkt, sizeof(sendPkt), 0, (SA *)&addr, addrSize);
      }
    }
  }
}
