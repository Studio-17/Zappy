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

#include "server/server.h"

#include "zappy/map/map.h"

#include "options/options.h"

void sigint_handler(__attribute__((unused)) int sig)
{
    printf("Server is shutting down...\n");
    exit(0);
}

int main(int ac, char **av)
{
    srand(time(NULL));
    signal(SIGINT, sigint_handler);

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

    create_server(zappy);

    free_options(zappy->options);
    free_map(zappy->map);
    free_resources(zappy->resources);

    free_server(zappy);

    return (EXIT_SUCCESS);
}
