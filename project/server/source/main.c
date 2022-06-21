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
#include "map.h"
#include "options.h"

void sigint_handler(__attribute__((unused)) int sig)
{
    printf("Server is shutting down...\n");
    exit(0);
}

int main(int ac, char const * const *av)
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

    create_server(zappy);
    server_loop(zappy);

    free_options(zappy->options);
    free_map(zappy->map);
    free_resources(zappy->resources);

    free_server(zappy);

    return (EXIT_SUCCESS);
}
