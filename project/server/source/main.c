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

#include "server/server.h"

#include "zappy/zappy.h"
#include "zappy/map/map.h"

#include "options/options.h"

int main(int ac, char **av)
{
    srand(time(NULL));

    zappy_t *zappy = malloc(sizeof(zappy_t));

    int options_status = 1;
    zappy->options = malloc(sizeof(options_t));

    setup_options(zappy->options);

    options_status = get_options(ac, av, zappy->options);
    if (options_status == EXIT_FAILURE)
        return (EXIT_FAILURE);

    options_status = handle_options(zappy->options);
    if (options_status == EXIT_FAILURE)
        return (EXIT_FAILURE);

    zappy->map = malloc(sizeof(map_t));

    create_map(zappy->map, zappy->options->width, zappy->options->height);

    resources_t resource[] = {
        {
            .name = "food",
            .resources = FOOD,
            .density = 0.5,
            .quantity = 0,
        },
        {
            .name = "linemate",
            .resources = LINEMATE,
            .density = 0.3,
            .quantity = 0,
        },
        {
            .name = "deraumere",
            .resources = DERAUMERE,
            .density = 0.15,
            .quantity = 0,
        },
        {
            .name = "sibur",
            .resources = SIBUR,
            .density = 0.1,
            .quantity = 0,
        },
        {
            .name = "mendiane",
            .resources = MENDIANE,
            .density = 0.1,
            .quantity = 0,
        },
        {
            .name = "phiras",
            .resources = PHIRAS,
            .density = 0.08,
            .quantity = 0,
        },
        {
            .name = "thystame",
            .resources = THYSTAME,
            .density = 0.05,
            .quantity = 0,
        },
    };

    setup_resources(resource, zappy->map->width, zappy->map->height);

    float number_of_resources = 0.0f;
    for (int index = 0; index < NB_ITEMS ; index += 1)
        number_of_resources += resource[index].quantity;

    zappy->map->ratio = number_of_resources / zappy->map->size;

    fill_map(zappy->map, resource);

    zappy->server = malloc(sizeof(server_t));

    create_server(zappy->server, zappy->options);

    free_options(zappy->options);

    free_map(zappy->map);

    free_server(zappy->server);

    return (EXIT_SUCCESS);
}
