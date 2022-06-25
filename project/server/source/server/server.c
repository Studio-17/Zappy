/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** server
*/

#include "server/server.h"
#include "server/communication/request/request.h"

void create_server(zappy_t *zappy)
{
    create_server_socket(zappy->server);
    allow_multiple_connections(zappy->server);

    configure_socket_type(zappy->server);
    bind_socket_to_server(zappy->server);
}

bool server_loop(zappy_t *zappy)
{
    while (1) {
        clear_socket_set(zappy->server);

        add_server_socket_to_set(zappy->server);
        add_client_socket_to_set(zappy);

        wait_for_connections(zappy->server);

        if (!connect_client(zappy))
            return false;
    }
    return true;
}

void client_deconnected(zappy_t *zappy, int client_socket)
{
    // close(zappy->server->socket_descriptor->socket_descriptor);
    // zappy->server->server_socket->client[client_socket] = 0;
}

void debug_server(server_t *server)
{
    printf("[DEBUG] server->port = %d\n", server->port);
    printf("[DEBUG] server->address_length = %d\n", server->address_length);

    printf("[DEBUG] server->server_socket->server = %d\n", server->server_socket->server);
    printf("[DEBUG] server->server_socket->max_client = %d\n", server->server_socket->max_client);

    printf("[DEBUG] server->socket_descriptor->max_socket_descriptor = %d\n", server->socket_descriptor->max_socket_descriptor);
}

void free_server(server_t *server)
{
    free(server->socket_descriptor);
    free(server->server_socket);
    free(server);
}
