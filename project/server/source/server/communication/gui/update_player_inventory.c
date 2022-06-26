/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** update_player_inventory
*/

#include "protocol/player.h"

#include "ai_request.h"
#include "gui_update.h"

void gui_update_player_inventory(zappy_t *zappy, int player_index)
{
    post_header(zappy->server->gui, (payload_header_t){
        .size = sizeof(response_payload_player_inventory_t),
        .type = PLAYER_INVENTORY
    });

    post_response_player_inventory(zappy->server->gui, (response_payload_player_inventory_t){
        .player_id = zappy->client[player_index].id,
        .linemate = zappy->client[player_index].player.resource_inventory[LINEMATE].quantity,
        .deraumere = zappy->client[player_index].player.resource_inventory[DERAUMERE].quantity,
        .sibur = zappy->client[player_index].player.resource_inventory[SIBUR].quantity,
        .mendiane = zappy->client[player_index].player.resource_inventory[MENDIANE].quantity,
        .phiras = zappy->client[player_index].player.resource_inventory[PHIRAS].quantity,
        .thystame = zappy->client[player_index].player.resource_inventory[THYSTAME].quantity,
        .food = zappy->client[player_index].player.resource_inventory[FOOD].quantity,
    });
}
