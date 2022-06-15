/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** server
*/

#include "server/server.h"
#include "server/communication/request/request.h"

void create_server(server_t *server, options_t *options)
{
    setup_server(server, options);
    initialise_all_clients_sockets(server);
    create_server_socket(server);
    allow_multiple_connections(server);

    configure_socket_type(server);
    bind_socket_to_server(server);

    while (1) {
        clear_socket_set(server);

        add_server_socket_to_set(server);
        add_client_socket_to_set(server);

        if (wait_for_connections(server))
            connect_client(server);

        handle_server(server);
    }
}

void client_deconnected(server_t *server, int client_socket)
{
    close(server->sd->socket_descriptor);
    server->ss->client[client_socket] = 0;
}

void client_sent_request(server_t *server, int client_socket, char *command)
{
    return;
}

void handle_server(server_t *server)
{
    char request[MESSAGE_SIZE];
    int read_status;

    for (int index = 0; index < server->ss->max_client; index += 1)
    {
        server->sd->socket_descriptor = server->ss->client[index];

        if (FD_ISSET(server->sd->socket_descriptor, &server->sd->readfd))
        {
            if ((read_status = read(server->sd->socket_descriptor, request, MESSAGE_SIZE)) == 0)
                client_deconnected(server, index);
            else
                client_sent_request(server, index, request);
        }
    }
}

void debug_server(server_t *server)
{
    printf("[DEBUG] server->port = %d\n", server->port);
    printf("[DEBUG] server->address_length = %d\n", server->address_length);

    printf("[DEBUG] server->ss->server = %d\n", server->ss->server);
    for (int index = 0; index < server->ss->max_client; index += 1)
        printf("[DEBUG] server->ss->client[%d] = %d\n", index, server->ss->client[index]);
    printf("[DEBUG] server->ss->max_client = %d\n", server->ss->max_client);

    printf("[DEBUG] server->sd->socket_descriptor = %d\n", server->sd->socket_descriptor);
    printf("[DEBUG] server->sd->max_socket_descriptor = %d\n", server->sd->max_socket_descriptor);
}

void free_server(server_t *server)
{
    free(server);
}
