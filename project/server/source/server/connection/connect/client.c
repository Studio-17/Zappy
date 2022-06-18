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
#include "protocol/player.h"

#include <fcntl.h>

#include "server/server.h"
#include "server/communication/request/request.h"

static void send_new_player_connected_to_gui(zappy_t *zappy)
{
    post_header(zappy->server->gui, (payload_header_t){
        .id = SERVER,
        .size = sizeof(response_payload_player_connected_t),
        .type = PLAYER_CONNECTED}
    );

    post_response_player_connected(zappy->server->gui, (response_payload_player_connected_t){
        .id = zappy->server->clients,
        .level = zappy->client[zappy->server->clients].player.level,
        .orientation = zappy->client[zappy->server->clients].player.orientation,
        .position = zappy->client[zappy->server->clients].player.position,
    });

    zappy->server->clients += 1;
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

    }

    setup_non_blocking_sockets(client_socket);

    if (zappy->server->is_gui_connected)
        send_new_player_connected_to_gui(zappy);

    listen_clients(zappy);
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
