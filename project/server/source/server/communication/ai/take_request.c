/*
** EPITECH PROJECT, 2022
** project
** File description:
** take_request
*/

#include "ai_request.h"
#include "gui_update.h"

void ai_take_request(zappy_t *zappy, void *data, int player_index)
{
    char *request = (char *)data;
    enum ITEM resource = (enum ITEM)get_resource_from_request(request);
    int x, y = 0;

    if ((int)resource == -1)
        ai_response_ok_ko(zappy->client[player_index].socket, false);
    else {
        x = zappy->client[player_index].player.position.x;
        y = zappy->client[player_index].player.position.y;
        if (zappy->map->tiles[y][x].resources[resource].quantity > 0) {
            zappy->client[player_index].player.resource_inventory[resource].quantity += 1;
            zappy->map->tiles[y][x].resources[resource].quantity -= 1;
            if (zappy->server->is_gui_connected) {
                gui_update_player_inventory(zappy, player_index);
                gui_update_tile_content(zappy, (position_t){x, y});
            }
            ai_response_ok_ko(zappy->client[player_index].socket, true);
        } else
            ai_response_ok_ko(zappy->client[player_index].socket, false);
    }
}
