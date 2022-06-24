/*
** EPITECH PROJECT, 2022
** project
** File description:
** look_request
*/

#include "ai_request.h"

static const position_t direction[] = {
    {0, -1}, {1, 0}, {0, 1}, {-1, 0}
};

static const position_t row_direction[] = {
    {1, 0}, {0, -1}, {-1, 0}, {0, 1}
};

static void print_tile_content(int socket, tile_t const tile, bool player, bool first)
{
    bool first_resource = true;

    if (player) {
        if (!first_resource) {
            first = false;
            dprintf(socket, " ");
        }
        dprintf(socket, "player");
        first_resource = false;
    }
    for (int index = 0; index < NB_ITEMS; index++)
        if (tile.resources[index].quantity) {
            if (!first && first_resource) {
                dprintf(socket, " ");
                first_resource = false;
            } else if (!first_resource)
                dprintf(socket, " ");
            dprintf(socket, "%s", tile.resources[index].name);
        }
}

static bool is_player_at_postion(zappy_t *zappy, position_t const position)
{
    for (int player_index = 0; player_index != zappy->options->max_clients; player_index++)
        if (zappy->server->server_socket->client[player_index])
            if (zappy->client[player_index].player.position.x == position.x && zappy->client[player_index].player.position.y == position.y)
                return true;
    return false;
}

void ai_look_request(zappy_t *zappy, void *data, int player_index)
{
    int socket = zappy->client[player_index].socket;
    position_t player_orientation = direction[zappy->client[player_index].player.orientation];
    position_t row_orientation = row_direction[zappy->client[player_index].player.orientation];
    int nb_tiles = 0;

    for (int i = 0; i <= zappy->client[player_index].player.level; i++)
        nb_tiles += 1 + (i * 2);
    bool first = true;
    dprintf(socket, "[ ");
    for (int i = 0; i <= zappy->client[player_index].player.level; i++) {
        for (int index = -i; index <= i; index++) {
            if (!first)
                dprintf(socket, ",");
            position_t tmp_pos;
            tmp_pos.x = zappy->client[player_index].player.position.x;
            tmp_pos.x += player_orientation.x * i;
            tmp_pos.x += row_orientation.x * index;
            if (tmp_pos.x >= zappy->map->width)
                tmp_pos.x = 0;
            else if (tmp_pos.x < 0)
                tmp_pos.x = zappy->map->width - 1;
            tmp_pos.y = zappy->client[player_index].player.position.y;
            tmp_pos.y += player_orientation.y * i;
            tmp_pos.y += row_orientation.y * index;
            if (tmp_pos.y >= zappy->map->height)
                tmp_pos.y = 0;
            else if (tmp_pos.y < 0)
                tmp_pos.y = zappy->map->height - 1;
            print_tile_content(socket, zappy->map->tiles[tmp_pos.y][tmp_pos.x], is_player_at_postion(zappy, tmp_pos), first);
            if (first)
                first = false;
        }
    }
    dprintf(socket, " ]\n");
}