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

typedef struct pkt {
  int ACK;
  int seqno;
  char data[25];
} pkt_t;

int main() {
  struct pkt sendPkt, recvPkt;
  SA_IN addr;
  int sockfd = check(socket(AF_INET, SOCK_DGRAM, 0), "Socket creation failed");
  addr.sin_family = AF_INET;
  addr.sin_port = htons(4000);
  addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  socklen_t addr_size = sizeof(addr);
  check(bind(sockfd, (SA *)&addr, addr_size), "Failed to bind socket");
  while (1) {
    check(
        recvfrom(sockfd, &recvPkt, sizeof(recvPkt), 0, (SA *)&addr, &addr_size),
        "Failed to receive data");
    int drop = rand() % 10;
    if (drop < 2) {
      printf("Packet with no. %d recieved but no ACK will be sent to "
             "simulate lost ACK\n",
             recvPkt.seqno);
      continue;
    } else if (drop < 4) {
      printf("Packet with no. %d recieved but will be dropped to simulate "
             "lost packet\n",
             recvPkt.seqno);
      continue;
    } else if (drop < 6) {
      printf("Packet with no. %d recieved but duplicate ack of prev packet "
             "will be send to simulate network traffic\n",
             recvPkt.seqno);
      sendPkt.ACK = 1;
      sendPkt.seqno = (recvPkt.seqno + 1) % 2;
      sendto(sockfd, &sendPkt, sizeof(sendPkt), 0, (SA *)&addr, addr_size);
    } else {
      printf("Packet with no. %d recieved, sending ACK to simulate normal "
             "transmission\n",
             recvPkt.seqno);
      sendPkt.ACK = 1;
      sendPkt.seqno = recvPkt.seqno;
      sendto(sockfd, &sendPkt, sizeof(sendPkt), 0, (SA *)&addr, addr_size);
    }
  }
}
