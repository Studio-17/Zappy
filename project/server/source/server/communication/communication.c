/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** communication
*/

#include "server.h"
#include "ai_request.h"

void death_protocol(zappy_t *zappy, int index)
{
    dprintf(zappy->client[index].socket, "dead\n");
    // disconnect the player
}

bool listen_clients(zappy_t *zappy)
{
    printf("server can listen to maximum of %d clients\n", zappy->server->server_socket->max_client);

    for (int index = 0; index < zappy->server->server_socket->max_client; index += 1) {
        if (FD_ISSET(zappy->server->server_socket->client[index], &zappy->server->socket_descriptor->readfd)) {

            if (!zappy->server->server_socket->client[index])
                continue;

            zappy->server->socket_descriptor->socket_descriptor = zappy->server->server_socket->client[index];

            if (!ai_handle_request(zappy, index))
                return false;

            // if (check_death(zappy, index))
            //     death_protocol(zappy, index);
        }
    }
    return true;
}
