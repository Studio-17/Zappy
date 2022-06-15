/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** client
*/

#include "client/client.h"

void setup_client(client_t *client, options_t *options)
{
    int port = options->port;
    char *machine = options->machine;

    client->socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client->socket == -1) {
        perror("socket");
        exit(0);
    }

    bzero(&client->server, sizeof(client->server));

    client->server.sin_family = AF_INET;
    client->server.sin_addr.s_addr = inet_addr(machine);
    client->server.sin_port = htons(port);
}

void get_greeting_message(int sockfd)
{
    char msg[24] = {0};
    bzero(msg, sizeof(msg));
    recv(sockfd, msg, sizeof(msg), 0);

    printf("[CLIENT RECV] %s", msg);
}

void send_request(int sockfd, char *request)
{
    printf("[CLIENT SEND] %s", request);

    send(sockfd, request, sizeof(request), 0);
}

void connect_client(client_t *client, char *team_name)
{
    if (connect(client->socket, (struct sockaddr *)&client->server, sizeof(client->server)) != 0) {
        perror("connect");
        exit(0);
    } else {
        get_greeting_message(client->socket);
        send_request(client->socket, strcat(team_name, "\n"));
        get_greeting_message(client->socket);
        get_greeting_message(client->socket);
    }
}

void debug_client(client_t *client)
{
    printf("[DEBUG] client->socket: %d\n", client->socket);
    printf("[DEBUG] client->server: %d\n", client->server.sin_port);
}

void free_client(client_t *client)
{
    free(client);
}

int handle_client(client_t *client)
{
    bool exited = false;

    while (1) {
        if (exited)
            close(client->socket);
    }
}
