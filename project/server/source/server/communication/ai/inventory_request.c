/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** inventory_request
*/

#include "ai_request.h"
#include "gui_update.h"

void ai_inventory_request(zappy_t *zappy, void *data, int player_index)
{
    inventory_resource_t *inventory = zappy->client[player_index].player.resource_inventory;

    dprintf(zappy->client[player_index].socket, "[ ");

    for (int index = 0; index < NB_ITEMS; index += 1) {

        dprintf(zappy->client[player_index].socket, (index == NB_ITEMS - 1) ? "%s %d" : "%s %d, ", zappy->resources[index].name, inventory[index].quantity);

    }

    dprintf(zappy->client[player_index].socket, " ]\n");
}
