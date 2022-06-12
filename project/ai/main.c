/* client.c */

#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <inttypes.h>

#define MAX 80
#define PORT 8888

#define SA struct sockaddr

void get_greeting_message(int sockfd)
{
    char msg[24] = {0};
    bzero(msg, sizeof(msg));
    recv(sockfd, msg, sizeof(msg), 0);

    printf("%s", msg);
}

void get_map_size(int sockfd)
{
    send(sockfd, "map", sizeof("map"), 0);

    char msg[24] = {0};
    bzero(msg, sizeof(msg));
    recv(sockfd, msg, sizeof(msg), 0);

    printf("%s", msg);
}

int main()
{
    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;

    bool exited = false;

    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    } else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);

    // connect the client socket to server socket
    if (connect(sockfd, (SA *)&servaddr, sizeof(servaddr)) != 0) {
        printf("connection with the server failed...\n");
        exit(0);
    }
    else
        printf("connected to the server..\n");

    // function for chat
    get_greeting_message(sockfd);
    // func(sockfd);
    get_map_size(sockfd);
    get_map_size(sockfd);
    get_map_size(sockfd);

    // close the socket
    while (1) {
        if (exited)
            close(sockfd);
        else
            continue;
    }
}