/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** client
*/

#define _GNU_SOURCE

#include "minilib.h"
#include "netlib.h"

#include "server/server.h"

static void greeting_protocol(server_t *server, int client_socket)
{
    // GET CLIENT TYPE & SEND WELCOME
    request_payload_t request = get_request(client_socket);
    post_response(client_socket, (response_payload_t) {true, "WELCOME\n"});

    // GET CLIENT NAME & SEND OK/KO
    request_payload_t team_name_request = get_request(client_socket);
    printf("%s", team_name_request.payload);
    post_response(client_socket, (response_payload_t) {true, "OK\n"});

    // GET INFO CLIENT & SEND CLIENT NUMBER
    request_payload_t info_client_request = get_request(client_socket);
    post_response_client_number(client_socket, (response_client_number_t) {true, client_socket});

    // GET INFO MAP & SEND MAP DIMENSIONS
    request_payload_t info_map_request = get_request(client_socket);
    post_response_map(client_socket, (response_payload_map_t) {true, 10, 10});
}

void connect_client(server_t *server)
{
    int client_socket;

    if (FD_ISSET(server->ss->server, &server->sd->readfd))
    {
        if ((client_socket = accept(server->ss->server,
                                 (struct sockaddr *)&server->address, (socklen_t *)&server->address_length)) < 0)
        {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        add_client_to_server(server, client_socket);

        greeting_protocol(server, client_socket);

        // CODE HERE ALL GREETING RELATED FUNCTIONS
    }

    // handle_client(server);
}

void clear_socket_set(server_t *server)
{
    FD_ZERO(&server->sd->readfd);
}

void add_server_socket_to_set(server_t *server)
{
    FD_SET(server->ss->server, &server->sd->readfd);
    server->sd->max_socket_descriptor = server->ss->server;
}

void add_client_socket_to_set(server_t *server)
{
    for (int index = 0; index < server->ss->max_client; index += 1)
    {
        server->sd->socket_descriptor = server->ss->client[index];

        if (server->sd->socket_descriptor > 0)
            FD_SET(server->sd->socket_descriptor, &server->sd->readfd);

        if (server->sd->socket_descriptor > server->sd->max_socket_descriptor)
            server->sd->max_socket_descriptor = server->sd->socket_descriptor;
    }
}

void wait_for_connections(server_t *server)
{
    if ((select(server->sd->max_socket_descriptor + 1, &server->sd->readfd, NULL, NULL, NULL) < 0))
    {
        perror("select");
    }
}

void add_client_to_server(server_t *server, int client_socket)
{
    for (int index = 0; index < server->ss->max_client; index += 1)
    {
        if (server->ss->client[index] == 0)
        {
            server->ss->client[index] = client_socket;
            break;
        }
    }
}
