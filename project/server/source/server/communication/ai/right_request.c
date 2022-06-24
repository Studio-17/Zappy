/*
** EPITECH PROJECT, 2022
** project
** File description:
** right_request
*/

#include "ai_request.h"
#include "gui_update.h"

void ai_right_request(zappy_t *zappy, void *data, int player_index)
{
    int socket = zappy->client[player_index].socket;

    if (zappy->client[player_index].player.orientation >= WEST)
        zappy->client[player_index].player.orientation = NORTH;
    else
        zappy->client[player_index].player.orientation += 1;

    // gui_update_player_position(zappy, player_index);
    gui_update_player_orientation(zappy, player_index);


    ai_response_ok_ko(socket, true);
}
