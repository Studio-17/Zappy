/*
** EPITECH PROJECT, 2022
** project
** File description:
** forward_request
*/

#include "player.h"
#include "request.h"
#include "ai_request.h"
#include "gui_update.h"

void ai_forward_request(zappy_t *zappy, __attribute((unused)) void *data, int player_index)
{
    const position_t direction[] = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
    position_t movement = direction[zappy->client[player_index].player.orientation];

    move(zappy, movement, player_index);

    if (zappy->server->is_gui_connected)
        gui_update_player_position(zappy, player_index);

    ai_response_ok_ko(zappy->client[player_index].socket, true);
}