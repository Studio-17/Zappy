/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** update_tile
*/

#include "protocol/map.h"

#include "ai_request.h"
#include "gui_update.h"

void gui_update_tile_content(zappy_t *zappy, position_t tile)
{
    int x = tile.x;
    int y = tile.y;

    printf("modified tile: y:%d x:%d\n", y, x);

    post_header(zappy->server->gui, (payload_header_t){
        .size = sizeof(response_payload_content_tile_t),
        .type = CONTENT_TILE,
    });

    post_response_content_tile(zappy->server->gui, (response_payload_content_tile_t){
        .position.x = x,
        .position.y = y,
        .food = zappy->map->tiles[y][x].resources[FOOD].quantity,
        .linemate = zappy->map->tiles[y][x].resources[LINEMATE].quantity,
        .deraumere = zappy->map->tiles[y][x].resources[DERAUMERE].quantity,
        .sibur = zappy->map->tiles[y][x].resources[SIBUR].quantity,
        .mendiane = zappy->map->tiles[y][x].resources[MENDIANE].quantity,
        .phiras = zappy->map->tiles[y][x].resources[PHIRAS].quantity,
        .thystame = zappy->map->tiles[y][x].resources[THYSTAME].quantity,
    });
}
