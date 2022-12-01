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

bool setup_zappy_content(zappy_t *zappy)
{
    zappy->options->team_names = my_strtok(zappy->options->names, ' ');
    if (!zappy->options->team_names)
        return false;
    zappy->options->max_teams = my_arrlen(zappy->options->team_names);
    zappy->options->max_clients = zappy->options->max_teams * zappy->options->clients_nb;
    if (!setup_client(zappy, zappy->options->max_clients))
        return false;
    zappy->server = malloc(sizeof(server_t));
    if (!zappy->server)
        return false;
    if (!setup_elevation_processus(zappy))
        return false;
    zappy->map = create_map(zappy->options->width, zappy->options->height);
    zappy->resources = setup_resources(zappy->options->width, zappy->options->height);
    if (!zappy->map || !zappy->resources)
        return false;
    if (!setup_server(zappy->server, zappy->options))
        return false;
    return true;
}

void free_zappy(zappy_t *zappy)
{
    if (zappy->client)
        free_clients(zappy->client, zappy->options->max_clients);
    free_options(zappy->options);
    free_map(zappy->map);
    free_resources(zappy->resources);
    free_elevation(zappy->elevation);
    free_server(zappy->server);
    free(zappy);
}