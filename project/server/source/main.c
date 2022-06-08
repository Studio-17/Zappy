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

#include "zappy/map/map.h"

#include "options/options.h"

int main(int ac, char **av)
{
    srand(time(NULL));

    int options_status = 1;
    options_t *options = malloc(sizeof(options_t));

    setup_options(options);

    options_status = get_options(ac, av, options);
    if (options_status == EXIT_FAILURE)
        return (EXIT_FAILURE);

    options_status = handle_options(options);
    if (options_status == EXIT_FAILURE)
        return (EXIT_FAILURE);

    map_t *map = malloc(sizeof(map_t));

    create_map(map, options->width, options->height);

    resources_t resource[] = {
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

    setup_resources(resource, options->width, options->height);

    fill_map(map, resource);

    debug_map(map);

    debug_resources(resource);

    free_options(options);

    free_map(map);

    return (EXIT_SUCCESS);
}
