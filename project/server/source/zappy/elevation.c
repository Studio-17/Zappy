/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** elevation
*/

#include "server.h"

bool setup_elevation_processus(zappy_t *zappy)
{
    int needed_resources[LEVEL_MAX - 1][NB_ITEMS] = {{0, 1, 0, 0, 0, 0, 0}, {0, 1, 1, 1, 0, 0, 0}, {0, 2, 0, 1, 0, 2, 0}};
    int nb_player_needed[LEVEL_MAX - 1] = {1, 2, 2};

    zappy->elevation = malloc(sizeof(elevations_t));
    if (!zappy->elevation)
        return false;
    zappy->elevation->elevation_step = malloc(sizeof(elevation_step_t) * LEVEL_MAX);
    if (!zappy->elevation->elevation_step)
        return false;
    for (int index = 0; index < LEVEL_MAX - 1; index += 1) {
        zappy->elevation->elevation_step[index].resource = malloc(sizeof(elevation_resources_t) * NB_ITEMS);
        if (!zappy->elevation->elevation_step[index].resource)
            return false;
        zappy->elevation->elevation_step[index].from_level = index + 1;
        zappy->elevation->elevation_step[index].to_level = index + 2;
        zappy->elevation->elevation_step[index].player_needed = nb_player_needed[index];
        for (int food_index = 0; food_index != NB_ITEMS - 1; food_index++) {
            zappy->elevation->elevation_step[index].resource[food_index].quantity_needed = needed_resources[index][food_index];
            zappy->elevation->elevation_step[index].resource[food_index].type = (enum ITEM)(food_index + 1);
        }
    }
    return true;
}

void free_elevation(elevations_t *elevation)
{
    for (int index = 0; index < LEVEL_MAX - 1; index += 1)
        free(elevation->elevation_step[index].resource);
    free(elevation->elevation_step);
    free(elevation);
}

void debug_elevation(elevations_t *elevation)
{
    for (int index = 0; index != LEVEL_MAX - 1; index++) {
        printf("[DEBUG] elevation from lever %d\n", elevation->elevation_step[index].from_level);
        printf("[DEBUG] need %d players to reach level %d\n", elevation->elevation_step[index].player_needed, elevation->elevation_step[index].player_needed);
        printf("[DEBUG] and need some resources:\n");
        for (int resource_index = 0; resource_index != NB_ITEMS - 1; resource_index++)
            printf("            -%d needed of %d\n", elevation->elevation_step[index].resource[resource_index].quantity_needed, elevation->elevation_step[index].resource[resource_index].type);
    }
}