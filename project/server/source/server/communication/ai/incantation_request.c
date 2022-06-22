/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** incantation_request
*/

#include "server.h"

/*
 *  elevation   nb of players   linemate    deraumere   sibur   mendiane    phiras  thystame
 *  1->2        1               1           0           0       0           0       0
 *  2->3        2               1           1           1       0           0       0
 *  3->4        2               2           0           1       0           2       0
 *  4->5        4               1           1           2       0           1       0
 *  5->6        4               1           2           1       3           0       0
 *  6->7        6               1           2           3       0           1       0
 *  7->8        6               2           2           2       2           2       1
 */

static bool check_elevation(zappy_t *zappy, int elevation_index, int player_level, int player_index)
{
    // PRELIMINARIES
    position_t player_position = zappy->client[player_index].player.position;

    // PRE FOR TILE CHECKS
    int player_needed = zappy->elevation[elevation_index].elevation_step->player_needed;
    // CHECK PLAYERS ON TILE
    int players_on_tile = 0;
    for (int index = 0; index != zappy->server->clients; index += 1) {
        if (zappy->client[index].player.position.x == player_position.x
        && zappy->client[index].player.position.y == player_position.y) {
            players_on_tile += 1;
        }
    }
    if (players_on_tile != zappy->elevation[elevation_index].elevation_step->player_needed)
        return (false);

    // PRE FOR RESOURCE CHECKS
    elevation_resources_t *resources_need = zappy->elevation[elevation_index].elevation_step->resource;
    resources_t *tile_resources = zappy->map->tiles[player_position.x][player_position.y].resources;

    // CHECK RESOURCES ON TILE
    for (int index = 1; index != NB_ITEMS; index += 1) {
        if (resources_need[index].quantity_needed != tile_resources[index].quantity) {

            return (false);
        }
    }

    zappy->client[player_index].player.level += 1;
    return (true);
}

void ai_incantation_request(zappy_t *zappy, void *data, int player_index)
{
    int elevation_processus_index = zappy->client[player_index].player.level - 1;

    printf("current player level: %d\n", zappy->client[player_index].player.level);
    printf("elevation processus index: %d\n", elevation_processus_index);


    if (check_elevation(zappy, elevation_processus_index, zappy->client[player_index].player.level, player_index)) {
        dprintf(zappy->server->socket_descriptor->socket_descriptor, "Elevation underway\nCurrent level: %d\n", zappy->client[player_index].player.level);
    } else {
        ai_response_ok_ko(zappy->server->socket_descriptor->socket_descriptor, false);
    }
}