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

        // request_payload_player_position_t player_position_request = get_request_player_position(zappy->server->sd->socket_descriptor);

        // payload_header_t header = {
        //     .size = sizeof(payload_header_t),
        //     .type = 0,
        // };
        // post_header(zappy->server->sd->socket_descriptor, header);

        // response_payload_player_position_t response = {
        //     .status = true,
        //     .player_id = zappy->client[player_position_request.player_id].client_nb,
        //     .position = zappy->client[player_position_request.player_id].player.position,
        // };
        // post_response_player_position(zappy->server->sd->socket_descriptor, response);
    }
}
