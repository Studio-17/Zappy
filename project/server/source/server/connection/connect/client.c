/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** client
*/

#define _GNU_SOURCE

#include "minilib.h"
#include "netlib.h"
#include "protocol/greeting.h"

#include <fcntl.h>

#include "server/server.h"

static bool team_name_allowed(char *client_names, char *team_name)
{
    if (strcmp(team_name, "GRAPHIC") == 0)
        return (true);

    char **names = my_strtok(client_names, ' ');

    for (int index = 0; names[index]; index += 1) {
        if (strcmp(names[index], team_name) == 0) {
            return (true);
        }
    }
    return (false);
}

static void greeting_protocol(zappy_t *zappy, int client_socket)
{
    // GET CLIENT TYPE & SEND WELCOME
    request_payload_t request = get_request(client_socket);
    post_response(client_socket, (response_payload_t) {true, "WELCOME\n"});

    // GET CLIENT NAME & SEND OK/KO
    if (zappy->server->clients > zappy->options->clients_nb) {
        post_response(client_socket, (response_payload_t) {false, "KO\n"});
        close(client_socket);
        exit(0);
    }
    request_payload_t team_name_request = get_request(client_socket);
    printf("%s\n", team_name_request.payload);
    if (team_name_allowed(zappy->options->names, team_name_request.payload)) {
        post_response(client_socket, (response_payload_t) {true, "OK\n"});
    } else {
        post_response(client_socket, (response_payload_t) {false, "KO\n"});
        close(client_socket);
        return;
    }

    // GET INFO CLIENT & SEND CLIENT NUMBER
    request_payload_t info_client_request = get_request(client_socket);
    post_response_client_number(client_socket, (response_client_number_t) {true, zappy->server->clients});

    if (strcmp(request.payload, "IA\n") == 0) {
    // CREATE A CLIENT (struct)
        player_t player = (player_t) {.id = zappy->server->clients, .level = 1, .orientation = 0, .position = (position_t){rand() % zappy->options->width, rand() % zappy->options->height}};
        zappy->client[zappy->server->clients] = (ai_client_t){client_socket, zappy->server->clients, AI, player};
        zappy->server->clients += 1;
    }

    // GET INFO MAP & SEND MAP DIMENSIONS
    request_payload_t info_map_request = get_request(client_socket);
    post_response_map(client_socket, (response_payload_map_t) {true, zappy->options->width, zappy->options->height});
}

void connect_client(zappy_t *zappy)
{
    int client_socket;

    if (FD_ISSET(zappy->server->ss->server, &zappy->server->sd->readfd))
    {
        if ((client_socket = accept(zappy->server->ss->server,
                                 (struct sockaddr *)&zappy->server->address, (socklen_t *)&zappy->server->address_length)) < 0)
        {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        add_client_to_server(zappy->server, client_socket);

        greeting_protocol(zappy, client_socket);


        // CODE HERE ALL GREETING RELATED FUNCTIONS
    }

    int unblock = fcntl(client_socket, F_GETFL, 0);
    fcntl(client_socket, F_SETFL, unblock | O_NONBLOCK);

    handle_client(zappy);
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
