/*
** EPITECH PROJECT, 2022
** project
** File description:
** forward_request
*/

#include "player.h"
#include "request.h"
#include "ai_request.h"

static void post_player_movement(zappy_t *zappy, int player_index)
{
    post_header(zappy->server->gui, (payload_header_t){
        .id = SERVER,
        .size = sizeof(response_payload_player_position_t),
        .type = PLAYER_POSITION
    });

    post_response_player_position(zappy->server->gui, (response_payload_player_position_t){
        .status = true,
        .player_id = player_index,
        .position = zappy->client[player_index].player.position,
    });
}

void ai_forward_request(zappy_t *zappy, void *data, int player_index)
{
    const position_t direction[] = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
    position_t movement = direction[zappy->client[player_index].player.orientation];

    move(zappy, movement, player_index);
    post_player_movement(zappy, player_index);
    ai_response_ok_ko(zappy->server->socket_descriptor->socket_descriptor, true);
}