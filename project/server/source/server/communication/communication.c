/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** communication
*/

#include "server.h"

bool listen_clients(zappy_t *zappy)
{
    for (int index = 0; index < zappy->server->server_socket->max_client; index += 1) {
        if (FD_ISSET(zappy->server->server_socket->client[index], &zappy->server->socket_descriptor->readfd)) {
            if (!zappy->server->server_socket->client[index])
                continue;
            zappy->server->socket_descriptor->socket_descriptor = zappy->server->server_socket->client[index];

            if (zappy->server->is_gui_connected)
                gui_handle_request(zappy);

            if (!ai_handle_request(zappy, index))
                return false;
        }
    }
    return true;
}
