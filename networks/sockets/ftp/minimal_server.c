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
#define MAX_CLIENTS 10

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
    int server_sock;
    SA_IN server_addr;
    server_sock = check(socket(AF_INET, SOCK_STREAM, 0), "Socket creation failed!");
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(PORT);
    check(bind(server_sock, (SA *)&server_addr, sizeof(server_addr)), "Socket binding failed!");
    check(listen(server_sock, 5), "Listening on socket failed!");
    printf("FTP Server listening on port %d...\n", PORT);

    int client_sock = check(accept(server_sock, NULL, NULL), "Failed to accept connection!");
    printf("A client connected!\n");

    char filename[256] = {0};
    int bytes_read = check(read(client_sock, filename, sizeof(filename) - 1), "Error reading filename from client");
    filename[bytes_read] = '\0';
    printf("Client requested file: %s\n", filename);

    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        char *error_msg = "File not found";
        check(send(client_sock, error_msg, strlen(error_msg), 0), "Error sending message to client");
    }
    else
    {
        char buffer[BUF_SIZE];
        size_t bytes;
        while ((bytes = fread(buffer, 1, BUF_SIZE, fp)) > 0)
        {
            check(send(client_sock, buffer, bytes, 0), "Error sending file content to client");
        }
        fclose(fp);
    }
    shutdown(client_sock, SHUT_RDWR);
    close(server_sock);
    close(client_sock);
    return 0;
}
