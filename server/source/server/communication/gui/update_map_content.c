/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** update_map_content
*/

#include "protocol/map.h"

#include "ai_request.h"
#include "gui_update.h"

void gui_update_map_content(zappy_t *zappy)
{
    int cpt = 0;
    response_payload_content_tile_t *map_tiles = malloc(sizeof(response_payload_content_tile_t) * zappy->options->height * zappy->options->width);

    for (int map_height = 0; map_height < zappy->options->height; map_height += 1) {
        for (int map_width = 0; map_width < zappy->options->width; cpt += 1, map_width += 1) {
            map_tiles[cpt].position.x = map_width;
            map_tiles[cpt].position.y = map_height;
            map_tiles[cpt].food = zappy->map->tiles[map_height][map_width].resources[FOOD].quantity;
            map_tiles[cpt].linemate = zappy->map->tiles[map_height][map_width].resources[LINEMATE].quantity;
            map_tiles[cpt].deraumere = zappy->map->tiles[map_height][map_width].resources[DERAUMERE].quantity;
            map_tiles[cpt].sibur = zappy->map->tiles[map_height][map_width].resources[SIBUR].quantity;
            map_tiles[cpt].mendiane = zappy->map->tiles[map_height][map_width].resources[MENDIANE].quantity;
            map_tiles[cpt].phiras = zappy->map->tiles[map_height][map_width].resources[PHIRAS].quantity;
            map_tiles[cpt].thystame = zappy->map->tiles[map_height][map_width].resources[THYSTAME].quantity;
        }
    }

    usleep(3000);

    post_header(zappy->server->gui, (payload_header_t){
        .size = sizeof(response_payload_content_tile_t) * zappy->options->height * zappy->options->width,
        .type = CONTENT_MAP
    });

    post_response_content_map(zappy->server->gui, map_tiles, sizeof(response_payload_content_tile_t) * zappy->options->height * zappy->options->width);
}
