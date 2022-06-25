/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** update_incantation
*/

#include "protocol/player.h"

#include "ai_request.h"
#include "gui_update.h"

void gui_update_player_started_incantation(zappy_t *zappy, int player_index)
{
    post_header(zappy->server->gui, (payload_header_t){
        .size = sizeof(response_payload_player_start_incantation_t),
        .type = PLAYER_STARTED_INCANTATION
    });

    post_response_player_start_incantation(zappy->server->gui, (response_payload_player_start_incantation_t){
        .player_id = zappy->client[player_index].id,
    });
}

void gui_update_player_ended_incantation(zappy_t *zappy, int player_index, bool incantation_status)
{
    post_header(zappy->server->gui, (payload_header_t){
        .size = sizeof(response_payload_player_end_incantation_t),
        .type = PLAYER_ENDED_INCANTATION
    });

    post_response_player_end_incantation(zappy->server->gui, (response_payload_player_end_incantation_t){
        .player_id = zappy->client[player_index].id,
        .success = incantation_status,
    });
}
