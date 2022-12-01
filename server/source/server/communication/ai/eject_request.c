/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** eject_request
*/

#include "ai_request.h"
#include "gui_update.h"

void ai_eject_request(zappy_t *zappy, __attribute((unused)) void *data, int player_index)
{
    position_t player_position = zappy->client[player_index].player.position;

    const position_t direction[] = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
    position_t player_movement = direction[zappy->client[player_index].player.orientation];

    int player_on_tile = 0;

    for (int index = 0; index < zappy->server->clients; index += 1) {
        if (zappy->client[index].player.position.x == player_position.x
        && zappy->client[index].player.position.y == player_position.y) {

            move(zappy, player_movement, index);

            if (zappy->server->is_gui_connected)
                gui_update_player_position(zappy, index);

            player_on_tile += 1;

            dprintf(zappy->client[index].socket, "eject: %d\n", 1);

        }
    }

    if (player_on_tile == 0)
        ai_response_ok_ko(zappy->client[player_index].socket, false);
    else
        ai_response_ok_ko(zappy->client[player_index].socket, true);
}
