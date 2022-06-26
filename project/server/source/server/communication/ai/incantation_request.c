/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** incantation_request
*/

#include "server.h"
#include "ai_request.h"
#include "gui_update.h"

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

static void remove_elevation_stones(zappy_t *zappy, int player_index)
{
    for (int index = 0; index < NB_ITEMS; index += 1)
        zappy->map->tiles[zappy->client[player_index].player.position.y][zappy->client[player_index].player.position.x].resources[index].quantity = 0;
}

static bool check_elevation(zappy_t *zappy, int elevation_index, int player_index)
{
    // PRELIMINARIES
    position_t player_position = zappy->client[player_index].player.position;


    // PRE FOR TILE CHECKS
    // int player_needed = zappy->elevation[elevation_index].elevation_step->player_needed;
    int player_needed = (zappy->client[player_index].player.level == 1) ? 1 : 2;
    // CHECK PLAYERS ON TILE
    int players_on_tile = 0;
    for (int index = 0; index != zappy->server->clients; index += 1) {
        if (zappy->client[index].player.position.x == player_position.x
        && zappy->client[index].player.position.y == player_position.y) {
            players_on_tile += 1;
        }
    }
    if (players_on_tile != player_needed)
        return (false);

    // PRE FOR RESOURCE CHECKS
    elevation_resources_t *resources_need = zappy->elevation[elevation_index].elevation_step->resource;
    resources_t *tile_resources = zappy->map->tiles[player_position.y][player_position.x].resources;

    // CHECK RESOURCES ON TILE
    for (int index = 0; index != NB_ITEMS; index += 1) {
        if (resources_need[index].quantity_needed != tile_resources[index].quantity) { // Conditional jump or move depends on uninitialised value(s)
            return (false);
        }
    }

    return (true);
}

bool start_incantation(zappy_t *zappy, int player_index)
{
    int elevation_processus_index = zappy->client[player_index].player.level - 1;

    if (check_elevation(zappy, elevation_processus_index, player_index)) {

        zappy->client[player_index].player.elevation_status = BEGIN;

        if (zappy->server->is_gui_connected)
            gui_update_player_started_incantation(zappy, player_index);

        dprintf(zappy->client[player_index].socket, "Elevation underway\n");

        return (true);
    } else {
        zappy->client[player_index].player.elevation_status = FAILED;

        ai_response_ok_ko(zappy->client[player_index].socket, false);

        return (false);
    }

    return (true);
}

void ai_incantation_request(zappy_t *zappy, __attribute((unused)) void *data, int player_index)
{
    int elevation_processus_index = zappy->client[player_index].player.level - 1;

    if (check_elevation(zappy, elevation_processus_index, player_index)) {

        zappy->client[player_index].player.elevation_status = END;
        zappy->client[player_index].player.level += 1;

        remove_elevation_stones(zappy, player_index);

        if (zappy->server->is_gui_connected) {
            gui_update_tile_content(zappy, (position_t){zappy->client[player_index].player.position.x, zappy->client[player_index].player.position.y});
            // gui_update_player_level(zappy, player_index);
            gui_update_player_ended_incantation(zappy, player_index, true); // add player.level to gui
        }

        dprintf(zappy->client[player_index].socket, "Current level: %d\n", zappy->client[player_index].player.level);

    } else {

        zappy->client[player_index].player.elevation_status = FAILED;

        if (zappy->server->is_gui_connected)
            gui_update_player_ended_incantation(zappy, player_index, false);

        ai_response_ok_ko(zappy->client[player_index].socket, false);

    }
}
