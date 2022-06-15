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

#include "zappy/zappy.h"
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

    zappy->server = malloc(sizeof(server_t));

    create_server(zappy->server, zappy->options);

    free_options(zappy->options);

    free_server(zappy->server);

    return (EXIT_SUCCESS);
}
