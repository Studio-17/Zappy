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

#include "gui_update.h"

#include "server/server.h"
#include "server/communication/request/request.h"

static void gui_post_player_connected(zappy_t *zappy)
{
    for (int index = 0; index < zappy->server->clients; index += 1) {
        if (zappy->client[index].socket != zappy->server->gui
        && zappy->client[index].socket > 0) {
            gui_update_player_connected(zappy, index);
        }
    }
}

bool connect_client(zappy_t *zappy)
{
    int client_socket = 0;
    int client_id = 0;

    if (FD_ISSET(zappy->server->server_socket->server, &zappy->server->socket_descriptor->readfd))
    {
        if ((client_socket = accept(zappy->server->server_socket->server,
                                 (struct sockaddr *)&zappy->server->address, (socklen_t *)&zappy->server->address_length)) < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        printf("client connected on socket %d\n", client_socket);

        if (greeting_protocol(zappy, client_socket)) {

            if (zappy->server->is_gui_connected) {
                gui_update_map_content(zappy);
                gui_post_player_connected(zappy);
            }

        }
    }
    return (listen_clients(zappy));
}

void clear_socket_set(server_t *server)
{
    FD_ZERO(&server->socket_descriptor->readfd);
}

void add_server_socket_to_set(server_t *server)
{
    FD_SET(server->server_socket->server, &server->socket_descriptor->readfd);
    server->socket_descriptor->max_socket_descriptor = server->server_socket->server;
}

void add_client_socket_to_set(zappy_t *zappy)
{
    for (int index = 0; index < zappy->server->clients; index += 1) {

        if (zappy->client[index].socket > 0)
            FD_SET(zappy->client[index].socket, &zappy->server->socket_descriptor->readfd);

        if (zappy->client[index].socket > zappy->server->socket_descriptor->max_socket_descriptor)
            zappy->server->socket_descriptor->max_socket_descriptor = zappy->client[index].socket;

    }
}

void wait_for_connections(server_t *server)
{
    struct timeval tv = {
        .tv_sec = 0,
        .tv_usec = 5,
    };

    if ((select(server->socket_descriptor->max_socket_descriptor + 1, &server->socket_descriptor->readfd, NULL, NULL, &tv) < 0)) {
        close(server->socket_descriptor->max_socket_descriptor + 1);
    }
}

void add_client_to_server(zappy_t *zappy, int client_socket)
{
    for (int index = 0; index < zappy->server->clients; index += 1) {

        if (zappy->client[index].socket == 0) {
            zappy->client[index].socket = client_socket;
            break;
        }
    }
}
