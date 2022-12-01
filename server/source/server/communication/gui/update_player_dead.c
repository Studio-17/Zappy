/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** update_player_dead
*/

#include "protocol/player.h"

#include "ai_request.h"
#include "gui_update.h"

void gui_update_player_dead(zappy_t *zappy, int player_index)
{
    post_header(zappy->server->gui, (payload_header_t){
        .size = sizeof(response_payload_player_dead_t),
        .type = PLAYER_DEAD
    });

    post_response_player_dead(zappy->server->gui, (response_payload_player_dead_t){
        .player_id = zappy->client[player_index].id,
    });
}
