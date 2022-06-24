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

bool connect_client(zappy_t *zappy)
{
    int client_socket;
    int saved_index = 0;

    if (FD_ISSET(zappy->server->server_socket->server, &zappy->server->socket_descriptor->readfd))
    {
        if ((client_socket = accept(zappy->server->server_socket->server,
                                 (struct sockaddr *)&zappy->server->address, (socklen_t *)&zappy->server->address_length)) < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        if (!greeting_protocol(zappy, client_socket)) {

            for (int index = 0; index < zappy->server->server_socket->max_client; index += 1) {

                if (zappy->server->server_socket->client[index] == 0) {
                    saved_index = index;
                    // zappy->client[index].socket = client_socket;
                    zappy->server->server_socket->client[index] = client_socket;
                    break;

                }
            }

            if (zappy->server->is_gui_connected)
                gui_update_player_connected(zappy, saved_index);

        } else {

            gui_update_map_content(zappy);
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

void add_client_socket_to_set(server_t *server)
{
    for (int index = 0; index < server->server_socket->max_client; index += 1)
    {
        server->socket_descriptor->socket_descriptor = server->server_socket->client[index];

        if (server->socket_descriptor->socket_descriptor > 0)
            FD_SET(server->socket_descriptor->socket_descriptor, &server->socket_descriptor->readfd);

        if (server->socket_descriptor->socket_descriptor > server->socket_descriptor->max_socket_descriptor)
            server->socket_descriptor->max_socket_descriptor = server->socket_descriptor->socket_descriptor;
    }
}

void wait_for_connections(server_t *server)
{
    struct timeval tv;

    /* Pendant 5 secondes maxi */
    tv.tv_sec = 0;
    tv.tv_usec = 5;
    if ((select(server->socket_descriptor->max_socket_descriptor + 1, &server->socket_descriptor->readfd, NULL, NULL, &tv) < 0))
    {
        perror("select");
    }
}

void add_client_to_server(server_t *server, int client_socket)
{
    for (int index = 0; index < server->server_socket->max_client; index += 1)
    {
        if (server->server_socket->client[index] == 0)
        {
            server->server_socket->client[index] = client_socket;
            break;
        }
    }
}
