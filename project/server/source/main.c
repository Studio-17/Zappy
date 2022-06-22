/*
** EPITECH PROJECT, 2022
** B-EPI-000-PAR-0-0-projectname-user.email
** File description:
** main
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>

#include "server.h"
// #include "map.h"
#include "options.h"

void sigint_handler(__attribute__((unused)) int sig)
{
    printf("Server is shutting down...\n");
    exit(0);
}

static void initialize_elevation_processus(zappy_t *zappy)
{
    elevations_t *elevation_processus = malloc(sizeof(elevation_step_t) * LEVEL_MAX);

    for (int index = 0; index < LEVEL_MAX; index += 1) {
        elevation_processus[index].elevation_step = malloc(sizeof(elevation_step_t));
        elevation_processus[index].elevation_step->resource = malloc(sizeof(elevation_resources_t) * NB_ITEMS);

        // elevation_processus[index].elevation_step->from_level = 1;
        // elevation_processus[index].elevation_step->to_level = 2;
        // elevation_processus[index].elevation_step->player_needed = 1;

        // for (int resource = 0; resource < NB_ITEMS; resource += 1) {
        //     elevation_processus[index].elevation_step->resource[index].type = (enum ITEM)index;
        //     elevation_processus[index].elevation_step->resource[index].quantity_needed = -1;
        // }
    }

    elevation_processus[0].elevation_step->from_level = 1;
    elevation_processus[0].elevation_step->to_level = 2;
    elevation_processus[0].elevation_step->player_needed = 1;
    elevation_processus[0].elevation_step->resource[LINEMATE].quantity_needed = 1;
    elevation_processus[0].elevation_step->resource[DERAUMERE].quantity_needed = 0;
    elevation_processus[0].elevation_step->resource[SIBUR].quantity_needed = 0;
    elevation_processus[0].elevation_step->resource[MENDIANE].quantity_needed = 0;
    elevation_processus[0].elevation_step->resource[PHIRAS].quantity_needed = 0;
    elevation_processus[0].elevation_step->resource[THYSTAME].quantity_needed = 0;

    elevation_processus[1].elevation_step->from_level = 2;
    elevation_processus[1].elevation_step->to_level = 3;
    elevation_processus[1].elevation_step->player_needed = 2;
    elevation_processus[1].elevation_step->resource[LINEMATE].quantity_needed = 1;
    elevation_processus[1].elevation_step->resource[DERAUMERE].quantity_needed = 1;
    elevation_processus[1].elevation_step->resource[SIBUR].quantity_needed = 1;
    elevation_processus[1].elevation_step->resource[MENDIANE].quantity_needed = 0;
    elevation_processus[1].elevation_step->resource[PHIRAS].quantity_needed = 0;
    elevation_processus[1].elevation_step->resource[THYSTAME].quantity_needed = 0;

    elevation_processus[2].elevation_step->from_level = 3;
    elevation_processus[2].elevation_step->to_level = 4;
    elevation_processus[2].elevation_step->player_needed = 2;
    elevation_processus[2].elevation_step->resource[LINEMATE].quantity_needed = 2;
    elevation_processus[2].elevation_step->resource[DERAUMERE].quantity_needed = 0;
    elevation_processus[2].elevation_step->resource[SIBUR].quantity_needed = 1;
    elevation_processus[2].elevation_step->resource[MENDIANE].quantity_needed = 0;
    elevation_processus[2].elevation_step->resource[PHIRAS].quantity_needed = 2;
    elevation_processus[2].elevation_step->resource[THYSTAME].quantity_needed = 0;

    zappy->elevation = elevation_processus;
}

int main(int ac, char * const *av)
{
    zappy_t *zappy = init_zappy();

    srand(time(NULL));
    signal(SIGINT, sigint_handler);
    if (!zappy)
        return 84;
    if (!get_options(ac, av, zappy->options))
        return 84;
    if (!handle_options(zappy->options))
        return 84;

    zappy->options->team_names = my_strtok(zappy->options->names, ' ');

    zappy->client = malloc(sizeof(ai_client_t) * zappy->options->clients_nb);
    zappy->server = malloc(sizeof(server_t));
    zappy->map = create_map(10, 10);
    zappy->resources = setup_resources(10, 10);

    float number_of_resources = 0.0;
    for (int index = 0; index < NB_ITEMS ; index += 1)
        number_of_resources += zappy->resources[index].quantity;
    zappy->map->ratio = number_of_resources / zappy->map->size;
    fill_map(zappy->map, zappy->resources);

    zappy->elevation = malloc(sizeof(elevations_t));
    initialize_elevation_processus(zappy);

    create_server(zappy);
    server_loop(zappy);

    free_options(zappy->options);
    free_map(zappy->map);
    free_resources(zappy->resources);

    free_server(zappy);

    return (EXIT_SUCCESS);
}
