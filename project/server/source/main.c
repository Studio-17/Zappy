/*
** EPITECH PROJECT, 2022
** B-EPI-000-PAR-0-0-projectname-user.email
** File description:
** main
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>

#include "server.h"
#include "options.h"

#include "gui_update.h"

zappy_t *store_zappy(zappy_t *zappy)
{
    static zappy_t *stored_zappy = NULL;

    if (!zappy)
        return stored_zappy;
    stored_zappy = zappy;
    return stored_zappy;
}

void sigint_handler(__attribute__((unused)) int sig)
{
    zappy_t *zappy = store_zappy(NULL);

    if (zappy->server->is_gui_connected)
        gui_update_server_offline(zappy);

    free_zappy(zappy);
    printf("Server is shutting down...\n");
    exit(EXIT_SUCCESS);
}

int main(int ac, char * const *av)
{
    zappy_t *zappy = init_zappy();
    float number_of_resources = 0.0;

    srand(time(NULL));
    signal(SIGINT, sigint_handler);
    if (!zappy)
        return 84;
    if (!get_options(ac, av, zappy->options))
        return 84;
    if (!handle_options(zappy->options))
        return 84;
    if (!setup_zappy_content(zappy))
        return 84;
    for (int index = 0; index < NB_ITEMS ; index += 1)
        number_of_resources += zappy->resources[index].quantity;
    zappy->map->ratio = number_of_resources / zappy->map->size;
    fill_map(zappy->map, zappy->resources);
    create_server(zappy);
    store_zappy(zappy);
    if (!server_loop(zappy))
        return 84;
    return (EXIT_SUCCESS);
}
