/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** update_player_level
*/

#include "protocol/player.h"

#include "ai_request.h"
#include "gui_update.h"

void gui_update_player_level(zappy_t *zappy, int player_index)
{
    post_header(zappy->server->gui, (payload_header_t){
        .size = sizeof(response_payload_player_level_t),
        .type = PLAYER_LEVEL
    });

    post_response_player_level(zappy->server->gui, (response_payload_player_level_t){
        .player_id = zappy->client[player_index].id,
        .level = zappy->client[player_index].player.level,
    });
}
