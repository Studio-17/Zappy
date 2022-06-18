/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** communication
*/

#include "protocol/player.h"

#include "server/communication/communication.h"
#include "server/server.h"

static void gui_client_sent_request(int type)
{
    return;
}

static int get_generic_request(int client_socket, int size_to_read)
{
    char *data = malloc(size_to_read);

    read(client_socket, data, size_to_read);
}

void listen_clients(zappy_t *zappy)
{
    int request_type = -1;

    for (int index = 0; index < zappy->server->ss->max_client; index += 1) {

        zappy->server->sd->socket_descriptor = zappy->server->ss->client[index];

        payload_header_t header = get_header(zappy->server->sd->socket_descriptor);

        request_type = get_generic_request(zappy->server->sd->socket_descriptor, header.size);

        gui_client_sent_request(header.type);
    }
}
