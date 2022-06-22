/*
** EPITECH PROJECT, 2022
** project
** File description:
** zappy
*/

#include <stdlib.h>

#include "minilib.h"
#include "server.h"

zappy_t *init_zappy(void)
{
    zappy_t *zappy = malloc(sizeof(zappy_t));

    if (!zappy)
        return NULL;
    zappy->options = malloc(sizeof(options_t));
    if (!zappy->options) {
        free(zappy);
        return NULL;
    }
    setup_options(zappy->options);
    return zappy;
}

static bool initialize_elevation_processus(zappy_t *zappy)
{
    zappy->elevation = malloc(sizeof(elevations_t));
    if (!zappy->elevation)
        return false;
    zappy->elevation->elevation_step = malloc(sizeof(elevation_step_t) * LEVEL_MAX);
    if (!zappy->elevation->elevation_step)
        return false;
    for (int index = 0; index < LEVEL_MAX; index += 1) {
        zappy->elevation->elevation_step[index].resource = malloc(sizeof(elevation_resources_t) * NB_ITEMS);
        if (!zappy->elevation->elevation_step[index].resource)
            return false;

        // zappy->elevation->elevation_step[index].from_level = 1;
        // zappy->elevation->elevation_step[index].to_level = 2;
        // zappy->elevation->elevation_step[index].player_needed = 1;

        // for (int resource = 0; resource < NB_ITEMS; resource += 1) {
        //     zappy->elevation->elevation_step[index].resource[index].type = (enum ITEM)index;
        //     zappy->elevation->elevation_step[index].resource[index].quantity_needed = -1;
        // }
    }

    zappy->elevation->elevation_step[0].from_level = 1;
    zappy->elevation->elevation_step[0].to_level = 2;
    zappy->elevation->elevation_step[0].player_needed = 1;
    zappy->elevation->elevation_step[0].resource[LINEMATE].quantity_needed = 1;
    zappy->elevation->elevation_step[0].resource[DERAUMERE].quantity_needed = 0;
    zappy->elevation->elevation_step[0].resource[SIBUR].quantity_needed = 0;
    zappy->elevation->elevation_step[0].resource[MENDIANE].quantity_needed = 0;
    zappy->elevation->elevation_step[0].resource[PHIRAS].quantity_needed = 0;
    zappy->elevation->elevation_step[0].resource[THYSTAME].quantity_needed = 0;

    zappy->elevation->elevation_step[1].from_level = 2;
    zappy->elevation->elevation_step[1].to_level = 3;
    zappy->elevation->elevation_step[1].player_needed = 2;
    zappy->elevation->elevation_step[1].resource[LINEMATE].quantity_needed = 1;
    zappy->elevation->elevation_step[1].resource[DERAUMERE].quantity_needed = 1;
    zappy->elevation->elevation_step[1].resource[SIBUR].quantity_needed = 1;
    zappy->elevation->elevation_step[1].resource[MENDIANE].quantity_needed = 0;
    zappy->elevation->elevation_step[1].resource[PHIRAS].quantity_needed = 0;
    zappy->elevation->elevation_step[1].resource[THYSTAME].quantity_needed = 0;

    zappy->elevation->elevation_step[2].from_level = 3;
    zappy->elevation->elevation_step[2].to_level = 4;
    zappy->elevation->elevation_step[2].player_needed = 2;
    zappy->elevation->elevation_step[2].resource[LINEMATE].quantity_needed = 2;
    zappy->elevation->elevation_step[2].resource[DERAUMERE].quantity_needed = 0;
    zappy->elevation->elevation_step[2].resource[SIBUR].quantity_needed = 1;
    zappy->elevation->elevation_step[2].resource[MENDIANE].quantity_needed = 0;
    zappy->elevation->elevation_step[2].resource[PHIRAS].quantity_needed = 2;
    zappy->elevation->elevation_step[2].resource[THYSTAME].quantity_needed = 0;

    // zappy->elevation = elevation_processus;
    return true;
}

bool setup_zappy_content(zappy_t *zappy)
{
    zappy->options->team_names = my_strtok(zappy->options->names, ' ');
    if (!zappy->options->team_names)
        return false;
    zappy->options->max_clients = my_arrlen(zappy->options->team_names) * zappy->options->clients_nb;
    zappy->client = malloc(sizeof(ai_client_t) * zappy->options->clients_nb);
    if (!zappy->client)
        return false;
    zappy->server = malloc(sizeof(server_t));
    if (!zappy->server)
        return false;
    initialize_elevation_processus(zappy);
    zappy->map = create_map(10, 10);
    zappy->resources = setup_resources(10, 10);
    if (!setup_server(zappy->server, zappy->options))
        return false;
    return true;
}

void free_zappy(zappy_t *zappy)
{
    free_options(zappy->options);
    free(zappy->client);
    free_map(zappy->map);
    free_resources(zappy->resources);
    free_server(zappy->server);
    free(zappy);
}