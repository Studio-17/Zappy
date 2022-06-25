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

// static int gui_update_client_id(zappy_t *zappy)
// {
//     int id = zappy->options->max_clients - zappy->server->clients;

//     if (id < 0)
//         return (-1);

//     zappy->client[zappy->server->clients].id = id;

//     printf("client-id: %d\n", zappy->client[zappy->server->clients].id);

//     zappy->server->clients += 1;

//     return (id);
// }

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

        // if (!greeting_protocol(zappy, client_socket)) {

            // client_id = gui_update_client_id(zappy);
            // if (client_id == -1)
            //     return (false);

            // if (zappy->server->is_gui_connected)
            //     gui_update_player_connected(zappy, zappy->server->clients);

        // } else {
        //     if (zappy->server->is_gui_connected)
        //         gui_update_map_content(zappy);
        // }

        if (greeting_protocol(zappy, client_socket)) {

            if (zappy->server->is_gui_connected)
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
    struct timeval tv;

    /* Pendant 5 secondes maxi */
    tv.tv_sec = 0;
    tv.tv_usec = 5;
    if ((select(server->socket_descriptor->max_socket_descriptor + 1, &server->socket_descriptor->readfd, NULL, NULL, &tv) < 0))
    {
        perror("select"); // error with select on ^C (client-side)
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
