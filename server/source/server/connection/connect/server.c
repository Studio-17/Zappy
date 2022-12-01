/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** server
*/

#include "server/server.h"

void configure_socket_type(server_t *server)
{
    server->address.sin_family = AF_INET;
    server->address.sin_addr.s_addr = INADDR_ANY;
    server->address.sin_port = htons(server->port);
}

void bind_socket_to_server(server_t *server)
{
    if (bind(server->server_socket->server, (struct sockaddr *)&server->address, sizeof(struct sockaddr_in)) < 0) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    if (listen(server->server_socket->server, server->server_socket->max_client) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    server->address_length = sizeof(server->address);
}
