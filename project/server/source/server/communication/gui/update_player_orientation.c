/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** update_player_orientation
*/

#include "protocol/player.h"

#include "ai_request.h"
#include "gui_update.h"

void gui_update_player_orientation(zappy_t *zappy, int player_index)
{
    post_header(zappy->server->gui, (payload_header_t){
        .size = sizeof(response_payload_player_orientation_t),
        .type = PLAYER_ORIENTATION,
    });

    post_response_player_orientation(zappy->server->gui, (response_payload_player_orientation_t){
        .player_id = player_index,
        .orientation = zappy->client[player_index].player.orientation,
    });
}
