/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** setup
*/

#include "server/server.h"

void setup_server(server_t *server, options_t *options)
{
    server->port = options->port;

    server->socket_descriptor = malloc(sizeof(server_socket_descriptor_t));
    server->server_socket = malloc(sizeof(server_socket_t));

    server->server_socket->client = malloc(sizeof(int) * options->clients_nb);
    server->server_socket->max_client = options->clients_nb;

    server->clients = 0;

    server->is_gui_connected = false;
}

void initialise_all_clients_sockets(server_t *server)
{
    for (int index = 0; index < server->server_socket->max_client; index++)
        server->server_socket->client[index] = 0;
}

void create_server_socket(server_t *server)
{
    if ((server->server_socket->server = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }
}

void allow_multiple_connections(server_t *server)
{
    int opt = 1;

    if (setsockopt(server->server_socket->server, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
}

void setup_non_blocking_sockets(int client_socket)
{
    int unblock = fcntl(client_socket, F_GETFL, 0);

    fcntl(client_socket, F_SETFL, unblock | O_NONBLOCK);
}
