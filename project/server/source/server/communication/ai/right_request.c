/*
** EPITECH PROJECT, 2022
** project
** File description:
** right_request
*/

#include "ai_request.h"
#include "gui_update.h"

void ai_right_request(zappy_t *zappy, __attribute((unused)) void *data, int player_index)
{
    int socket = zappy->client[player_index].socket;

    if (zappy->client[player_index].player.orientation >= WEST)
        zappy->client[player_index].player.orientation = NORTH;
    else
        zappy->client[player_index].player.orientation += 1;

    if (zappy->server->is_gui_connected)
        gui_update_player_orientation(zappy, player_index);

    ai_response_ok_ko(socket, true);
}
