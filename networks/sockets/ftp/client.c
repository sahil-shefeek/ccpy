#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080
#define BUF_SIZE 1024
#define SOCKET_ERROR (-1)

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

int main()
{
  int sock = check(socket(AF_INET, SOCK_STREAM, 0), "Error creating socket!");
  SA_IN server_addr;
  char filename[256];
  char buffer[BUF_SIZE];

  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  server_addr.sin_port = htons(PORT);
  check(connect(sock, (SA *)&server_addr, sizeof(server_addr)), "Failed to connect");
  printf("Connected to FTP server at 127.0.0.1:%d\n"
         "Enter the filename to request: ",
         PORT);
  if (fgets(filename, sizeof(filename), stdin) == NULL)
  {
    fprintf(stderr, "Error reading filename\n");
    close(sock);
    exit(EXIT_FAILURE);
  }
  filename[strcspn(filename, "\n")] = '\0';

  send(sock, &filename, sizeof(filename), 0);
  int bytes_read;
  do
  {
    bytes_read = check(recv(sock, buffer, sizeof(buffer) - 1, 0), "Error receiving file contents from server");
    buffer[bytes_read] = '\0';
    printf("%s", buffer);
  } while (bytes_read > 0);
  close(sock);
  return 0;
}
