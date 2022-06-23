/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** gui
*/

#include "protocol/greeting.h"
#include "protocol/map.h"
#include "protocol/player.h"

#include "server.h"
#include "gui_update.h"

static const gui_update_t gui_request_to_handle[] = {
    {
        .type = MAP_SIZE,
        .handler = &update_map_size
    },
    {
        .type = CONTENT_TILE,
        .handler = &update_tile_content
    },
    {
        .type = NAME_OF_TEAMS,
        .handler = &update_team_names
    },
    {
        .type = PLAYER_CONNECTED,
        .handler = &update_player_connected
    },
    {
        .type = PLAYER_POSITION,
        .handler = &update_player_position
    },
    {
        .type = PLAYER_LEVEL,
        .handler = &update_player_level
    },
    {
        .type = PLAYER_INVENTORY,
        .handler = &update_player_inventory
    },
};

void update_map_size(zappy_t *zappy)
{
    post_header(zappy->server->gui, (payload_header_t){
        .id = SERVER,
        .size = sizeof(response_payload_map_t),
        .type = MAP_SIZE
    });

    post_response_map(zappy->server->gui, (response_payload_map_t) {
        .status = true,
        .width = zappy->map->width,
        .height = zappy->map->height,
    });
}

void update_map_content(zappy_t *zappy)
{
    return;
}

void update_tile_content(zappy_t *zappy, position_t tile)
{
    int x = tile.x;
    int y = tile.y;

    post_header(zappy->server->gui, (payload_header_t){
        .id = SERVER,
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

void update_team_names(zappy_t *zappy)
{
    return;
}

void update_player_connected(zappy_t *zappy, int updated_data)
{
    post_header(zappy->server->gui, (payload_header_t){
        .id = SERVER,
        .size = sizeof(response_payload_player_connected_t),
        .type = PLAYER_CONNECTED
    });

    post_response_player_connected(zappy->server->gui, (response_payload_player_connected_t){
        .status = true,
        .id = updated_data,
        .level = zappy->client[updated_data].player.level,
        .orientation = zappy->client[updated_data].player.orientation,
        .position = zappy->client[updated_data].player.position,
        .team_name = "not implemented",
    });
}

void update_player_position(zappy_t *zappy, int player_index)
{
    post_header(zappy->server->gui, (payload_header_t){
        .id = SERVER,
        .size = sizeof(response_payload_player_position_t),
        .type = PLAYER_CONNECTED
    });

    post_response_player_position(zappy->server->gui, (response_payload_player_position_t){
        .status = true,
        .player_id = player_index,
        .position = zappy->client[player_index].player.position,
    });
}

void update_player_inventory(zappy_t *zappy, int player_index)
{
    post_header(zappy->server->gui, (payload_header_t){
        .id = SERVER,
        .size = sizeof(response_payload_player_inventory_t),
        .type = PLAYER_INVENTORY
    });

    post_response_player_inventory(zappy->server->gui, (response_payload_player_inventory_t){
        .status = true,
        .player_id = zappy->client[player_index].client_nb,
        .food = zappy->client[player_index].player.resource_inventory[FOOD].quantity,
        .linemate = zappy->client[player_index].player.resource_inventory[LINEMATE].quantity,
        .deraumere = zappy->client[player_index].player.resource_inventory[DERAUMERE].quantity,
        .sibur = zappy->client[player_index].player.resource_inventory[SIBUR].quantity,
        .mendiane = zappy->client[player_index].player.resource_inventory[MENDIANE].quantity,
        .phiras = zappy->client[player_index].player.resource_inventory[PHIRAS].quantity,
        .thystame = zappy->client[player_index].player.resource_inventory[THYSTAME].quantity,
    });
}

void update_player_level(zappy_t *zappy, int player_index)
{
    post_header(zappy->server->gui, (payload_header_t){
        .id = SERVER,
        .size = sizeof(response_payload_player_level_t),
        .type = PLAYER_CONNECTED
    });

    post_response_player_level(zappy->server->gui, (response_payload_player_level_t){
        .status = true,
        .player_id = player_index,
        .level = zappy->client[player_index].player.level,
    });
}
