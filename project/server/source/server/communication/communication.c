/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** communication
*/

#include "server/communication/communication.h"
#include "server/server.h"

void client_sent_request(server_t *server)
{
    return;
}

void handle_client(zappy_t *zappy)
{
    for (int index = 0; index < zappy->server->ss->max_client; index += 1) {

        zappy->server->sd->socket_descriptor = zappy->server->ss->client[index];

        // CODE HERE ALL RESPONSE RELATED FUNCTIONS
        // client_sent_request(server);
    }
}
