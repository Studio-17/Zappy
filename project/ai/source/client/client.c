/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** client
*/

#define _GNU_SOURCE

#include <stdio.h>

#include "netlib.h"
#include "minilib.h"

#include "ai/include/client/client.h"
#include "ai/include/options/options.h"

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

void connect_client(client_t *client, char *team_name)
{
    if (connect(client->socket, (struct sockaddr *)&client->server, sizeof(client->server)) != 0) {
        perror("connect");
        exit(0);
    } else {
        handle_client(client);
        while (1) {
            continue;
        }
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
    char *identification = NULL;
    asprintf(&identification, "IA Client Connected on socket %d, at address %s\n", client->socket, inet_ntoa(client->server.sin_addr));

    send_request(client->socket, identification);
    printf("%s\n", get_response(client->socket));

    send_request(client->socket, "martin");
    printf("%s\n", get_response(client->socket));
}
