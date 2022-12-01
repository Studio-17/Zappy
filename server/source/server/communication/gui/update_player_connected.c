
/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** update_player_connected
*/

#include "protocol/player.h"

#include "ai_request.h"
#include "gui_update.h"

void gui_update_player_connected(zappy_t *zappy, int updated_data)
{
    post_header(zappy->server->gui, (payload_header_t){
        .size = sizeof(response_payload_player_connected_t),
        .type = PLAYER_CONNECTED
    });
    // char *team_name = "not implemented";

    post_response_player_connected(zappy->server->gui, (response_payload_player_connected_t){
        .id = zappy->client[updated_data].id,
        .level = zappy->client[updated_data].player.level,
        .orientation = zappy->client[updated_data].player.orientation,
        .position = zappy->client[updated_data].player.position,
        .team_name = "not implemented",
    });
}
