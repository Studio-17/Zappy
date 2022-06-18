/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** communication
*/

#include "protocol/player.h"

#include "server/communication/communication.h"
#include "server/server.h"

static void client_sent_request(int type)
{
    return;
}

void listen_clients(zappy_t *zappy)
{
    // for (int index = 0; index < zappy->server->ss->max_client; index += 1) {

    //     zappy->server->sd->socket_descriptor = zappy->server->ss->client[index];

    //     payload_header_t header = get_header(zappy->server->sd->socket_descriptor);

    //     char *data = NULL;
    //     data = (char *)malloc(header.size);

    //     read(zappy->server->sd->socket_descriptor, data, header.size);

    //     client_sent_request(header.type);
    // }
}
