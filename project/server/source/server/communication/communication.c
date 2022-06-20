/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** communication
*/

#include "protocol/player.h"
#include "protocol/greeting.h"

#include "server/server.h"
#include "server/communication/communication.h"
#include "server/communication/request/request.h"

void listen_clients(zappy_t *zappy)
{
    for (int index = 0; index < zappy->server->ss->max_client; index += 1) {

        zappy->server->sd->socket_descriptor = zappy->server->ss->client[index];

        if (zappy->server->is_gui_connected)
            gui_handle_request(zappy);

        ai_handle_request(zappy);

    }
}
